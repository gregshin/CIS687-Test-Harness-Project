#include "ThreadManager.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>

using std::thread;
using std::unique_lock;
using std::mutex;
using std::cout;
using std::endl;
using std::string;
using std::chrono::system_clock;

// Base constructor - creates a number of threads equal to the total number supported by user's CPU minus one
ThreadManager::ThreadManager()
	: taskMutex(), taskAvailable(), stop(false) {
	int numThreads = (thread::hardware_concurrency() > 2)
		? thread::hardware_concurrency() - 1
		: 1;
	setNumThreadsAvailable(numThreads);
	for (auto i = 0; i < numThreads; i++) {
		availableThreads.push_back(thread());
	}
};

// Overload constructor - creates the specified numbers of threads
ThreadManager::ThreadManager(int numThreads)
	: taskMutex(), taskAvailable(), stop(false) {
	setNumThreadsAvailable(numThreads);
	for (auto i = 0; i < numThreads; i++) {
		availableThreads.push_back(thread());
	}
}

// Infinite loop function to check for available tasks in the queue and execute them
// Returns the start and stop time as well as the task result (pass/fail)
void ThreadManager::pollForTasks() {
	for (auto& thr : availableThreads) {
		thr = thread([this]() {
			getResult();
		});
	}

	while (true) {
		numThreadsAvailable++;
		unique_lock<mutex> lock(taskMutex);
		taskAvailable.wait(lock, [this]() { return stop; });
		numThreadsAvailable--;
		string testResult = "";
		try {
			testResult = "Test starting: " + getTime();
			// Run the function
			testResult = testResult + "Test Passed! \n";
		}
		catch (string e) {

			cout << "FAIL" << endl;
		}
		testResult = testResult + "Test ending: " + getTime();
		cout << testResult << endl;
	}
};

// Destructor for the thread manager - ensures all mutexes and threads are safely destroyed
ThreadManager::~ThreadManager() {
	unique_lock<mutex> lock(taskMutex);
	stop = true;
	lock.unlock();
	taskAvailable.notify_all;
	for (auto& thr : availableThreads) {
		thr.join();
	}
};

// Function that returns the number of threads available at any given time
int ThreadManager::getNumThreadsAvailable() {
	return numThreadsAvailable;
};

// Function that sets the number of threads available
void ThreadManager::setNumThreadsAvailable(int threads) {
	numThreadsAvailable = threads;
};

string ThreadManager::getResult() {
	return "weee";
};

void ThreadManager::startThread(function<bool()> func) {

};

// Private helper function to get the time. Used to determine the start and stop time to be displayed
string ThreadManager::getTime() {
	auto rawTime = system_clock::now();
	const time_t convertedTime = system_clock::to_time_t(rawTime);
	char displayTime[30];
	ctime_s(displayTime, sizeof displayTime, &convertedTime);
	return string(displayTime);
}