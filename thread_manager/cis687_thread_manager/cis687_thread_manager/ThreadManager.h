#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

using std::vector;
using std::thread;
using std::function;
using std::mutex;
using std::condition_variable;

class ThreadManager {
	public:
		ThreadManager();
		~ThreadManager();
		void pollForTasks();
	private:
		vector<thread> availableThreads;
		vector<function<void()>> tasks;
		mutex taskMutex;
		condition_variable taskAvailable;
		bool stop;
};

#endif