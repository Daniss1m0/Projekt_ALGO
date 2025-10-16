#ifndef KONWERSJA_H
#define KONWERSJA_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip> //biblioteke dla printMacierz
#include <cstdlib> // abs()
#include <cmath> // abs()

//Zakres [RAND_ONE;RAND_SECOND]
#define RAND_ONE -10
#define RAND_SECOND 10

using namespace std;

string RandomCiag(int iloscLiczb);
int** createMacierz(int n);
void printMacierz(int** macierz, int n, ofstream& file);
void deleteMacierz(int** macierz, int n);
int getElement(int** macierz, int N, int element);
string getCode(int** macierz, int N, string wiadomosc, unsigned char tablicaZnakow[]);
int findElement(unsigned char tablicaZnakow[], unsigned char element);
string getDecode(unsigned char tablicaZnakow[], string nazwaPlikuSzyfr, string nazwaPlikuKlucz);
bool zapiszDoPliku(string nazwaPliku, string wiadomosc);

#endif
