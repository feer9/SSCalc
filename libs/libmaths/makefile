CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
LIBNAME:=libmaths.so.1.0.0
SONAME:=libmaths.so.1.0
LIB:=libmaths.so

.PHONY: all build install clean

all: build

build: ../$(LIBNAME)

../$(LIBNAME): ./obj ./obj/libmaths.o
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ ./obj/libmaths.o
#	sudo ldconfig -vn ../
	ln -sf $(LIBNAME) ../libmaths.so.1.0
	ln -sf libmaths.so.1.0 ../libmaths.so

./obj/libmaths.o: ./src/libmaths.c ./src/libmaths.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir obj

debug: ./src/libmaths.c ./src/debug.c ./src/libmaths.h
	gcc -Wall ./src/libmaths.c ./src/debug.c -o $@

install: ../$(LIBNAME)
	install -c ../$(LIBNAME) ~/.local/lib
	ln -sf $(LIBNAME) ~/.local/lib/$(SONAME)
	ln -sf $(SONAME) ~/.local/lib/$(LIB)

clean:
	rm -rf ./obj/*.o ./obj core libmaths.so* debug
