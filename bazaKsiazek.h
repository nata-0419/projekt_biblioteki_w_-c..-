#ifndef bazaKsiazek_h
#define bazaKsiazek_h

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

class Biblioteka {
private:
    string tytul, autor, rodzaj;
    int rok_wydania, ilosc_min, stan;
    int nrKsiazki;

public:
    void zakup_ksiazki() {
        system("chcp 65001>>null");

        cout << "Podaj tytuł książki: "; cin >> tytul;
        cout << "Podaj autora książki: "; cin >> autor;
        cout << "Podaj rok wydania książki: "; cin >> rok_wydania;
        rodzaj = wybierz_rodzaj();
        cout << "Podaj minimalną ilość jaka musi być na stanie w bibliotece: "; cin >> ilosc_min;
        cout << "Podaj ile kupujesz egzemplarzy książki: "; cin >> stan;
        nrKsiazki = odczytaj_ostatni_nr_ksiazki() + 1;

        zloz_zamowienie();
    }
    bool zloz_zamowienie() {
        cout << "Zamówienie zostało wysłane.\n";
        this_thread::sleep_for(chrono::seconds(5));
        system ("cls");

        char decyzja;
        cout << "Czy zamówienie zostalo oplacone? (t/n): "; cin >> decyzja;
        if (decyzja == 't' || decyzja == 'T') {
            cout << "Zamówienie zostało przyjęte. Rozpoczynamy realizację zamówienia...\n";
            return opoznienie1();
        } else {
            cout << "Zamówienie nie zostało przyjęte. Paczka zostaje anulowana.\n";
            exit(0);
        }
    }

private:
    int odczytaj_ostatni_nr_ksiazki() {
        ifstream plik("numer_ksiazki.txt");
        int ostatniNrKsiazki = 900;

        if (plik.is_open()) {
            plik >> ostatniNrKsiazki;
            plik.close();
        } else {
            cout << "Plik numer_ksiazki.txt nie istnieje, zaczynamy od 901." << endl;
        }
        return ostatniNrKsiazki;
    }

    void zapisz_numer_ksiazki(int nrKsiazki) {
        ofstream plik("numer_ksiazki.txt");
        if (plik.is_open()) {
            plik << nrKsiazki;
            plik.close();
        } else {
            cout << "Błąd przy zapisywaniu numeru książki!" << endl;
        }
    }

    void zapisz_ksiazke() {
        ofstream plik("ksiazki.txt", ios::app);
        if (plik.is_open()) {
            plik << tytul << ":" << autor << ":" << rok_wydania << ":" << rodzaj << ":" << ilosc_min << ":" << stan << ":" << nrKsiazki << endl;
                cout << "Zamówiono do biblioteki książkę " << tytul <<endl;
        } else {
            cout << "Błąd przy zapisywaniu danych o książce!" << endl;
        }
        zapisz_numer_ksiazki(nrKsiazki);
    }

    string wybierz_rodzaj() {
        int wybor_rodzaju;
        string rodzaj;

        cout << "Wybierz rodzaj książki:" << endl;
        cout << "1. Bajka" << endl;
        cout << "2. Powieść" << endl;
        cout << "3. Kryminal" << endl;
        cout << "4. Fantastyka" << endl;
        cout << "5. Kulinarna" << endl;
        cout << "Wybierz odpowiedni numer: "; cin >> wybor_rodzaju;

        switch(wybor_rodzaju) {
            case 1: rodzaj = "bajka"; break;
            case 2: rodzaj = "powiesc"; break;
            case 3: rodzaj = "kryminal"; break;
            case 4: rodzaj = "fantastyka"; break;
            case 5: rodzaj = "kulinarne"; break;
            default: cout << "Niepoprawny wybór!"; break;
        }
        return rodzaj;
    }

    bool opoznienie1() {
        int licznik = 0;
        while (licznik < 2) {
            cout << "Kompletowanie zamówienia... (" << (licznik + 1) << "/2)\n";
            this_thread::sleep_for(chrono::seconds(5));
            licznik++;
        }
        cout << "Paczka jest gotowa do wysylki!"<<endl;
        cout << endl;
        return kurier();
    }

    bool kurier() {
        char decyzja;
        int prob = 0;
        while (prob < 3) {
            cout << "Czy paczka została odebrana przez kuriera? (t/n): ";
            cin >> decyzja;

            if (decyzja == 't' || decyzja == 'T') {
                cout << "Paczka została odebrana przez kuriera. Kontroluj trasę paczki...\n";
                return opoznienie2();
            } else if (decyzja == 'n' || decyzja == 'N') {
                prob++;
                if (prob >= 3) {
                    cout << "Przekroczono maksymalną liczbę prób. Paczka zostaje anulowana.\n";
                    return false;
                }
                cout << "Paczka nie została odebrana. Czekamy na kuriera...\n";
                this_thread::sleep_for(chrono::seconds(5));
            } else {
                cout << "Nieprawidłowa odpowiedź. Proszę wpisać 't' lub 'n'.\n";
            }
        }
    }

    bool opoznienie2() {
        int licznik = 0;
        while (licznik < 2) {
            cout << "Zamówienie w drodze... (" << (licznik + 1) << "/2)\n";
            this_thread::sleep_for(chrono::seconds(5));
            licznik++;
        }
        cout << "Paczka dostarczona do miejsca docelowego!" << endl;
        cout << endl;
        return dostarczenie();
    }

    bool dostarczenie() {
        char decyzja;
        int prob = 0;
        while (prob < 3) {
            cout << "Czy paczka została odebrana przez zamawiającego? (t/n): ";
            cin >> decyzja;

            if (decyzja == 't' || decyzja == 'T') {
                cout << "Paczka została odebrana. Czekamy na zapisanie książek do bazy biblioteki.\n";
                return opoznienie3();
            } else if (decyzja == 'n' || decyzja == 'N') {
                prob++;
                if (prob >= 3) {
                    cout << "Przekroczono maksymalną liczbę prób. Paczka zostaje anulowana.\n";
                    return false;
                }
                cout << "Paczka nie została odebrana. Czekamy na odebranie zamówienia...\n";
                this_thread::sleep_for(chrono::seconds(5));
            } else {
                cout << "Nieprawidłowa odpowiedź. Proszę wpisać 't' lub 'n'.\n";
            }
        }
    }

    bool opoznienie3() {
        int licznik = 0;
        while (licznik < 2) {
            cout << "Zatwierdzanie egzemplarzy.... (" << (licznik + 1) << "/2)\n";
            this_thread::sleep_for(chrono::seconds(5));
            licznik++;
        }
        cout << "Książki są w bazie bibliotecznej!" << endl;
        cout << endl;
        return rozlozenie();
    }

    bool rozlozenie() {
        char decyzja;
        int prob = 0;
        while (prob < 3) {
            cout << "Czy książki zostały rozłożone na półki? (t/n): ";
            cin >> decyzja;

            if (decyzja == 't' || decyzja == 'T') {
                cout << "Książki znajdują się na odpowiednich półkach.\n";
                this_thread::sleep_for(chrono::seconds(5));
                system("cls");
                zapisz_ksiazke();
                return true;
            } else if (decyzja == 'n' || decyzja == 'N') {
                prob++;
                if (prob >= 3) {
                    cout << "Przekroczono maksymalną liczbę prób. Program zostaje zakończony.\n";
                    return false;
                }
                cout << "Książki nie zostały rozłożone. Czekamy na dalsze informacje...\n";
                this_thread::sleep_for(chrono::seconds(5));
            } else {
                cout << "Nieprawidłowa odpowiedź. Proszę wpisać 't' lub 'n'.\n";
            }
        }
    }
};

#endif
