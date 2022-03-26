//* More visible comment{}
//! Warning comment
//? Question comment
// TODO Reminder to implement a feature
// @param param opis parametra

#include <fstream>
#include <iomanip>
#include <iostream>
#include <windows.h>
using namespace std;

#define A 2315

void cls() {
    // system("cls");
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void barva(int i) { // 96 rumena 32 zelena 15 crna
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, i);
}

void load_file(char tab1[A][5]) {
    ifstream inFile("besede_raw.txt");
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < 5; j++) {
            inFile >> tab1[i][j];
        }
    }
    // cout<<endl;
}

void switc(char arr[5], char arr2[5]) {
    char t[5];
    for (int i = 0; i < 5; i++) {
        t[i] = arr[i];
        arr[i] = arr2[i];
        arr2[i] = t[i];
    }
}

void sort(char tab[A][5]) { // ce je place 1 je useless ker bo samo tabelo prepisalo znova, ne dela zadnja crka pri sortiranju glede na 1. mesto
    for (int i = 0; i < A; i++) {
        for (int j = A - 1; j > i; j--) {
            if (tab[j - 1][0] > tab[j][0] && tab[j - 1][1] > tab[j][1] && tab[j - 1][2] > tab[j][2] && tab[j - 1][3] > tab[j][3] && tab[j - 1][4] > tab[j][4])
                switc(tab[j - 1], tab[j]);
        }
    }
}

void print(char mreza[A][5]) {
    int z = 0;
    for (int i = 0; i < A && mreza[i][0] != '|'; i++) {
        for (int j = 0; j < 5; j++)
            cout << mreza[i][j];
        cout << endl;
        z++;
    }
    cout << z << endl;
}

void vpis(char zel[5], char rum[5]) {
    barva(32);
    cout << "napisi zeleni izraz\n";
    for (int i = 0; i < 5; i++) {
        cin >> ws >> noskipws >> zel[i];
    }
    barva(96);
    cout << "napisi rumeni izraz\n";
    for (int i = 0; i < 5; i++) {
        cin >> ws >> noskipws >> rum[i];
    }
    barva(15);
    cout << endl;
}

void start() {
    cout << "********************\n";
    cout << "   wordle  solver   \n";
    cout << "      beta v1.0     \n";
    cout << "********************\n";
}

void zl(char mreza[A][5], char zel[5], int in) {
    for (int i = 0; i < A && mreza[i][0] != '|'; i++) {
        if (mreza[i][in] != zel[in])
            for (int j = 0; j < 5; j++)
                mreza[i][j] = '|';
    }
    sort(mreza);
}

void ru(char mreza[A][5], char rum[5], int in) {
    int z;
    for (int i = 0; i < A && mreza[i][0] != '|'; i++) {
        z = 0;
        for (int j = 0; j < 5; j++)
            if (mreza[i][j] != rum[in])
                z++;
        if (z == 5) {
            for (int j = 0; j < 5; j++)
                mreza[i][j] = '|';
        }
    }
    sort(mreza);
}

void decider(char mreza[A][5], char model[5], bool zeru) {
    int x;
    if (model[0] >= 'a' && model[0] <= 'z') {
        if (zeru == true)
            zl(mreza, model, 0);
        else
            ru(mreza, model, 0);
    }
    if (model[1] >= 'a' && model[1] <= 'z') {
        if (zeru == true)
            zl(mreza, model, 1);
        else
            ru(mreza, model, 1);
    }
    if (model[2] >= 'a' && model[2] <= 'z') {
        if (zeru == true)
            zl(mreza, model, 2);
        else
            ru(mreza, model, 2);
    }
    if (model[3] >= 'a' && model[3] <= 'z') {
        if (zeru == true)
            zl(mreza, model, 3);
        else
            ru(mreza, model, 3);
    }
    if (model[4] >= 'a' && model[4] <= 'z') {
        if (zeru == true)
            zl(mreza, model, 4);
        else
            ru(mreza, model, 4);
    }
}

bool check(char mreza[A][5]) {
    if (mreza[1][0] == '|')
        return 1;
    return 0;
}

void end(char mreza[A][5]) {
    cls();
    if (mreza[0][0] != '|') {
        barva(32);
        cout << "********************\n";
        cout << " Bravo tok si neumn \nda ne mors rest sam!\n     hahahahaha     \nbeseda je bila:";
        for (int i = 0; i < 5; i++)
            cout << mreza[0][i];
        cout << "\n********************\n";
        barva(15);
    } else {
        barva(64);
        cout << "********************\n";
        cout << "                    \n   neki si zajebu   \n";
        cout << "vpis ni sprejemljiv!\n                    \n";
        cout << "********************\n";
        barva(15);
    }
}

int main() {
    char mreza[A][5];
    char zel[5], rum[5];
    load_file(mreza);
    start();
    while (1) {
        vpis(zel, rum);
        decider(mreza, zel, 1);
        decider(mreza, rum, 0);
        print(mreza);
        if (check(mreza)) {
            end(mreza);
            break;
        }
    }
    return 0;
}
