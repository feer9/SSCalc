CC=g++
CFLAGS=-Wall -ggdb -fPIC
LDFLAGS=-fPIC -shared
NOMBRE_LIB=libmaths.so.1.0.0
SONAME=libmaths.so.1.0

$(NOMBRE_LIB): ./obj ./obj/libmaths.o
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ ./obj/libmaths.o
	ln -s $(NOMBRE_LIB) libmaths.so
	sudo ldconfig -vn ./

./obj/libmaths.o: libmaths.c
	$(CC) $(CFLAGS) -c $^ -o $@

./obj:
	mkdir obj

clean:
	$(RM) ./obj/*.o core libmaths.so*
