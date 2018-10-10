karate_grafo:   main.o  userinterface.o dataprocessing.o    readgml.o
	gcc -c -o readgml.o readgml.c
	g++ -o $@ $^
