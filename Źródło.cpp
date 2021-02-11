#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include "struktury.h"
#include "funkcje.h";


using namespace std;



int main(int argc, char **argv)
{
	ifstream plik; //tworz� obiekt do obs�ugi strumienia
	ofstream plik_wyjsciowy; //tworz� obiekt do obs�ugi strumienia
	int wynik;
	setlocale(LC_ALL, "polish");//ustawiam lokalizacje na polska
	lista_info moja_lista; // tworz� list� o nazwie moja lista 
	moja_lista.H = nullptr;//ustawiam wska�nik listy etykiet na nullptr
	moja_lista.T = nullptr;//ustawiam wska�nik listy etykiet na nullptr
	wynik = zaladowanie_pliku(argc, argv, plik, plik_wyjsciowy);//wywo�anie funkcji sprawdzaj�cej poprawno�� plik�w wejscia, wyj�cia oraz argument�w. Liczba jak� zwr�ci ta funkcja zapisywana jest w zmiennej 
	if (wynik == 0) // je�eli funkcja za�adowanie pliku zwr�ci warto�� 0 
	{
		cout <<endl<< "Nie udalo sie poprawnie zaladowac pliku" << endl;
		cout << "Program zostanie zamkniety" << endl;
		return 0;//Nast�puje zamkni�cie programu 
	}
	if (wczytaj(moja_lista, plik) == true)	//sparwdzam czy uda�o si� poprawnie wczyta� wszystkie linie z pliku wej�ciowego
	{
		cout << "Udalo sie wczytac wszystkie ksiazki z pliku z ksiazkami " << endl;//Je�eli tak, stosowny komunikat 
	}
	else if (wczytaj(moja_lista, plik) == false) // je�eli nie uda�o by si� poprawnie wczyta� to wy�wietlam nast�puj�ce kominukaty. 
	{
		cout << "Nie uda�o si� wczyta� poprawnie ksi��ki" << endl;
		cout << "Nastapi zakonczenie dzialania programu" << endl;
		return 0;//Nast�puje zamkni�cie programu 
		
	}

	pokazList(moja_lista.H, plik_wyjsciowy); //funkcja zapisuj�ca zawarto�� listy i podlisty do pliku Ksiazki

	cout << "ilosc list : " << moja_lista.licznik << endl; // wypisuj� ilo�� list etykiet powsta�ych w skutek pracy programu 

	zwolnij(moja_lista);//usuni�cie listy;

	system("pause");
}

