#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>

using std::vector;
using std::thread;
using std::function;
using std::mutex;
using std::condition_variable;
using std::string;

class ThreadManager {
	public:
		ThreadManager();
		ThreadManager(int numThreads);
		~ThreadManager();
		void pollForTasks();
		int getNumThreadsAvailable();
		void setNumThreadsAvailable(int threads);
		string getResult();
		void startThread(function<bool()> func);
	private:
		// Private helper functions
		string getTime();

		// Private data members
		vector<thread> availableThreads;
		mutex taskMutex;
		condition_variable taskAvailable;
		bool stop;
		int numThreadsAvailable;
};

#endif