#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

void ** budujTabelaDynamic(int rozmiarTabeli){
    void ** tabelaDynamic = calloc((size_t)rozmiarTabeli, sizeof(char*));
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        tabelaDynamic[i] = NULL;
    }
    return tabelaDynamic;
}


void usunTabelaDynamic(void** dTabela, int rozmiarTabeli){
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        usunBlokDynamic(dTabela, i, rozmiarTabeli);
    }
    free(dTabela);
}

//-------------------------------------------------------------
void ** dodajBlokDynamic(int rozmiarTabeli, int rozmiarBloku, int index, char* zawartosc, void** dTabela){
    if(index < 0 || index >= rozmiarTabeli){
        return dTabela;
    }

    blok * nowyBlok = stworzBlok(rozmiarBloku, zawartosc);
    if(dTabela[index] == NULL){
        dTabela[index] = nowyBlok;
    }
    else{
        printf("Nadpisywanie zawartości bloku %d\n", index);
        dTabela[index] =nowyBlok;
    }
    wypiszBlok(nowyBlok);
    return dTabela;
}


void ** usunBlokDynamic(void ** dTabela, int index, int rozmiarTabeli){
    if(index < 0 || index >= rozmiarTabeli){
        return dTabela;
    }
    if(dTabela[index] == NULL){
        return dTabela;
    }

    blok * blok = getBlok(dTabela[index]);
    free(blok -> zawartosc);
    blok -> zawartosc = NULL;
    free(blok);
    dTabela[index] = NULL;
    return dTabela;
}


int znajdzBlokDynamic(void ** dTabela, int index, int rozmiarTabeli){
    int i;
    int znalezionaRoznica = 999999;
    int sprawdzanaRoznica;
    int znalezionyIndex;
    int szukana, sprawdzaneASCII;

    szukana = getSumaAscii(dTabela[index]);

    for(i = 0; i < rozmiarTabeli; i++){
        if(dTabela[i] == NULL || index == i){
            continue;
        }

        sprawdzaneASCII = getSumaAscii(dTabela[i]);
        sprawdzanaRoznica = abs(sprawdzaneASCII - szukana);
        if(sprawdzanaRoznica < znalezionaRoznica){
            znalezionaRoznica = sprawdzanaRoznica;
            znalezionyIndex = i;
        }

    }
    return znalezionyIndex;
}

//----------------------------------------------------------------
void wypiszTabelaDynamic(void ** dTabela, int rozmiarTabeli){
    printf("TABELA DYNAMICZNA\n");
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        if(dTabela[i] != NULL){
            printf("Index %d: \n", i);
            printf("    ");
            wypiszBlok(dTabela[i]);
        }
    }
}
