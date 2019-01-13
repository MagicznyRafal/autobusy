

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>

using namespace std;


struct Hour
{
	unsigned short hours;
	unsigned short minutes;
	Hour *next;
};

void insertHour(Hour * & head, unsigned short hours, unsigned short minutes);

struct Line
{
	int number;
	Hour *hoursHead;
	Line *next;
};

Line * getLine(Line * & head, int number);

struct Station
{
	string name;
	Line *linesHead = nullptr;
	Station *next = nullptr;
};

Station * getStation(Station * & head, string name);

void deleteLists(Station * & stationHead);

void generateStations(Station * & stationHead, string & fileName);//g³ówna funkcja generuj¹ca stacje

void generateFiles();



#endif //PCH_H
