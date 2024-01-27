#include "iQueue.h"

//This class is adapted from the IntQueue class, which was provided in lecture materials.
//NED: "No essential difference from the corresponding function in IntQueue.cpp."
iQueue::iQueue(const int &size){ //Constructs an instructors' queue object; the array contains qNode's, which contain information about the instructors' requests (check funcCmdQ.h for more information about the structs)
	queueArray=new qNode[size];
	queueSize=size;
	front=-1;
	rear=-1;
	numItems=0;
}

iQueue::~iQueue(){ //Destructs the iQueue object
	delete[] queueArray;
}

void iQueue::enqueue(const qNode &info){ //NED
	if (isFull()==true){
         cout << "The queue is full." << endl;
    }else{
		rear=(rear+1)%queueSize;
		queueArray[rear]=info;
		numItems++;
	}
}

void iQueue::dequeue(qNode &deqInfoPtr){ //NED
	if (isEmpty()==true){
       cout << "Attempting to dequeue on empty queue, exiting program..." << endl;
       exit(1);
    }else{
		front=(front+1)%queueSize;
		deqInfoPtr=queueArray[front];
		numItems--;
	}
}

bool iQueue::isEmpty() const{ //NED
	if (numItems>0){
		return false;
	}else{
		return true;
	}
}

bool iQueue::isFull() const{ //NED
	if (numItems<queueSize){
		return false;
	}else{
		return true;
	}
}
