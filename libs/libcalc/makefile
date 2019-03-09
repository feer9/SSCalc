# compiler
CC:=g++

OBJS:=./obj/notacion.o ./obj/manejo_nodos.o ./obj/calc.o
HEADERS:=../libmaths/src/maths.h ./src/calc.h ./src/notacion.h ./src/manejo_nodos.h ./src/nodo.h
LIB:=libcalc.so
LIBVER:=.0.9
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)
INSTALL_DIR:=${HOME}/.local/lib

# compiler flags
CFLAGS:=-Wall -ggdb -fPIC
# linker flags
LDFLAGS:=-Wall -Wl,-soname,$(SONAME) -L${HOME}/.local/lib -L../libmaths -L../libvarious


all: build

build: $(LIBNAME)

.PHONY: all build install build_console install_console uninstall uninstall_console clean clean_build

	# importante que "-L. -lmaths" esté a la derecha
$(LIBNAME): ./obj  $(OBJS) $(HEADERS)
	$(CC) -shared $(LDFLAGS) -o $@ $(OBJS) -lmaths
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

obj/calc.o: src/calc.c src/calc.h src/notacion.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/notacion.o: src/notacion.c src/notacion.h src/calc.h src/manejo_nodos.h src/nodo.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/manejo_nodos.o: src/manejo_nodos.c src/manejo_nodos.h src/notacion.h src/nodo.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/console.o: src/console.c src/calc.h
	$(CC) -Wall -c $< -o $@

obj:
	mkdir $@

#-L. -Wl,-rpath=..
build_console: ./obj ./obj/console.o $(OBJS) $(HEADERS)
	$(CC) $(LDFLAGS) $(OBJS) ./obj/console.o -o calc -lmaths -lvarious

install: $(OBJS) $(LIBNAME)
	install -c $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)
	sudo ldconfig

install_console: build_console
	mkdir -p ~/.local/bin
	install calc ~/.local/bin
	sudo ldconfig

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

uninstall_console:
	rm ~/.local/bin/calc

clean:
	$(RM) *.o ./obj/*.o core
	rmdir ./obj

clean_build:
	rm -f $(LIB)* calc
