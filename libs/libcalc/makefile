# compiler
CC:=g++

OBJS:=./obj/notacion.o ./obj/manejo_nodos.o ./obj/calc.o
HEADERS:=../libmaths/src/maths.h ./src/calc.h ./src/notacion.h ./src/manejo_nodos.h ./src/nodo.h
LIB:=libcalc.so
LIBVER:=.0.9
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)
INSTALL_DIR:=~/.local/lib

# compiler flags
CFLAGS:=-Wall -ggdb -fPIC -I..
# linker flags
LDFLAGS:=-shared -Wl,-soname,$(SONAME)


all: build

build: $(LIBNAME)

.PHONY: all build install clean

	# importante que "-L. -lmaths" esté a la derecha
$(LIBNAME): ./obj  $(OBJS) $(HEADERS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -L../libmaths -lmaths
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

./obj/calc.o: ./src/calc.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/notacion.o: ./src/notacion.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/manejo_nodos.o: ./src/manejo_nodos.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/debug.o: ./src/debug.c
	$(CC) -Wall -c $< -o $@

./obj:
	mkdir $@

#-L. -Wl,-rpath=..
debug: ./obj ./obj/debug.o $(OBJS) $(HEADERS)
	$(CC) -Wall $(OBJS) ./obj/debug.o -o debug -L../libmaths -lmaths -L../libstring -lstring -Wl,-rpath=$(INSTALL_DIR)

install: $(LIBNAME)
	install -c $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

clean:
	$(RM) *.o ./obj/*.o core debug
	rmdir ./obj

clean_build:
	rm -f $(LIB)*
