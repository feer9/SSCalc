LIB:=libmaths.so
LIBVER:=.0.7
LIBSUBVER:=.0
SONAME:=$(LIB)$(LIBVER)
LIBNAME:=$(LIB)$(LIBVER)$(LIBSUBVER)
INSTALL_DIR:=${HOME}/.local/lib

CC:=g++
CFLAGS:=-Wall -ggdb -fPIC
LDFLAGS:=-shared -Wl,-soname,$(SONAME)

OBJ:=./obj/maths.o
OBJDIR:=./obj


all: build

build: $(LIBNAME)
	
.PHONY: all build install clean

#	sudo ldconfig -vn .
$(LIBNAME): $(OBJDIR) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
	ln -sf $(LIBNAME) $(SONAME)
	ln -sf $(SONAME) $(LIB)

./obj/maths.o: ./src/maths.c ./src/maths.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir obj

debug: ./src/maths.c ./src/debug.c ./src/maths.h
	gcc -Wall -no-pie ./src/maths.c ./src/debug.c -o $@

install: $(LIBNAME)
	install -c $(LIBNAME) $(INSTALL_DIR)
	ln -sf $(LIBNAME) $(INSTALL_DIR)/$(SONAME)
	ln -sf $(SONAME) $(INSTALL_DIR)/$(LIB)
#	sudo ldconfig

uninstall:
	rm -rf $(INSTALL_DIR)/$(LIB)*

clean:
	rm -rf ./obj/*.o ./obj core debug

clean_build:
	rm -f $(LIB)*