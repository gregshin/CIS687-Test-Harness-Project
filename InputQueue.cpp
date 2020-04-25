///////////////////////////////////////////////
// CSE687 Object Oriented Design Project
// Version 2
// By Mark Hurban
///////////////////////////////////////////////

#include "InputQueue.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//constructor
InputQueue::InputQueue(int n) {//enter size of queue in main()
	room = true;//initially there is room on the thread manager to run tests
	empty = true;//initially input queue is empty
	full = false;//initially input queue is not full
	front = 0;
	back = 0;
	qsize = n;
	qptr = new int[qsize];//create array in heap
	count = 0;//amount of elements in queue
}
	
InputQueue::~InputQueue() {}//destructor

void InputQueue::enqueue(int e) {//add element at back of queue
	empty = false;//set class data member to false

	if (count < qsize) {

		qptr[back++] = e;
		count++;
		//cout << "count is " << count << endl;

	}
	else {//if queue buffer is full then e will not be added to the queue and will be lost

		cout << "Error, queue buffer is full" << endl;
		full = true;
	}

}


int InputQueue::dequeue() {//return and remove 1st element added to queue FIFO
	full = false;
	if (count > 0) {
		//cout << "front is " << front++ << endl;
		
		count--;
		//cout << "count is " << count << endl;
		return qptr[front++];
	}

	else {
		cout << "Error queue buffer is empty" << endl;
		empty = true;

		return 0;

	}

}




//set empty private class data member	
void InputQueue::setempty(bool e) {

	empty = e;
}

//set room private class data member 
void InputQueue::setroom(bool r) {

	room = r;
}

//checks if queue is empty or not 
bool InputQueue::getempty() {

	return empty;
}


//IQ ask TM if it has room to run 
//another test TM returns true or false
bool InputQueue::getroom() {

	return room;
}
