CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-shared
SOURCEDIR:=src
SOURCES:=src/std.c src/strings.c src/various.c
OBJECTSDIR:=obj
OBJECTS:=obj/std.o obj/strings.o obj/various.o
LIB:=libvarious.so
LIBVER:=.0.2
LIBSUBVER:=.1
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)
INSTALL_DIR:=${HOME}/.local/lib

all: build

build: $(LIBNAME)

.PHONY: all build install uninstall clean

$(LIBNAME): $(OBJECTSDIR) $(OBJECTS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

obj/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

src/%.c:
	$(error No existe el archivo $@)

$(SOURCEDIR):
	$(error Falta directorio de archivos fuente)

$(OBJECTSDIR): $(SOURCEDIR)
	mkdir -p $@

install: $(LIBNAME)
	mkdir -p $(INSTALL_DIR)
	install -c $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)
#	sudo ldconfig

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

clean:
	rm -f ./obj/*.o *~ core
	rmdir ./obj

clean_build:
	rm -f $(LIB)*