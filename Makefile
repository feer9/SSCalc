CC:=gcc
OBJS:=./obj/main.o ./obj/mainWindow.o
HEADERS:=./src/mainWindow.h
EXECUTABLE:=calc-ui
INSTALL_DIR:=${HOME}/.local/bin
LIBS_DIR:=${HOME}/.local/lib
LIBS:=libvarious libmaths libcalc
ICONS_DIR:=${HOME}/.local/share/icons
APPLICATIONS_DIR:=${HOME}/.local/share/applications
# compiler flags
CFLAGS:=-Wall
# linker flags
LDFLAGS:=-Wl,-rpath,$$'ORIGIN' -L${HOME}/.local/lib -L./libs -L./libs/libcalc -L./libs/libmaths -L./libs/libvarious -lui -lvarious -lmaths -lcalc -no-pie
#:$$'ORIGIN'/../lib


all: build

build: ./libs/libvarious/libvarious.so ./libs/libmaths/libmaths.so ./libs/libcalc/libcalc.so $(EXECUTABLE)

.PHONY: all build install uninstall clean configure-shared-libraries


$(EXECUTABLE): ./obj  $(OBJS) $(HEADERS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

obj/main.o: src/main.c src/mainWindow.h ./obj 
	$(CC) $(CFLAGS) -c $< -o $@

obj/mainWindow.o: src/mainWindow.c src/mainWindow.h ./obj 
	$(CC) $(CFLAGS) -c $< -o $@

./libs/libvarious/libvarious.so:
	make -C libs/libvarious

./libs/libmaths/libmaths.so:
	make -C libs/libmaths

./libs/libcalc/libcalc.so:
	make -C libs/libcalc 

./obj:
	mkdir $@

$(INSTALL_DIR):
	mkdir $@

$(LIBS_DIR):
	mkdir $@

$(ICONS_DIR):
	mkdir $@

$(APPLICATIONS_DIR):
	mkdir $@

$(LIBS):
	make -C libs/$@


install: $(OBJS) $(EXECUTABLE) $(INSTALL_DIR) $(LIBS_DIR) $(ICONS_DIR) $(APPLICATIONS_DIR)
	make -C libs/libvarious install
	make -C libs/libmaths install
	make -C libs/libcalc install
	install -C $(EXECUTABLE) $(INSTALL_DIR)
	install -C libs/libui.so.0 ~/.local/lib
	ln -sf libui.so.0 ~/.local/lib/libui.so
	install -C ./resources/Surprised_Patrick.png $(ICONS_DIR)/calc-ui.png
	./resources/desktop_gen

configure:
	./resources/configure

uninstall:
	make -C libs/libvarious uninstall
	make -C libs/libmaths uninstall
	make -C libs/libcalc uninstall
	rm -f $(INSTALL_DIR)/$(EXECUTABLE) $(LIBS_DIR)/libui.so*
	rm -f $(ICONS_DIR)/calc-ui.png
	rm -f $(APPLICATIONS_DIR)/calc-ui.desktop

clean:
	make -C libs/libvarious clean
	make -C libs/libmaths clean
	make -C libs/libcalc clean
	rm -rf *.o ./obj/*.o ./obj core

clean-build:
	make -C libs/libvarious clean-build
	make -C libs/libmaths clean-build
	make -C libs/libcalc clean-build
	rm -rf $(EXECUTABLE)
