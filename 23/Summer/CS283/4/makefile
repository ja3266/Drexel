all: ccadd ccitem cclist ccdel ccmatch ccyear ccedit

ccadd: ccadd.o
	gcc ccadd.o -o ccadd 

ccadd.o : ccadd.c
	gcc -c ccadd.c

ccitem: ccitem.o
	gcc ccitem.o -o ccitem 

ccitem.o : ccitem.c
	gcc -c ccitem.c

cclist: cclist.o
	gcc cclist.o -o cclist 

cclist.o : cclist.c
	gcc -c cclist.c

ccdel : ccdel.o
	gcc ccdel.o -o ccdel

ccdel.o : ccdel.c
	gcc -c ccdel.c

ccmatch : ccmatch.o
	gcc ccmatch.o -o ccmatch

ccmatch.o : ccmatch.c
	gcc -c ccmatch.c

ccyear: ccyear.o
	gcc ccyear.o -o ccyear

ccyear.o : ccyear.c
	gcc -c ccyear.c

ccedit : ccedit.o
	gcc ccedit.o -o ccedit

ccedit.o : ccedit.c
	gcc -c ccedit.c

clean :
	-\rm ccadd *.o
	-\rm ccitem *.o
	-\rm cclist *.o
	-\rm ccdel *.o

test:
	-\rm ccdb
	./ccadd 1 "Macbook Pro" "Apple" "M1 Pro" 2021 "My current laptop"
	./ccadd 2 "Macbook Pro" "Apple" "i5" 2017 "My previous laptop"
	./ccadd 3 "Pavilion 15" "HP" "fx6300" 2015 "My first laptop"
	./cclist
