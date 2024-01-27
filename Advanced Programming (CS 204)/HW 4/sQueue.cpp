#include "sQueue.h"

//This class is adapted from the DynIntQueue class, which was provided in lecture materials.
//NED: "No essential difference from the corresponding function in DynIntQueue.cpp."
sQueue::sQueue(){ //NED
	front=NULL;
	rear=NULL;
	orgFront=NULL;
}

sQueue::~sQueue(){ //Destructs the sQueue object
	qPtr remover=orgFront, temp=NULL;
	while (remover!=NULL){
		temp=remover->next;
		delete remover;
		remover=temp;
	}
}

void sQueue::enqueue(const qPtr &tBQ){ //NED
	if (isEmpty()==true){
		front=tBQ;
		orgFront=tBQ;
		rear=tBQ;
	}else{
		rear->next=tBQ;
		rear=rear->next;
	}
}

void sQueue::dequeue(qPtr &deqInfoPtr){ //NED
	if (isEmpty()==true){
		cout << "Attempting to dequeue on empty queue, exiting program..." << endl;
		exit(1);
	}else{
		deqInfoPtr=front;
		front=front->next;
	}
}

bool sQueue::isEmpty() const{ //NED
	if (front==NULL){
		return true;
	}else{
		return false;
	}
}