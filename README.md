Laboratorio I: Arbol de procesos

Integrantes:
	José Arce
	Juan Giglio

Supuestos:

	El archivo de entrada es válido

	Los procesos en el archivo de entrada se encuentran ordenados según su nivel, proceso inicial en la primera línea, seguido por las lineas de sus procesos hijos, en el orden que debieran ser creados, desde el id más bajo hasta el más alto.

Descripción de la solución:

	Desde un archivo plano separado por espacios se crea una matriz n x n dinámica, n se determina con el id de proceso máximo, en esta matriz se identifica con un 1 las posiciones en que las filas son el proceso padre y las columnas los hijos.
	
	Se recorre esta matriz creando los procesos, en caso que el id coincida con la del padre se crea un pipe luego se realiza un fork y se realizan las siguientes acciones:

Padre:
	Se cierra pipe de lectura
	Se escribe en pipe la acumulación de pids

Hijo:
	Se actualiza id a la del hijo
	Se cierra pipe de escritura
	Se lee acumulación de pids desde el pipe de lectura, se agrega pid del proceso hijo
	
	Finalmente se escribe el resultado solicitado, ID proceso, PID y suma de PIDS.

Manual de compilación:

	1.- Descompimir archivo ptree.zip

	2.- Ejecutar el comando "make" desde la carpeta ptree.

Manual de ejecución:

	1.- Compilar

	2.- Mover archivo a cargar dentro de la carpeta "build"

	3.- Ejecutar desde la carpeta build "./arbol -f <nombre de archivo>" luego de la opción -f escribir el nombre de archivo a leer.
