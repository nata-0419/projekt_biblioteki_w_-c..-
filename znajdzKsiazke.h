#ifndef ZNAJDZKSIAZKE_H_INCLUDED
#define ZNAJDZKSIAZKE_H_INCLUDED

#include "zadaniaNaKsiazkach.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool porownaj_rodzaj_a_tytul(const Ksiazka& k1, const Ksiazka& k2) {
    if (k1.rodzaj == k2.rodzaj) {
        return k1.tytul < k2.tytul;
    }
    return k1.rodzaj < k2.rodzaj;
}

void miejsce_ksiazki(const string& rodzaj) {
    if (rodzaj == "bajka") {
        cout << "Ten rodzaj znajduje się na regale 1-5." << endl;
    } else if (rodzaj == "powiesc") {
        cout << "Ten rodzaj znajduje się na regale 6-10." << endl;
    } else if (rodzaj == "kryminal") {
        cout << "Ten rodzaj znajduje się na regale 11-15." << endl;
    } else if (rodzaj == "fantastyka") {
        cout << "Ten rodzaj znajduje się na regale 15-20." << endl;
    } else if (rodzaj == "kulinarne") {
        cout << "Ten rodzaj znajduje się na regale 21-25." << endl;
    } else {
        cout << "Nie znaleziono regału dla takiego rodzaju." << endl;
    }
}

void oblicz_miejsce_ksiazki(Ksiazka ksiazki[], int liczbaKsiazek) {
    sort(ksiazki, ksiazki + liczbaKsiazek, porownaj_rodzaj_a_tytul);

    int miejsca_na_polce = 0;
    int aktualna_polka = 1;

    for (int i = 0; i < liczbaKsiazek; i++) {
        int stan = ksiazki[i].stan;
        while (stan > 0) {
            int miejsca_do_zajecia = min(stan, 30 - miejsca_na_polce);
            stan -= miejsca_do_zajecia;
            miejsca_na_polce += miejsca_do_zajecia;

            if (miejsca_na_polce == 30) {
                aktualna_polka++;
                miejsca_na_polce = 0;
            }
        }
    }
    cout << "Książka znajduje się na półce nr " << aktualna_polka << "." << endl;
}

void wyszukaj_ksiazke_po_tytule(const string& tytul, Ksiazka ksiazki[], int liczbaKsiazek) {
    sort(ksiazki, ksiazki + liczbaKsiazek, porownaj_rodzaj_a_tytul);

    for (int i = 0; i < liczbaKsiazek; i++) {
        if (ksiazki[i].tytul == tytul) {
            cout << "Znaleziono książkę: " << ksiazki[i].tytul << " autor: " << ksiazki[i].autor << endl;
            miejsce_ksiazki(ksiazki[i].rodzaj);
            oblicz_miejsce_ksiazki(ksiazki, liczbaKsiazek);
            return;
        }
    }
    cout << "Książka o tytule " << tytul << " nie została znaleziona." << endl;
}

void wyszukaj_ksiazke_po_autorze(const string& autor, Ksiazka ksiazki[], int liczbaKsiazek) {
    for (int i = 0; i < liczbaKsiazek; i++) {
        if (ksiazki[i].autor == autor) {
            cout << "Znaleziono książkę autora: " << ksiazki[i].autor << " tytul: " << ksiazki[i].tytul << endl;
            miejsce_ksiazki(ksiazki[i].rodzaj);
            oblicz_miejsce_ksiazki(ksiazki, liczbaKsiazek);
            return;
        }
    }
    cout << "Książki autora " << autor << " nie zostały znalezione." << endl;
}

void wyszukaj_ksiazke_po_rodzaju(const string& rodzaj, Ksiazka ksiazki[], int liczbaKsiazek) {
    for (int i = 0; i < liczbaKsiazek; i++) {
        if (ksiazki[i].rodzaj == rodzaj) {
            cout << "Znaleziono książki w rodzaju: " << ksiazki[i].rodzaj << endl;
            miejsce_ksiazki(ksiazki[i].rodzaj);
            return;
        }
    }
    cout << "Książki o rodzaju " << rodzaj << " nie zostały znalezione." << endl;
}

void znajdz_ksiazke() {
    system("chcp 65001>>null");

    string znajdzPo;
    Ksiazka ksiazki[MAX_KSIAZEK];
    int liczbaKsiazek = odczytaj_ksiazki_z_pliku("ksiazki.txt", ksiazki);

    cout << "Wybierz po czym chcesz znaleźć swoją książkę w bibliotece: tytul, rodzaj, autor" << endl;
    cout << "Jeśli dokonaleś wybór, wpisz słowo po, którym chcesz wyszukać książkę: ";

    cin.ignore();
    getline(cin, znajdzPo);

    if (znajdzPo == "tytul") {
        string tytul;
        cout << "Podaj tytul książki: ";
        getline(cin, tytul);
        wyszukaj_ksiazke_po_tytule(tytul, ksiazki, liczbaKsiazek);
    }
    else if (znajdzPo == "rodzaj") {
        string rodzaj;
        cout << "Podaj rodzaj książki: ";
        getline(cin, rodzaj);
        wyszukaj_ksiazke_po_rodzaju(rodzaj, ksiazki, liczbaKsiazek);
    }
    else if (znajdzPo == "autor") {
        string autor;
        cout << "Podaj autora książki: ";
        getline(cin, autor);
        wyszukaj_ksiazke_po_autorze(autor, ksiazki, liczbaKsiazek);
    }
    else {
        cout << "Niepoprawny wybór!" << endl;
    }
}

#endif
