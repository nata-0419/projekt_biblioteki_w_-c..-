#ifndef KLIENT_H_INCLUDED
#define KLIENT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include "bazaKsiazek.h"

using namespace std;

struct Klient {
    string imie;
    string nazwisko;
    int rok_urodzenia;
    int nrKarty;
};

const int MAX_KLIENTOW = 1000;

void wyswietl_wszystkich_czytelnikow() {
    system("chcp 65001>>null");

    ifstream plik("klient.txt");
    string linia;

    if (!plik.is_open()) {
        cout << "Bląd przy otwieraniu pliku." << endl;
        return;
    }

    cout << "Dane wszystkich uczniów w bibliotece:" << endl;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }
    plik.close();
}

void wyswietl_wszystkie_wypozyczenia() {
    system("chcp 65001>>null");

    ifstream plik("wypozyczenieK.txt");
    string linia;

    if (!plik.is_open()) {
        cout << "Bląd przy otwieraniu pliku." << endl;
        return;
    }

    cout << "Dane wszystkich wypożyczonych książek w bibliotece:" << endl;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }

    plik.close();
}

int odczytaj_klientow_z_pliku(const string& filename, Klient klienci[MAX_KLIENTOW]) {
    ifstream plik(filename);
    if (!plik.is_open()) {
        cout << "Nie udało się otworzyć pliku " << filename << endl;
        return 0;
    }

    string linia;
    int liczbaKlientow = 0;
    while (getline(plik, linia) && liczbaKlientow < MAX_KLIENTOW) {
        stringstream ss(linia);
        Klient klient;
        getline(ss, klient.imie, ':');
        getline(ss, klient.nazwisko, ':');
        ss >> klient.rok_urodzenia;
        ss.ignore();
        ss >> klient.nrKarty;
        klienci[liczbaKlientow++] = klient;
    }

    plik.close();
    return liczbaKlientow;
}

bool sprawdz_klienta(int nrKartyKlienta, Klient klienci[MAX_KLIENTOW], int liczbaKlientow) {
    for (int i = 0; i < liczbaKlientow; i++) {
        if (klienci[i].nrKarty == nrKartyKlienta){
        return true;
    }}
    return false;
}

bool sprawdz_ksiazke_dostepna(int nrKsiazki, Ksiazka ksiazki[MAX_KSIAZEK], int liczbaKsiazek) {
    for (int i = 0; i < liczbaKsiazek; i++) {
        if (ksiazki[i].nrKsiazki == nrKsiazki && ksiazki[i].stan > 0) {
            ksiazki[i].stan--;
            return true;
        }
    }
    return false;
}

bool sprawdz_wypozyczenie(int nrKartyKlienta, int nrKsiazki) {
    ifstream plikWypozyczenie("wypozyczenieK.txt");
    string linia;
    while (getline(plikWypozyczenie, linia)) {
        stringstream ss(linia);
        int nrKartyWyp, nrKsiazkiWyp;
        string dataWypozyczenia;
        ss >> nrKartyWyp;
        ss.ignore();
        ss >> nrKsiazkiWyp;
        ss.ignore();
        getline(ss, dataWypozyczenia);
        if (nrKartyWyp == nrKartyKlienta && nrKsiazkiWyp == nrKsiazki) {
            return true;
        }
    }
    return false;
}

void zaktualizuj_ksiazki(Ksiazka ksiazki[MAX_KSIAZEK], int liczbaKsiazek) {
    fstream plik("ksiazki.txt", ios::in | ios::out);
    if (plik.is_open()) {
        plik.seekg(0, ios::beg);
        stringstream ss;
        for (int i = 0; i < liczbaKsiazek; i++) {
            ss << ksiazki[i].tytul << ":" << ksiazki[i].autor << ":" << ksiazki[i].rok_wydania << ":"
               << ksiazki[i].rodzaj << ":" << ksiazki[i].ilosc_min << ":" << ksiazki[i].stan << ":"
               << ksiazki[i].nrKsiazki << endl;
        }
        plik.seekp(0, ios::beg);
        plik << ss.str();
        plik.close();
    } else {
        cout << "Błąd przy zapisywaniu książek!" << endl;
    }
}

void wypozycz_ksiazke() {
    system("chcp 65001>>null");

    int nrKartyKlienta, nrKsiazki;
    Klient klienci[MAX_KLIENTOW];
    int liczbaKlientow = odczytaj_klientow_z_pliku("klient.txt", klienci);

    Ksiazka ksiazki[MAX_KSIAZEK];
    int liczbaKsiazek = odczytaj_ksiazki_z_pliku("ksiazki.txt", ksiazki);

    cout << "Podaj numer karty czytelnika: "; cin >> nrKartyKlienta;
    if (!sprawdz_klienta(nrKartyKlienta, klienci, liczbaKlientow)) {
        cout << "Nie znaleziono czytelnika o takim numerze karty!" << endl;
        return;
    }

    cout << "Podaj numer książki, którą wypożyczasz: "; cin >> nrKsiazki;
    if (!sprawdz_ksiazke_dostepna(nrKsiazki, ksiazki, liczbaKsiazek)) {
        cout << "Książka o numerze " << nrKsiazki << " jest niedostępna lub nie istnieje!" << endl;
        return;
    }

    if (sprawdz_wypozyczenie(nrKartyKlienta, nrKsiazki)) {
        cout << "Ta książka została już wypożyczona przez tego czytelnika!" << endl;
        return;
    }
    zaktualizuj_ksiazki(ksiazki, liczbaKsiazek);

    ofstream plikWypozyczenieNowe("wypozyczenieK.txt", ios::app);
    if (plikWypozyczenieNowe.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        plikWypozyczenieNowe << nrKartyKlienta << ":" << nrKsiazki << ":" << dt << endl;
        cout << "Książka została wypożyczona." << endl;
    } else {
        cout << "Błąd przy zapisywaniu wypożyczenia!" << endl;
    }
}

void sprawdz_konto_klienta() {
    system("chcp 65001>>null");

    int nrKartyKlienta;
    cout << "Podaj numer karty: "; cin >> nrKartyKlienta;

    Ksiazka ksiazki[MAX_KSIAZEK];
    int liczbaKsiazek = odczytaj_ksiazki_z_pliku("ksiazki.txt", ksiazki);

    ifstream plikWypozyczenie("wypozyczenieK.txt");
    string linia;
    bool znaleziono = false;

    while (getline(plikWypozyczenie, linia)) {
        stringstream ss(linia);
        int nrKarty, nrKsiazki;
        string dataWypozyczenia;

        ss >> nrKarty;
        ss.ignore();
        ss >> nrKsiazki;
        ss.ignore();
        getline(ss, dataWypozyczenia);

        if (nrKarty == nrKartyKlienta) {
            cout << "Wypożyczono książkę nr " << nrKsiazki << " dnia: " << dataWypozyczenia << endl;
            znaleziono = true;
        }
    }
    if (!znaleziono) {
        cout << "Ten czytelnik nie ma zadnej książki na swoim koncie!" << endl;
    }
    plikWypozyczenie.close();
}

void zwroc_ksiazke() {
    system("chcp 65001>>null");

    int nrKartyKlienta, nrKsiazki;
    Klient klienci[MAX_KLIENTOW];
    int liczbaKlientow = odczytaj_klientow_z_pliku("klient.txt", klienci);

    Ksiazka ksiazki[MAX_KSIAZEK];
    int liczbaKsiazek = odczytaj_ksiazki_z_pliku("ksiazki.txt", ksiazki);

    cout << "Podaj numer karty czytelnika: "; cin >> nrKartyKlienta;
    if (!sprawdz_klienta(nrKartyKlienta, klienci, liczbaKlientow)) {
        cout << "Nie znaleziono czytelnika o takim numerze karty!" << endl;
        return;
    }

    cout << "Podaj numer książki, którą zwracasz: "; cin >> nrKsiazki;
    if (!sprawdz_wypozyczenie(nrKartyKlienta, nrKsiazki)) {
        cout << "Nie znaleziono wypożyczenia tej książki dla tego klienta!" << endl;
        return;
    }

    for (int i = 0; i < liczbaKsiazek; i++) {
        if (ksiazki[i].nrKsiazki == nrKsiazki) {
            ksiazki[i].stan++;
            cout << "Książka o numerze " << nrKsiazki << " została zwrócona." << endl;
            break;
        }
    }

    zaktualizuj_ksiazki(ksiazki, liczbaKsiazek);

    ifstream plikWypozyczenieOrig("wypozyczenieK.txt");
    ofstream plikTemp("temp.txt");

    string liniaWypozyczenia;
    while (getline(plikWypozyczenieOrig, liniaWypozyczenia)) {
        stringstream ss(liniaWypozyczenia);
        int nrKartyWyp, nrKsiazkiWyp;
        string dataWypozyczenia;

        ss >> nrKartyWyp;
        ss.ignore();
        ss >> nrKsiazkiWyp;
        ss.ignore();
        getline(ss, dataWypozyczenia);

        if (!(nrKartyWyp == nrKartyKlienta && nrKsiazkiWyp == nrKsiazki)) {
            plikTemp << liniaWypozyczenia << endl;
        }
    }
    plikWypozyczenieOrig.close();
    plikTemp.close();
    remove("wypozyczenieK.txt");
    rename("temp.txt", "wypozyczenieK.txt");

    cout << "Wypożyczenie zostało usunięte z systemu." << endl;
}

#endif
