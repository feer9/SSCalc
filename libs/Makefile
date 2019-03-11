build:
	make -C libvarious
	make -C libmaths
	make -C libcalc 

install:
	make -C libvarious install
	make -C libmaths install
	make -C libcalc install

install_console:
	make -C libcalc install_console

configure-shared-libraries:
	sudo ldconfig

clean:
	make -C libvarious clean
	make -C libmaths clean
	make -C libcalc clean

clean_build:
	make -C libvarious clean_build
	make -C libmaths clean_build
	make -C libcalc clean_build