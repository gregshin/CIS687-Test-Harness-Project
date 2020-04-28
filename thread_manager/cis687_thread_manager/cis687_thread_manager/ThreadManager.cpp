#include "ThreadManager.h"
#include <thread>
#include <mutex>
#include <iostream>

using std::thread;
using std::lock_guard;
using std::mutex;
using std::cout;
using std::endl;

ThreadManager::ThreadManager()
	: tasks(), taskMutex(), taskAvailable(), stop(false) {
	int numThreads = (thread::hardware_concurrency() > 2)
		? thread::hardware_concurrency() - 1
		: 1;

	for (auto i = 0; i < numThreads; i++) {
		availableThreads.push_back(thread());
	}
};

void ThreadManager::pollForTasks() {
	/*
	while(!stop) {
		unique_lock<mutex> lock(taskMutex);
		taskAvailable.wait(taskAvailable.notify_one);
		function<void()> task = tasks.pop();
		try {
			task();
		} catch (std::string e) {
			throw e;
		}
	}
	*/

	// I think you would initialize the thread calling an infinite loop to poll for tasks
	// Use mutex to lock the thread and condition_variable to wake it up when there's a new task
	for (auto& thr : availableThreads) {
		thr = thread([]() {
				cout << "hello" << endl;
			}
		);
	}
};

ThreadManager::~ThreadManager() {
	for (auto& thr : availableThreads) {
		thr.join();
	}
};