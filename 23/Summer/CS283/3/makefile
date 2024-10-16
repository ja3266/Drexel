build: thumb 

thumn : thumb.o
	gcc thumb.o -o thumb 

265inventory.o : 265inventory.c
	gcc -c thumb.c

clean :
	-\rm thumb *.o

view:
	less thumb.c

test: test.o
	gcc test.o -o test

test.o: test.c
	gcc -c test.c

thumbs : 
	./thumb < eniac.pgm > eniact.pgm
	./thumb < porsche.pgm > porschet.pgm
