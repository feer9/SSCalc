CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
SOURCEDIR:=./src
SOURCES:=./src/string.c
HEADERS:= ./src/string.h
OBJECTSDIR:=./obj
OBJECTS:=./obj/string.o
LIBNAME:=libstring.so.1.0.0
SONAME:=libstring.so.1.0
LIB:=libstring.so


../$(LIBNAME): $(OBJECTSDIR) $(OBJECTS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME) ../$(SONAME)
	ln -sf $(SONAME) ../$(LIB)

./obj/string.o: ./src/string.c ./src/string.h
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

clean:
	rm -f ./obj/*.o *~ core $(EXECUTABLE)
	rmdir ./obj
