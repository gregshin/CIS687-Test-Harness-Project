#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "InputQueue.h"
#include <atomic>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <queue>

class ThreadManager 
{
	public:
		// Constructors
		ThreadManager();
		ThreadManager(int threads);
		
		// Deconstructor
		~ThreadManager();

		// Getters and Setters
		int getMaxThreads();
		void setMaxThreads();
		void setMaxThreads(unsigned int threads);
		int getRunningThreads();
		void setRunningThreads();
		void setThreads();

		// Public functions
		void enqueue(std::string path);
		void startProcessing(std::vector<std::string>& resultVector);
		void startThread();

	private:
		// Instance of InputQueue
		InputQueue* lpcIQ = new InputQueue(100);

		// Private helper functions
		std::string getTime();
		void loadDLL(std::string dllLocation);

		// Private data members
		std::queue<std::function<bool()>> dlls;
		std::atomic<bool> done;
		int maxThreads;
		int runningThreads;
		std::condition_variable taskAvailable;
		std::condition_variable resultsAvailable;
		std::mutex taskMutex;
		std::vector<std::string> results;
		std::vector<std::thread> threads;
};

#endif