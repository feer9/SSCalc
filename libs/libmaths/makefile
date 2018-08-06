CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-fPIC -shared
LIBNAME:=libmaths.so.1.0.0
SONAME:=libmaths.so.1.0
LIB:=libmaths.so

.PHONY: all build install clean

all: build

build: ../$(LIBNAME)

../$(LIBNAME): ./obj ./obj/maths.o
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ ./obj/maths.o
#	sudo ldconfig -vn ../
	ln -sf $(LIBNAME) ../$(SONAME)
	ln -sf $(SONAME) ../$(LIB)

./obj/maths.o: ./src/maths.c ./src/maths.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir obj

debug: ./src/maths.c ./src/debug.c ./src/maths.h
	gcc -Wall ./src/maths.c ./src/debug.c -o $@

install: ../$(LIBNAME)
	install -c ../$(LIBNAME) ~/.local/lib
	ln -sf $(LIBNAME) ~/.local/lib/$(SONAME)
	ln -sf $(SONAME) ~/.local/lib/$(LIB)

clean:
	rm -rf ./obj/*.o ./obj core libmaths.so* debug
