#include "ThreadManager.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	ThreadManager thr;
	thr.testLoad();
	thr.otherTest();
	thr.testLoad();
	thr.otherTest();
	return 0;
}