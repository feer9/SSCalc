CC=g++
CFLAGS=-Wall -ggdb -fPIC
LDFLAGS=-fPIC -shared
OBJS=./obj/infija_a_postfija.o ./obj/manejo_nodos.o
NOMBRE_LIB=libcalc.so.1.0.0
SONAME=libcalc.so.1.0


all: $(NOMBRE_LIB)

$(NOMBRE_LIB): ./obj ./obj/libcalc.o  $(OBJS)
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ ./obj/libcalc.o $(OBJS)
	ln -sf $(NOMBRE_LIB) libcalc.so
	sudo ldconfig -vn ./

./obj/libcalc.o: libcalc.c
	$(CC) $(CFLAGS) -c $^ -o $@

./obj/infija_a_postfija.o: ./src/infija_a_postfija.c
	$(CC) $(CFLAGS) -c $^ -o $@

./obj/manejo_nodos.o: ./src/manejo_nodos.c
	$(CC) $(CFLAGS) -c $^ -o $@

./obj:
	mkdir $@

clean:
	$(RM) *.o ./obj/*.o core libcalc.so*


#CFLAGS 	Extra flags to give to the C compiler.
#LDFLAGS 	Extra flags to give to compilers when they are supposed 
#			to invoke the linker, `ld'.