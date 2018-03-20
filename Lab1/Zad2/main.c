#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>
#include "lib.h"
#include <sys/times.h>
#include <sys/resource.h>

#define _POSIX_C_SOURCE >=199309L


#ifndef DLL
#include "lib.h"
#endif

struct instrukcja{
    int komenda;
    char* zawartosc;
}instrukcja;

char* generujChar(int rozmiarBloku){
    char randomChar[rozmiarBloku];

    char p;
    int i = 100 *(rand() / (RAND_MAX + 1.0));
    srand(time(NULL)+i);
    for(i = rozmiarBloku; i > 0; i--){
        int tmp = 26 *(rand() / (RAND_MAX + 1.0));
        p = 'a' + tmp;
        *(randomChar + rozmiarBloku - i) = p;
    }
    char *wynik = randomChar;\
    return wynik;
}

void pokazCzas (FILE* out, clock_t clk,struct tms startTime,struct tms endTime, char* operationName) {
  fprintf(out,"%s\nreal\t%fus\nuser\t%fus\nsys\t%fus\n...................\n", operationName,((double)clk*1000000)/(CLOCKS_PER_SEC),((double)(endTime.tms_utime - startTime.tms_utime)*1000000)/CLOCKS_PER_SEC,((double)(endTime.tms_stime - startTime.tms_stime)*1000000)/CLOCKS_PER_SEC);
}


int main(int argc, char *argv[]){

#ifdef DLL
    void *uchwyt = dlopen(./"liblib.so", RTLD_LAZY);
//--------------------------------------------------------------------------------

  void (*budujTabelaStatic)(int) = dlsym(uchwyt, "budujTabelaStatic");
  int *(*usunTabelaStatic)(int) = dlsym(uchwyt, "usunTabelaStatic");

  void (*dodajBlokStatic)(int, int, int, char*) = dlsym(uchwyt, "dodajBlokStatic");
  void (*usunBlokStatic)(int, int) = dlsym(uchwyt, "usunBlok");
  int (*znajdzBlokStatic)(int, int) = dlsym(uchwyt, "znajdzBlok");

  void (*wypiszTabelaStatic)(int) =dlsym(uchwyt, "wypiszTabelaStatic");

//---------------------------------------------------------------------------------

  void **(*budujTabelaDynamic)(int) = dlsym(uchwyt, "budujTabelaDynamic");
  void (*usunTabelaDynamic)(void**, int) = dlsym(uchwyt, "usunTabelaDynamic");

  void **(*dodajBlokDynamic)(int, int, int, char*, void**) = dlsym(uchwyt, "dodajBlokDynamic");
  void **(*usunBlokDynamic)(void**, int, int) = dlsym(uchwyt, "usunBlokDynamic");
  int (*znajdzBlokDynamic)(void**, int, int) = dlsym(uchwyt, "znajdzBlokDynamic");

  void (*wypiszTabelaDynamic)(void**, int) =dlsym(uchwyt, "wypiszTabelaDynamic");

//---------------------------------------------------------------------------------

  blok *(*stworzBlok)(int, char*) = dlsym(uchwyt, "stworzBlok");
  void (*wypiszBlok)(blok*) = dlsym(uchwyt, "wypiszBlok");
  int (*wyliczSumaAscii)(char*) = dlsym(uchwyt, "wyliczSumaAscii");
  int (*getSumaAscii)(blok*) = dlsym(uchwyt, "getSumaAscii");
  blok *(*getBlok)(blok*) = dlsym(uchwyt, "getBlok");
#endif
//----------------------------------------------------------------------------------
clock_t clk;
struct tms startTime, endTime;

//----------------------------------------------------------------------------------


    int rozmiarTablicy = atoi(argv[1]);
    int rozmiarBloku = atoi(argv[2]);
    FILE* out = fopen(argv[3], "w");
    char* typ = argv[4];
    int index, number;
    void ** dTabela;
    int i, m, rozmiarInstrukcji = argc-5;
    struct instrukcja instrukcje[rozmiarInstrukcji];
    char* info;


    for(i = 5; i < argc; i++){
        instrukcje[i-5].zawartosc = argv[i];
        instrukcje[i-5].komenda = 0;
    }

    for(i = 0; i < rozmiarInstrukcji; i++){
        if(!strcmp(typ, "static")){
            if(!strcmp(instrukcje[i].zawartosc, "create_table")){
                instrukcje[i].komenda = 1;
            }
            if(!strcmp(instrukcje[i].zawartosc, "search")){
                instrukcje[i].komenda = 2;
                i++;
            }
            if(!strcmp(instrukcje[i].zawartosc, "remove")){
                instrukcje[i].komenda = 3;
                i++;
            }
            if(!strcmp(instrukcje[i].zawartosc, "add")){
                instrukcje[i].komenda = 4;
                i++;
            }
            if(!strcmp(instrukcje[i].zawartosc, "remove_and_add")){
                instrukcje[i].komenda = 5;
                i+=2;
            }
        }
        else{
            if(!strcmp(typ, "dynamic")){
                if(!strcmp(instrukcje[i].zawartosc, "create_table")){
                    instrukcje[i].komenda = 6;
                }
                if(!strcmp(instrukcje[i].zawartosc, "search")){
                    instrukcje[i].komenda = 7;
                    i++;
                }
                if(!strcmp(instrukcje[i].zawartosc, "remove")){
                    instrukcje[i].komenda = 8;
                    i++;
                }
                if(!strcmp(instrukcje[i].zawartosc, "add")){
                    instrukcje[i].komenda = 9;
                    i++;
                }
                if(!strcmp(instrukcje[i].zawartosc, "remove_and_add")){
                    instrukcje[i].komenda = 10;
                    i+=2;
                }
            }
            else{
                printf("Zly sposob alokacji pamieci\n");
            }
        }
    }


    for(i = 0; i < rozmiarInstrukcji; i++){
      times(&startTime);
      clk = clock();
        switch(instrukcje[i].komenda){
            case 0:
                continue;
                break;
            case 1:
                budujTabelaStatic(rozmiarTablicy);
                info = "Budowanie statyczne drzewa";
                break;
            case 2:
                number = atoi(instrukcje[i+1].zawartosc);
                int znalezione = znajdzBlokStatic(number, rozmiarTablicy);
                printf("Znaleziony blok:\n");
                wypiszBlok(tabela[znalezione]);
                info = "Znajdowanie statyczne drzewa";
                break;
            case 3:
                number = atoi(instrukcje[i+1].zawartosc);
                for(m = 0; m < number; m++){
                    usunBlokStatic(m, rozmiarTablicy);
                }
                info = "Usuwanie statyczne blokow z drzewa";
                break;
            case 4:
                number = atoi(instrukcje[i+1].zawartosc);
                for(m = 0; m < number; m++){
                    dodajBlokStatic(rozmiarTablicy, rozmiarBloku, m, generujChar(rozmiarBloku));
                }
                info = "Dodawanie statyczne blokow do drzewa";
                break;
            case 5:
                index = atoi(instrukcje[i+2].zawartosc);
                for(number = atoi(instrukcje[i+1].zawartosc); number > 0; number--){
                    usunBlokStatic(index, rozmiarTablicy);
                    printf("\nPozostalo prob nr: %d\n", number);
                    dodajBlokStatic(rozmiarTablicy, rozmiarBloku, number, generujChar(rozmiarBloku));
                }
                info = "Usuwanie i dodawanie statyczne blokow do drzewa";
                break;
            case 6:
                dTabela = budujTabelaDynamic(rozmiarTablicy);
                info = "Tworzenie dynamiczne drzewa";
                break;
            case 7:                                                                         //search
                number = atoi(instrukcje[i+1].zawartosc);
                index = znajdzBlokDynamic(dTabela, number , rozmiarTablicy);
                wypiszBlok(dTabela[index]);
                info = "Szukanie dynamiczne drzewa";
                break;
            case 8:
                number = atoi(instrukcje[i+1].zawartosc);
                for(m = 0; m < number; m++){
                    usunBlokDynamic(dTabela, m, rozmiarTablicy);
                }
                info = "Usuwanie dynamiczne blokow z drzewa";
                break;
            case 9:
                number = atoi(instrukcje[i+1].zawartosc);
                for(m = 0; m < number; m++){
                    dodajBlokDynamic(rozmiarTablicy, rozmiarBloku, m, generujChar(rozmiarBloku), dTabela);
                }
                info = "Dodawanie dynamiczne blokow do drzewa";
                break;
            case 10:
                index = atoi(instrukcje[i+2].zawartosc);
                for(number = atoi(instrukcje[i+1].zawartosc); number > 0; number--){
                    usunBlokDynamic(dTabela, index, rozmiarTablicy);
                    printf("\nPozostalo prob nr: %d\n", number);
                    dodajBlokDynamic(rozmiarTablicy, rozmiarBloku, index, generujChar(rozmiarBloku), dTabela);
                }
                info = "Usuwanie i dodawanie dynamiczne blokow z drzewa";
                break;
        }
        clk = clock() - clk;
          times(&endTime);
      	pokazCzas(out,clk,startTime,endTime,info);
    }

    printf("Sukces\n");
#ifdef DLL
    dlclose(uchwyt);
#endif
    return 0;
}
