src/arbol:src/arbol.o
	gcc -o build/arbol src/arbol.o
src/arbol.o:src/arbol.c src/arbol.h
	gcc -c src/arbol.c -o src/arbol.o
clean:
	rm src/*.o
run:
	./build/arbol
