#ifndef RSTACK_H
#define RSTACK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//The basic logic of this header is the same as that of DynIntStack.h provided in class (some extra functionality is added).
//Examine the associated .cpp file for more information.
struct sNode{
	string funcName, cmdName;
	sNode *next;
	sNode(): funcName(""), cmdName(""), next(NULL){}
	//TEMPORARY NOTE: USE THE FOLLOWING WHILE RUNNING THE CODE ON LINUX
	/*
	sNode(){
		funcName="";
		cmdName="";
		next=NULL;
	};
	*/
};

typedef sNode *sNPtr;

class rStack{
	public:
		rStack();
		void push(const sNode &);
		void pop(sNode &);
		void clear();
		void print();
		bool isEmpty() const;
	private:
		 sNPtr top;
};

#endif
