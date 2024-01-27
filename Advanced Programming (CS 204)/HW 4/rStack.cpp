#include "rStack.h"

//This class is adapted from the DynIntStack class, which was provided in lecture materials.
//NED: "No essential difference from the corresponding function in DynIntQueue.cpp."
rStack::rStack(){ //NED
	top=NULL;
}

void rStack::push(const sNode &tBP){ //NED
	sNPtr newNode=new sNode;
	newNode->funcName=tBP.funcName;
	newNode->cmdName=tBP.cmdName;
	if (isEmpty()==true){
		top=newNode;
		newNode->next=NULL;
	}else{
		newNode->next=top;
		top=newNode;
	}
}

void rStack::pop(sNode &poppedSNode){ //NED
	sNode *temp;
	if (isEmpty()==true){
		cout << "The stack is empty." << endl;
	}else{
		poppedSNode.funcName=top->funcName;
		poppedSNode.cmdName=top->cmdName;
		temp=top->next;
		delete top;
		top=temp;
	}
}

void rStack::clear(){ //Clears the stack
	sNPtr temp=top;
	while (temp!=NULL){
		temp=temp->next;
		delete top;
		top=temp;
	}
}

void rStack::print(){ //Prints the stack
	cout << "PRINTING THE STACK TRACE:" << endl;
	sNPtr prtPtr=top;
	vector<sNode> topToBottom; 
	if (isEmpty()==false){
		while (prtPtr!=NULL){
			sNode current;
			current.cmdName=prtPtr->cmdName;
			current.funcName=prtPtr->funcName;
			topToBottom.push_back(current);
			prtPtr=prtPtr->next;
		}
		for (int i=topToBottom.size()-1; i>=0; i--){
			cout << topToBottom[i].funcName << ": " << topToBottom[i].cmdName << endl;
		}
	}else{
		cout << "The stack is empty" << endl;
	}
}

bool rStack::isEmpty() const{ //NED
	if (top==NULL){
		return true;
	}else{
		return false;
	}
}