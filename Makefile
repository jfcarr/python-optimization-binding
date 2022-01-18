default:
	@echo 'build'
	@echo 'shared'
	@echo 'clean'

run: build
	./abo_client

build: abo_client

shared:
	gcc -I. abo_lib.c -shared -o abo_lib.so
	@ # gcc -Wall -fPIC -c abo_lib.c
	@ # gcc -shared -Wl,-soname,abo_lib.so.1 -o abo_lib.so abo_lib.o


abo_client: abo_client.o abo_lib.o
	gcc -o abo_client abo_client.o abo_lib.o -lm

abo_client.o: abo_client.c abo_lib.h
	gcc -c abo_client.c

abo_lib.o: abo_lib.c
	gcc -c abo_lib.c

clean:
	-rm -f abo_client *.o *.so
