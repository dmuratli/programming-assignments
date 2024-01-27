#ifndef SQUEUE_H
#define SQUEUE_H

#include "funcCmdQ.h"

using namespace std;

//The basic logic of this header is the same as that of DynIntQueue.h provided in class.
//Examine the associated .cpp file for more information.
class sQueue{
	public:
		sQueue();
		~sQueue();
		void enqueue(const qPtr &);
		void dequeue(qPtr &);
  		bool isEmpty() const; 
	private:
		qPtr front;
		qPtr rear;
		qPtr orgFront; //Added to enable the destructor to find the dynamically allocated memory
		int size;
};

#endif
