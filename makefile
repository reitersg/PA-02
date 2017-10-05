# HEADERS dispatcher.h wrappers.h

all: dispatcher amal/amal basim/basim

dispatcher: dispatcher.o wrappers.o
	gcc -o dispatcher dispatcher.o wrappers.o

dispatcher.o: dispatcher.c wrappers.h
	gcc -c dispatcher.c	

amal/amal: amal/amal.o wrappers.o myCrypto.o
	gcc -o amal/amal amal.o wrappers.o myCrypto.o

basim/basim: basim/basim.o wrappers.o myCrypto.o
	gcc -o basim/basim basim.o wrappers.o myCrypto.o

amal/amal.o: amal/amal.c wrappers.h myCrypto.h
	gcc -c amal/amal.c

basim/basim.o: basim/basim.c wrappers.h myCrypto.h
	gcc -c basim/basim.c

wrappers.o: wrappers.c wrappers.h
	gcc -c wrappers.c
myCrypto.o: myCrypto.c myCrypto.h
	gcc -c myCrypto.c
clean:
	rm dispatcher amal/amal basim/basim
