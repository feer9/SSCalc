# compiler
CC:=gcc

OBJS:=./obj/notacion.o ./obj/manejo_nodos.o ./obj/calc.o
HEADERS:=../libmaths/src/maths.h ./src/calc.h ./src/notacion.h ./src/manejo_nodos.h ./src/nodo.h
LIB:=libcalc.so
LIBVER:=1.0
LIBSUBVER:=0
SONAME:=$(LIB).$(LIBVER)
LIBNAME:=$(LIB).$(LIBVER).$(LIBSUBVER)
INSTALL_DIR:=${HOME}/.local/lib
EXECUTABLE:=../../bin/calc

# compiler flags
CFLAGS:=-Wall -fPIC
EXEC_CFLAGS:=-Wall
# linker flags
LDFLAGS:=-shared -Wl,-soname,$(SONAME) -L../libmaths -L../libvarious


.PHONY: all build build-debug install uninstall clean clean-all

all: build

build: $(LIBNAME) $(EXECUTABLE)

build-debug: CFLAGS += -ggdb
build-debug: EXEC_CFLAGS += -ggdb
build-debug: $(LIBNAME) $(EXECUTABLE)

	# importante que "-L. -lmaths" esté a la derecha
$(LIBNAME): ./obj  $(OBJS) $(HEADERS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lmaths -lvarious
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

obj/calc.o: src/calc.c src/calc.h src/notacion.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/notacion.o: src/notacion.c src/notacion.h src/calc.h src/manejo_nodos.h src/nodo.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/manejo_nodos.o: src/manejo_nodos.c src/manejo_nodos.h src/notacion.h src/nodo.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/console.o: src/console.c src/calc.h
	$(CC) $(EXEC_CFLAGS) -c $< -o $@

obj:
	mkdir $@

../../bin:
	mkdir $@

#-L. 
$(EXECUTABLE): ./obj ./obj/console.o $(OBJS) $(HEADERS) ../../bin
	$(CC) $(OBJS) ./obj/console.o -o $@ -L../libmaths -L../libvarious -Wl,-rpath,$$'ORIGIN':$$'ORIGIN'/../lib -lmaths -lvarious -no-pie

install: $(LIBNAME) $(EXECUTABLE)
	install -C $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)
	install -C $(EXECUTABLE) ~/.local/bin


uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*
	rm -f ~/.local/bin/calc


clean:
	rm -rf *.o ./obj/*.o ./obj core

clean-all: clean
	rm -f $(LIB)*
