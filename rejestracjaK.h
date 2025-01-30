#ifndef REJESTRACJAK_H
#define REJESTRACJAK_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <cctype>

using namespace std;

int sprawdz_znaki_alfabetyczne(const string& dane) {
    for (char c : dane) {
        if (!isalpha(c)) {
            return 0;
        }
    }
    return 1;
}

int sprawdz_poprawnosc_roku(int rok) {
    auto teraz = std::chrono::system_clock::now();
    std::time_t czas = std::chrono::system_clock::to_time_t(teraz);
    struct tm *czas_tm = std::localtime(&czas);
    int obecny_rok = 1930 + czas_tm->tm_year;
    return (rok > 1930 && rok <= obecny_rok);
}

int odczytaj_ostatni_nr_karty() {
    ifstream plik("numer_karty.txt");
    int ostatniNrKarty = 1;

    if (plik.is_open()) {
        plik >> ostatniNrKarty;
        plik.close();
    }
    return ostatniNrKarty;
}

void zapisz_numer_karty(int nrKarty) {
    ofstream plik("numer_karty.txt");
    if (plik.is_open()) {
        plik << nrKarty;
        plik.close();
    } else {
        cout << "Blad przy zapisywaniu numeru karty!" << endl;
    }
}

void zapisz_klienta(const string& imieK, const string& nazwiskoK, int rokK, int nrKarty) {
    system("chcp 65001>>null");

    ofstream plik("klient.txt", ios::app);
    if (plik.is_open()) {
        plik << imieK << ":" << nazwiskoK << ":" << rokK << ":" << nrKarty << endl;
        cout << "Zostales zapisany jako czytelnik: " << imieK << " z numerem karty: " << nrKarty << endl;
    } else {
        cout << "Blad przy zapisywaniu danych czytelnika!" << endl;
    }
}

void rejestracja_klienta() {
    system("chcp 65001>>null");

    string imieK, nazwiskoK;
    int rokK;
    int nrKarty = odczytaj_ostatni_nr_karty() + 1;

    int poprawneImie = 0;
    while (poprawneImie == 0) {
        cout << "Podaj imie: "; cin >> imieK;
        if (sprawdz_znaki_alfabetyczne(imieK) == 1) {
            poprawneImie = 1;
        } else {
            cout << "Imie powinno zawierac tylko litery!" << endl;
        }
    }

    int poprawneNazwisko = 0;
    while (poprawneNazwisko == 0) {
        cout << "Podaj nazwisko: "; cin >> nazwiskoK;
        if (sprawdz_znaki_alfabetyczne(nazwiskoK) == 1) {
            poprawneNazwisko = 1;
        } else {
            cout << "Nazwisko powinno zawierac tylko litery!" << endl;
        }
    }

    int poprawnyRok = 0;
    while (poprawnyRok == 0) {
        cout << "Podaj rok urodzenia: "; cin >> rokK;
        if (sprawdz_poprawnosc_roku(rokK) == 1) {
            poprawnyRok = 1;
        } else {
            cout << "Rok urodzenia musi byc wiekszy niz 1930 i mniejszy niz biezacy rok!" << endl;
        }
    }

    zapisz_klienta(imieK, nazwiskoK, rokK, nrKarty);
    zapisz_numer_karty(nrKarty);
}




#endif
