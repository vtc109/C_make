all: main
main:	
	gcc 2019.c fields.c jval.c dllist.c jrb.c weightedGraphlib.c -o 2019
clean:	
	rm -f *.o *~
