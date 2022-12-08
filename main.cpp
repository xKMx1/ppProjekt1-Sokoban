#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

const int mapX = 120;
const int mapY = 35;

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

void genBlock(int y, int x, char tab[mapY][mapX], int var, int *chest)
{
     for (int i = 0; i < 3; i++) // generujemy blok 3x3 razem z koleinym forem
     {
          for (int j = 0; j < 3; j++)
          {
               if (var == 0) // jeśli zostało podane 0 na wejście generujemy miejsce spotu
               {
                    tab[y + i][x + j] = 32;
               }
               else if (var == 1) // jeśli została podana na wejście jedynka generujemy skrzynię
               {
                    tab[y + i][x + j] = *chest;
               }
               else if (var == 2) // jeśli została podana na wejście dwójka generujemy bohatera
               {
                    tab[y + i][x + j] = 135;
               }
          }
     }
}

void fillMap1(char tab[mapY][mapX]) // funkcja wypełniająca mapę 1
{
     fstream file;

     file.open("level1.txt");

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

void fillMap2(char tab[mapY][mapX]) // funkcja wypełniająca mapę 2
{
     fstream file;

     file.open("level2.txt");

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

void genMap(char tab[mapY][mapX]) // wypisujemy na ekran mapę
{
     ClearScreen();

     for (int i = 4; i < 24; i++)
     {
          for (int j = 0; j < 80; j++)
          {
               cout << tab[i][j];
          }
          cout << "\n";
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

void onSpot(int *cx1, int *cy1, int *cx2, int *cy2, int *sx1, int *sy1, int *sx2, int *sy2, int &chest1, int &chest2)
{
     if ((*cx1 == *sx1 && *cy1 == *sy1) || (*cx1 == *sx2 && *cy1 == *sy2)) // Sprawdza czy pierwsza skrzynia znajduje się na pierwszym miejscu docelowym
     {
          chest1 = 36;
     }
     else
          chest1 = 35;

     if ((*cx2 == *sx1 && *cy2 == *sy1) || (*cx2 == *sx2 && *cy2 == *sy2)) // Sprawdza czy druga skrzynia znajduje się na pierwszym miejscu docelowym
     {
          chest2 = 36;
     }
     else
          chest2 = 35;
}

void action(int *y, int *x, int *cx1, int *cy1, int *cx2, int *cy2, int *sx1, int *sy1, int *sx2, int *sy2, int &chest1, int &chest2, char tab[mapY][mapX])
{
     cout << "Wprowadz znak: ";
     char znak = getch();
     cout << znak;

     if (znak == 119 || znak == 87) // instrukcje dla "W"
     {
          if (tab[*y - 1][*x] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (*y == *cy1 + 3 && *x == *cx1) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if ((tab[*y - 4][*x] != 48) && (tab[*y - 4][*x] != 35) && (tab[*y - 4][*x] != 36)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *y -= 3;
                         *cy1 -= 3;
                    }
               }
               else if (*y == *cy2 + 3 && *x == *cx2) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[*y - 4][*x] != 48 && (tab[*y - 4][*x] != 35) && (tab[*y - 4][*x] != 36)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *y -= 3;
                         *cy2 -= 3;
                    }
               }
               else
               {
                    *y -= 3;
               }
          }
     }

     if (znak == 115 || znak == 83) // instrukcje dla "S"
     {
          if (tab[*y + 3][*x] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (*y == *cy1 - 3 && *x == *cx1) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[*y + 6][*x] != 48 && tab[*y + 6][*x] != 35 && tab[*y + 6][*x] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *y += 3;
                         *cy1 += 3;
                    }
               }
               else if (*y == *cy2 - 3 && *x == *cx2) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[*y + 6][*x] != 48 && tab[*y + 6][*x] != 35 && tab[*y + 6][*x] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *y += 3;
                         *cy2 += 3;
                    }
               }
               else
               {
                    *y += 3;
               }
          }
     }

     if (znak == 97 || znak == 65) // instrukcje dla "A"
     {
          if (tab[*y][*x - 1] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {

               if (*y == *cy1 && *x == (*cx1 + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[*y][*x - 4] != 48 && tab[*y][*x - 4] != 35 && tab[*y][*x - 4] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *x -= 3;
                         *cx1 -= 3;
                    }
               }
               else if (*y == *cy2 && *x == (*cx2 + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[*y][*x - 4] != 48 && tab[*y][*x - 4] != 35 && tab[*y][*x - 4] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *x -= 3;
                         *cx2 -= 3;
                    }
               }
               else
               {
                    *x -= 3;
               }
          }
     }

     if (znak == 100 || znak == 68) // instrukcje dla "D"
     {
          if (tab[*y][*x + 3] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (*y == *cy1 && *x == (*cx1 - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[*y][*x + 6] != 48 && tab[*y][*x + 6] != 35 && tab[*y][*x + 6] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *x += 3;
                         *cx1 += 3;
                    }
               }
               else if (*y == *cy2 && *x == (*cx2 - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[*y][*x + 6] != 48 && tab[*y][*x + 6] != 35 && tab[*y][*x + 6] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         *x += 3;
                         *cx2 += 3;
                    }
               }
               else
               {
                    *x += 3;
               }
          }
     }

     onSpot(cx1, cy1, cx2, cy2, sx1, sy1, sx2, sy2, chest1, chest2);
}

void level(char tab[mapY][mapX])
{
     int lvl = 1;

     if (lvl == 1)
     {
          int heroX = 24, heroY = 17;
          int chestOneX = 39, chestOneY = 8;
          int chestTwoX = 39, chestTwoY = 11;
          int spotOneX = 27, spotOneY = 5;
          int spotTwoX = 30, spotTwoY = 5;
          int chest1 = 35;
          int chest2 = 35;
          int steps = 500;

          for (int i = 1; i < steps + 1; i++)
          {
               fillMap1(tab);
               genBlock(spotOneY, spotOneX, tab, 0, &chest1);
               genBlock(spotTwoY, spotTwoX, tab, 0, &chest2);
               genBlock(heroY, heroX, tab, 2, &chest1);
               genBlock(chestOneY, chestOneX, tab, 1, &chest1);
               genBlock(chestTwoY, chestTwoX, tab, 1, &chest2);
               cout << (steps - i); // wypisujemy na ekran pozostałe kroki
               genMap(tab);
               action(&heroY, &heroX, &chestOneX, &chestOneY, &chestTwoX, &chestTwoY, &spotOneX, &spotOneY, &spotTwoX, &spotTwoY, chest1, chest2, tab);
               if (chest1 == 36 && chest2 == 36)
               {
                    lvl++;
                    break;
               }
          }
     }
     if (lvl == 2)
     {
          int heroX = 24, heroY = 17;
          int chestOneX = 39, chestOneY = 8;
          int chestTwoX = 39, chestTwoY = 11;
          int spotOneX = 27, spotOneY = 5;
          int spotTwoX = 30, spotTwoY = 5;
          int chest1 = 35;
          int chest2 = 35;
          int steps = 500;

          for (int i = 1; i < steps + 1; i++)
          {
               fillMap2(tab);
               genBlock(spotOneY, spotOneX, tab, 0, &chest1);
               genBlock(spotTwoY, spotTwoX, tab, 0, &chest2);
               genBlock(heroY, heroX, tab, 2, &chest1);
               genBlock(chestOneY, chestOneX, tab, 1, &chest1);
               genBlock(chestTwoY, chestTwoX, tab, 1, &chest2);
               cout << (steps - i); // wypisujemy na ekran pozostałe kroki
               genMap(tab);
               action(&heroY, &heroX, &chestOneX, &chestOneY, &chestTwoX, &chestTwoY, &spotOneX, &spotOneY, &spotTwoX, &spotTwoY, chest1, chest2, tab);
               if (chest1 == 36 && chest2 == 36)
               {
                    lvl++;
                    break;
               }
          }
     }
}

int main()
{
     char mainMap[mapY][mapX];

     // startScreen();

     if (genMenu() == 1)
     {
          level(mainMap);
     }

     return 0;
}
