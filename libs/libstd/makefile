CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
SOURCEDIR:=./src
SOURCES:=./src/std.c
HEADERS:= ./src/std.h
OBJECTSDIR:=./obj
OBJECTS:=./obj/std.o
LIBNAME:=libstd.so.1.0.0
SONAME:=libstd.so.1.0
LIB:=libstd.so

all: build

build: ../$(LIBNAME)

.PHONY: all build install uninstall clean

../$(LIBNAME): $(OBJECTSDIR) $(OBJECTS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME) ../$(SONAME)
	ln -sf $(SONAME) ../$(LIB)

./obj/std.o: ./src/std.c ./src/std.h
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
