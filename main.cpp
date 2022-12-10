#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct level
{
     int heroX;
     int heroY;
     int tempX;
     int tempY;
     int chestOneX;
     int chestOneY;
     int chestTwoX;
     int chestTwoY;
     int spotOneX;
     int spotOneY;
     int spotTwoX;
     int spotTwoY;
     int chest1;
     int chest2;
     int steps;
     int stepsUsed;
     int camX;
     int camY;
     char fileName[11];
};

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

     cout << "  /$$$$$$            /$$                 /$$                          " << endl;
     cout << " /$$__  $$          | $$                | $$                          " << endl;
     cout << "| $$  " << char(92) << "__/  /$$$$$$ | $$   /$$  /$$$$$$ | $$$$$$$   /$$$$$$  /$$$$$$$ " << endl;
     cout << "|  $$$$$$  /$$__  $$| $$  /$$/ /$$__  $$| $$__  $$ |____  $$| $$__  $$" << endl;
     cout << " " << char(92) << "____  $$| $$  " << char(92) << " $$| $$$$$$/ | $$  " << char(92) << " $$| $$  " << char(92) << " $$  /$$$$$$$| $$  " << char(92) << " $$" << endl;
     cout << " /$$  " << char(92) << " $$| $$  | $$| $$_  $$ | $$  | $$| $$  | $$ /$$__  $$| $$  | $$" << endl;
     cout << "|  $$$$$$/|  $$$$$$/| $$ " << char(92) << "  $$|  $$$$$$/| $$$$$$$/|  $$$$$$$| $$  | $$" << endl;
     cout << " " << char(92) << "______/  " << char(92) << "______/ |__/  " << char(92) << "__/ " << char(92) << "______/ |_______/  " << char(92) << "_______/|__/  |__/" << endl
          << endl;
     cout << "                        Kamil Ratajczyk s193345                                                                             ";

     Sleep(3000);
}

void genBlock(int y, int x, char tab[mapY][mapX], int var, int *chest)
{
     for (int i = 0; i < 3; i++) // generujemy blok 3x3 razem z koleinym forem
     {
          for (int j = 0; j < 3; j++)
          {
               if (var == 0) // jeśli zostało podane 0 na wejście generujemy miejsce spotu
               {
                    tab[y + i][x + j] = 33;
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

void fillMap(char tab[mapY][mapX], char path[11]) // funkcja wypełniająca mapę 1
{
     fstream file;

     file.open(path);

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

void genMap(char tab[mapY][mapX], int *cameraX, int *cameraY) // wypisujemy na ekran mapę
{
     ClearScreen();

     for (int i = *cameraY; i < *cameraY + 25; i++)
     {
          for (int j = *cameraX; j < *cameraX + 80; j++)
          {
               cout << tab[i][j];
          }
          cout << "\n";
     }
     cout << "\n";
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

void action(int *y, int *x, int *cx1, int *cy1, int *cx2, int *cy2, int *sx1, int *sy1, int *sx2, int *sy2, int &chest1, int &chest2, int *cameraX, int *cameraY, char tab[mapY][mapX])
{
     cout << "Wprowadz znak: ";
     char znak = getch();
     cout << znak;

     if (znak == 119 || znak == 87) // instrukcje dla "W" i "w" RUCH GÓRA
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

     if (znak == 115 || znak == 83) // instrukcje dla "S" i "s" RUCH DÓŁ
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

     if (znak == 97 || znak == 65) // instrukcje dla "A" i "a" RUCH LEWO
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

     if (znak == 100 || znak == 68) // instrukcje dla "D" i "d" RUCH PRAWO
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

     if (znak == 106 || znak == 74) // instrukcja dla "J" i "j" KAMERA LEWO
     {
          if (*cameraX != 0) // ogranicza wyjście kamery za mapę
          {
               (*cameraX)--;
          }
     }

     if (znak == 107 || znak == 75) // instrukcja dla "K" i "k" KAMERA PRAWO
     {
          if (*cameraX != 39) // ogranicza wyjście kamery za mapę
          {
               (*cameraX)++;
          }
     }

     if (znak == 105 || znak == 73) // instrukcja dla "I" i "i" KAMERA GÓRA
     {
          if (*cameraY != 0) // ogranicza wyjście kamery za mapę
          {
               (*cameraY)--;
          }
     }

     if (znak == 109 || znak == 77) // instrukcja dla "M" i "m" KAMERA DÓŁ
     {
          if (*cameraY != 10) // ogranicza wyjście kamery za mapę
          {
               (*cameraY)++;
          }
     }

     if (znak == 113 || znak == 81) // instrukcja dla "Q" i "q" MENU
     {
          cout << "Do naprawienia";
     }

     onSpot(cx1, cy1, cx2, cy2, sx1, sy1, sx2, sy2, chest1, chest2);
}

void schowSteps(int *heroX, int *heroY, int *tempX, int *tempY, int steps, int *stepsUsed) // Wyświetlanie liczby kroków i logika związana z krokami
{
     int stepsLeft;

     if (*heroX != *tempX || *heroY != *tempY)
     {
          *tempX == *heroX;
          *tempY == *heroY;
          (*stepsUsed)++;
     }
     stepsLeft = steps - *stepsUsed;
     cout << "Pozostalo krokow: " << stepsLeft << " \n";

     if (stepsLeft == 0)
     {
          system("CLS");
          cout << "PRZEGRANA"
               << "\n"
               << "BRAK RUCHOW";
          getchar();
     }
}

void genLevel(char tab[mapY][mapX], level lvl)
{
     while (1)
     {
          fillMap(tab, lvl.fileName);
          genBlock(lvl.spotOneY, lvl.spotOneX, tab, 0, &lvl.chest1);
          genBlock(lvl.spotTwoY, lvl.spotTwoX, tab, 0, &lvl.chest2);
          genBlock(lvl.heroY, lvl.heroX, tab, 2, &lvl.chest1);
          genBlock(lvl.chestOneY, lvl.chestOneX, tab, 1, &lvl.chest1);
          genBlock(lvl.chestTwoY, lvl.chestTwoX, tab, 1, &lvl.chest2);
          genMap(tab, &lvl.camX, &lvl.camY);
          schowSteps(&lvl.heroX, &lvl.heroY, &lvl.tempX, &lvl.tempY, lvl.steps, &lvl.stepsUsed);
          action(&lvl.heroY, &lvl.heroX, &lvl.chestOneX, &lvl.chestOneY, &lvl.chestTwoX, &lvl.chestTwoY, &lvl.spotOneX, &lvl.spotOneY, &lvl.spotTwoX, &lvl.spotTwoY, lvl.chest1, lvl.chest2, &lvl.camX, &lvl.camY, tab);

          if (lvl.chest1 == 36 && lvl.chest2 == 36)
          {
               break;
          }
     }
}

int genMenu(char tab[mapY][mapX], level lvl1, level lvl2, level lvl3)
{
     system("cls");
     cout << "Wybierz:"
          << "\n";
     cout << "(1) Wybierz poziom"
          << "\n";
     cout << "(2) Opusc gre"
          << "\n";

     while (1)
     {
          char znak;
          cin >> znak;

          if (znak == 49)
          {
               system("CLS");
               cout << "Wybierz: "
                    << "\n"
                    << "(1) Poziom 1"
                    << "\n"
                    << "(2) Poziom 2"
                    << "\n"
                    << "(3) Poziom 3"
                    << "\n";

               cin >> znak;
               if (znak == 49)
               {
                    genLevel(tab, lvl1);
               }
               if (znak == 50)
               {
                    genLevel(tab, lvl2);
               }
               if (znak == 51)
               {
                    genLevel(tab, lvl3);
               }
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
               genMenu(tab, lvl1, lvl2, lvl3);
          }
     }
}

int main()
{
     char mainMap[mapY][mapX];

     level lvlOne;
     level lvlTwo;
     level lvlThree;

     lvlOne.heroX = 24; // Definicja wartości dla pierwszego poziomu
     lvlOne.heroY = 17;
     lvlOne.tempX = 24;
     lvlOne.tempY = 17;
     lvlOne.chestOneX = 39;
     lvlOne.chestOneY = 8;
     lvlOne.chestTwoX = 39;
     lvlOne.chestTwoY = 11;
     lvlOne.spotOneX = 27;
     lvlOne.spotOneY = 5;
     lvlOne.spotTwoX = 30;
     lvlOne.spotTwoY = 5;
     lvlOne.chest1 = 35;
     lvlOne.chest2 = 35;
     lvlOne.steps = 25;
     lvlOne.stepsUsed = 0;
     lvlOne.camX = 0;
     lvlOne.camY = 0;
     strcpy(lvlOne.fileName, "level1.txt");

     lvlTwo.heroY = 13; // Definicja wartości dla drugiego poziomu
     lvlTwo.heroX = 23;
     lvlTwo.tempX = 23;
     lvlTwo.tempY = 13;
     lvlTwo.chestOneX = 68;
     lvlTwo.chestOneY = 7;
     lvlTwo.chestTwoX = 80;
     lvlTwo.chestTwoY = 19;
     lvlTwo.spotOneX = 8;
     lvlTwo.spotOneY = 4;
     lvlTwo.spotTwoX = 26;
     lvlTwo.spotTwoY = 4;
     lvlTwo.chest1 = 35;
     lvlTwo.chest2 = 35;
     lvlTwo.steps = 60;
     lvlTwo.stepsUsed = 0;
     lvlTwo.camX = 0;
     lvlTwo.camY = 0;
     strcpy(lvlTwo.fileName, "level2.txt");

     lvlThree.heroY = 21; // Definicja wartości dla trzeciego poziomu
     lvlThree.heroX = 23;
     lvlThree.tempX = 23;
     lvlThree.tempY = 23;
     lvlThree.chestOneX = 35;
     lvlThree.chestOneY = 24;
     lvlThree.chestTwoX = 92;
     lvlThree.chestTwoY = 21;
     lvlThree.spotOneX = 89;
     lvlThree.spotOneY = 3;
     lvlThree.spotTwoX = 89;
     lvlThree.spotTwoY = 6;
     lvlThree.chest1 = 35;
     lvlThree.chest2 = 35;
     lvlThree.steps = 400;
     lvlThree.stepsUsed = 0;
     lvlThree.camX = 0;
     lvlThree.camY = 0;
     strcpy(lvlThree.fileName, "level3.txt");

     // startScreen();

     genMenu(mainMap, lvlOne, lvlTwo, lvlThree);

     return 0;
}