# compiler
CC:=g++

OBJS:=./obj/infija_a_postfija.o ./obj/manejo_nodos.o ./obj/calc.o
HEADERS:=../libmaths/src/maths.h ./src/calc.h ./src/infija_a_postfija.h ./src/manejo_nodos.h ./src/nodo.h
LIB:=libcalc.so
SONAME:=libcalc.so.1.0
LIBNAME:=libcalc.so.1.0.0

# compiler flags
CFLAGS:=-Wall -ggdb -fPIC -I..
# linker flags
LDFLAGS:=-shared -Wl,-soname,$(SONAME)


all: build

build: ../$(LIBNAME)

.PHONY: all build install clean

../$(LIBNAME): ./obj  $(OBJS) $(HEADERS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -L.. -lmaths
	# importante que "-L.. -lmaths" esté a la derecha
	ln -sf $(LIBNAME) ../$(SONAME)
	ln -sf $(SONAME) ../$(LIB)

./obj/calc.o: ./src/calc.c
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
	$(CC) -L.. -Wl,-rpath=.. -Wall $(OBJS) ./obj/debug.o -o debug -lmaths -lstring

install: ../$(LIBNAME)
	install -c ../$(LIBNAME) ~/.local/lib
	ln -sf $(LIBNAME) ~/.local/lib/$(SONAME)
	ln -sf $(SONAME) ~/.local/lib/$(LIB)

uninstall:
	rm -rf ~/.local/lib/$(LIBNAME) ~/.local/lib/$(SONAME) \
	~/.local/lib/$(LIB)

clean:
	$(RM) *.o ./obj/*.o core debug
	rmdir ./obj
