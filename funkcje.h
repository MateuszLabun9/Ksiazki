#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>




using namespace std; 

bool wczytaj(lista_info&dane_z_lista_info, ifstream & plik);//funkcja wczytuj�ca plik tekstowy, zapisuj�ca autor�w i tytu�y oraz etykiety 

void sprawdz(lista_info&dane_z_lista_info, string etykieta, string autor, string tytul);//funkcja kt�ra sprawdza czy dana etykieta ju� znjaduje si� na li�cie etykiet

void pokazList(lista *listainfo, ofstream & plik_wyjsciowy);//funkcja zapisuj�ca zawarto�� listy i podlisty do pliku Ksiazki

void zwolnij(lista_info & listainfo);//funkcja kt�ra usuwa elementy list

void dodaj(string dane_do_dodania, lista_info &dane_z_lista_info, string autor, string tytul);//funkcja kt�ra dodaje kolejny element listy etykiet

void dodajpodliste(string autor, string tytul, lista *glowa);//funkcja kt�ra dodaje kolejny element podlisty

int zaladowanie_pliku(int argc, char **argv, ifstream & plik, ofstream & plik_wyjsciowy);

int porownaj(string etykieta, string etykieta2);

void help();
