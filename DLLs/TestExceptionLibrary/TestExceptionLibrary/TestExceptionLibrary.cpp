#include "TestExceptionLibrary.h"
#include <string>
using std::string;

bool iTest() {
	string exce = "A PROBLEM IN A DLL\n";
	throw exce;
	return true;
}