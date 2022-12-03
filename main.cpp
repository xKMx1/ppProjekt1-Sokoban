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

void genHero(int y1, int y2, int x1, int x2, char tab[mapY][mapX]) // Dostajemy koordynaty które w przesłanej tablicy zamieniamy na znaki odpowiadające naszemu bohaterowi
{
     tab[y1][x1] = 135;
     tab[y1][x2] = 135;
     tab[y2][x1] = 135;
     tab[y2][x2] = 135;
}

void fillMap1(char tab[mapY][mapX]) // funkcja wypełniająca mapę 1
{
     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               if (i == 0 && j == 0 || i == 0 && j == 79 || i == 24 && j == 0 || i == 24 && j == 79)
               {
                    tab[i][j] = '#';
               }
               else
               {
                    tab[i][j] = '0';
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

void action(int *b1, int *b2, int *a1, int *a2)
{
     cout << "Wprowadz znak: ";
     char znak = getch();
     cout << znak;

     if (znak == 119) // instrukcje dla 'w'
     {
          *b1 -= 1;
          *b2 -= 1;
     }
     if (znak == 87) // instrukcje dla 'W'
     {
          *b1 -= 1;
          *b2 -= 1;
     }
     if (znak == 115) // instrukcje dla 's'
     {
          *b1 += 1;
          *b2 += 1;
     }
     if (znak == 83) // instrukcje dla 'S'
     {
          *b1 += 1;
          *b2 += 1;
     }
     if (znak == 97) // instrukcje dla 'a'
     {
          *a1 -= 1;
          *a2 -= 1;
     }
     if (znak == 65) // instrukcje dla 'A'
     {
          *a1 -= 1;
          *a2 -= 1;
     }
     if (znak == 100) // instrukcje dla 'd'
     {
          *a1 += 1;
          *a2 += 1;
     }
     if (znak == 68) // instrukcje dla 'D'
     {
          *a1 += 1;
          *a2 += 1;
     }
}

int main()
{
     char mainMap[mapY][mapX];
     int y1 = 14, y2 = 15, x1 = 48, x2 = 49;
     // startScreen();

     if (genMenu() == 1)
     {
          fillMap1(mainMap);
          genHero(y1, y2, x1, x2, mainMap);
          genMap1(mainMap);
          for (int i = 0; i < 50; i++)
          {
               action(&y1, &y2, &x1, &x2);
               fillMap1(mainMap);
               genHero(y1, y2, x1, x2, mainMap);
               genMap1(mainMap);
          }
     }

     getchar();
     return 0;
}