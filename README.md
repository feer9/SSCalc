Proyecto calculadora gráfica escrita desde cero en C

TODO: Abrir un branch para portar todo a C con alguna libreria grafica, y sacar del medio a Qt


Para poder linkear correctamente las librerias:

1) agregar "${HOME}/.local/lib" a /etc/ld.so.conf.d/libc.conf
2) hacer "make install" en cada subdirectorio de la carpeta libs
3) actualizar las librerias del sistema con "sudo ldconfig"
