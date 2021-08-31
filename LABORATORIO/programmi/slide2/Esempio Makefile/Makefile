# makefile per usarev
# versione 1
output: usarev.o reverse.o
	gcc -o prog usarev.o reverse.o
usarev.o: usarev.c
	gcc -c usarev.c
reverse.o: reverse.c
	gcc -c reverse.c
clean:
	rm *.o output
