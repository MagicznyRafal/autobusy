#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>

#include "functions.h"

using namespace std;

void insertHour(Hour * & head, unsigned short hours, unsigned short minutes)
{
	Hour * newHour = new Hour{ hours, minutes, nullptr };

	if (head == nullptr)  // je¿eli lista jest pusta
	{
		head = newHour;
	}
	else//jak coœ ju¿ w niej jest
	{
		Hour *temp = head;
		Hour *prevTemp = nullptr;
		while (temp != nullptr)
		{
			if (temp->hours > hours || (temp->hours == hours && temp->minutes >= minutes))
			{
				newHour->next = temp;
				if (prevTemp != nullptr)
				{
					prevTemp->next = newHour;
				}
				else
				{
					head = newHour;
				}
				return;
			}

			prevTemp = temp;
			temp = temp->next;
		}

		prevTemp->next = newHour;
	}
}


Station * getStation(Station * & head, string name)
{
	if (head == nullptr)
	{
		Station *newStation = new Station{ name, nullptr, nullptr };
		head = newStation;
		return newStation;
	}
	else
	{
		Station *temp = head;
		Station *prevTemp = nullptr;

		while (temp != nullptr)
		{
			if (temp->name.compare(name) == 0)
			{
				return temp;
			}

			prevTemp = temp;
			temp = temp->next;
		}

		Station * newStation = new Station{ name, nullptr, nullptr };
		prevTemp->next = newStation;
		return newStation;
	}
}


Line * getLine(Line * & head, int number)
{
	if (head == nullptr)
	{
		Line * newLine = new Line{ number, nullptr, nullptr };
		head = newLine;
		return newLine;
	}
	else
	{
		Line *temp = head;
		Line *prevTemp = nullptr;

		while (temp != nullptr)
		{
			if (temp->number == number)
			{
				return temp;
			}
			else if (temp->number > number)
			{
				Line * newLine = new Line{ number, nullptr, temp };

				if (prevTemp != nullptr)
				{
					prevTemp->next = newLine;
				}
				else
				{
					head = newLine;
				}
				return newLine;
			}

			prevTemp = temp;
			temp = temp->next;
		}

		Line * newLine = new Line{ number, nullptr, nullptr };
		prevTemp->next = newLine;
		return newLine;
	}
}

void generateFiles(Station * & head, Line * & lineHead)
{
	Station *stationTemp = head;
	Line *lineTemp = lineHead;
	Hour *hourTemp = nullptr;
	hourTemp = lineTemp->hoursHead;
	do
	{
		string stationName = stationTemp->name;
		string txt = ".txt";

		ofstream file(stationName + txt);
		if (file.is_open())
		{
			file << stationTemp->name << endl << "==== \n \n \n";
			do
			{
				file << "linia " << lineTemp->number << "\n \n";
				while (hourTemp != nullptr)
				{
					if (hourTemp->next != nullptr)
					{
						file << setfill('0') << setw(2) << hourTemp->hours << ":";
						file << setfill('0') << setw(2) << hourTemp->minutes << ", ";
					}
					else
					{
						file << setfill('0') << setw(2) << hourTemp->hours << ":";
						file << setfill('0') << setw(2) << hourTemp->minutes << "\n \n";
					}
					hourTemp = hourTemp->next;
				}
				lineTemp = lineTemp->next;
				if (lineTemp != nullptr)
				{
					hourTemp = lineTemp->hoursHead;
				}
			} while (lineTemp != nullptr);
		}
		file.close();
		stationTemp = stationTemp->next;
		if (stationTemp != nullptr)
		{
			lineTemp = stationTemp->linesHead;
			hourTemp = lineTemp->hoursHead;
		}
	} while (stationTemp != nullptr);
}

void deleteHourList(Hour *&  hourHead)
{
	while (hourHead)
	{
		Hour * hourTemp = hourHead->next;
		delete hourHead;
		hourHead = hourTemp;
	}
	
	
}

void deleteLineList(Line * & lineHead)
{
	while (lineHead)
	{
		Line * lineTemp = lineHead->next;
		deleteHourList(lineHead->hoursHead);
		delete lineHead;
		lineHead = lineTemp;
	}
}

void deleteStationList(Station *&stationHead)
{
	while (stationHead)
	{
		Station * stationTemp = stationHead->next;
		deleteLineList(stationHead->linesHead);
		delete stationHead;
		stationHead = stationTemp;
	}
}


void generateStations(Station * & stationHead, string & fileName)
{
	int lineNum = 0;

	ifstream infile(fileName);

	string a, b;
	while (infile >> a >> b)
	{
		if (a.compare("LINIA") == 0)
		{
			lineNum = stoi(b);
		}
		else
		{
			auto station = getStation(stationHead, b);
			auto size = a.find(":");
			auto hours = stoi(a.substr(0, size));
			auto minutes = stoi(a.substr(3, size));
			auto line = getLine(station->linesHead, lineNum);
			insertHour(line->hoursHead, hours, minutes);
		}
	}
	generateFiles(stationHead, stationHead->linesHead);
}