#ifndef SZYFROWANIEHASLA_H_INCLUDED
#define SZYFROWANIEHASLA_H_INCLUDED

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

string wczytaj_haslo() {
    string haslo = "";
    char ch;

    cout << "Podaj hasło: ";
    while ((ch = _getch()) != '\r') {
        if (ch == 8) {
            if (!haslo.empty()) {
                haslo.pop_back();
                cout << "\b \b";
            }
        } else {
            haslo.push_back(ch);
            cout << "*";
        }
    }
    cout << endl;
    return haslo;
}

bool logowanie_pracownika() {
    system("chcp 65001>>null");
    string imieP;
    string haslo;

    const string imie_poprawne = "natalia";
    const string haslo_poprawne ="zaq123";
    int przesuniecie = 3;

    cout << "Witaj pracowniku, podaj swoje dane" << endl;
    cout << "Imię: "; cin >> imieP;

    if(haslo.length() == haslo_poprawne.length()){
    for (int i =0; i < haslo.length(); ++i) {
        if (isalpha(haslo[i])) {
            if (isupper(haslo[i])) {
                haslo[i] = (haslo[i] - 'A' + przesuniecie) % 26 + 'A';
            } else {
                haslo[i] = (haslo[i] - 'a' + przesuniecie) % 26 + 'a';
            }
        }
    }
    return false;
    }
    haslo = wczytaj_haslo();
    if (imieP == imie_poprawne && haslo == haslo_poprawne) {
        cout << "Zalogowano pomyślnie!" << endl;
        return true;
    } else {
        cout << "Niepoprawne dane! Spróbuj ponownie" << endl;
        return false;
    }
}

#endif

