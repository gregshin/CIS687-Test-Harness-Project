#include "TestExceptionLibrary.h"
#include <string>
using std::string;

bool iTest() {
	string exce = "A PROBLEM IN A DLL";
	throw exce;
	return true;
}