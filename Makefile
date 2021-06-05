CC:=gcc
OBJS:=./obj/main.o ./obj/mainWindow.o
HEADERS:=./src/mainWindow.h
EXECUTABLE:=bin/calc-ui
#LIBS:=libvarious libmaths libcalc
INSTALL_DIR:=${HOME}/.local
INSTALL_BIN_DIR:=${INSTALL_DIR}/bin
INSTALL_LIBS_DIR:=${INSTALL_DIR}/lib
ICONS_DIR:=${HOME}/.local/share/icons
APPLICATIONS_DIR:=${HOME}/.local/share/applications
# compiler flags
CFLAGS:=-Wall -Ilib
# linker flags
LDFLAGS:=-Wl,-rpath,$$'ORIGIN':$$'ORIGIN'/../lib -L./lib -lui -lvarious -lmaths -lcalc -no-pie
#:$$'ORIGIN'/../lib
DEBUGFLAGS:=

.PHONY: all build build-clean build-debug install uninstall clean clean-all clean-bin configure

all: build

build: ./lib/libvarious.so ./lib/libmaths.so ./lib/libcalc.so ./bin/calc $(EXECUTABLE) ./lib

build-clean: clean-all build



build-debug: CFLAGS += -ggdb
build-debug: DEBUGFLAGS += build-debug
build-debug: ./lib/libvarious.so ./lib/libmaths.so ./lib/libcalc.so $(EXECUTABLE)



$(EXECUTABLE): ./obj ./bin $(OBJS) $(HEADERS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

obj/main.o: src/main.c src/mainWindow.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/mainWindow.o: src/mainWindow.c src/mainWindow.h
	$(CC) $(CFLAGS) -c $< -o $@



lib/libvarious.so: ./lib/libvarious/libvarious.so
	cp -P $<* ./lib

lib/libmaths.so: ./lib/libmaths/libmaths.so
	cp -P $<* ./lib

lib/libcalc.so: ./lib/libcalc/libcalc.so
	cp -P $<* ./lib



./lib/libvarious/libvarious.so:
	make -C lib/libvarious $(DEBUGFLAGS)

./lib/libmaths/libmaths.so:
	make -C lib/libmaths $(DEBUGFLAGS)

./lib/libcalc/libcalc.so:
	make -C lib/libcalc $(DEBUGFLAGS)


./calc:
	make -C lib/libcalc $(DEBUGFLAGS)


./obj:
	mkdir $@

./lib:
	mkdir $@

./bin:
	mkdir $@

$(INSTALL_BIN_DIR):
	mkdir $@

$(INSTALL_LIBS_DIR):
	mkdir $@

$(ICONS_DIR):
	mkdir $@

$(APPLICATIONS_DIR):
	mkdir $@


install: $(OBJS) $(EXECUTABLE) $(INSTALL_BIN_DIR) $(INSTALL_LIBS_DIR) $(ICONS_DIR) $(APPLICATIONS_DIR)
	make -C lib/libvarious install
	make -C lib/libmaths install
	make -C lib/libcalc install
	install -C $(EXECUTABLE) $(INSTALL_BIN_DIR)
	install -C lib/libui.so.0 ~/.local/lib
	ln -sf libui.so.0 ~/.local/lib/libui.so
	install -C ./resources/Surprised_Patrick.png $(ICONS_DIR)/calc-ui.png
	./resources/desktop_gen
	@echo "Done."

configure:
	./resources/configure

uninstall:
	make -C lib/libvarious uninstall
	make -C lib/libmaths uninstall
	make -C lib/libcalc uninstall
	rm -f $(INSTALL_DIR)/$(EXECUTABLE) $(INSTALL_LIBS_DIR)/libui.so*
	rm -f $(ICONS_DIR)/calc-ui.png
	rm -f $(APPLICATIONS_DIR)/calc-ui.desktop
	@echo "Done."

clean:
	make -C lib/libvarious clean
	make -C lib/libmaths clean
	make -C lib/libcalc clean
	rm -rf *.o ./obj core

clean-all:
	make -C lib/libvarious clean-all
	make -C lib/libmaths clean-all
	make -C lib/libcalc clean-all

clean-bin:
	rm -rf bin lib/libvarious.so* lib/libmaths.so* lib/libcalc.so*



win64CC:=x86_64-w64-mingw32-gcc
sources:=lib/libvarious/src/std.c lib/libvarious/src/strings.c lib/libvarious/src/various.c lib/libmaths/src/maths.c lib/libcalc/src/calc.c lib/libcalc/src/manejo_nodos.c lib/libcalc/src/notacion.c src/mainWindow.c src/main.c

win64:
	$(win64CC) -Wall libui.a $(sources) -o calcui.exe
