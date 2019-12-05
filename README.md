# GUI Scientific Calculator
Written from scratch in C

## About the project
The GUI works with the **_libui_** C graphic library from Pietro Gagliardi  
All the thanks to his project, link to [his git](https://github.com/andlabs/libui)  
About the core, it's all written in 3 libraries, one for the math functions, other for processing the expressions, and the third with some common functions like string ones.

## Building (linux)
To build just use the makefile in the project main folder
```
$ make build
```
### Installing
To install, root privileges are not required, since the install dir is in the user tree.  
Anyway, to properly set the library path into the system (optional), the only way is via `/etc/ld.so.conf`, for which root permissions are required (see below).  
Install with
```
$ make install
```

### Run
You can run the GUI simply with the desktop entry that is put into `/home/user/.local/share/applications`, accessible from your desktop menu.  
Also the program can be run from the terminal (if the path is properly set, see below), both in gui and terminal mode.  
To run the gui:
```
$ calc-ui
```
and the console mode:
```
$ calc
```

### Configuring the PATH
To properly set the libraries and the PATH environment variable, you need to run `make configure`. It will ask for setting a line into your `~/.bashrc`, and then add the library directory to `/etc/ld.so.conf.d/user.config` (root are required). Be careful on this step, since it will override this file, even if it already exists.  
Also it is recommended moving the PATH export from `~/.bashrc` to the more general `~/.profile` file. But be aware that, if you do so, the changes only will apply on the next login.


## Documentation
Any problem within linking the shared libraries, more info in:
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
