src/arbol:src/arbol.o
	gcc -o build/arbol build/arbol.o
src/arbol.o:src/arbol.c
	gcc -c src/arbol.c -o build/arbol.o
clean:
	rm build/*

