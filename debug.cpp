#include <iostream>
#include <string> 
#include "debug.h"

using namespace std;

bool debug = false;

//Used to print out simple messages to the console which stand out from everything else

void DebugOutput(string message)
{
	if (debug == true)
		cout << "[[     Debug: " << message << " ]]" << endl;
}