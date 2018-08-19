CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
SOURCEDIR:=./src
SOURCES:=./src/my_string.c
HEADERS:= ./src/my_string.h
OBJECTSDIR:=./obj
OBJECTS:=./obj/my_string.o
LIB:=libstring.so
LIBVER:=.0.4
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)


all: build

build: ../$(LIBNAME)
	
.PHONY: all build install clean

../$(LIBNAME): $(OBJECTSDIR) $(OBJECTS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME) ../$(SONAME)
	ln -sf $(SONAME) ../$(LIB)

./obj/my_string.o: ./src/my_string.c ./src/my_string.h
	$(CC) $(CFLAGS) -c $< -o $@

./src/%.c:
	$(error No existe el archivo $@)

$(SOURCEDIR):
	$(error Falta directorio de archivos fuente)

$(OBJECTSDIR): $(SOURCEDIR)
	mkdir -p $@

install: ../$(LIBNAME)
	install -c ../$(LIBNAME) ~/.local/lib
	ln -sf $(LIBNAME) ~/.local/lib/$(SONAME)
	ln -sf $(SONAME) ~/.local/lib/$(LIB)

uninstall:
	rm -rf ~/.local/lib/$(LIBNAME) ~/.local/lib/$(SONAME) \
	~/.local/lib/$(LIB)

clean:
	rm -f ./obj/*.o *~ core
	rmdir ./obj
