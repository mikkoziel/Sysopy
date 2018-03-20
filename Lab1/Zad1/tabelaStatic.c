//
// Created by Windows 8.1 on 2018-03-15.
//

//
// Created by Windows 8.1 on 2018-03-15.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"

void budujTabelaStatic(int rozmiarTabeli){
    if(rozmiarTabeli > 1024){
        printf("Maksymalny rozmiar tabeli to 1024");
        rozmiarTabeli = 1024;
    }
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        tabela[i] = NULL;
    }
}


int * usunTabelaStatic(int rozmiarTabeli){
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        if(tabela[i] != NULL){
            usunBlokStatic(i, rozmiarTabeli);
        }
    }
    return *tabela;
}

//----------------------------------------------------------

void dodajBlokStatic(int rozmiarTabeli, int rozmiarBloku, int index, char* zawartosc){
    if(index < 0 || index >= rozmiarTabeli){
        return;
    }

    blok * nowyBlok = stworzBlok(rozmiarBloku, zawartosc);
    if(tabela[index] == NULL){
        tabela[index] = nowyBlok;
    }
    else{
        printf("Nadpisywanie zawartości bloku %d\n", index);
        tabela[index] = nowyBlok;
    }
    wypiszBlok(nowyBlok);
}


void usunBlokStatic(int index, int rozmiarTabeli){
    if(index < 0 || index >= rozmiarTabeli){
        return;
    }
    if(tabela[index] == NULL){
        return;
    }

    blok *blok = getBlok(tabela[index]);
    free(blok -> zawartosc);
    blok -> zawartosc = NULL;
    free(blok);
    tabela[index] = NULL;
}


int znajdzBlokStatic(int index, int rozmiarTabeli){
    int i;
    int znalezionaRoznica = 999999;
    int sprawdzanaRoznica;
    int znalezionyIndex;
    int szukana;

    szukana = getSumaAscii(tabela[index]);

    for(i = 0; i < rozmiarTabeli; i++){
        if(tabela[i] == NULL || index == i){
            continue;
        }

        sprawdzanaRoznica = abs(getSumaAscii(tabela[i]) - szukana);
        if(sprawdzanaRoznica < znalezionaRoznica){
            znalezionaRoznica = sprawdzanaRoznica;
            znalezionyIndex = i;
        }

    }
    return znalezionyIndex;
}

//---------------------------------------------------------

void wypiszTabelaStatic(int rozmiarTabeli){
    printf("TABELA STATYCZNA\n");
    int i;
    for(i = 0; i < rozmiarTabeli; i++){
        if(tabela[i] != NULL){
            printf("Index %d: \n", i);
            printf("    ");
            wypiszBlok(tabela[i]);
        }
    }
}
