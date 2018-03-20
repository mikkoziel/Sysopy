#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

blok * stworzBlok(int rozmiarBloku, char * generatedChar){
    struct blok * blok = (struct blok *) malloc(sizeof(blok));
    blok -> zawartosc = (char *) malloc(rozmiarBloku * sizeof(char)+1);
    int i;
    for(i = 0; i < rozmiarBloku; i++){
        blok -> zawartosc[i] = generatedChar[i];
    }
    blok -> sumaAscii = -1;
    getSumaAscii(blok);
    return blok;
}


void wypiszBlok(blok * blok){
    if(blok == NULL){
        return;
    }
    blok -> sumaAscii = getSumaAscii(blok);
    printf("Suma ASCII: %d\n", blok -> sumaAscii);
    printf("Zawartość: %s\n\n", blok -> zawartosc);
}


int wyliczSumaAscii(char * zawartosc){
    int suma = 0;
    int dlugosc = strlen(zawartosc);
    int i, p;
    char a;
    for(i = 0; i < dlugosc; i++){
        a = zawartosc[i];
        p = (int) a;
        suma = suma + p;
    }
    return suma;
}


int getSumaAscii(blok * blok){
    if(blok -> sumaAscii == -1){
        blok -> sumaAscii = wyliczSumaAscii(blok -> zawartosc);
    }
    return blok -> sumaAscii;
}


blok * getBlok(blok * blok){
    return blok;
}
