#ifndef IQUEUE_H
#define IQUEUE_H

#include "funcCmdQ.h"

using namespace std;

//The basic logic of this header is the same as that of IntQueue.h provided in class.
//Examine the associated .cpp file for more information.
class iQueue{
	public:
		iQueue(const int &);
		~iQueue();
		void enqueue(const qNode &);
  		void dequeue(qNode &);
  		bool isEmpty() const;
  		bool isFull() const;
	private:
		qPtr queueArray;
		int queueSize;
		int front;
		int rear;
		int numItems;
};

#endif
