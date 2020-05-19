#include "ThreadManager.h"



#include <chrono>

#include <iostream>

#include <string>

#include <thread>

#include <time.h>



using std::chrono::system_clock;

using std::cout;

using std::endl;

using std::string;

using std::thread;



// Default constructor

ThreadManager::ThreadManager()

	: runningThreads{ 1 }

{

	setMaxThreads();

};



// Overloaded constructor - allows setting number of threads

ThreadManager::ThreadManager(int threads)

	: runningThreads{ 1 }

{

	setMaxThreads(threads);



};



// Default destructor

ThreadManager::~ThreadManager() {



};



// Function to start a thread and run a DLL process

string ThreadManager::startThread(string dllLocation) {

	runningThreads++;

	string result = "";

	result += "Test starting at: " + getTime();

	// parse DLL

	thread thr([]() {cout << "wee" << endl; });

	thr.detach();

	/*

	try {

		result += "This is the test! \n";

		thread thr(sampleFunc());

		thr.join();

		result += "Test Passed! \n";

	}

	catch (string e) {

		result += e;

		result += "Test Failed! \n";

	}

	*/

	result += "Test ending at: " + getTime();

	runningThreads--;

	return result;

};



// Getter for maximum number of threads

int ThreadManager::getMaxThreads() {

	return maxThreads;

};



// Setter for maximum number of threads - sets max to total hardware can support

void ThreadManager::setMaxThreads() {

	maxThreads = (thread::hardware_concurrency() > 2)

		? thread::hardware_concurrency() - 1

		: 1;

};



// Setter for maximum number of threads - sets to user specified number or max possible for CPU

void ThreadManager::setMaxThreads(int threads) {

	maxThreads = (thread::hardware_concurrency() > threads)

		? threads

		: thread::hardware_concurrency() - 1;

};



int ThreadManager::getRunningThreads() {

	return runningThreads;

}



void ThreadManager::setRunningThreads() {

	runningThreads = 0;

}



bool ThreadManager::isThreadAvailable() {

	return runningThreads < maxThreads;

};



// Helper function to return a string representing the current time

string ThreadManager::getTime() {

	auto rawTime = system_clock::now();

	const time_t convertedTime = system_clock::to_time_t(rawTime);

	char displayTime[30];

	ctime_s(displayTime, sizeof displayTime, &convertedTime);

	return string(displayTime);

};



// Helper function for testing

void ThreadManager::sampleFunc() {

	std::this_thread::sleep_for(std::chrono::seconds(2000));

};