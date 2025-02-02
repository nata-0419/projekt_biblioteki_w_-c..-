#ifndef zadaniaNaKsiazkach_h
#define zadaniaNaKsiazkach_h

#include "bazaKsiazek.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <cstdio>
#include <thread>

using namespace std;

struct Ksiazka {
    string tytul;
    string autor;
    string rodzaj;
    int rok_wydania;
    int ilosc_min;
    int stan;
    int nrKsiazki;
};
const int MAX_KSIAZEK = 1000;


void domow_ksiazke(Biblioteka& biblioteka){
    system("chcp 65001>>null");

    ifstream plik("ksiazki.txt");
    ofstream plikTymczasowy("ksiazkiTym.txt");
    string linia;
    int nrKsiazkiPlik, iloscKsiazek;

    cout << "Podaj nr książki, jaką chcesz dokupić: "; cin >> nrKsiazkiPlik;
    cout << "Ile egzemplarzy chcesz dokupić do biblioteki: "; cin >> iloscKsiazek;
    int znaleziono = 0;

    if (!plik.is_open() || !plikTymczasowy.is_open()) {
        cout << "Błąd przy otwieraniu plików." << endl;
        return;
    }

    while (getline(plik, linia)) {
        stringstream ss(linia);
        string tytul, autor, rodzaj;
        int rok_wydania, ilosc_min, stan, nrKsiazki;

        getline(ss, tytul, ':');
        getline(ss, autor, ':');
        ss >> rok_wydania;
        ss.ignore();
        getline(ss, rodzaj, ':');
        ss >> ilosc_min;
        ss.ignore();
        ss >> stan;
        ss.ignore();
        ss >> nrKsiazki;

        if (nrKsiazki == nrKsiazkiPlik){
            stan += iloscKsiazek;
            znaleziono = 1;
        }

        plikTymczasowy << tytul << ":" << autor << ":" << rok_wydania << ":" << rodzaj << ":" << ilosc_min << ":" << stan << ":" << nrKsiazki << endl;
    }

    plik.close();
    plikTymczasowy.close();

    if (znaleziono == 1) {
        bool aaa=biblioteka.zloz_zamowienie();
        if (aaa == false){
            return;
        }
        if (remove("ksiazki.txt") != 0) {
            cout << "Błąd przy usuwaniu pliku 'ksiazki.txt'." << endl;
            return;
        }
        if (rename("ksiazkiTym.txt", "ksiazki.txt") != 0) {
            cout << "Bląd przy zmianie nazwy pliku tymczasowego na 'ksiazki.txt'." << endl;
            return;
        }

        cout << "Zaktualizowano stan książki nr " << nrKsiazkiPlik << " o " << iloscKsiazek << " egzemplarzy." << endl;
    } else {
        remove("ksiazkiTym.txt");
        cout << "Nie znaleziono książki o numerze " << nrKsiazkiPlik << "." << endl;
    }
}

int odczytaj_ksiazki_z_pliku(const string& filename, Ksiazka ksiazki[]) {
    ifstream plik(filename);
    string linia;
    int liczbaKsiazek = 0;

    while (getline(plik, linia) && liczbaKsiazek < MAX_KSIAZEK) {
        stringstream ss(linia);
        Ksiazka ksiazka;

        getline(ss, ksiazka.tytul, ':');
        getline(ss, ksiazka.autor, ':');
        ss >> ksiazka.rok_wydania;
        ss.ignore();
        getline(ss, ksiazka.rodzaj, ':');
        ss >> ksiazka.ilosc_min;
        ss.ignore();
        ss >> ksiazka.stan;
        ss.ignore();
        ss >> ksiazka.nrKsiazki;

        ksiazki[liczbaKsiazek] = ksiazka;
        liczbaKsiazek++;
    }

    plik.close();
    return liczbaKsiazek;
}

void stan_ksiazek(){
    ifstream plik("ksiazki.txt");
    string linia;

    while (getline(plik, linia)) {
        Ksiazka ksiazki[MAX_KSIAZEK];
        int liczbaKsiazek = odczytaj_ksiazki_z_pliku("ksiazki.txt", ksiazki);

        string domawianie;
        for (int i = 0; i < liczbaKsiazek; i++) {
            int brakujace = ksiazki[i].ilosc_min - ksiazki[i].stan;
            if (brakujace > 0) {
            cout << "Książka nr " << ksiazki[i].nrKsiazki << ", do poprawnej ilości w bibliotece, brakuje " << brakujace << " egzemplarzy." << endl;
        }
    }
        cout << "Czy chcesz domówić książki? Wpisz tak/nie: "; cin >> domawianie;
        plik.close();

        if (domawianie == "tak"){
            Biblioteka biblioteka;
            domow_ksiazke(biblioteka);
        }
    }
}

void wyswietl_wszystkie_ksiazki() {
    ifstream plik("ksiazki.txt");
    string linia;
    if (!plik.is_open()) {
        cout << "Błąd przy otwieraniu pliku." << endl;
        return;
    }
    cout << "Dane wszystkich książek w bibliotece:" << endl;
    while (getline(plik, linia)) {
        cout << linia << endl;
    }

    plik.close();
}


#endif
