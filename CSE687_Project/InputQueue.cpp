///////////////////////////////////////////////

// CSE687 Object Oriented Design Project

// Version 2

// By Mark Hurban

///////////////////////////////////////////////



#include "InputQueue.h"



#include <iostream>

#include <condition_variable>

#include <mutex>



using std::cout;

using std::cin;

using std::endl;

using std::string;



//constructor

InputQueue::InputQueue(int n) {//enter size of queue in main()

	room = true;//initially there is room on the thread manager to run tests

	empty = true;//initially input queue is empty

	full = false;//initially input queue is not full

	front = 0;

	back = 0;

	qsize = n;

	buffer = new string[qsize];//allocate memory for string queue in heap

	count = 0;//amount of elements in queue

}



InputQueue::~InputQueue() {}//destructor



void InputQueue::enqueue(string e) {//add element at back of queue



	empty = false;//set class data member to false





	if (count < qsize) {//check if queue buffer is full



		std::lock_guard<std::mutex> lock(mutex);//lock critical code so no other 

		//threads can add to enqueue at the same time

		buffer[back++] = e;//enqueue critical code

		count++;

		con_var.notify_all();//let all threads know that enqueue is unlocked





	}

	else {//if queue buffer is full then e will not be added to the queue and will be lost



		cout << "Error, queue buffer is full" << endl;

		full = true;

	}



}





std::string InputQueue::dequeue() {//return and remove 1st element added to queue FIFO

	full = false;

	if (count > 0) {//check if queue is empty

		string str = "";//local variable initialize to empty string

		std::lock_guard<std::mutex> lock(mutex);//lock critical code so no other 

		//threads can remove from queue at the same time

		count--;



		str = buffer[front++];//dequeue critical code

		con_var.notify_all();//let all threads know that dequeue is unlocked

		return str;

	}



	else {



		empty = true;



		return "Error queue buffer is empty";



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



int InputQueue::getcount() {



	return count;

}





//IQ ask TM if it has room to run 

//another test TM returns true or false

bool InputQueue::getroom() {



	return room;

}