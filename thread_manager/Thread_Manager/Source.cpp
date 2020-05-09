#include "ThreadManager.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	ThreadManager thr;
	for (int i = 0; i < 5; i++) {
		cout << thr.startThread("wee") << endl;
	}
	return 0;
}