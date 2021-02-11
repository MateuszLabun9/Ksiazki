#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include "struktury.h"
#include "funkcje.h";


using namespace std;


int porownaj(string etykieta, string etykieta2)
{

	 // Funkcja, kt�ra por�wnuje napis b�d�cy w li�cie z dopiero co wprowadzonym napisem

		int dlugosc = etykieta.length() + 1;// Sprawdzam d�ugo�� napisu 
		char * tablica = new char[dlugosc]; // dynamicznie lokuje tyle pami�ci ile potrzeba do zapisania danego napisu (+1 poniewa� na ko�cu string mamy zawsze NULL)
		//strcpy_s(tablica, dlugosc, etykieta.c_str()); // Funkcja, kt�ra przepisuje stringa (wprowadzone s�owo) do tablicy typu char o odpowiedniej d�ugo�ci
		for (int i = 0; i < dlugosc; i++)
		{
			tablica[i] = etykieta[i];
			
		}

		int dlugosc1 = etykieta2.length() + 1; // Sprawdzam d�ugo�� napisu 
		char * tablica1 = new char[dlugosc1]; //dynamicznie lokuje tyle pami�ci ile potrzeba do zapisania danego napisu (+1 poniewa� na ko�cu string mamy zawsze NULL)
		//strcpy_s(tablica1, dlugosc1, etykieta2.c_str()); // Funkcja, kt�ra przepisuje stringa (aktualne s�owo) do tablicy typu char o odpowiedniej d�ugo�ci
		for (int i = 0; i < dlugosc1; i++)
		{
			tablica1[i] = etykieta2[i];
			
		}

		// Funkcja, kt�ra por�wnuje wprowadzone s�owo z aktualnym s�owem w liscie, literka po literce, traktuje du�e litery jako ma�e podczas por�wnywania
		if (_stricmp(tablica, tablica1) == 0) // Je�li wprowadzone s�owo i aktualne s�owo w liscie s� identyczne
		{
			return 0;
		}
		else if (strcoll(tablica, tablica1) < 0) // Je�li wprowadzone s�owo jest pierwsze w kolejno�ci alfabetycznej, a za nim aktualne s�owo w liscie
		{
			return 1;
		}
		else if (strcoll(tablica, tablica1) > 0) // Je�li wprowadzone s�owo jest nastepne w kolejno�ci alfabetycznej, a pierwsze jest aktualne s�owo w liscie
		{
			return 2;
		}


		delete[] tablica; // Usuwam zalokowan� pami�� aby nie odprowadzi� do wycieku pami�ci 
		delete[] tablica1;
	
}

void dodaj(string etykieta, lista_info &dane_z_lista_info, string autor, string tytul)
{
	if (dane_z_lista_info.licznik == 0)//sprawdzam czy istnieje ju� jaki� element w li�cie 
	{
		dane_z_lista_info.licznik++;//zwi�kszam licznik kt�ry m�wi ile posiadam element�w listy 
		lista *pom = new lista;//tworz� nowy wska�nik pomocniczy i przypisuj� mu nowy element listy (nowy obszar pami�ci)
		pom->etykieta = etykieta;//jako nazwa etykiety w tym elemnecie listy zapisuj� string etykieta kt�rego dostaj� po wczytaniu danej linijki pliku txt 
		pom->lista_nast = nullptr;//ustawiam warto�� wska�nika na nast�pny element listy etykiet jako nullptr, poniewa� moja lista dodaje nowe elementy na ko�cu 
		pom->lista_poprzedni = nullptr;//z racji tego �e jest to pierwszy element listy warto�� wska�nika na poprzedni ustawiam jako nullprt, w lis�ie mam teraz tylko jeden element w�a�nie ten, kt�ry teraz jest tworzony
		dane_z_lista_info.H = pom;//wska�nik na g�ow� listy etykiet ustawiam na adres jaki aktualnie przyjmuje pom czyli na m�j nowy element listy 
		dane_z_lista_info.T = pom;//wska�nik na ogon listy etykiet r�wnie� ustawiam na adres pom czyli na adres nowego elementu dlatego �e mam aktualnie list� z jednym elementem
		dodajpodliste(autor, tytul, pom); //wywo�uj� funkcje kt�ra dodaje podlist� zawieraj�ca autora i tytu� danej ksia�ki do kt�rej nale�y wcze�niej utworzona etykieta
	}
	else//je�eli istnieje jaki� element w li�cie czyli licznik jest wi�kszy od zera to tworzymy po prostu kolejny element listy etykiet
	{
		dane_z_lista_info.licznik++;//zwi�kszam licznik ilo�ci element�w w li�cie etykiet
		lista *pom = new lista;//tworz� nowy wska�nik pomocniczy u przypisuj� mu nowy element listy (nowy obszar pami�ci)
		pom->etykieta = etykieta; // jako nazwa etykiety w tym elemnecie listy zapisuj� stringa etykieta kt�rego "dostaj�" po wczytaniu danej linijki pliku txt
		pom->lista_nast = nullptr;;//ustawiam warto�� wska�nika na nast�pny element listy etykiet jako nullptr, poniewa� moja lista dodaje nowe elementy na ko�cu 
		pom->lista_poprzedni = dane_z_lista_info.T;//ustawiam wska�nik na poprzedni elemnt na to co pokazuje aktualnie wska�nik ogon listy 
		dane_z_lista_info.T->lista_nast = pom;//
		dane_z_lista_info.T = pom;//ustawiam wska�nik ogon listy na element kt�ry w�a�nie powsta� o adresie takim jak pokazuje wska�nik pom
		dodajpodliste(autor, tytul, pom);
	}
}

void sprawdz(lista_info&dane_z_lista_info, string etykieta, string autor, string tytul)//funkcja kt�ra sprawdza czy dana etykieta ju� znjaduje si� na li�cie etykiet
{
	lista *pom = dane_z_lista_info.H;//tworze wska�nik pomocniczy 
	bool nie_ma;//tworz� flag� 
	nie_ma = true;//ustawiam flag� na warto�� true
	while (pom != nullptr)
	{
		if (porownaj(etykieta, pom->etykieta)==0/*pom->etykieta==etykieta*/)//jezeli etykieta kt�r� chce doda� do listy jest jaka sama jak ju� istniej�cy element listy to dodaje tylko podliste z autorem i tytu�em
		{
			dodajpodliste(autor, tytul, pom);//wywyo�anie funkcji kt�ra dodaje do podlisty autora i tytu� 
			nie_ma = false;//je�li ta p�tla si� wykona czyli etykieta kt�r� chce doda� jest taka sama jak juz istniej�ca to tylko dodaje el podlisty 
		}
		pom = pom->lista_nast;//ustawiam wska�nik na nast�pnym element w li�cie etykiet
	}
	if (nie_ma)//je�eli wcze�niejszy "if" nie zadzia�a� to znaczy ze flaga nie jest podniesiona czyli w aktulanej liscie etykiet nie ma takiej samej etykiety jak� chc� doda�
	{
		dodaj(etykieta, dane_z_lista_info, autor, tytul);//wywyo�anie funkcji, kt�ra dodaje nowy elemnt listy etykiet
	}

}
void dodajpodliste(string autor, string tytul, lista *glowa)//fukncja dodaj�ca kolejny element podlisty
{
	if (glowa->Head == nullptr)//jezeli wskaznik na glowe podlisty elementu z listy etykiet jest nullptr to znaczy ze go nie ma to tworze zupelnie nowa podliste dal tego el.
	{
		glowa->Head = new podlista;//tworz� nowy element podlisty i przypisuje mu wska�nik g�owy poniewa� to pierwszy element
		glowa->Head->autor = autor;//w miejscu autora wpisuj� pobranego autora 
		glowa->Head->tytul = tytul;//w miejscu tytu�u wpisuj� pobrany tytu�
		glowa->Head->podlista_nast = nullptr;//wska�nik na nastepny element ustawiam jako nullprt, poniewa� w podli�cie mam tylko jeden element
		glowa->Head->podlista_poprzedni = nullptr;//wska�nik na poprzedni element usatwiam r�wnie� na nullptr
		glowa->Tail = glowa->Head;//ustawiam wska�nik ogona podlisty na to samo co g�owa poniewa� mam tylko jeden element 
	}
	else//je�eli podlista posiada jeden element lub wi�cej
	{
		podlista *pom; //tworz� wska�nik pomocniczy
		pom = glowa->Head; //ustawiam ten wska�nik na g�ow�
		int ile = 0; //tworz� zmienn� pomocnicz�
		bool nie_jest; //tworz� now� flag� 
		nie_jest = false; //ustawiam warto�� flagi na true
		while (glowa->Head != nullptr) //je�eli wska�nik na g�ow� nie b�dzie wskazywa� na nullprt
		{
			int i = (porownaj(autor, pom->autor));
			switch (i)
			{
			case 1:
			{
				if (ile == 0) //je�eli jest to pierwsze wywo�anie p�tli to znaczy �e dodaje nowy element przed tym na kt�ry aktualnie wksazuje g�owa
				{
					pom->podlista_poprzedni = new podlista; //dodaje now� podlist� przed elementem na kt�ry wskazuje g�owa
					pom->podlista_poprzedni->podlista_nast = glowa->Head;//nasz nowy element kt�ry jest teraz pierwszy w podliscie wsksazuje na ten element kt�ry wczesniej by� pierwszy czyli na to co wskazuje g�owa
					glowa->Head = pom->podlista_poprzedni;//teraz g�owa wskazuje na element kt�ry w�asnie dodajemy
					glowa->Head->autor = autor; //uzupe�niam zawarto�� podlisty
					glowa->Head->tytul = tytul; //uzupe�niam zawarto�� podlisty
					glowa->Head->podlista_poprzedni = nullptr; //wska�nik na poprzedni wskazuje na nullprt poniewa� jest to teraz pierwszy element podlisty
					nie_jest = true;
				}
				else //je�eli nie jest to pierwsze wywo�anie czyli dodajemy element pomi�dzy dwa inne 
				{
					pom->podlista_poprzedni->podlista_nast = new podlista; //dodaje nowy element podlisty
					pom->podlista_poprzedni->podlista_nast->podlista_nast = pom; //poprzedni element wskazuje teraz na nowy obszar kt�ry przed chwil� stworzyli�my
					pom->podlista_poprzedni->podlista_nast->podlista_poprzedni = pom->podlista_poprzedni; //nowy element wskazuje teraz na poprzedni w podliscie
					pom->podlista_poprzedni = pom->podlista_poprzedni->podlista_nast; //element kt�ry jest po nowym elemencie wskazuje teraz na niego 
					pom->podlista_poprzedni->autor = autor; //uzupe�niam warto�� podlisty
					pom->podlista_poprzedni->tytul = tytul; //uzupe�niam warto�� podlisty
					nie_jest = true;
				}
				break;
			}
			case 2:
			{
				
				if (pom==glowa->Tail)//je�eli pokazujemy na ostatni element a to co chcemy dodac dalej jest alfabetycznie po�niej to dodajemy ten element jako ostatni, za ogon
				{
					glowa->Tail->podlista_nast = new podlista; //ogon pokazuje teraz na nowo utworzony element 
					glowa->Tail->podlista_nast->podlista_poprzedni = glowa->Tail; // ustawiam wska�nik nowego elementu na element poprzedni
					glowa->Tail = glowa->Tail->podlista_nast; // przypisuje wska�nik ogona do nowego elementu
					glowa->Tail->autor = autor; //wype�niam warto�� podlisty 
					glowa->Tail->tytul = tytul; //wype�niam warto�� podlisty 
					glowa->Tail->podlista_nast = nullptr; // ustwiam warto�� wska�nika na nast�pny element jako nullprt 
					nie_jest = true;
				}
				else {
					pom = pom->podlista_nast;
				}
				break;
			}
			case 0: //je�li dwie ksazki s� takie same to dodaje jedna za drug� 
			{
				if (ile == 0) //je�eli jest to pierwsze wywo�anie p�tli to znaczy �e dodaje nowy element przed tym na kt�ry aktualnie wksazuje g�owa
				{
					pom->podlista_poprzedni = new podlista; //dodaje now� podlist� przed elementem na kt�ry wskazuje g�owa
					pom->podlista_poprzedni->podlista_nast = glowa->Head;//nasz nowy element kt�ry jest teraz pierwszy w podliscie wsksazuje na ten element kt�ry wczesniej by� pierwszy czyli na to co wskazuje g�owa
					glowa->Head = pom->podlista_poprzedni;//teraz g�owa wskazuje na element kt�ry w�asnie dodajemy
					glowa->Head->autor = autor; //uzupe�niam zawarto�� podlisty
					glowa->Head->tytul = tytul; //uzupe�niam zawarto�� podlisty
					glowa->Head->podlista_poprzedni = nullptr; //wska�nik na poprzedni wskazuje na nullprt poniewa� jest to teraz pierwszy element podlisty
					nie_jest = true;
				}
				else
				{
					pom->podlista_poprzedni->podlista_nast = new podlista; //dodaje nowy element podlisty
					pom->podlista_poprzedni->podlista_nast->podlista_nast = pom; //poprzedni element wskazuje teraz na nowy obszar kt�ry przed chwil� stworzyli�my
					pom->podlista_poprzedni->podlista_nast->podlista_poprzedni = pom->podlista_poprzedni; //nowy element wskazuje teraz na poprzedni w podliscie
					pom->podlista_poprzedni = pom->podlista_poprzedni->podlista_nast; //element kt�ry jest po nowym elemencie wskazuje teraz na niego 
					pom->podlista_poprzedni->autor = autor; //uzupe�niam warto�� podlisty
					pom->podlista_poprzedni->tytul = tytul; //uzupe�niam warto�� podlisty
					nie_jest = true;
				}
				break;
			}

			
			
			}
			ile++;
			if (nie_jest)//jezeli przejrza�em ca�� podlist� i �aden autor nie by� alfabetycznie wcze�niej to dodaj ksiazke jako ostatni element podlisty 
			{
				break;
			}
		}
	}
}
bool wczytaj(lista_info &dane_z_lista_info, ifstream & plik)  //lista &lista, podlista &dane_z_podlisty funkcja wczytuj�ca zawartosc pliku tekstowego linijka po linijce 
{
	//plik.open("Text.txt"); //otwieram plik o nazwie Text.txt
	string linia; //tworz� zmienn� pomocnicz� kt�ra b�dzie przechowywa�a linijk� wczytan� z pliku 

	
		plik.seekg(0, ios::beg); // wstawienie wska�nika na pocz�tek pliku

		do
		{
			int licznik = 0; //tworz� zmienn� pomocnicz� 
			int ilosc = 0;
			string autor; //tworz� zmienn� pomocnicz� przechowuj�c� autora
			string tytul; //tworz� zmienn� pomocnicz� przechowuj�c� tytu�
			string etykieta; //tworz� zmienn� pomocnicz� przechowuj�c� etykiete
			string reszta;//tworze pomocniczego stringa w kt�rym zapisz� etykiet� bez dodatkowych spacji 
			string cos;
			
			getline(plik, linia); // pobieram z pliku ca�� linijk�
			int dlugosc = linia.length(); // tworz� zmienn� przechowuj�c� d�ugos� pobranej linii tekstu 
			for (int r = 0; r < dlugosc; r++)//w tej petli sprawdzam ile jest srednik�w w ca�ej linijce 
			{
				if (linia[r] == ';')//jesli jest ich mniej niz 2 onazacz ze uzytkownik blednie wpisa� ksiazke, program zignoruje ta linijk� i wykona p�tle do nast�pnej linijki
				{
					ilosc++;
				}
			}
			if (ilosc < 2)
			{
				continue;
			}
			int i = 0; // zmienna pomocnicza 
			if (dlugosc < 5)// Je�eli linijka kodu bedzie mniejsza b�d� r�wna 5 to znaczy �e u�ytkownik wpisa� niepoprawnie dane i pomijam wtedy t� linijk�
			{
				continue;
			}
			while (linia[i] != ';')//czytam autora i zaposuje go 
			{
				if (linia[i] == '/' || linia[i] == '.' || linia[i] == ',' || linia[i] == '(' || linia[i] == ')' || linia[i] == '!' || linia[i] == '@' || linia[i] == '#' || linia[i] == '$'
					|| linia[i] == '%' || linia[i] == '^' || linia[i] == '&' || linia[i] == '*' || linia[i] == '-' || linia[i] == '+' || linia[i] == '=' || linia[i] == '[' || linia[i] == ']'
					|| linia[i] == '{' || linia[i] == '}' || linia[i] == '"' || linia[i] == '<' || linia[i] == '>' || linia[i] == '~' || linia[i] == '`' || linia[i] == '|' || linia[i] =='_'
					||linia[i]=='\t')//usuawm przypadkowe b�edy u�ytkownika ignoruj�c niek�tre znaki 
					i++;
				else if ((linia[i] == ' ') && (linia[(i + 1)] == ' '))// usuwam ci�g przecink�w zamieniaj�c go w jeden przecinek
				{
					i++;
				}
				else {
					autor = autor + linia[i]; // sklejam autora 
					i++; // zwi�kszam zmienn� kt�ra m�wi na jakim miejscu w linii jestem
				}

			}
			int m = autor.length();
			if (m == 0)// jezelu uzytkownik nie poda� autora przechodze do nastepnej linikjki ignoruj�c dalsz� cz�� aktualnej 
			{
				continue;
			}
			
			i++; // zwi�kszam zmienn� aby wska�nik przesun�� si� z ';' na kolejny znak 
			while (linia[i] != ';')//czytam linie i ja zapisuje
			{
				if (linia[i] == '/' || linia[i] == '.' || linia[i] == ',' || linia[i] == '(' || linia[i] == ')' || linia[i] == '!' || linia[i] == '@' || linia[i] == '#' || linia[i] == '$'
					|| linia[i] == '%' || linia[i] == '^' || linia[i] == '&' || linia[i] == '*' || linia[i] == '-' || linia[i] == '+' || linia[i] == '=' || linia[i] == '[' || linia[i] == ']'
					|| linia[i] == '{' || linia[i] == '}' || linia[i] == '"' || linia[i] == '<' || linia[i] == '>' || linia[i] == '~' || linia[i] == '`' || linia[i] == '|' || linia[i] == '_' || linia[i] == '\t')//usuawm przypadkowe b�edy u�ytkownika ignoruj�c niek�tre znaki 
					i++;
				else
				{
					tytul = tytul + linia[i]; //sklejam tytu�
					i++; // zwi�kszam zmienn� kt�ra m�wi na jakim miejscu w linii jestem
				}
			}

			
			int q = i;
		
			while (q < dlugosc)// wykonuje p�tle sprawdzaj�c� i usuwaj�c� nadmiaj przecink�w 
			{
				if (linia[q] == '/' || linia[q] == '.'  || linia[q] == '(' || linia[q] == ')' || linia[q] == '!' || linia[q] == '@' || linia[q] == '#' || linia[q] == '$'
					|| linia[q] == '%' || linia[q] == '^' || linia[q] == '&' || linia[q] == '*' || linia[q] == '-' || linia[q] == '+' || linia[q] == '=' || linia[q] == '[' || linia[q] == ']'
					|| linia[q] == '{' || linia[q] == '}' || linia[q] == '"' || linia[q] == '<' || linia[q] == '>' || linia[q] == '~' || linia[q] == '`' || linia[q] == '|' || linia[q] == '_'
					|| linia[q] == ' ' ||linia[q] == '\t')
				{
					q++;
				}
				else if ((linia[q] == ',') && (linia[(q + 1)] == ','))// usuwam ci�g przecink�w zamieniaj�c go w jeden przecinek
				{
					q++;
				}
				else//dodaje kolejne litery do string�w 
				{
					reszta= reszta + linia[q]; // tworze stringa reszta w kt�rym b�de mia� wszystkie etykiety sklaejone jednym stringiem 
					q++;
				}

			}
			int j = reszta.length();//sprawdzam dlugosc stringa reszta czyli stringa w kt�rym mam zapisane wszystkie etykiety 
		
			
			for (int m=0; m <j; m++)			//petla sprawdzajaca ile w linijce jest przecinkow, jesli znajdzie jakis to zwieksza wartosc licznika
			{
				
				if (reszta[m] == ',') // czytam linijk� do ko�ca i jeli napotkam przecinek to zwi�kszam licznik
				{					
						licznik++;//ilosc tych przecinkow, ilosc etykiet jest o jeden wieksza niz ilosc przecinkow
					
				}
			}

			int g = 0;
			for (int k = 0; k < (licznik + 1); k++) // p�tla kt�ra skleja etykiety w linijce 
			{
				
				g++;
				while ((reszta[g] != ',') && (g < j)) {

					etykieta = etykieta + reszta[g]; // sklejam etykiet� 
					g++;


				}
				int e = etykieta.length();
				if (e < 2) {
					continue;
				}
				

				
					sprawdz(dane_z_lista_info, etykieta, autor, tytul); // wywo�uj� funkcj� kt�ra najpierw sprawdza czy etykieta kt�r� chc� doda� ju� istnieje w li�cie etykiet
					// je�li nie istnieje to dodaje nowy element listy etykiet a do tego elementu tworz� podlist� z autorem i tytu�em 
					etykieta = ""; // czyszcz� zawarto�� etykiety aby by�o mo�liwe wczytanie kolejnej 
					
					cos = "";
				
			}
		} while (!plik.eof()); // powtarzam dop�ki nie natrafi� na koniec pliku 

		plik.close(); // zamykam plik 
		return true;
	

}
void help() // funkcja kt�ra wy�wietla komunikat w przypadku b�ednego wprowadzenia argument�w
{
	cout << endl<< "=================================================" << endl;
	cout << "======================POMOC=====================" << endl;
	cout << "Argumenty wprowadzono w sposob nieprawidlowy" << endl;
	cout << " -i  argument wejscia Text.txt" << endl;
	cout << "-o argument wyjscia Etykiety.txt" << endl;
	cout << "Prosz� spr�bowa� ponownie z argumentami jak wy�ej" << endl;
	cout << "=================================================" << endl;

}
void pokazList(lista * listainfo, ofstream & plik_wyjsciowy) // funkcja zapisuj�ca zawarto�� listy i podlisty do pliku Ksiazki
{
	
	lista *kolejny;	//wskaznik o nazwie kolejny
	podlista *pom;
	kolejny = listainfo;
	
	while (kolejny != nullptr)
	{
		plik_wyjsciowy << endl;
		plik_wyjsciowy << "etykieta to " << kolejny->etykieta << endl;

		while (kolejny->Head != nullptr)
		{
			plik_wyjsciowy << " autor : " << kolejny->Head->autor << " tytul : " << kolejny->Head->tytul << endl;
			kolejny->Head = kolejny->Head->podlista_nast;
			plik_wyjsciowy << '\t';
		}
		kolejny = kolejny->lista_nast;
		plik_wyjsciowy << endl << endl;
	}
	plik_wyjsciowy << "\n";
}
void zwolnij(lista_info & listainfo) // funkcja kt�ra zwalnia pami�� po wykonaniu programu 
{
	lista *pom; // tworz� wska�nik pomocniczy 
	podlista * wsk; // wska�nik pomocniczy 
	while (listainfo.H != nullptr) //dop�ki wska�nik g�owy listy nie wskazuje na nullprt 
	{
		pom = listainfo.H; // wska�nik pomocniczy wskazuje na g�ow� 
	
		while (listainfo.H->Tail!=nullptr) // dop�ki wska�nik ogona podlisty danego elementy nie jest r�wny nullprt usuwam elementy podlisty od ko�ca 
		{
			wsk = listainfo.H->Tail; // wska�nik pokazuje teraz na to co ogon podlisty 
			listainfo.H->Tail = listainfo.H->Tail->podlista_poprzedni;// ogon pokazuje na poprzedni element podlisty 
			delete wsk; // usuwam wska�nik 
		}
		listainfo.H = listainfo.H->lista_nast; // g�owa listy pokazuje teraz na nast�pny element listy 
		delete pom; // usuwam wska�nik 
	}
}

int zaladowanie_pliku(int argc, char** argv, ifstream & plik, ofstream & plik_wyjsciowy) { // Funkcja , kt�ra za�adowuje pliki do programu
	// "-i" dotyczy pliku wejsciowego
	// "-o" dotyczy pliku wyjsciowego

	bool poprawnie = false;
	int zmienna1 = 1; // Zmienna pomocnicza 
	int zmienna2 = 1;
	for (int i = 1; i < argc; i++)
	{
		if (argc > 1 && argv[i] == (string) "-i")
			zmienna1 = i;
		if (argc > 1 && argv[i] == (string) "-o")
			zmienna2 = i;
	}
	if (argc > 1 && argv[zmienna1] == (string) "-i") 
	{  // Je�eli ilo�� argument�w jest wi�ksza od jedynki i jednoczesnie drugi argument to "-i"
		if ((!argv[zmienna1 + 1])|| !argv[zmienna2 + 1]) { // Je�eli nie zosta�a okre�lona scie�ka drugiego argumentu
			cout << "Nie okre�lono scie�ki wej�ciowej" << endl; // Je�eli otwarcie pliku si� nie powiod�o
			help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku nie poprawnego wprowadzenia argument�w podczas uruchamiania programu
			return 0;
		}
		else { // Je�eli zosta�a okre�lona scie�ka drugiego argumentu
			plik.open(argv[zmienna1 + 1]); // Skojarzenie obiektu plik_wejsciowy z scie�k� "-i"
			if (plik.is_open() == 1) // Sprawdzenie czy plik do odczytu zosta� otwarty poprawnie
			{ 
				cout << "Plik wejsciowy zosta� otworzony prawid�owo" << endl; // Je�eli otwarcie pliku si� nie powiod�o
				plik.seekg(0, ios::end);
				if(plik.tellg())
				{
					
					if (argc > 1 && argv[zmienna2] == (string) "-o") // Je�eli ilo�� argument�w jest wi�ksza od jedynki i jednoczesnie trzeci argument to "-o"
					{


						if (!argv[zmienna2 + 1] || argv[zmienna2 + 1] == (string)"-i") // Je�eli nie zosta�a okre�lona scie�ka czwartego argumentu
						{
							cout << "Nie okre�lono �cie�ki wyj�ciowej" << endl; //Je�eli otwarcie pliku si� nie powiod�o
							help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku nie poprawnego wprowadzenia argument�w podczas uruchamiania programu
							return 0;
						}
						else
							plik_wyjsciowy.open(argv[zmienna2 + 1]); // Skojarzenie obiektu plik_wyjsciowy z scie�k� "-o"
						if (plik_wyjsciowy.is_open() == 1) // Sprawdzenie czy plik do zapisu zosta� otwarty poprawnie
						{
							cout << "Plik wyj�ciowy zosta� utworzony prawid�owo" << endl; // Je�eli otwarcie pliku si� nie powiod�o
							return 1;
						}
						else
						{
							cout << "Nie uda�o si� otworzy� pliku wyj�ciowego z podanej �cie�ki" << endl;  // Je�eli otwarcie pliku si� nie powiod�o 
							help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku nie poprawnego wprowadzenia argument�w podczas uruchamiania programu
							return 0;
						}
					}
					else
					{  // Je�eli nie zosta�a okre�lona scie�ka trzeciego argumentu
						cout << "Nie okre�lono �cie�ki wyj�ciowej" << endl;  // Odpowiedni komunikat
						help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku nie poprawnego wprowadzenia argument�w podczas uruchamiania programu
						return 0;
					}
				}
				else
				{
					cout << "Plik wejsciowy jest pusty" << endl;
					help();
					return 0;
				}
			}
			else 
			{
				cout << endl<< "Nie uda�o si� otworzy� pliku wej�ciowego z podanej �cie�ki" << endl;  // Je�eli otwarcie pliku si� nie powiod�o 
				help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku nie poprawnego wprowadzenia argument�w podczas uruchamiania programu
				return 0;
			}
		}
	}
	
	else
	{
		help(); // Funkcja, wy�wietlaj�ca pomocne informacje w przypadku  b��dnego wprowadzenia argument�w podczas uruchamiania programu
		return 0;
	}
};

