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
CFLAGS:=-Wall -Ilibraries
# linker flags
LDFLAGS:=-Wl,-rpath,$$'ORIGIN':$$'ORIGIN'/../lib -L./lib -lui -lvarious -lmaths -lcalc -no-pie
#:$$'ORIGIN'/../lib
DEBUGFLAGS:=

.PHONY: all build build-clean build-debug install uninstall clean clean-all clean-bin configure

all: build

build: ./lib/libvarious.so ./lib/libmaths.so ./lib/libcalc.so ./bin/calc $(EXECUTABLE)

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



lib/libvarious.so: ./libraries/libvarious/libvarious.so ./lib
	cp $<* ./lib

lib/libmaths.so: ./libraries/libmaths/libmaths.so ./lib
	cp $<* ./lib

lib/libcalc.so: ./libraries/libcalc/libcalc.so ./lib
	cp $<* ./lib



./libraries/libvarious/libvarious.so:
	make -C libraries/libvarious $(DEBUGFLAGS)

./libraries/libmaths/libmaths.so:
	make -C libraries/libmaths $(DEBUGFLAGS)

./libraries/libcalc/libcalc.so:
	make -C libraries/libcalc $(DEBUGFLAGS)


./calc:
	make -C libraries/libcalc $(DEBUGFLAGS)


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
	make -C libraries/libvarious install
	make -C libraries/libmaths install
	make -C libraries/libcalc install
	install -C $(EXECUTABLE) $(INSTALL_BIN_DIR)
	install -C lib/libui.so.0 ~/.local/lib
	ln -sf libui.so.0 ~/.local/lib/libui.so
	install -C ./resources/Surprised_Patrick.png $(ICONS_DIR)/calc-ui.png
	./resources/desktop_gen
	@echo "Done."

configure:
	./resources/configure

uninstall:
	make -C libraries/libvarious uninstall
	make -C libraries/libmaths uninstall
	make -C libraries/libcalc uninstall
	rm -f $(INSTALL_DIR)/$(EXECUTABLE) $(INSTALL_LIBS_DIR)/libui.so*
	rm -f $(ICONS_DIR)/calc-ui.png
	rm -f $(APPLICATIONS_DIR)/calc-ui.desktop
	@echo "Done."

clean:
	make -C libraries/libvarious clean
	make -C libraries/libmaths clean
	make -C libraries/libcalc clean
	rm -rf *.o ./obj core

clean-all:
	make -C libraries/libvarious clean-all
	make -C libraries/libmaths clean-all
	make -C libraries/libcalc clean-all

clean-bin:
	rm -rf bin lib/libvarious.so* lib/libmaths.so* lib/libcalc.so*



win64CC:=x86_64-w64-mingw32-gcc
sources:=libraries/libvarious/src/std.c libraries/libvarious/src/strings.c libraries/libvarious/src/various.c libraries/libmaths/src/maths.c libraries/libcalc/src/calc.c libraries/libcalc/src/manejo_nodos.c libraries/libcalc/src/notacion.c src/mainWindow.c src/main.c

win64:
	$(win64CC) -Wall libui.a $(sources) -o calcui.exe
