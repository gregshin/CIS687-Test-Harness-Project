#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <string>
#include <thread>

using std::string;
using std::thread;

class ThreadManager {
	public:
		ThreadManager();
		ThreadManager(int threads);
		~ThreadManager();
		string startThread(string dllLocation);
		void setMaxThreads();
		void setMaxThreads(int threads);
		int getMaxThreads();
		void setRunningThreads();
		int getRunningThreads();
		bool isThreadAvailable();

		void sampleFunc();
	private:
		// Private helper functions
		string getTime();

		// Private data members
		int maxThreads;
		int runningThreads;
};

#endif