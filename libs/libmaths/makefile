LIB:=libmaths.so
LIBVER:=0.7
LIBSUBVER:=0
SONAME:=$(LIB).$(LIBVER)
LIBNAME:=$(LIB).$(LIBVER).$(LIBSUBVER)
INSTALL_DIR:=${HOME}/.local/lib

CC:=gcc
CFLAGS:=-Wall -fPIC
LDFLAGS:=-shared -Wl,-soname,$(SONAME)

OBJ:=./obj/maths.o
OBJDIR:=./obj
	
.PHONY: all build debug install uninstall clean clean-build

all: build

build: $(LIBNAME)

debug: CFLAGS += -ggdb
debug: $(LIBNAME)

#	sudo ldconfig -vn .
$(LIBNAME): $(OBJDIR) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

./obj/maths.o: ./src/maths.c ./src/maths.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir obj

test: ./src/maths.c ./src/test.c ./src/maths.h
	gcc -Wall -no-pie ./src/maths.c ./src/test.c -o $@

install: $(LIBNAME)
	install -C $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

clean:
	rm -rf ./obj/*.o ./obj core test

clean-build:
	rm -f $(LIB)*