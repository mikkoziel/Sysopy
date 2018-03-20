CC=gcc
FLAG=-Wall -std=c99
LFLAG=-fPIC

all: static

static:
	$(CC) $(FLAG) -c main.c
	$(CC) $(FLAG) -c blok.c
	$(CC) $(FLAG) -c tabelaStatic.c
	$(CC) $(FLAG) -c tabelaDynamic.c
	ar crs libtabela.a blok.o tabelaStatic.o tabelaDynamic.o
	$(CC) $(FLAG) main.c -o main -L. -ltabela
	rm -f *.o

shared:
	$(CC) $(FLAG) $(LFLAG) -c blok.c -o blok.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaStatic.c -o tabelaS.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaDynamic.c -o tabelaD.o
	$(CC) $(FLAG) -shared -o libtabela.so tabelaS.o tabelaD.o blok.o
	$(CC) $(FLAG) -Wl,-rpath=. -L. -o m_shared main.c -ltabela

dynamic:
	$(CC) $(FLAG) $(LFLAG) -c blok.c -o blok.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaStatic.c -o tabelaS.o
	$(CC) $(FLAG) $(LFLAG) -c tabelaDynamic.c -o tabelaD.o
	$(CC) $(FLAG) -Wl,-rpath=. $(LFLAG) -shared -o libtabela.so tabelaS.o tabelaD.o blok.o
	$(CC) $(FLAG) -L. -o md main.c -ldl -D DLL

clean:
	rm -f *.o *.a *.so main
