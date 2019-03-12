# GUI Scientific Calculator proyect
Written from scratch in C

## About the project
The GUI works with the **_libui_** graphic library from Pietro Gagliardi  
All the thanks to his project, link to [his git](https://github.com/andlabs/libui)  
About the core, it's all written in 3 libraries, one for the math functions, other for processing the expressions, and the third with some common functions like string ones.

## Building (linux)
run
```
$ make build
```
### Installing
run
```
$ make install
```

### Run
You can run the GUI version with
```
$ calc-ui
```
or the console one
```
$ calc
```

### Linking the libraries
To properly link the libraries, you need to do the following:

* First add ```${HOME}/.local/lib``` to ```/etc/ld.so.conf```
* and then run ```$ sudo ldconfig```


## Documentation
Any problem with linking the shared libraries, more info in:
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
