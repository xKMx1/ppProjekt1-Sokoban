#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

const int mapX = 80;
const int mapY = 25;

void ClearScreen()
{
     COORD cursorPosition;
     cursorPosition.X = 0;
     cursorPosition.Y = 0;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void startScreen()
{ // funkcja wyswietlajaca ekran powitalny
     system("CLS");
     cout << "\n"
          << "SOKOBAN"
          << "\n";
     cout << "Kamil Ratajczyk"
          << "\n";
     cout << "s193345"
          << "\n";

     Sleep(1000);
     system("CLS");
}

void genBlock(int y, int x, char tab[mapY][mapX], int var)
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               if (var == 0)
               { // generate spot
                    tab[y + i][x + j] = 38;
               }
               else if (var == 1)
               { // generate chest
                    tab[y + i][x + j] = 35;
               }
               else if (var == 2)
               { // generate hero
                    tab[y + i][x + j] = 135;
               }
          }
     }
}

void fillMap1(char tab[mapY][mapX]) // funkcja wypełniająca mapę 1
{
     fstream file;

     file.open("blank.txt");

     if (!file)
     {
          cout << "Pobranie mapy z pliku się nie powiodło";
          exit(0);
     }

     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               tab[i][j] = file.get();
          }
     }

     file.close();
}

void genMap1(char tab[mapY][mapX]) // wypisujemy na ekran mapę
{
     ClearScreen();

     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               cout << tab[i][j];
          }
     }
     cout << "\n";
}

int genMenu()
{
     system("cls");
     cout << "Wybierz:"
          << "\n";
     cout << "(1) Rozpocznij gre od pierwszego etapu"
          << "\n";
     cout << "(2) Opusc gre"
          << "\n";

     while (1)
     {
          char znak = getchar();

          if (znak == 49)
          {
               return 1;
          }
          else if (znak == 50)
          {
               exit(0);
          }
          else
          {
               cout << "Wybrales niepoprawny znak! Mozesz wybrac 1 lub 2."
                    << "\n";
               Sleep(1000);
               genMenu();
          }
     }
}

bool onSpot(int *cx1, int *cy1, int *cx2, int *cy2, int *sx1, int *sy1, int *sx2, int *sy2)
{
     if ((*cx1 == (*sx1 || *sx2) && *cy1 == (*sy1 || *sy2)) || (*cx2 == (*sx1 || *sx2) && *cy2 == (*sy1 || *sy2)))
     {
          return 1;
     }
}

void action(int *y, int *x, int *cx1, int *cy1, int *cx2, int *cy2)
{
     cout << "Wprowadz znak: ";
     char znak = getch();
     cout << znak;

     if (znak == 119 || znak == 87) // instrukcje dla "W"
     {
          if (*y == *cx1 + 3 && *x == *cy1)
          {
               *y -= 3;
               *cx1 -= 3;
          }
          else if (*y == *cx2 + 3 && *x == *cy2)
          {
               *y -= 3;
               *cx2 -= 3;
          }
          else
          {
               *y -= 3;
          }
     }

     if (znak == 115 || znak == 83) // instrukcje dla "S"
     {
          if (*y == *cx1 - 3 && *x == *cy1)
          {
               *y += 3;
               *cx1 += 3;
          }
          else if (*y == *cx2 - 3 && *x == *cy2)
          {
               *y += 3;
               *cx2 += 3;
          }
          else
          {
               *y += 3;
          }
     }

     if (znak == 97 || znak == 65) // instrukcje dla "A"
     {
          if (*y == *cx1 && *x == (*cy1 + 3))
          {
               *x -= 3;
               *cy1 -= 3;
          }
          else if (*y == *cx2 && *x == (*cy2 + 3))
          {
               *x -= 3;
               *cy2 -= 3;
          }
          else
          {
               *x -= 3;
          }
     }

     if (znak == 100 || znak == 68) // instrukcje dla "D"
     {
          if (*y == *cx1 && *x == (*cy1 - 3))
          {
               *x += 3;
               *cy1 += 3;
          }
          else if (*y == *cx2 && *x == (*cy2 - 3))
          {
               *x += 3;
               *cy2 += 3;
          }
          else
          {
               *x += 3;
          }
     }
}

void level(int lvl, char tab[mapY][mapX])
{
     if (lvl == 1)
     {
          int heroX = 24, heroY = 17;
          int chestOneX = 39, chestOneY = 8;
          int chestTwoX = 39, chestTwoY = 11;
          int spotOneX = 27, spotOneY = 5;
          int spotTwoX = 30, spotTwoY = 5;
          int steps = 500;

          for (int i = 0; i < steps; i++)
          {
               fillMap1(tab);
               genBlock(heroY, heroX, tab, 2);
               genBlock(chestOneY, chestOneX, tab, 1);
               genBlock(chestTwoY, chestTwoX, tab, 1);
               genBlock(spotOneY, spotOneX, tab, 0);
               genBlock(spotTwoY, spotTwoX, tab, 0);
               genMap1(tab);
               action(&heroY, &heroX, &chestOneY, &chestOneX, &chestTwoY, &chestTwoX);
               if (onSpot(&chestOneX, &chestOneY, &chestTwoX, &chestTwoY, &spotOneX, &spotOneY, &spotTwoX, &spotTwoY))
               {
                    tab[24][79] = 45;
               }
               genMap1(tab);
               Sleep(1000);
          }
     }
}

int main()
{
     char mainMap[mapY][mapX];

     // startScreen();

     if (genMenu() == 1)
     {
          level(1, mainMap);
     }

     return 0;
}