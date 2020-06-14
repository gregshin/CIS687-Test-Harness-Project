#include "TestWaitLibrary.h"
#include <chrono>
using std::chrono_literals::operator""s;

#include <thread>
using std::this_thread::sleep_for;

bool iTest() {
	sleep_for(5s);
	return true;
}