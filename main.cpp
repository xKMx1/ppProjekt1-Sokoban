#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm>

using namespace std;

struct level
{
     int lvlId;
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
     int chestPictoBad;
     int chestPictoGood;
     int steps;
     int stepsUsed;
     int camX;
     int camY;
     bool locked;
     char fileName[11];
};

const int mapX = 120;
const int mapY = 35;
const int tabX = 10;
const int tabY = 2;

void ClearScreen()
{
     COORD cursorPosition;
     cursorPosition.X = 0;
     cursorPosition.Y = 0;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void startScreen();
void endScreen();
void winScreen();
void winCheck(int *chestPicto1, int *chestPicto2, level lvl1, level lvl2, level lvl3);
void fillTable(int tab[tabX][tabY]);
void genBlock(int y, int x, char tab[mapY][mapX], int var, int *chest);
void fillMap(char tab[mapY][mapX], char path[11]);
void genMap(char tab[mapY][mapX], int *cameraX, int *cameraY);
void onSpot(level lvl);
void schowSteps(int *heroX, int *heroY, int *tempX, int *tempY, int steps, int *stepsUsed, bool flag);
void genLevel(char tab[mapY][mapX], level lvl, level lvl1, level lvl2, level lvl3);
void genMenu(char tab[mapY][mapX], level lvl1, level lvl2, level lvl3);
void action(level *lvl, level lvl1, level lvl2, level lvl3, int pastMoves[tabX][tabY], int *counter, int *z, bool *flag, char tab[mapY][mapX]);

int main()
{
     char mainMap[mapY][mapX];

     level lvlOne;
     level lvlTwo;
     level lvlThree;

     lvlOne.lvlId = 1; // Definicja wartości dla pierwszego poziomu
     lvlOne.heroX = 24;
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
     lvlOne.chestPictoBad = 35;
     lvlOne.chestPictoGood = 35;
     lvlOne.steps = 50;
     lvlOne.stepsUsed = 0;
     lvlOne.camX = 0;
     lvlOne.camY = 0;
     lvlOne.locked = false;
     strcpy(lvlOne.fileName, "level1.txt");

     lvlTwo.lvlId = 2; // Definicja wartości dla drugiego poziomu
     lvlTwo.heroY = 13;
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
     lvlTwo.chestPictoBad = 35;
     lvlTwo.chestPictoGood = 35;
     lvlTwo.steps = 160;
     lvlTwo.stepsUsed = 0;
     lvlTwo.camX = 0;
     lvlTwo.camY = 0;
     lvlTwo.locked = true;
     strcpy(lvlTwo.fileName, "level2.txt");

     lvlThree.lvlId = 3; // Definicja wartości dla trzeciego poziomu
     lvlThree.heroY = 21;
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
     lvlThree.chestPictoBad = 35;
     lvlThree.chestPictoGood = 35;
     lvlThree.steps = 400;
     lvlThree.stepsUsed = 0;
     lvlThree.camX = 0;
     lvlThree.camY = 0;
     lvlThree.locked = true;
     strcpy(lvlThree.fileName, "level3.txt");

     // startScreen();

     genMenu(mainMap, lvlOne, lvlTwo, lvlThree);

     return 0;
}

void startScreen() // funkcja wyswietlajaca ekran powitalny
{
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
     cout << "                        Kamil Ratajczyk s193345" << endl
          << endl;
     cout << "                   Wyslij dowolny znak aby rozpoczac" << endl;
     getchar();
}

void endScreen() // funkcja wyswietlajaca ekran przegranej
{
     char a;
     system("CLS");
     cout << "PRZEGRALES!" << endl;
     cout << "BRAK KROKOW" << endl;
     cin >> a;
     exit(1);
}

void winScreen() // funkcja wyswietlajaca ekran wygranej
{
     char a;
     system("CLS");
     cout << "WYGRALES!" << endl;
     cout << "GRATULACJE" << endl;
     cin >> a;
     exit(1);
}

void winCheck(char tab[mapY][mapX], int *chestPicto1, int *chestPicto2, level lvl, level lvl1, level lvl2, level lvl3)
{
     if (lvl.chestPictoBad == 36 && lvl.chestPictoGood == 36)
     {
          if (lvl.lvlId == lvl1.lvlId)
          {
               lvl2.locked = false;
               genMenu(tab, lvl1, lvl2, lvl3);
          }
          if (lvl.lvlId == lvl2.lvlId)
          {
               lvl3.locked = false;
               genMenu(tab, lvl1, lvl2, lvl3);
          }
          if (lvl.lvlId == lvl3.lvlId)
          {
               winScreen();
          }
     }
}

void genBlock(int y, int x, char tab[mapY][mapX], int var, int *chest) // funkcja generująca blok w podanym miejscu
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

void fillMap(char tab[mapY][mapX], char path[11]) // funkcja wypełniająca mapę danymi z podnaego pliku
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

void genMap(char tab[mapY][mapX], int *cameraX, int *cameraY) // funkcja wypisujaca na ekran mapę
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

void onSpot(level lvl) // funkcja sprawdzająca położenie skrzyń
{
     if ((lvl.chestOneX == lvl.spotOneX && lvl.chestOneY == lvl.spotOneY) || (lvl.chestOneX == lvl.spotTwoX && lvl.chestOneY == lvl.spotTwoY)) // Sprawdza czy pierwsza skrzynia znajduje się na miejscu docelowym
     {                                                                                                                                         // Zamieniamy tutaj piktogram skrzyni
          lvl.chestPictoBad = 36;
     }
     else
          lvl.chestPictoBad = 35;

     if ((lvl.chestTwoX == lvl.spotOneX && lvl.chestTwoY == lvl.spotOneY) || (lvl.chestTwoX == lvl.spotTwoX && lvl.chestTwoY == lvl.spotTwoY)) // Sprawdza czy druga skrzynia znajduje się na miejscu docelowym
     {
          lvl.chestPictoGood = 36;
     }
     else
          lvl.chestPictoGood = 35;
}

void schowSteps(int *heroX, int *heroY, int *tempX, int *tempY, int steps, int *stepsUsed, int pastMoves[tabX][tabY], int *counter, bool flag) // Wyświetlanie liczby kroków i logika związana z krokami
{
     int stepsLeft;

     if (*heroX != *tempX || *heroY != *tempY)
     {
          if (flag == false)
          {
               (*counter)++;
          }

          pastMoves[*counter - 1][0] = *tempX;
          pastMoves[*counter - 1][1] = *tempY;

          *tempX = *heroX;
          *tempY = *heroY;
          (*stepsUsed)++;

          if (*counter == 10)
          {
               *counter = 0;
          }
     }

     stepsLeft = steps - *stepsUsed;
     cout << "Pozostalo krokow: " << stepsLeft << " \n";

     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 2; j++)
          {
               cout << pastMoves[i][j] << " ";
          }
          cout << "\n";
     }

     if (stepsLeft == 0)
     {
          endScreen();
     }
}

void fillTable(int tab[tabX][tabY])
{
     for (int i = 0; i < tabX; i++)
     {
          for (int j = 0; j < tabY; j++)
          {
               tab[i][j] = 0;
          }
     }
}

void genLevel(char tab[mapY][mapX], level lvl, level lvl1, level lvl2, level lvl3)
{
     int pastMoves[tabX][tabY];
     int counter = 0;
     int z = 1;
     bool lastMoveUndo = false;

     fillTable(pastMoves);

     while (1)
     {
          fillMap(tab, lvl.fileName);
          genBlock(lvl.spotOneY, lvl.spotOneX, tab, 0, &lvl.chestPictoBad);
          genBlock(lvl.spotTwoY, lvl.spotTwoX, tab, 0, &lvl.chestPictoGood);
          genBlock(lvl.heroY, lvl.heroX, tab, 2, &lvl.chestPictoBad);
          genBlock(lvl.chestOneY, lvl.chestOneX, tab, 1, &lvl.chestPictoBad);
          genBlock(lvl.chestTwoY, lvl.chestTwoX, tab, 1, &lvl.chestPictoGood);
          genMap(tab, &lvl.camX, &lvl.camY);
          schowSteps(&lvl.heroX, &lvl.heroY, &lvl.tempX, &lvl.tempY, lvl.steps, &lvl.stepsUsed, pastMoves, &counter, lastMoveUndo);
          action(&lvl, lvl1, lvl2, lvl3, pastMoves, &counter, &z, &lastMoveUndo, tab);
          winCheck(tab, &lvl.chestPictoBad, &lvl.chestPictoGood, lvl, lvl1, lvl2, lvl3);
     }
}

void genMenu(char tab[mapY][mapX], level lvl1, level lvl2, level lvl3)
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
          int dot1 = 248, dot2 = 248;
          cin >> znak;

          if (lvl2.locked == false) // odpowiada za kropki w menu sygnalizujace czy odblokowalismy poziom
          {
               dot1 = 42;
          }
          if (lvl3.locked == false)
          {
               dot2 = 42;
          }

          if (znak == 49)
          {
               system("CLS");
               cout << "Wybierz: "
                    << "\n"
                    << "(1) Poziom 1 " << static_cast<char>(42)
                    << "\n"
                    << "(2) Poziom 2 " << static_cast<char>(dot1)
                    << "\n"
                    << "(3) Poziom 3 " << static_cast<char>(dot2)
                    << "\n";

               cin >> znak;
               if (znak == 49)
               {
                    genLevel(tab, lvl1, lvl1, lvl2, lvl3);
               }
               if (znak == 50)
               {
                    if (lvl2.locked != true)
                    {
                         genLevel(tab, lvl2, lvl1, lvl2, lvl3);
                    }
                    else
                    {
                         cout << "Nie odblokowales jeszcze tego poziomu!";
                         Sleep(3000);
                         genMenu(tab, lvl1, lvl2, lvl3);
                    }
               }
               if (znak == 51)
               {
                    if (lvl3.locked != true)
                    {
                         genLevel(tab, lvl3, lvl1, lvl2, lvl3);
                    }
                    else
                    {
                         cout << "Nie odblokowales jeszcze tego poziomu!";
                         Sleep(3000);
                         genMenu(tab, lvl1, lvl2, lvl3);
                    }
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

void action(level *lvl, level lvl1, level lvl2, level lvl3, int pastMoves[tabX][tabY], int *counter, int *z, bool *flag, char tab[mapY][mapX])
{
     cout << "Wprowadz znak: ";
     char znak = getch();

     cout << znak;

     if (znak == 119 || znak == 87) // instrukcje dla "W" i "w" RUCH GÓRA
     {
          if (tab[lvl->heroY - 1][lvl->heroX] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY + 3 && lvl->heroX == lvl->chestOneX) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if ((tab[lvl->heroY - 4][lvl->heroX] != 48) && (tab[lvl->heroY - 4][lvl->heroX] != 35) && (tab[lvl->heroY - 4][lvl->heroX] != 36)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY -= 3;
                         lvl->chestOneY -= 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY + 3 && lvl->heroX == lvl->chestTwoX) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY - 4][lvl->heroX] != 48 && (tab[lvl->heroY - 4][lvl->heroX] != 35) && (tab[lvl->heroY - 4][lvl->heroX] != 36)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY -= 3;
                         lvl->chestTwoY -= 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else
               {
                    lvl->heroY -= 3;
                    *flag = false;
                    *z = 1;
               }
          }
     }

     if (znak == 115 || znak == 83) // instrukcje dla "S" i "s" RUCH DÓŁ
     {
          if (tab[lvl->heroY + 3][lvl->heroX] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY - 3 && lvl->heroX == lvl->chestOneX) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY + 6][lvl->heroX] != 48 && tab[lvl->heroY + 6][lvl->heroX] != 35 && tab[lvl->heroY + 6][lvl->heroX] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY += 3;
                         lvl->chestOneY += 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY - 3 && lvl->heroX == lvl->chestTwoX) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY + 6][lvl->heroX] != 48 && tab[lvl->heroY + 6][lvl->heroX] != 35 && tab[lvl->heroY + 6][lvl->heroX] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY += 3;
                         lvl->chestTwoY += 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else
               {
                    lvl->heroY += 3;
                    *flag = false;
                    *z = 1;
               }
          }
     }

     if (znak == 97 || znak == 65) // instrukcje dla "A" i "a" RUCH LEW1
     {
          if (tab[lvl->heroY][lvl->heroX - 1] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {

               if (lvl->heroY == lvl->chestOneY && lvl->heroX == (lvl->chestOneX + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY][lvl->heroX - 4] != 48 && tab[lvl->heroY][lvl->heroX - 4] != 35 && tab[lvl->heroY][lvl->heroX - 4] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX -= 3;
                         lvl->chestOneX -= 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY && lvl->heroX == (lvl->chestTwoX + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY][lvl->heroX - 4] != 48 && tab[lvl->heroY][lvl->heroX - 4] != 35 && tab[lvl->heroY][lvl->heroX - 4] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX -= 3;
                         lvl->chestTwoX -= 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else
               {
                    lvl->heroX -= 3;
                    *flag = false;
                    *z = 1;
               }
          }
     }

     if (znak == 100 || znak == 68) // instrukcje dla "D" i "d" RUCH PRAWO
     {
          if (tab[lvl->heroY][lvl->heroX + 3] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY && lvl->heroX == (lvl->chestOneX - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY][lvl->heroX + 6] != 48 && tab[lvl->heroY][lvl->heroX + 6] != 35 && tab[lvl->heroY][lvl->heroX + 6] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX += 3;
                         lvl->chestOneX += 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY && lvl->heroX == (lvl->chestTwoX - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY][lvl->heroX + 6] != 48 && tab[lvl->heroY][lvl->heroX + 6] != 35 && tab[lvl->heroY][lvl->heroX + 6] != 36) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX += 3;
                         lvl->chestTwoX += 3;
                         *flag = false;
                         *z = 1;
                    }
               }
               else
               {
                    lvl->heroX += 3;
                    *flag = false;
                    *z = 1;
               }
          }
     }

     if (znak == 106 || znak == 74) // instrukcja dla "J" i "j" KAMERA LEWO
     {
          if (lvl->camX != 0) // ogranicza wyjście kamery za mapę
          {
               (lvl->camX)--;
          }
     }

     if (znak == 107 || znak == 75) // instrukcja dla "K" i "k" KAMERA PRAWO
     {
          if (lvl->camX != 39) // ogranicza wyjście kamery za mapę
          {
               (lvl->camX)++;
          }
     }

     if (znak == 105 || znak == 73) // instrukcja dla "I" i "i" KAMERA GÓRA
     {
          if (lvl->camY != 0) // ogranicza wyjście kamery za mapę
          {
               (lvl->camY)--;
          }
     }

     if (znak == 109 || znak == 77) // instrukcja dla "M" i "m" KAMERA DÓŁ
     {
          if (lvl->camY != 10) // ogranicza wyjście kamery za mapę
          {
               (lvl->camY)++;
          }
     }

     if (znak == 113 || znak == 81) // instrukcja dla "Q" i "q" MENU
     {
          *flag = false;
          genMenu(tab, lvl1, lvl2, lvl3);
     }

     if (znak == 117 || znak == 85) // instruckcja dla "U" i "u" UNDO
     {
          if ((*counter - *z) < 0)
          {
               *z = *counter - *z;
          }
          if (*counter >= *z)
          {
               lvl->heroX = pastMoves[(*counter - *z) % tabX][0];
               lvl->heroY = pastMoves[(*counter - *z) % tabX][1];
               (*z)++;
               *flag = true;
          }
          else
          {
               cout << "Nie mozna cofnac ruchu";
          }
     }

     if (znak == 114 || znak == 82) // instruckcja dla "R" i "r" REDO
     {
     }

     onSpot(*lvl);
}