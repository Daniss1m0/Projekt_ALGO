#ifndef KONWERSJADLL_H
#define KONWERSJADLL_H

#ifdef _WIN32
#define EXPORT __declspec(dllimport)
#else
#define EXPORT
#endif

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip> //biblioteke dla printMacierz
#include <cstdlib> // abs()
#include <cmath> // abs()

using namespace std;

extern "C" EXPORT string RandomCiag(int iloscLiczb);
extern "C" EXPORT int** createMacierz(int n);
extern "C" EXPORT void printMacierz(int** macierz, int n, ofstream & file);
extern "C" EXPORT void deleteMacierz(int** macierz, int n);
extern "C" EXPORT int getElement(int** macierz, int N, int element);
extern "C" EXPORT string getCode(int** macierz, int N, string wiadomosc, unsigned char tablicaZnakow[]);
extern "C" EXPORT int findElement(unsigned char tablicaZnakow[], unsigned char element);
extern "C" EXPORT string getDecode(unsigned char tablicaZnakow[], string nazwaPlikuSzyfr, string nazwaPlikuKlucz);
extern "C" EXPORT bool zapiszDoPliku(string nazwaPliku, string wiadomosc);

#endif // KONWERSJADLL_H

