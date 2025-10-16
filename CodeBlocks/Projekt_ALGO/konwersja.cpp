#include "konwersja.h"

string RandomCiag(int iloscLiczb) {
    string liczba = "";
    for (int j = 0; j < iloscLiczb; j++)
    {
        for (int i = 0; i < 8; i++)
            liczba += to_string(rand() % 10);
    }
    return liczba;
}

int** createMacierz(int n) {
    int** macierz = new int* [n];

    for (int i = 0; i < n; i++) {
        macierz[i] = new int[n];
        for (int j = 0; j < n; j++)
            macierz[i][j] = RAND_ONE + rand() % (RAND_SECOND - RAND_ONE + 1);
    }
    return macierz;
}

void printMacierz(int** macierz, int n, ofstream& file) {
    // Nachodzimy maksymaln¹ szerokoœæ liczby w macierzy
    unsigned short int maxWidth = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int numWidth = to_string(macierz[i][j]).length();
            if (numWidth > maxWidth)
                maxWidth = numWidth;
        }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(maxWidth + 1) << macierz[i][j]; //console
            file << setw(maxWidth + 1) << macierz[i][j]; //zapis do pliku
        }
        cout << endl;
        file << endl;
    }
}

void deleteMacierz(int** macierz, int n) {
    for (int i = 0; i < n; i++)
        delete[] macierz[i];
    delete[] macierz;
}

int getElement(int** macierz, int N, int element)
{
    if (element > 0)
    {
        element = element % (N * N);
        return macierz[element / N][element % N];
    }
    else
    {
        element = element % (N * N);
        element = N * N - 1 + element;
        return macierz[element / N][element % N];
    }
}

string getCode(int** macierz, int N, string wiadomosc, unsigned char tablicaZnakow[])
{
    string szyfr = "";

    int iloscLiczb = wiadomosc.size() / 8;
    for (int i = 0; i < iloscLiczb; i++)
    {
        string czescWiadomosci = "";
        for (int C = 0; C < 8; C++)
        {
            czescWiadomosci += wiadomosc[C + i * 8];
        }

        int sumaRogow = macierz[0][0] + macierz[0][N - 1] + macierz[N - 1][0] + macierz[N - 1][N - 1];
        int krok = 1;

        for (int k = 0; k < 4; k++)
        {
            string tekst = "";
            tekst += czescWiadomosci[2 * k];
            tekst += czescWiadomosci[2 * k + 1];

            int indeksZnaku = stoi(tekst);

            char znak = tablicaZnakow[(100 + (indeksZnaku + getElement(macierz, N, sumaRogow * krok)) % 100) % 100];

            szyfr += znak;
            krok += 1;
        }
    }
    return szyfr;
}

int findElement(unsigned char tablicaZnakow[], unsigned char element)
{
    for (int i = 0; i < 100; i++)
    {
        if (element == tablicaZnakow[i])
             return i;
    }
    cout << "\nnie znaleziono takiego znaku - blad" << endl;
    return -1;
}

string getDecode(unsigned char tablicaZnakow[], string nazwaPlikuSzyfr, string nazwaPlikuKlucz)
{
    // wczytywanie szyfru
    fstream plikSzyfru;
    plikSzyfru.open(nazwaPlikuSzyfr);
    if (!plikSzyfru.is_open())
        cout << "Nie udalo sie otworzyc plik: " << nazwaPlikuSzyfr << endl;
    string szyfr = "";
    while (true)
    {
        string nowaWiad;
        plikSzyfru >> nowaWiad;
        szyfr += nowaWiad;
        if (!plikSzyfru.good())
            break;
    }
    plikSzyfru.close();

    // wczytywanie klucza
    fstream plikKlucza;
    plikKlucza.open(nazwaPlikuKlucz);
    if (!plikKlucza.is_open())
        cout << "Nie udalo sie otworzyc plik: " << nazwaPlikuKlucz << endl;

    int tab[12 * 12];
    int indeks = 0;

    while (true)
    {
        if (!plikKlucza.good())
        {
            cout << "Koniec" << endl;
            break;
        }

        string nowaWiad;
        plikKlucza >> nowaWiad;
        if (nowaWiad == "")
            break;
        tab[indeks] = stoi(nowaWiad);
        indeks += 1;
    }
    plikKlucza.close();

    int N = sqrt(indeks);
    indeks = 0;
    int** macierz = createMacierz(N);
    for (int w = 0; w < N; w++)
        for (int k = 0; k < N; k++)
        {
            macierz[w][k] = tab[indeks];
            indeks++;
        }

    string wiadomosc = "";
    int iloscLiczb = szyfr.size() / 4;
    for (int k = 0; k < iloscLiczb; k++)
    {
        string czescSzyfru = "";
        for (int C = 0; C < 4; C++)
            czescSzyfru += szyfr[C + k * 4];

        int sumaRogow = macierz[0][0] + macierz[0][N - 1] + macierz[N - 1][0] + macierz[N - 1][N - 1];
        int krok = 1;

        for (int i = 0; i < 4; i++)
        {
            if (!(findElement(tablicaZnakow, czescSzyfru[i]) + 1)) // +1 bo 0 to tez false
            {
                cout << "Koniec" << endl;
                break;
            }

            int indeksZnaku = findElement(tablicaZnakow, czescSzyfru[i]);
            //cout<<indeksZnaku<<endl;
            int cofnietaLiczba = indeksZnaku - getElement(macierz, N, sumaRogow * krok);

            string liczba = to_string((100 + (cofnietaLiczba) % 100) % 100);

            // sprawdza czy jest cyfra, jesli tak to dopisuje '0' na poczatku bo to_string i stoi ucina 0 na poczatku
            if (liczba.size() == 1)
                liczba = "0" + liczba;

            wiadomosc += liczba;
            krok += 1;
        }
    }
    return wiadomosc;
}

bool zapiszDoPliku(string nazwaPliku, string wiadomosc)
{
    ofstream plik(nazwaPliku);
    if (!plik.is_open())
    {
        cout << "blad przy otwieraniu pliku " << nazwaPliku << endl;
        return false;
    }
    plik << wiadomosc;
    plik.close();

    return true;
}
