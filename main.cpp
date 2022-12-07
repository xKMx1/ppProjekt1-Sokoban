#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

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

void genHero(int y, int x, char tab[mapY][mapX]) // Dostajemy koordynaty które w przesłanej tablicy zamieniamy na znaki odpowiadające naszemu bohaterowi
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               tab[y + i][x + j] = 135;
          }
     }
}

void genChest(int y, int x, char tab[mapY][mapX])
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               tab[y + i][x + j] = 35;
          }
     }
}

void fillMap1(char tab[mapY][mapX]) // funkcja wypełniająca mapę 1
{
     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               if (i == 0 || i == 1 || i == 24 || i == 23 || j == 0 || j == 79 || (j == 1 && i > 30 && i < 60))
               {
                    tab[i][j] = 178;
               }
               else
               {
                    tab[i][j] = 32;
               }
          }
     }
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
          cout << "\n";
     }
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

void action(int *y, int *x, int *b, int *a)
{
     cout << "Wprowadz znak: ";
     char znak = getch();
     cout << znak;

     if (znak == 119 || znak == 87) // instrukcje dla "W"
     {
          if (*y == *b + 3 && *x == *a)
          {
               *y -= 3;
               *b -= 3;
          }
          else
          {
               *y -= 3;
          }
     }

     if (znak == 115 || znak == 83) // instrukcje dla "S"
     {
          if (*y == *b - 3 && *x == *a)
          {
               *y += 3;
               *b += 3;
          }
          else
          {
               *y += 3;
          }
     }

     if (znak == 97 || znak == 65) // instrukcje dla "A"
     {
          if (*y == *b && *x == (*a + 3))
          {
               *x -= 3;
               *a -= 3;
          }
          else
          {
               *x -= 3;
          }
     }

     if (znak == 100 || znak == 68) // instrukcje dla "D"
     {
          if (*y == *b && *x == (*a - 3))
          {
               *x += 3;
               *a += 3;
          }
          else
          {
               *x += 3;
          }
     }
}

int main()
{
     char mainMap[mapY][mapX];
     int y = 14, x = 48;
     int a = 6, b = 8;

     // startScreen();
     if (genMenu() == 1)
     {
          fillMap1(mainMap);
          genHero(y, x, mainMap);
          genChest(b, a, mainMap);
          genMap1(mainMap);
          for (int i = 0; i < 500; i++)
          {
               action(&y, &x, &b, &a);
               fillMap1(mainMap);
               genHero(y, x, mainMap);
               genChest(b, a, mainMap);
               genMap1(mainMap);
          }
     }

     return 0;
}