/** @file */

/*

STRUKTURY PROGRAMU

*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>

using namespace std;

/**
Lista przechowujaca poszczegolne godziny
*/

struct Hour
{
	/// godzina, o ktorej odjezdza autobus
	unsigned short hours;
	///minuty, o jakich odjezdza autobus
	unsigned short minutes;
	///wskaznik na nastepny element
	Hour *next;
};

/**
Funkcja wstawia godziny do listy od razu sortujac je

@param head wskaznik na poczatek listy godzin
@param hours godzina, ktora chcemy wstawic do listy
@param minutes minuty, ktore chcemy wstawic do listy
*/

void insertHour(Hour * & head, unsigned short hours, unsigned short minutes);

/**
Lista przechowujaca informacje o poszczegolnych liniach
*/

struct Line
{
	/// numer linii
	int number;
	/// wskaznik na poczatek listy z godzinami
	Hour *hoursHead;
	/// wskaznik na nastepny element
	Line *next;
};

/**
Funkcja wstawia dany numer linii do listy uprzednio sprawdzajac czy dany numer linii nie znajduje sie juz w liscie

@param head wskaznik na poczatek listy linii
@param number numer linii, ktory chcemy wstawic do listy
@return zwraca wskaznik na linie, ktora wstawilismy(jak juz jest w liscie to zwraca wskaznik na istniejacy element o takiej samej wartosci)
*/

Line * getLine(Line * & head, int number);

/**
Lista przechowujaca informacje o poszczegolnych przystankach
*/

struct Station
{
	///nazwa przystanku
	string name;
	///wskaznik na poczatek listy z liniami
	Line *linesHead = nullptr;
	/// wskaznik na nastepny element
	Station *next = nullptr;
};

/**
Funkcja wstawia dana nazwe stacji do listy uprzednio sprawdzajac czy dana nazwa stacji nie znajduje sie juz w liscie

@param head wskaznik na poczatek listy stacji
@param name nazwa stacji, ktora chcemy wstawic do listy
@return zwraca wskaznik na stacje, ktora wstawilismy(jak juz jest w liscie to zwraca wskaznik na istniejacy element o takiej samej wartosci)
*/

Station * getStation(Station * & head, string name);

/**
Funkcja usuwa liste godzin

@param hourHead wskaznik na poczatek listy godzin
*/

void deleteHourList(Hour *&  hourHead);

/**
Funkcja usuwa liste linii

@param lineHead wskaznik na poczatek listy linii
*/

void deleteLineList(Line *& lineHead);

/**
Funkcja usuwa liste stacji

@param stationHead wskaznik na poczatek listy stacji
*/

void deleteStationList(Station *&stationHead);

/**
Funkcja odczytuje z plikow wejsciowych dane i wstawia je do poszczegolnych list

@param stationHead wskaznik na poczatek listy stacji
@param fileName nazwa pliku, z ktorego odczytywane sa dane
*/
void generateStations(Station * & stationHead, string & fileName);

/**
Funkcja tworzy plik wyjsciowy i wstawia do niego poszczegolny dane

@param head wskaznik na poczatek listy stacji
@param lineHead wskaznik na poczatek listy linii
*/

void generateFiles(Station * & head, Line * & lineHead);



#endif //PCH_H
