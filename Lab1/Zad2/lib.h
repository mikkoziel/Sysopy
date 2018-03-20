#ifndef Blocks
#define Blocks

//-------------------------------------------------
void * tabela[1024];

void budujTabelaStatic(int);
int * usunTabelaStatic(int);

void dodajBlokStatic(int, int, int, char*);
void usunBlokStatic(int, int);
int znajdzBlokStatic(int, int);

void wypiszTabelaStatic(int);
//-------------------------------------------------

void ** budujTabelaDynamic(int);
void usunTabelaDynamic(void**, int);

void ** dodajBlokDynamic(int, int, int, char*, void**);
void ** usunBlokDynamic(void **, int, int);
int znajdzBlokDynamic(void **, int, int);

void wypiszTabelaDynamic(void **, int);
//-------------------------------------------------

typedef struct blok{
    int sumaAscii;
    char * zawartosc;
}blok;

struct blok * stworzBlok(int, char*);
void wypiszBlok(struct blok*);
int wyliczSumaAscii(char*);
int getSumaAscii(struct blok*);
struct blok * getBlok(struct blok*);

#endif
