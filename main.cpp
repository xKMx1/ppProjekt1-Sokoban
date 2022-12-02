#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

using namespace std;

struct level
{
};

const int mapX = 80;
const int mapY = 25;

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

void fillMap(char tab[mapY][mapX]) // Funkcja tymczasowa, zapełniamy tablicę zerami i haszami
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

void genHero(int y1, int y2, int x1, int x2, char tab[mapY][mapX]) // Dostajemy koordynaty które w przesłanej tablicy zamieniamy na znaki odpowiadające naszemu bohaterowi
{
     tab[y1][x1] = 135;
     tab[y1][x2] = 135;
     tab[y2][x1] = 135;
     tab[y2][x2] = 135;
}

void movement()
{
     char ruch = getchar();
     switch (ruch) // Zależnie od wcisniętego klawisza wykonuje instrukcję
     {             // WSAD (pruszanie się) - początek
     case 119:     // w
          cout << "w";
          break;
     case 115: // s
          cout << "s";
          break;
     case 97: // a
          cout << "a";
          break;
     case 100: // d
          cout << "d";
          break;
     case 87: // W
          cout << "W";
          break;
     case 83: // S
          cout << "S";
          break;
     case 65: // A
          cout << "A";
          break;
     case 68: // D
          cout << "D";
          break;
          // WSAD - koniec
     default:
          cout << "Został wciśnięty nieznany klawisz";
          break;
     }
}

void genMap1() // wypisujemy na ekran mapę
{
     system("cls");

     char Map[mapY][mapX];
     fillMap(Map);
     genHero(14, 15, 45, 46, Map);

     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               cout << Map[i][j];
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
          }
     }
}

int main()
{
     startScreen();
     genMenu();

     return 0;
}