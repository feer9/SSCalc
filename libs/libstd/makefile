CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
SOURCEDIR:=./src
SOURCES:=./src/std.c
HEADERS:= ./src/std.h
OBJECTSDIR:=./obj
OBJECTS:=./obj/std.o
LIB:=libstd.so
LIBVER:=.0.1
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)
INSTALL_DIR:=~/.local/lib

all: build

build: $(LIBNAME)

.PHONY: all build install uninstall clean

$(LIBNAME): $(OBJECTSDIR) $(OBJECTS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

./obj/std.o: ./src/std.c ./src/std.h
	$(CC) $(CFLAGS) -c $< -o $@

./src/%.c:
	$(error No existe el archivo $@)

$(SOURCEDIR):
	$(error Falta directorio de archivos fuente)

$(OBJECTSDIR): $(SOURCEDIR)
	mkdir -p $@

install: $(LIBNAME)
	install -c $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

clean:
	rm -f ./obj/*.o *~ core
	rmdir ./obj

clean_build:
	rm -f $(LIB)*