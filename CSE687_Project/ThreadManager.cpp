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
void ThreadManager::startProcessing(std::vector<std::string>& resultVector)
{
	while (!lpcIQ->getempty())
	{
		loadDLL(lpcIQ->dequeue());
	}
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

// Setter for maximum number of threads - sets to user specified number or max possible for CPU
void ThreadManager::setMaxThreads(unsigned int threads)
{
	maxThreads = (thread::hardware_concurrency() > threads)
		? threads
		: thread::hardware_concurrency() - 1;
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
	function<void()> task;
	string result = "";
	while (true)
	{
		unique_lock<mutex> lock(taskMutex);
		taskAvailable.wait(lock, [this]() {return !dlls.empty() || !done; });
		if (dlls.empty())
		{
			return;
		}
		task = dlls.front();
		dlls.pop();
		lock.unlock();
		try
		{
			result = "Test starting at: " + getTime();
			task();
			result += "Test Passed!\n";
		}
		catch (string e)
		{
			result += "Test failed with the following error:\n";
			result += e;
		}
		result += "Test ended at: " + getTime();
		cout << result << endl;
	}
};

// Helper function to return a string representing the current time
string ThreadManager::getTime()
{
	auto rawTime = system_clock::now();
	const time_t convertedTime = system_clock::to_time_t(rawTime);
	char displayTime[30];
	ctime_s(displayTime, sizeof displayTime, &convertedTime);
	return string(displayTime);
};

// Defining the holder for the iTest function
typedef bool(__stdcall* _iTest)();

// Function to load a DLL given a location and add that DLL's iTest function to the task queue
void ThreadManager::loadDLL(string dllLocation, std::vector<std::string>& resultVector)
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
	dlls.push(iTest);
	lock.unlock();
	taskAvailable.notify_one();
};
