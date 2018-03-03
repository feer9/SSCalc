CC=gcc
CFLAGS=-Wall -ggdb -fPIC
LDFLAGS=-fPIC -shared
NOMBRE_LIB=libmaths.so.1.0.0
SONAME=libmaths.so.1.0

$(NOMBRE_LIB): libmaths.o
	$(CC) -Wl,-soname,$(SONAME) $(LDFLAGS) -o $@ $^
	ln -s $(NOMBRE_LIB) libmaths.so
	sudo ldconfig -vn ./

clean:
	$(RM) *.o core libmaths.so*