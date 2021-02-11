#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>


using namespace std; 

struct podlista {	//struktura podlisty danego elementu listy (etykiet)
	string autor;	//zmienna przechowuj�ca nazwisko autora danej ksi��ki kt�ra znajduje si� w podli�cie
	string tytul;  //zmienna przechowuj�ca tytu� danej ksi��ki kt�ra znajduje si� w podli�cie
	podlista*podlista_nast;  //wska�nik na nast�pny element podlisty
	podlista*podlista_poprzedni; //wska�nik na poprzedni element podlisty

};
struct lista //struktura typu lista zawieraj�ca etykiety
{
	string etykieta;	//zmienna przechowuj�ca nazw� konkretnej etykiety	
	lista*lista_nast;  //wska�nik na nast�pny element listy etykiet
	lista*lista_poprzedni; //wska�nik na poprzedni element listy etykiet
	podlista *Head = nullptr; // wska�nik na g�ow� podlisty 
	podlista *Tail = nullptr; //wska�nik na ogon podlisty 
};
struct lista_info //pomocnicza struktura 
{
	int licznik = 0; //licznik kt�ry posiada informacj� o tym czy istnieje ju� jaki� element funkcji etykiet, je�li nie to warto�� wynosi zero, je�li istnieje to warto�� wi�ksza od zera
	lista *H; // wska�nik na g�ow� listy etykiet
	lista *T; //wska�nik na ogon listy etykiet

};
