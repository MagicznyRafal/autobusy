#include "functions.h"
#include <iostream>
#include <string>
#define _CRTDBG_MAP_ALLOC

void onexit(void)
{
	_CrtDumpMemoryLeaks();
}
using namespace std;
int main(int argc, char** argv)
{
	atexit(onexit);
	{
		if (strcmp(argv[1], "-g") == 0)
		{
			cout << "Provided parameter is wrong! Possible parameter is -i" << endl;
		}
		else if (strcmp(argv[1], "-i") == 0)
		{
			cout << "Generating stations..." << endl;
			Station *stationHead = nullptr;
			for (int i = 2; i < argc; i++)
			{
				string fileName = argv[i];
				generateStations(stationHead, fileName);
			}
			deleteStationList(stationHead);
		}
		else
		{
			cout << "Provided parameter is wrong" << endl;
		}

		return 0;
	}

}