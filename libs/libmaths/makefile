LIB:=libmaths.so
LIBVER:=.0.7
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)

CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-shared -Wl,-soname,$(SONAME)

OBJ:=./obj/maths.o
OBJDIR:=./obj


all: build

build: ../$(LIBNAME)
	
.PHONY: all build install clean

../$(LIBNAME): $(OBJDIR) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
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

uninstall:
	rm -rf ~/.local/lib/$(LIBNAME) ~/.local/lib/$(SONAME) \
	~/.local/lib/$(LIB)

clean:
	rm -rf ./obj/*.o ./obj core debug
