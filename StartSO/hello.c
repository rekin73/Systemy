/* 
 Program wypisuje w losowo wybranych miejscach na ekranie: Hello world!
 ----------------------------------------------------------------------
 Autor: Wieslaw Placzek,                             Krakow, 18.02.2020
 ----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define XMAX 70      // Maksymalna liczba kolumn ekranu 
#define YMAX 30      // Maksymalna liczba wierszy ekranu
#define NMAX 10      // Liczba wypisan na ekran

/*
  =========================================================================
  Ustawienie pozycji kursora w punkcie o wspolrzednych (x,y) na ekranie,
  gdzie x - liczba kolumn (od lewej), y - liczba wierszy (od gory).
  Sekwencja \033[2K powoduje wymazanie poprzedniego napisu w danym wierszu.
  =========================================================================
*/
void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y, x);
}

int main()
{
  int x, y;                // wspolrzedne kursora 

  printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
  printf("    ---- Nacisnij klawisz [Enter], aby wystartowac! ----   ");
  getchar();
  printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania

  system("clear");         // Wyczysc ekran
  srand(23);               // Zainicjuj generator liczb losowych
  printf("\033[1;4m");     // Wlacz pogrubienie i podkreslenie

  // Powtarzaj wypisywanie NMAX razy
  int i;
  for (i = 0; i < NMAX; i++) {
    // Wybieraj losowo wspolrzedne kursora (x,y)
    x = 1 + (int) ( 1.0*XMAX*rand()/(RAND_MAX + 1.0) );
    y = 1 + (int) ( 1.0*YMAX*rand()/(RAND_MAX + 1.0) );
    gotoxy(x, y);
    printf("Hello World!\n");
    sleep(1);              // Poczekaj chwile
  } // for

  printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
  gotoxy(0, YMAX+1);

  return 0;
}

