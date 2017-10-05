# HEADERS dispatcher.h wrappers.h

all: dispatcher Amal/amal Basim/basim

dispatcher: dispatcher.o wrappers.o
	cc dispatcher.o wrappers.o -o dispatcher 

dispatcher.o: dispatcher.c wrappers.h
	cc -c dispatcher.c -o dispatcher.o 	

Amal/amal: Amal/amal.o wrappers.o myCrypto.o
	cc Amal/amal.o wrappers.o myCrypto.o -o Amal/amal

Basim/basim: Basim/basim.o wrappers.o myCrypto.o
	cc Basim/basim.o wrappers.o myCrypto.o -o Basim/basim

Amal/amal.o: Amal/amal.c wrappers.h myCrypto.h
	cc -c -lcrypto Amal/amal.c -o Amal/amal.o
Basim/basim.o: Basim/basim.c wrappers.h myCrypto.h
	cc -c -lcrypto Basim/basim.c -o Basim/basim.o

wrappers.o: wrappers.c wrappers.h
	cc -c wrappers.c -o
myCrypto.o: myCrypto.c myCrypto.h
	cc -c -lcrypto myCrypto.c -o myCrypto.o
clean:
	rm dispatcher Amal/amal Basim/basim
