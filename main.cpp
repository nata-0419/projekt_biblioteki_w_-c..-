#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

#include "rejestracjaK.h"
#include "zadaniaNaKsiazkach.h"
#include "bazaKsiazek.h"
#include "znajdzKsiazke.h"
#include "klient.h"
#include "szyfrowanieHasla.h"

using namespace std;

void wyswietl() {
    system("chcp 65001>>null");

    int wybWyswietl;
    int kontynuuj = 1;

    while (kontynuuj) {
    cout << endl;
    cout << "Wybierz cyfrę, która odpowiada plikowi jaki chcesz wyswietlić: " << endl;
    cout << "1. Baze książek" << endl;
    cout << "2. Czytelników biblioteki" << endl;
    cout << "3. Wypożyczone książki" << endl;
    cout << "4. Wrócić do menu pracownika" << endl;
    cout << "Jeśli dokonaleś wyboru, wpisz cyferkę przypisaną czynności: "; cin >> wybWyswietl;
    cout << endl;

    switch (wybWyswietl) {
        case 1:
            wyswietl_wszystkie_ksiazki();
            break;
        case 2:
            wyswietl_wszystkich_czytelnikow();
            break;
        case 3:
            wyswietl_wszystkie_wypozyczenia();
            break;
        case 4:
            kontynuuj = 0;
            break;
        default:
            cout << "Niepoprawny wybór!" << endl;
        }
    }
}

void wyswietl_czas() {
    time_t timestamp = time(NULL);                          // Pobiera bieżący czas w sekundach
    struct tm datetime = *localtime(&timestamp);            // Konwertuje na format lokalny
    char wyswietl[50];                                      // Tablica znaków do przechowywania sformatowanej daty
    strftime(wyswietl, 50, "%d:%m:%Y", &datetime);          // Formatuje czas
    cout << "Witam, dziś jest: " << wyswietl << endl;
    cout << "Miło cię widzieć w naszej bibliotece szkolnej w Mińsku Mazowieckim.";
}

int menu() {
    int wybor;
    cout << "\n Wybierz cyfrę, która poprowadzi cię na odpowiednie konto: " << endl;
    cout << "1. Pracownik" << endl;
    cout << "2. Czytelnik" << endl;
    cout << "3. Opuść bibliotekę" << endl;
    cout << "Podaj wybór: "; cin >> wybor;
    return wybor;
}

void menu_pracownika() {
    int pracownik;
    int kontynuuj = 1;

    while (kontynuuj) {
    cout << endl;
    cout << "Oto konto pracownika. Wybierz cyfrę, która przekieruje cię do bazy z odpowiednim zadaniem, które chcesz wykonać. " << endl;
    cout << "1. Wypożyczyć książkę czytelnikowi" << endl;
    cout << "2. Zwrot książki" << endl;
    cout << "3. Znaleźć miejsce książki w bibliotece" << endl;
    cout << "4. Sprawdźić brakującące egzemplarze książek" << endl;
    cout << "5. Dokup egzemplarze książek" << endl;
    cout << "6. Zamów nowe książki do biblioteki" << endl;
    cout << "7. Wyświetl zawartość plików" << endl;
    cout << "8. Wylogować się z konta pracownika" << endl;
    cout << "Jeśli dokonaleś wyboru, wpisz cyferkę przypisaną czynności: "; cin >> pracownik;
    cout << endl;

    switch (pracownik) {
        case 1:
            wypozycz_ksiazke();
            break;
        case 2:
            zwroc_ksiazke();
            break;
        case 3:
            znajdz_ksiazke();
            break;
        case 4:
            stan_ksiazek();
            break;
        case 5:{
            Biblioteka biblioteka;
            domow_ksiazke(biblioteka);
            break;
        }
        case 6:{
            Biblioteka biblioteka;
            biblioteka.zakup_ksiazki();
            break;
            }
        case 7:
            wyswietl();
            break;
        case 8:
            kontynuuj = 0;
            cout << "Dziękuję za dzisiejszą pracę" << endl;
            break;
        default:
            cout << "Niepoprawny wybór!" << endl;
        }
    }
}

void wybierz_opcje_klienta() {
    int klient;
    int kontynuuj = 1;

    while (kontynuuj) {
    cout << endl;
    cout << "Witaj czytelniku. Wybierz cyfrę, która odpowiada twojemu zadanu na dzisiaj: " << endl;
    cout << "1. Zlaleźć polożenie książki w bibliotece" << endl;
    cout << "2. Sprawdźić ilość książek na swoim koncie" << endl;
    cout << "3. Zarejestrowować się" << endl;
    cout << "4. Wrócić do menu glównego" << endl;
    cout << "Jeśli dokonaleś wyboru, wpisz cyferkę przypisaną czynności: "; cin >> klient;
    cout << endl;

    switch (klient) {
        case 1:
            znajdz_ksiazke();
            break;
        case 2:
            sprawdz_konto_klienta();
            break;
        case 3:
            rejestracja_klienta();
            break;
        case 4:
            kontynuuj = 0;
            break;
        default:
            cout << "Niepoprawny wybór!" << endl;
        }
    }
}

void opusc_biblioteke(){
    cout << "Milo cię bylo gościć w naszej bibliotece. Mamy nadzieję że znalazleś to czego potrzebowaleś"<< endl;
    cout << "Do zobaczenia!"<<endl;
    exit(0);
}

void blad(){
    cout << "Niepoprawny wybór!" << endl;
}

int main() {
    system("chcp 65001>>null");
    wyswietl_czas();

    int wybor;
    int kontynuuj = 1;
    while (kontynuuj){
        wybor = menu();
        switch (wybor) {
        case 1:
            if (logowanie_pracownika()){
                menu_pracownika();
            }
            break;
        case 2:
            wybierz_opcje_klienta();
            break;
        case 3:
            kontynuuj = 0;
            opusc_biblioteke();
            break;
        default:
            blad();
            break;
        }
    }
}
