#include <iostream>
#include <iomanip>
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
     int chestPictoOne = 35;
     int chestPictoTwo = 35;
     int steps;
     int stepsUsed = 0;
     int camX = 0;
     int camY = 0;
     bool locked;
};

const int mapX = 120;
const int mapY = 35;

void startScreen();
void endScreen();
void winScreen();
void winCheck(int *chestPicto1, int *chestPicto2, level lvl1, level lvl2, level lvl3);
void genBlock(int y, int x, char tab[mapY][mapX], int var, int chest);
void fillMap(char tab[mapY][mapX], char path[11]);
void genMap(char tab[mapY][mapX], int cameraX, int cameraY);
void onSpot(level *lvl);
void showSteps(level *lvl, level lvl1, level lvl2, level lvl3, char tab[mapY][mapX]);
void genLevel(char tab[mapY][mapX], level lvl, level lvl1, level lvl2, level lvl3);
void genMenu(char tab[mapY][mapX], level lvl1, level lvl2, level lvl3);
void action(level *lvl, level lvl1, level lvl2, level lvl3, char tab[mapY][mapX]);

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
     lvlOne.steps = 50;
     lvlOne.locked = false;

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
     lvlTwo.chestPictoOne = 35;
     lvlTwo.chestPictoTwo = 35;
     lvlTwo.steps = 160;
     lvlTwo.locked = true;

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
     lvlThree.chestPictoOne = 35;
     lvlThree.chestPictoTwo = 35;
     lvlThree.steps = 130;
     lvlThree.locked = true;

     startScreen();

     genMenu(mainMap, lvlOne, lvlTwo, lvlThree);

     return 0;
}

void startScreen() // funkcja wyswietlajaca ekran powitalny
{
     system("CLS");

     cout << "  /$$$$$$            /$$                 /$$                          "
          << "\n";
     cout << " /$$__  $$          | $$                | $$                          "
          << "\n";
     cout << "| $$  \\__/  /$$$$$$ | $$   /$$  /$$$$$$ | $$$$$$$   /$$$$$$  /$$$$$$$ "
          << "\n";
     cout << "|  $$$$$$  /$$__  $$| $$  /$$/ /$$__  $$| $$__  $$ |____  $$| $$__  $$"
          << "\n";
     cout << " \\____  $$| $$  \\ $$| $$$$$$/ | $$  \\ $$| $$  \\ $$  /$$$$$$$| $$  \\ $$"
          << "\n";
     cout << " /$$  \\ $$| $$  | $$| $$_  $$ | $$  | $$| $$  | $$ /$$__  $$| $$  | $$"
          << "\n";
     cout << "|  $$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/| $$$$$$$/|  $$$$$$$| $$  | $$"
          << "\n";
     cout << " \\______/  \\______/ |__/  \\__/ \\______/ |_______/  \\_______/|__/  |__/"
          << "\n"
          << "\n";
     cout << "                        Kamil Ratajczyk s193345"
          << "\n"
          << "\n";
     cout << "                   Wyslij dowolny znak aby rozpoczac"
          << "\n";
     getchar();
     fflush(stdin);
}

void endScreen(char tab[mapY][mapX], level lvl1, level lvl2, level lvl3) // funkcja wyswietlajaca ekran przegranej
{
     system("CLS");
     cout << "\n"
          << "\n"
          << "\n"
          << "                 PRZEGRALES!"
          << "\n";
     cout << "                 BRAK KROKOW"
          << "\n";
     fflush(stdin);
     getchar();
     fflush(stdin);
     genMenu(tab, lvl1, lvl2, lvl3);
}

void winScreen() // funkcja wyswietlajaca ekran wygranej
{
     system("CLS");
     cout << "\n"
          << "\n"
          << "\n"
             "                  WYGRALES!"
          << "\n";
     cout << "                 GRATULACJE"
          << "\n";
     fflush(stdin);
     getchar();
     exit(1);
}

void winCheck(char tab[mapY][mapX], level lvl, level lvl1, level lvl2, level lvl3)
{
     if (lvl.chestPictoOne == 36 && lvl.chestPictoTwo == 36)
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

void genBlock(int y, int x, char tab[mapY][mapX], int var, int chest) // funkcja generująca blok w podanym miejscu
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               if (var == 0) // jeśli zostało podane 0 na wejście generujemy miejsce spotu
               {
                    tab[y + i][x + j] = char(33);
               }
               else if (var == 1) // jeśli została podana na wejście jedynka generujemy skrzynię
               {
                    tab[y + i][x + j] = char(chest);
               }
               else if (var == 2) // jeśli została podana na wejście dwójka generujemy bohatera
               {
                    tab[y + i][x + j] = char(64);
               }
          }
     }
}

void fillMap(char tab[mapY][mapX], int x) // funkcja wypełniająca mapę danymi z podnaego pliku
{
     fstream file;

     if (x == 1)
     {
          file.open("level1.txt");
     }
     else if (x == 2)
     {
          file.open("level2.txt");
     }
     else if (x == 3)
     {
          file.open("level3.txt");
     }

     if (!file)
     {
          cout << "Pobranie mapy z pliku się nie powiodło";
          exit(0);
     }

     for (int i = 0; i < mapY; i++)
     {
          for (int j = 0; j < mapX; j++)
          {
               tab[i][j] = char(file.get());
          }
     }

     file.close();
}

void genMap(char tab[mapY][mapX], int cameraX, int cameraY) // funkcja wypisujaca na ekran mapę
{
     system("CLS");

     for (int i = cameraY; i < cameraY + 25; i++)
     {
          for (int j = cameraX; j < cameraX + 80; j++)
          {
               cout << tab[i][j];
          }
          cout << "\n";
     }
     cout << "\n";
}

void onSpot(level *lvl) // funkcja sprawdzająca położenie skrzyń
{
     if ((lvl->chestOneX == lvl->spotOneX && lvl->chestOneY == lvl->spotOneY) || (lvl->chestOneX == lvl->spotTwoX && lvl->chestOneY == lvl->spotTwoY))
     {
          lvl->chestPictoOne = 36;
     }
     else
          lvl->chestPictoOne = 35;

     if ((lvl->chestTwoX == lvl->spotOneX && lvl->chestTwoY == lvl->spotOneY) || (lvl->chestTwoX == lvl->spotTwoX && lvl->chestTwoY == lvl->spotTwoY)) // Sprawdza czy druga skrzynia znajduje się na miejscu docelowym
     {
          lvl->chestPictoTwo = 36;
     }
     else
          lvl->chestPictoTwo = 35;
}

void showSteps(level *lvl, level lvl1, level lvl2, level lvl3, char tab[mapY][mapX]) // Wyświetlanie liczby kroków i logika związana z krokami
{
     int stepsLeft;

     if (lvl->heroX != lvl->tempX || lvl->heroY != lvl->tempY)
     {
          (lvl->stepsUsed)++;

          lvl->tempX = lvl->heroX;
          lvl->tempY = lvl->heroY;
     }

     stepsLeft = lvl->steps - lvl->stepsUsed;
     cout << "Pozostalo krokow: " << stepsLeft << " \n";

     if (stepsLeft == 0)
     {
          endScreen(tab, lvl1, lvl2, lvl3);
     }
}

void genLevel(char tab[mapY][mapX], level lvl, level lvl1, level lvl2, level lvl3)
{
     while (1)
     {
          fillMap(tab, lvl.lvlId);
          genBlock(lvl.spotOneY, lvl.spotOneX, tab, 0, lvl.chestPictoOne);
          genBlock(lvl.spotTwoY, lvl.spotTwoX, tab, 0, lvl.chestPictoTwo);
          genBlock(lvl.heroY, lvl.heroX, tab, 2, lvl.chestPictoOne);
          genBlock(lvl.chestOneY, lvl.chestOneX, tab, 1, lvl.chestPictoOne);
          genBlock(lvl.chestTwoY, lvl.chestTwoX, tab, 1, lvl.chestPictoTwo);
          genMap(tab, lvl.camX, lvl.camY);
          showSteps(&lvl, lvl1, lvl2, lvl3, tab);
          action(&lvl, lvl1, lvl2, lvl3, tab);
          winCheck(tab, lvl, lvl1, lvl2, lvl3);
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
          znak = char(getchar());

          if (lvl2.locked == false) // odpowiada za kropki w menu sygnalizujace czy odblokowalismy poziom
          {
               dot1 = 42;
          }
          if (lvl3.locked == false)
          {
               dot2 = 42;
          }

          if (znak == 49) // 49 = "1"
          {
               fflush(stdin);
               system("CLS");
               cout << "Wybierz: "
                    << "\n"
                    << "(1) Poziom 1 " << char(42)
                    << "\n"
                    << "(2) Poziom 2 " << char(dot1)
                    << "\n"
                    << "(3) Poziom 3 " << char(dot2)
                    << "\n";

               znak = char(getchar());
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
                         cout << "Nie odblokowales jeszcze tego poziomu!"
                              << "\n";
                         cout << "Wyslij dowolny przycisk";
                         fflush(stdin);
                         getchar();
                         fflush(stdin);
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
                         cout << "Nie odblokowales jeszcze tego poziomu!"
                              << "\n";
                         cout << "Wyslij dowolny przycisk";
                         fflush(stdin);
                         getchar();
                         fflush(stdin);
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
               cout << "Wyslij dowolny przycisk";
               fflush(stdin);
               getchar();
               fflush(stdin);
               genMenu(tab, lvl1, lvl2, lvl3);
          }
     }
}

void action(level *lvl, level lvl1, level lvl2, level lvl3, char tab[mapY][mapX])
{
     cout << "Wprowadz znak: ";
     char znak = char(getchar());

     if (znak == 119 || znak == 87) // instrukcje dla "W" i "w" RUCH GÓRA
     {
          if (tab[lvl->heroY - 1][lvl->heroX] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY + 3 && lvl->heroX == lvl->chestOneX) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if ((tab[lvl->heroY - 4][lvl->heroX] != 48) && (tab[lvl->heroY - 4][lvl->heroX] != lvl->chestPictoTwo)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY -= 3;
                         lvl->chestOneY -= 3;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY + 3 && lvl->heroX == lvl->chestTwoX) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY - 4][lvl->heroX] != 48 && (tab[lvl->heroY - 4][lvl->heroX] != lvl->chestPictoOne)) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY -= 3;
                         lvl->chestTwoY -= 3;
                    }
               }
               else
               {
                    lvl->heroY -= 3;
               }
          }
     }

     if (znak == 115 || znak == 83) // instrukcje dla "S" i "s" RUCH DÓŁ
     {
          if (tab[lvl->heroY + 3][lvl->heroX] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY - 3 && lvl->heroX == lvl->chestOneX) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY + 6][lvl->heroX] != 48 && tab[lvl->heroY + 6][lvl->heroX] != lvl->chestPictoTwo) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY += 3;
                         lvl->chestOneY += 3;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY - 3 && lvl->heroX == lvl->chestTwoX) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY + 6][lvl->heroX] != 48 && tab[lvl->heroY + 6][lvl->heroX] != lvl->chestPictoOne) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroY += 3;
                         lvl->chestTwoY += 3;
                    }
               }
               else
               {
                    lvl->heroY += 3;
               }
          }
     }

     if (znak == 97 || znak == 65) // instrukcje dla "A" i "a" RUCH LEW1
     {
          if (tab[lvl->heroY][lvl->heroX - 1] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {

               if (lvl->heroY == lvl->chestOneY && lvl->heroX == (lvl->chestOneX + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY][lvl->heroX - 4] != 48 && tab[lvl->heroY][lvl->heroX - 4] != lvl->chestPictoTwo) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX -= 3;
                         lvl->chestOneX -= 3;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY && lvl->heroX == (lvl->chestTwoX + 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY][lvl->heroX - 4] != 48 && tab[lvl->heroY][lvl->heroX - 4] != lvl->chestPictoOne) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX -= 3;
                         lvl->chestTwoX -= 3;
                    }
               }
               else
               {
                    lvl->heroX -= 3;
               }
          }
     }

     if (znak == 100 || znak == 68) // instrukcje dla "D" i "d" RUCH PRAWO
     {
          if (tab[lvl->heroY][lvl->heroX + 3] != 48) // sprawdzamy czy nie jesteśmy przy ścianie
          {
               if (lvl->heroY == lvl->chestOneY && lvl->heroX == (lvl->chestOneX - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 1
               {
                    if (tab[lvl->heroY][lvl->heroX + 6] != 48 && tab[lvl->heroY][lvl->heroX + 6] != lvl->chestPictoTwo) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX += 3;
                         lvl->chestOneX += 3;
                    }
               }
               else if (lvl->heroY == lvl->chestTwoY && lvl->heroX == (lvl->chestTwoX - 3)) // sprawdzamy czy nie stoi obok nas skrzynia 2
               {
                    if (tab[lvl->heroY][lvl->heroX + 6] != 48 && tab[lvl->heroY][lvl->heroX + 6] != lvl->chestPictoOne) // sprawdzamy czy nie wpychamy skrzymi w ścienę ani drugą skrzynię
                    {
                         lvl->heroX += 3;
                         lvl->chestTwoX += 3;
                    }
               }
               else
               {
                    lvl->heroX += 3;
               }
          }
     }

     if (znak == 106 || znak == 74) // instrukcja dla "J" i "j" KAMERA LEWO
     {
          if (lvl->camX != 0)
          {
               (lvl->camX)--;
          }
     }

     if (znak == 107 || znak == 75) // instrukcja dla "K" i "k" KAMERA PRAWO
     {
          if (lvl->camX != 39)
          {
               (lvl->camX)++;
          }
     }

     if (znak == 105 || znak == 73) // instrukcja dla "I" i "i" KAMERA GÓRA
     {
          if (lvl->camY != 0)
          {
               (lvl->camY)--;
          }
     }

     if (znak == 109 || znak == 77) // instrukcja dla "M" i "m" KAMERA DÓŁ
     {
          if (lvl->camY != 10)
          {
               (lvl->camY)++;
          }
     }

     if (znak == 113 || znak == 81) // instrukcja dla "Q" i "q" MENU
     {
          fflush(stdin);
          genMenu(tab, lvl1, lvl2, lvl3);
     }

     fflush(stdin);
     onSpot(lvl);
}