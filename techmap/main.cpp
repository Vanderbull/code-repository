#include <iostream>
#include "starmap.h"

using namespace std;

int main()
{
	StarMap *Map=new StarMap(100,100);
	Map->Dump();
	delete Map;
	return 0;
}
