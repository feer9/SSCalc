# compiler
CC:=g++
# compiler flags
CFLAGS:=-Wall -ggdb -fPIC
# linker flags
LDFLAGS:=-fPIC -shared

OBJS:=./obj/infija_a_postfija.o ./obj/manejo_nodos.o ./obj/libcalc.o
HEADERS:=../libmaths/src/libmaths.h ./src/libcalc.h ./src/infija_a_postfija.h ./src/manejo_nodos.h ./src/nodo.h
LIBNAME:=libcalc.so.1.0.0
SONAME:=libcalc.so.1.0
LIB:=libcalc.so

.PHONY: all build install clean

all: build

build: ../$(LIBNAME)

../$(LIBNAME): ./obj  $(OBJS) $(HEADERS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $(OBJS)
	ln -sf $(LIBNAME) ../libcalc.so.1.0
	ln -sf libcalc.so.1.0 ../libcalc.so

./obj/libcalc.o: ./src/libcalc.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/infija_a_postfija.o: ./src/infija_a_postfija.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/manejo_nodos.o: ./src/manejo_nodos.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/debug.o: ./src/debug.c
	$(CC) -Wall -c $< -o $@

./obj:
	mkdir $@

debug: ./obj ./obj/debug.o $(OBJS) $(HEADERS)
	$(CC) $(OBJS) ./obj/debug.o -L.. -lmaths -o debug

install: ../$(LIBNAME)
	install -c ../$(LIBNAME) ~/.local/lib
	ln -sf $(LIBNAME) ~/.local/lib/$(SONAME)
	ln -sf $(SONAME) ~/.local/lib/$(LIB)
clean:
	$(RM) *.o ./obj/*.o core libcalc.so* debug
	rmdir ./obj
