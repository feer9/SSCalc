Proyecto calculadora gráfica escrita desde cero en C

TODO: {
-> Abrir un branch para portar todo a C con alguna libreria grafica, y sacar del medio a Qt
-> implementar ANS
}

Para poder linkear correctamente las librerias:

1) agregar "/home/<usuario>/.local/lib" a /etc/ld.so.conf.d/libc.conf
2) hacer "make install" en el directorio libs
3) actualizar las librerias del sistema con "sudo ldconfig"

info de librerías dinámicas:
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html