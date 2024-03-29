cmake_minimum_required(VERSION 3.19)
project(SSCalc C)

#set(CMAKE_C_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "-Wall")
# Be aware that defining DEBUG will break gdb functionality
#set(CMAKE_C_FLAGS_DEBUG "-DDEBUG")
set(CMAKE_C_FLAGS_RELEASE  "-DNDEBUG")


message( "src dir:        " ${CMAKE_CURRENT_SOURCE_DIR})
message( "cmake bin dir:  " ${CMAKE_BINARY_DIR})
message( "project bin dir:" ${PROJECT_BINARY_DIR} "\n")

add_library(maths STATIC
        lib/libmaths/src/maths.c
)

add_library(various STATIC
        lib/libvarious/src/std.c
        lib/libvarious/src/strings.c
        lib/libvarious/src/various.c
)

add_library(calc STATIC
        lib/libcalc/src/notacion.c
        lib/libcalc/src/manejo_nodos.c
        lib/libcalc/src/calc.c
        lib/libcalc/src/double_linked_lists.c lib/libcalc/src/double_linked_lists.h)

target_include_directories(calc PUBLIC lib)
target_link_libraries(calc PUBLIC maths various)

## Generate GUI source file to be compiled an linked to binary file
add_custom_command(
        OUTPUT
            ${CMAKE_BINARY_DIR}/sscalc.ui.c
        WORKING_DIRECTORY
            ..
        COMMAND
            glib-compile-resources
        ARGS
            --sourcedir=resources
            --generate-source
            --target=${CMAKE_BINARY_DIR}/sscalc.ui.c
            "resources/sscalc.gresource.xml"
        DEPENDS
            resources/sscalc.gresource.xml
            resources/sscalc.ui
            resources/sscalc.png
)



# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable( sscalc-gui
        src/main.c
        sscalc.ui.c
        src/mainWindow.c
        src/sscalc-gui.h
        src/callbacks.c
        src/statusbar.c
)

target_include_directories (sscalc-gui PRIVATE lib ${GTK3_INCLUDE_DIRS})
target_compile_options     (sscalc-gui PRIVATE ${GTK3_CFLAGS_OTHER})
target_compile_options     (sscalc-gui PUBLIC -fdata-sections -ffunction-sections -O2)
target_compile_definitions (sscalc-gui PRIVATE )
target_link_directories    (sscalc-gui PRIVATE ${GTK3_LIBRARY_DIRS})
target_link_libraries      (sscalc-gui PRIVATE calc ${GTK3_LIBRARIES})
target_link_options        (sscalc-gui PRIVATE -rdynamic -Wl,--gc-sections)


add_executable( sscalc
        lib/libcalc/src/console.c
)

target_compile_definitions (sscalc PRIVATE )
target_link_libraries      (sscalc PRIVATE calc )
target_link_options        (sscalc PRIVATE -rdynamic)

#add_dependencies(SSCalc sscalc.ui.c)

install(TARGETS sscalc-gui sscalc
        CONFIGURATIONS Release
        DESTINATION ~/.local/bin)

#PRIVATE   - use only for this specified build target
#PUBLIC    - use it for specified target and for targets which links with this project
#INTERFACE - use it only for targets which links with the current project

# static libs info
# https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index
