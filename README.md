# Simple Scientific Calculator
Written from scratch in C

## About the project
The GUI has been written in GTK+  
About the core, it's all written in 3 libraries, one for the math functions, other for processing the expressions, and the third with some common functions like string handling.

## Building (linux)
To build the project you can use cmake
```
$ mkdir -p build && cd build
$ cmake ..
$ make build
```

Also some makefiles are left from previous attempts

## Run
You can run the GUI simply by double clicking the generated executable or by command line  
```
build $ ./sscalc-gui
```
Also the program can be run from the terminal  
```
build $ ./sscalc
```

