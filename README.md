Proyecto calculadora gráfica escrita desde cero en C  
  
  
  
Para poder linkear correctamente las librerias:  

1) agregar "${HOME}/.local/lib" a /etc/ld.so.conf
2) hacer "# make install" en el directorio libs


version de consola casi terminada  
compilar con   # make install_console  
para ejecutar: $ calc  
  
cualquier problema con las librerias dinámicas, info en:  
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
