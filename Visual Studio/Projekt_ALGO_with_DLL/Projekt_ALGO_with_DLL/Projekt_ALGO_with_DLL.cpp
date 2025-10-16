#include "konwersjadll.h"

using namespace std;

int main() {
    unsigned char tablicaZnakow[100];

    for (int i = 0; i < 100; i++)
    {
        tablicaZnakow[i] = (unsigned char)(i + 34); // zaczyna od znaku nr 34 w kodzie ASCII rozszerzonym do 256 znakow bo unsigned char
    }
    //tablicaZnakow[7]=char(125);//zamiana spacji na '}'

    srand(time(0));
    unsigned short int rozmiar = 0;
    string wiadomosc = "";
    long long int iloscLiczb = 0;
    int** macierz = nullptr;
    ofstream key;
    ofstream szyfr;
    string odszyfrowanaWiadomosc = "";
    //MENU:
    unsigned short int wybor = 0;
    while (wybor != 6) {
        cout << "------------------------------------------\n"
            << "MENU:\n"
            << "1. Wprowadz ilosc liczb dla wiadomosci\n"
            << "2. Utworz macierz\n"
            << "3. Wyswietl i zapisz macierz\n"
            << "4. Zaszyfruj i zapisz\n"
            << "5. Odszyfruj i zapisz\n"
            << "6. Wyjdz z programu\n"
            << "------------------------------------------\n";
        cin >> wybor;
        switch (wybor) {
        case 1:
            cout << "Ile liczb 8-cyfrowych wykorzystamy?" << endl;
            cin >> iloscLiczb;
            wiadomosc = RandomCiag(iloscLiczb);
            break;
        case 2:
            do {
                cout << "Podaj rozmiar macierzy (od 4 do 12): ";
                cin >> rozmiar;
            } while (rozmiar < 4 || rozmiar > 12);
            macierz = createMacierz(rozmiar);
            cout << "Macierz " << rozmiar << "x" << rozmiar << " zostala utworzona" << endl;
            break;
        case 3:
            if (macierz == nullptr) {
                cout << "Nie jest mozliwe wypisanie i zapisanie macierzy bez jej utworzenia" << endl;
                break;
            }
            else {
                key.open("key.txt");
                if (key.is_open()) {
                    cout << "Macierz:" << endl;
                    printMacierz(macierz, rozmiar, key);
                    key.close();
                }
                else
                    cout << "Nie udalo sie otworzyc plik key.txt" << endl;
            }
            break;
        case 4:
            if (wiadomosc == "") {
                cout << "Nie jest mozliwe szyfrowanie bez wiadomosci" << endl;
                break;
            }
            else if (macierz == nullptr) {
                cout << "Nie jest mozliwe szyfrowanie bez macierzy" << endl;
                break;
            }
            else {
                szyfr.open("szyfr.txt");
                if (szyfr.is_open()) {
                    cout << "Twoj szyfr:" << endl;
                    cout << getCode(macierz, rozmiar, wiadomosc, tablicaZnakow) << endl;
                    szyfr << getCode(macierz, rozmiar, wiadomosc, tablicaZnakow) << endl;
                    szyfr.close();
                }
                else
                    cout << "Nie udalo sie otworzyc plik szyfr.txt" << endl;
            }
            break;
        case 5:
            if (wiadomosc == "") {
                cout << "Nie jest mozliwe odszyfrowanie bez wiadomosci" << endl;
                break;
            }
            else if (macierz == nullptr) {
                cout << "Nie jest mozliwe szyfrowanie bez macierzy" << endl;
                break;
            }
            else {
                odszyfrowanaWiadomosc = getDecode(tablicaZnakow, "szyfr.txt", "key.txt");

                if (odszyfrowanaWiadomosc == wiadomosc)
                    cout << "Poprawne odszyfrowanie." << endl;
                else
                    cout << "Niepoprawne odszyfrowanie!" << endl;

                zapiszDoPliku("odszyfrowane.txt", odszyfrowanaWiadomosc);
            }
            break;
        case 6:
            cout << "WYJSCIE Z PROGRAMU.\n";
            break;
        default:
            cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            break;
        }
    }

    deleteMacierz(macierz, rozmiar);
    return 0;
}
