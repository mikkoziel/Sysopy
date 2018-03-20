CC=gcc
FLAG=-Wall -std=c11
LFLAG=-fPIC

all: static shared

static:
	$(CC) $(FLAG) -c blok.c
	$(CC) $(FLAG) -c tabelaStatic.c
	$(CC) $(FLAG) -c tabelaDynamic.c
	ar crs libtabela.a blok.o tabelaStatic.o tabelaDynamic.o
	rm -f *.o

shared:
	$(CC) $(FLAG) $(LFLAG) -c blok.c -o blok.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaStatic.c -o tabelaS.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaDynamic.c -o tabelaD.o
	$(CC) $(FLAG) -shared -o libtabela.so tabelaS.o tabelaD.o blok.o
	rm -f *.o

clean:
	rm -f *.o *.a *.so main
