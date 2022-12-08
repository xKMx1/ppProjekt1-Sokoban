#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <stack>

using namespace std;

const int mapX = 80;
const int mapY = 25;

char mainMap[mapY][mapX];

stack<char (*)[mapX]> undoStack;//C++ jest dziwny i nie mam pojecia co robie
stack<char (*)[mapX]> redoStack;


void clearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void copyMaps(char changeMap[mapY][mapX], char sourceMap[mapY][mapX]) {
    for (int i = 0; i < mapY; ++i) {
        for (int j = 0; j < mapX; ++j) {
            changeMap[i][j] = sourceMap[i][j];
        }
    }
}

void startScreen() { // funkcja wyswietlajaca ekran powitalny
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

void genBlock(int y, int x, char tab[mapY][mapX], int var) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (var == 0) { // generate spot
                tab[y + i][x + j] = 38;
            } else if (var == 1) { // generate chest
                tab[y + i][x + j] = 35;
            } else if (var == 2) { // generate hero
                tab[y + i][x + j] = 135;
            }
        }
    }
}

void fillMap1() // funkcja wypełniająca mapę 1
{
    fstream file;

    file.open("blank.txt");

    if (!file) {
        cout << "Pobranie mapy z pliku się nie powiodło";
        exit(0);
    }

    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            mainMap[i][j] = file.get();
        }
    }

    file.close();
}

void genMap1(char tab[mapY][mapX]) // wypisujemy na ekran mapę
{
    clearScreen();

    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            cout << tab[i][j];
        }
    }
    cout << "\n\n";
}

int genMenu() {
    system("cls");
    cout << "Wybierz:"
         << "\n";
    cout << "(1) Rozpocznij gre od pierwszego etapu"
         << "\n";
    cout << "(2) Opusc gre"
         << "\n";

    while (true) {
        char znak = getchar();

        if (znak == 49) {
            return 1;
        } else if (znak == 50) {
            exit(0);
        } else {
            cout << "Wybrales niepoprawny znak! Mozesz wybrac 1 lub 2."
                 << "\n";
            Sleep(1000);
            genMenu();
        }
    }
}

void loadGameProgress() {
    //TODO probably move / change name
    //copy save from state stack
    undoStack.pop();
    char save[mapY][mapX];
    copyMaps(save, undoStack.top());

    //move previous state to redo and clean undo
    redoStack.push(mainMap);
    undoStack.pop();
    //TODO possible fuckups with pops

    //update main map
    copyMaps(mainMap, save);
    genMap1(mainMap);
}

void undo() {
    if (!undoStack.empty()) {
        loadGameProgress();
    }
}

void action(int *y, int *x, int *b, int *a) {
    cout << "Wprowadz znak: ";
    char znak = getch();
    cout << znak;

    if (znak == 'w' || znak == 'W') // instrukcje dla "W"
    {
        if (*y == *b + 3 && *x == *a) {
            *y -= 3;
            *b -= 3;
        } else {
            *y -= 3;
        }
    }

    if (znak == 's' || znak == 'S') // instrukcje dla "S"
    {
        if (*y == *b - 3 && *x == *a) {
            *y += 3;
            *b += 3;
        } else {
            *y += 3;
        }
    }

    if (znak == 'a' || znak == 'A') // instrukcje dla "A"
    {
        if (*y == *b && *x == (*a + 3)) {
            *x -= 3;
            *a -= 3;
        } else {
            *x -= 3;
        }
    }

    if (znak == 'd' || znak == 'D') // instrukcje dla "D"
    {
        if (*y == *b && *x == (*a - 3)) {
            *x += 3;
            *a += 3;
        } else {
            *x += 3;
        }
    }

    if (znak == 'z' || znak == 'Z') {
        undo();
    }

}

void saveGameProgress() {
    char save[mapY][mapX];

    copyMaps(save, mainMap);

    undoStack.push(save);
}

void level(int lvl, char tab[mapY][mapX]) {
    if (lvl == 1) {
        int heroX = 48, heroY = 5;
        int chestOneX = 39, chestOneY = 8;
        int chestTwoX = 39, chestTwoY = 11;
        int spotOneX = 27, spotOneY = 5;
        int spotTwoX = 30, spotTwoY = 5;

        fillMap1();
        genBlock(heroY, heroX, tab, 2);
        genBlock(chestOneY, chestOneX, tab, 1);
        genBlock(chestTwoY, chestTwoX, tab, 1);
        genBlock(spotOneY, spotOneX, tab, 0);
        genBlock(spotTwoY, spotTwoX, tab, 0);
        genMap1(tab);
        for (int i = 0; i < 500; i++) {
            action(&heroY, &heroX, &chestOneY, &chestOneX);
            fillMap1();
            genBlock(heroY, heroX, tab, 2);
            genBlock(chestOneY, chestOneX, tab, 1);
            genBlock(chestTwoY, chestTwoX, tab, 1);
            genBlock(spotOneY, spotOneX, tab, 0);
            genBlock(spotTwoY, spotTwoX, tab, 0);
            genMap1(tab);
            saveGameProgress();
        }
    }
}

int main() {

    // startScreen();

    if (genMenu() == 1) {
        level(1, mainMap);
    }

    return 0;
}