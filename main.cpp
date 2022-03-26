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

// spremenil v nize
// spremeni samo 1. crko v '|'
// narjeno za crne crke

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

void load_file(char tab1[A][6]) {
    ifstream inFile("besede_raw.txt");
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < 6; j++) {
            if (j < 5)
                inFile >> tab1[i][j]; // loda v prve 5 slotov
            else
                tab1[i][5] = '\0'; // v 6.ga da \0
        }
    }
}

void switc(char arr[6], char arr2[6]) {
    char t[6];
    for (int i = 0; i < 5; i++) {
        t[i] = arr[i];
        arr[i] = arr2[i];
        arr2[i] = t[i];
    }
}

void sort(char tab[A][6]) {
    for (int i = 0; i < A; i++) {
        for (int j = A - 1; j > i; j--) { // prvi pogoj do || je da lahko dela da zamenja samo 1. crko z '|'
            if (tab[j - 1][0] == '|' && tab[j][0] != '|' || tab[j - 1][0] > tab[j][0] && tab[j - 1][1] > tab[j][1] && tab[j - 1][2] > tab[j][2] && tab[j - 1][3] > tab[j][3] && tab[j - 1][4] > tab[j][4])
                switc(tab[j - 1], tab[j]);
        }
    }
}

void print(char mreza[A][6]) {
    int z = 0;
    for (int i = 0; i < A && mreza[i][0] != '|'; i++) {
        cout << mreza[i] << endl;
        z++;
    }
    cout << z << endl;
}

void vpis(char zel[6], char rum[6], char crn[27]) {
    for(int i=0;i<6;i++)
        zel[i] = '\0';
    barva(32);
    cout << "napisi zeleni izraz\n";
    barva(15);
    gets(zel);
    for(int i=0;i<6;i++)
        rum[i] = '\0';
    barva(96);
    cout << "napisi rumene crke\n";
    barva(15);
    gets(rum);
    for(int i=0;i<27;i++)
        crn[i] = '\0';
    barva(15);
    cout << "napisi crne crke\n";
    gets(crn);
    rum[5] = '\0';
}

void start() {
    cout << "********************\n";
    cout << "   wordle  solver   \n";
    cout << "         V1.1       \n";
    cout << "********************\n";
}

void ru(char mreza[A][6], char rum[6], int in) {
    int z;
    for (int i = 0; i < A && mreza[i][0] != '|'; i++) {
        z = 0;
        for (int j = 0; j < 5; j++)
            if (mreza[i][j] != rum[in])
                z++;
        if (z == 5)
            mreza[i][0] = '|';
    }
    sort(mreza);
}

void brain(char mreza[A][6], char zel[6],char rum[6], int in) {
    int z;
    for (int i = 0; i < A && mreza[i][0] != '|'&&(zel[in]!='\0'||rum[in]!='\0'); i++) {
        if (mreza[i][in] != zel[in]&&zel[in]!='\0'&&zel[in]>='a'&&zel[in]<='z'){//zelena
            mreza[i][0] = '|';
        }
        z = 0;
        for (int j = 0; j < 5&&rum[in]!='\0'&&rum[in]>='a'&&rum[in]<='z'; j++)//rumena
            if (mreza[i][j] != rum[in])
                z++;
        if (z == 5){
            mreza[i][0] = '|';
        }
    }
    sort(mreza);
}

void cr(char mreza[A][6], char crn[27]) {
    bool z = 0;
    for (int i = 0; i < A && mreza[i][0] != '|'&&crn[0]!='\0' ; i++) {
        z = 0;
        for (int j = 0; j < 5 && z == 0; j++)
            for (int k = 0; k < 26 && z == 0&&crn[k]; k++)
                if (mreza[i][j] == crn[k]) {
                    mreza[i][0] = '|';
                    z = 1;
                }
    }
    sort(mreza);
}


void deciderv2(char mreza[A][6], char zel[6],char rum[6]) {
    for(int i=0;i<5;i++)
        brain(mreza,zel,rum,i);
}

bool check(char mreza[A][6]) {
    if (mreza[1][0] == '|')
        return 1;
    return 0;
}

void end(char mreza[A][6]) {
    cls();
    if (mreza[0][0] != '|') {
        barva(32);
        cout << "********************\n";
        cout << " Bravo tok si neumn \nda ne mors rest sam!\n     hahahahaha     \nbeseda je bila:";
        cout << mreza[0];
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
    char mreza[A][6];
    char zel[6], rum[6], crn[27]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',};
    int mode=0;
    load_file(mreza);
    start();
    while (1) {
        vpis(zel, rum, crn);
        cr(mreza,crn);
        deciderv2(mreza,zel,rum);
        print(mreza);
        if (check(mreza)) {
            end(mreza);
            break;
        }
    }
    return 0;
}
