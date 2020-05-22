#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <atomic>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <queue>

class ThreadManager {
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
		void startThread();
		bool isThreadAvailable();
		void testLoad();
		void otherTest();
	private:
		// Private helper functions
		std::string getTime();
		void loadDLL(std::string dllLocation);

		// Private data members
		int maxThreads;
		int runningThreads;
		std::vector<std::thread> threads;
		std::mutex taskMutex;
		std::condition_variable taskAvailable;
		std::queue<std::function<bool()>> dlls;
		std::atomic<bool> done;
};

#endif