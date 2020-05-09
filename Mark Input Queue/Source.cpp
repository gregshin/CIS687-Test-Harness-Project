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
using std::string;

int main() {
	

	int size=10;
	InputQueue IQ(size); //object constructor queue size 50 string elements
	

	//GUI sends input queue a int with the number of string file paths coming per test request
	//ex: sent int 3 then sends 3 strings with a file path ex:"C:/Test/Dll/Test1"

	//add to queue
	IQ.enqueue("C:/Test/Dll/Test1");
	IQ.enqueue("C:/Test/Dll/Test2");
	IQ.enqueue("C:/Test/Dll/Test3");

	//remove from queue and put into local variables for display
	string x = IQ.dequeue();
	string y = IQ.dequeue();
	string z = IQ.dequeue();
	

	cout << "x= " << x << " ,y= " << y << " ,z= "<<z<<endl;

	
	int c = IQ.getcount();//get amount of elements currently in queue

	cout << "Count is: " << c<<endl;

	

	
	
	

	

	return 0;
}