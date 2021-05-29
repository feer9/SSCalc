cmake_minimum_required(VERSION 3.19)
project(SSCalc C)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "-Wall")

message( "src dir:        " ${CMAKE_CURRENT_SOURCE_DIR})
message( "cmake bin dir:  " ${CMAKE_BINARY_DIR})
message( "project bin dir:" ${PROJECT_BINARY_DIR} "\n")

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
)



# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_executable(sscalc-gui
        src/main.c
        sscalc.ui.c
        src/mainWindow.c src/mainWindow.h)

target_include_directories (sscalc-gui PRIVATE ${GTK3_INCLUDE_DIRS})
target_compile_options     (sscalc-gui PRIVATE ${GTK3_CFLAGS_OTHER})
target_compile_definitions (sscalc-gui PRIVATE )
target_link_directories    (sscalc-gui PRIVATE ${GTK3_LIBRARY_DIRS})
target_link_options        (sscalc-gui PRIVATE -rdynamic)
target_link_libraries      (sscalc-gui PRIVATE ${GTK3_LIBRARIES} )


#add_dependencies(SSCalc sscalc.ui.c)
