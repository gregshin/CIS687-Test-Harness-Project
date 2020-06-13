#include "InputQueue.h"
#include "ThreadManager.h"

#include <atomic>
using std::atomic;

#include <chrono>
using std::chrono::system_clock;

#include <condition_variable>
using std::condition_variable;

#include <functional>
using std::function;

#include <iostream>
using std::cout;
using std::endl;

#include <mutex>
using std::mutex;
using std::unique_lock;

#include <string>
using std::remove;
using std::string;
using std::wstring;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

#include <Windows.h>

// Default constructor
ThreadManager::ThreadManager() 
	: runningThreads{ 0 }, done{ false }
{
	setMaxThreads();
	setThreads();
};

// Overloaded constructor - allows setting number of threads
ThreadManager::ThreadManager(int threads) 
	: runningThreads{ 0 }, done{ false }
{
	setMaxThreads(threads);
	setThreads();
};

// Default destructor
ThreadManager::~ThreadManager()
{
	unique_lock<mutex> lock(taskMutex);
	done = true;
	lock.unlock();
	taskAvailable.notify_all();
	for (auto& thr : threads) {
		thr.join();
	}
	lpcIQ->~InputQueue();
};

// Empty the input queue and load the DLL information
vector<string> ThreadManager::startProcessing()
{
	int testsSent = lpcIQ->getcount();
	while (!lpcIQ->getempty())
	{
		loadDLL(lpcIQ->dequeue());
	}

	// Wait for all the results to be available before returning the results vector
	unique_lock<mutex> lock(taskMutex);
	resultsAvailable.wait(lock, [this, testsSent]() {return results.size() == testsSent; });
	return results;
};

// Wrapper for input queue's enqueue function
void ThreadManager::enqueue(string path)
{
	lpcIQ->enqueue(path);
};

// Getter for maximum number of threads
int ThreadManager::getMaxThreads()
{
	return maxThreads;
};

// Setter for maximum number of threads - sets max to total hardware can support
void ThreadManager::setMaxThreads()
{
	maxThreads = (thread::hardware_concurrency() > 2)
		? thread::hardware_concurrency() - 1
		: 1;
};

// Setter for maximum number of threads - sets to user specified number
void ThreadManager::setMaxThreads(unsigned int threads)
{
	maxThreads = threads;
};

// Getter for the number of threads currently running
int ThreadManager::getRunningThreads()
{
	return runningThreads;
};

// Setter for the number of threads running
void ThreadManager::setRunningThreads()
{
	runningThreads = 0;
};

// Setter for vector of threads
void ThreadManager::setThreads()
{
	function<void()> startThreadWrapper = [this]()
	{
		startThread();
	};

	for (auto i = 0; i < maxThreads; i++)
	{
		threads.push_back(thread(startThreadWrapper));
	}
};

// Function to start a thread and run a DLL process
void ThreadManager::startThread()
{
	while (true)
	{
		unique_lock<mutex> lock(taskMutex);
		taskAvailable.wait(lock, [this]() {return !dlls.empty() || done; });
		if (dlls.empty() && done)
		{
			return;
		}
		dllInfo dllDetails = dlls.front();
		dlls.pop();
		try
		{
			dllDetails.startTime = getTime() + ",";
			dllDetails.result = dllDetails.task() ? "Pass" : "Fail";
		}
		catch (string e)
		{
			dllDetails.result = "Fail,";
			dllDetails.errorMessage = e;
		}
		dllDetails.endTime = getTime() + ",";
		results.push_back(dllDetails.location + dllDetails.startTime + dllDetails.endTime + dllDetails.result + dllDetails.errorMessage);
		lock.unlock();
	}
};

// Helper function to return a string representing the current time
string ThreadManager::getTime()
{
	auto rawTime = system_clock::now();
	const time_t convertedTime = system_clock::to_time_t(rawTime);
	char displayTime[30];
	ctime_s(displayTime, sizeof displayTime, &convertedTime);
	string timeString(displayTime);
	timeString.erase(remove(timeString.begin(), timeString.end(), '\n'), timeString.end());
	return timeString;
};

// Defining the holder for the iTest function
typedef bool(__stdcall* _iTest)();

// Function to load a DLL given a location and add that DLL's iTest function to the task queue
void ThreadManager::loadDLL(string dllLocation)
{
	// Convert string to wide string
	wstring location(dllLocation.begin(), dllLocation.end());

	// Attempt to load the dll
	HINSTANCE getDLL = LoadLibrary(location.c_str());
	if (!getDLL)
	{
		cout << "Could not load the DLL!" << endl;
		exit(1);
	}

	// Attempt to get the function
	_iTest iTest = (_iTest)GetProcAddress(getDLL, "iTest");
	if (!iTest)
	{
		cout << "Could not load the DLL function!" << endl;
		exit(1);
	}

	// Lock the list of DLLs to add the new DLL
	unique_lock<mutex> lock(taskMutex);
	dlls.push(
		{
			"",
			"",
			dllLocation + ",",
			"",
			"",
			iTest
		}
	);
	lock.unlock();
	taskAvailable.notify_one();
};
