///////////////////////////////////////////////

// CSE687 Object Oriented Design Project

// Version 2

// By Mark Hurban

///////////////////////////////////////////////

//base class

#include <iostream>
#include <condition_variable>
#include <mutex>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// prevent multiple inclusions of header

#ifndef InputQueue_H
#define InputQueue_H

class InputQueue
{
public:

	InputQueue(int);//constructor
	~InputQueue();//destructor

	void StartProcessing();

	bool getroom();//ask Thread Manager if it has room to run another test Thread Manager returns true or false

	void setroom(bool);//set room private class data member 

	bool getempty();//checks if queue is empty or not 

	void setempty(bool);//set empty private class data member

	int getcount();

	void enqueue(string);//add element at end of queue

	string dequeue();//remove element at beginning of queue





private:

	//class data member



	bool room;

	bool empty;

	bool full;//queue buffer is full

	int qsize;

	string* buffer;//point to element in array

	int front; //remove element from array

	int back; //add to queue

	int count;//number of elements in queue

	std::mutex mutex;

	std::condition_variable con_var;





};





#endif