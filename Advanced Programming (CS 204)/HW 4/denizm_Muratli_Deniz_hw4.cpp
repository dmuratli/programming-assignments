#include <fstream>
#include <sstream>
#include "strutils.h"
#include "iQueue.h"
#include "sQueue.h"
#include "rStack.h"

using namespace std;

fPtr servicesHead=nullptr;
iQueue instructorsQueue(5);
sQueue studentsQueue;
rStack requestStack;
string orgFuncName;

void fileProcessor(const string &fileName, bool &success){ //Builds/modifies the linked list of functions based on the text files provided by the user
	success=true;
	ifstream file;
	string line;
	int lCounter=0;
	file.open(fileName.c_str());
	if (file.fail()){
		success=false;
		return;
	}else{
		while (getline(file, line)){
			lCounter+=1;
			string mLine=line.substr(0, line.length()-1);
			if (lCounter==1){
				fPtr tempNF=new function;
				tempNF->fName=mLine;
				if (servicesHead==NULL){
					servicesHead=tempNF;
				}else{
					fPtr finder=servicesHead;
					while (finder->next!=NULL){
						finder=finder->next;
					}
					finder->next=tempNF;
				}
			}else{
				cPtr tempNC=new command;
				tempNC->cName=mLine;
				fPtr finder=servicesHead;
				while (finder->next!=NULL){
					finder=finder->next;
				}
				if (finder->cmds==NULL){
					finder->cmds=tempNC;
				}else{
					cPtr cFinder=finder->cmds;
					while (cFinder->next!=NULL){
						cFinder=cFinder->next;
					}
					cFinder->next=tempNC;
				}
			}
		}
		file.close();
	}
}

void listPrinter(){ //Prints the linked list of functions
	cout << "-----------------------------------------------------------------" << endl << "PRINTIG AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl << "-----------------------------------------------------------------" << endl << endl << endl;
	fPtr mPtr=servicesHead;
	while (mPtr!=NULL){
		cout << mPtr->fName << ":" << endl;
		cPtr sPtr=mPtr->cmds;
		while (sPtr->next!=NULL){
			cout << sPtr->cName << ", ";
			sPtr=sPtr->next;
		}
		cout << sPtr->cName << "." << endl << endl;
		mPtr=mPtr->next;
	}
}

void fileArranger(bool &success){ //Takes and processes user input for the function files (.txt's)
	success=false;
	string inputFileOption, fileName;
	cout << "If you want to open a service <function> defining file," << endl << "then press <Y/y> for 'yes', otherwise press any single key" << endl;
	cin >> inputFileOption;
	ToLower(inputFileOption);
	while (inputFileOption=="y"){
		cout << "Enter the input file name: ";
		cin >> fileName;
		fileProcessor(fileName, success);
		if (success==true){
			;
		}else{
			cout << "Could not open the file." << endl;
			return;
		}
		cout << "Do you want to open another service defining file?" << endl << "Press <Y/y> for 'yes', otherwise press anykey" << endl;
		cin >> inputFileOption;
		ToLower(inputFileOption);
	}
	listPrinter();
}

void functionFinder(const string &funcName, fPtr &here, bool &found){ //Checks the linked list for services to see whether the provided function is there; provides the location of the function if it is
	found=false;
	fPtr finder=servicesHead;
	while (finder!=NULL){
		if (finder->fName==funcName){
			found=true;
			break;
		}else{
			;
		}
		finder=finder->next;
	}
	if (found==true){
		here=finder;
	}else{
		;
	}
}

void addInstructorRequest(){ //Adds a new instructor request to the instructors' queue based on information provided by the user
	bool found;
	string funcName;
	fPtr funcPtr=NULL;
	cout << "Add a service <function> that the instructor wants to use:" << endl;
	cin >> funcName;
	functionFinder(funcName, funcPtr, found);
	if (found==true){
		string iName;
		int iID;
		cout << "Give instructor's name: ";
		cin >> iName;
		cout << "Give instructor's ID <an int>: ";
		cin >> iID;
		qNode nInst;
		nInst.name=iName;
		nInst.ID=iID;
		nInst.cFunc=funcPtr;
		instructorsQueue.enqueue(nInst);
		cout << "Prof. " << iName << "'s service request of " << funcName << endl << "has been put in the instructor's queue." << endl << "Waiting to be served..." << endl;
	}else{
		cout << "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
		return;
	}
}

void addStudentRequest(){ //Adds a new student request to the students' queue based on information provided by the user
	bool found;
	string funcName;
	fPtr funcPtr=NULL;
	cout << "Add a service <function> that the student wants to use:" << endl;
	cin >> funcName;
	functionFinder(funcName, funcPtr, found);
	if (found==true){
		string sName;
		int sID;
		cout << "Give student's name: ";
		cin >> sName;
		cout << "Give student's ID <an int>: ";
		cin >> sID;
		qPtr nStu=new qNode;
		nStu->name=sName;
		nStu->ID=sID;
		nStu->cFunc=funcPtr;
		studentsQueue.enqueue(nStu);
		cout << sName << "'s service request of " << funcName << "has been put in the student's queue." << endl << "Waiting to be served..." << endl;
	}else{
		cout << "The requested service <function> does not exist." << endl << "GOING BACK TO MAIN MENU" << endl;
		return;
	}
}

void processARequest(const string &funcName){ //Recursively processes a single request
	fPtr funcPtr=NULL;
	bool found;
	string cmd, obj;
	functionFinder(funcName, funcPtr, found);
	if (found==true){
		cPtr cmdPtr=funcPtr->cmds;
		while (cmdPtr!=NULL){
			istringstream eltsCmd(cmdPtr->cName);
			eltsCmd >> cmd >> obj;
			if (cmd=="define"){
				sNode newDef;
				newDef.funcName=funcName;
				newDef.cmdName=cmdPtr->cName;
				requestStack.push(newDef);
			}else if (cmd=="call"){
				cout << "Calling " << obj << " from " << funcName << endl;
				processARequest(obj);
			}else if (cmd=="print"){
				requestStack.print();
			}else{
				;
			}
			cmdPtr=cmdPtr->next;
		}
		if (funcName==orgFuncName){
			cout << funcName << " is finished. Clearing the stack from it's data..." << endl;
			requestStack.clear();
		}else{
			cout << funcName << " is finished. Clearing the stack from it's data..." << endl;
			sNode poppedNode;
			do{
				requestStack.pop(poppedNode);
			}while (poppedNode.funcName!=orgFuncName);
			if (poppedNode.funcName==orgFuncName){
				requestStack.push(poppedNode);
			}else{
				;
			}
		}
		system("pause"); 
	}else{
		;
	}
}

void processARequest(){ //Checks the queues and processes the requests (if they exist)
	if (instructorsQueue.isEmpty()==false){
		qNode current;
		while (instructorsQueue.isEmpty()==false){
			instructorsQueue.dequeue(current);
			cout << "Processing prof." << current.name << "'s request <with ID " << current.ID << "> of service <function>:" << endl << current.cFunc->fName << endl;
			orgFuncName=current.cFunc->fName;
			processARequest(orgFuncName);
		}
		qPtr currentPtr=NULL;
		while (studentsQueue.isEmpty()==false){
			studentsQueue.dequeue(currentPtr);
			cout << "Processing " << currentPtr->name << "'s request <with ID " << currentPtr->ID << "> of service <function>:" << endl << currentPtr->cFunc->fName << endl;
			cout << "------------------------------------------------------------------" << endl;
			orgFuncName=currentPtr->cFunc->fName;
			processARequest(orgFuncName);
		}
		cout << "The stack is empty." << endl << "GOING BACK TO MAIN MENU" << endl;
	}else if (studentsQueue.isEmpty()==false){
		cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		qPtr current;
		while (studentsQueue.isEmpty()==false){
			studentsQueue.dequeue(current);
			cout << "Processing " << current->name << "'s request <with ID " << current->ID << "> of service <function>:" << endl << current->cFunc->fName << endl;
			cout << "------------------------------------------------------------------" << endl;
			orgFuncName=current->cFunc->fName;
			processARequest(orgFuncName);
		}
		cout << "The stack is empty." << endl << "GOING BACK TO MAIN MENU" << endl;
	}else{
		cout << "Both instructor's and student's queue is empty." << endl << "No request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
	}
}

void servicesDetonator(){ //Detonates the linked list for services and returns the memory to the heap
	fPtr fRemover=servicesHead;
	while (fRemover!=NULL){
		cPtr cRemover=fRemover->cmds;
		while (cRemover!=NULL){
			cRemover=cRemover->next;
			delete fRemover->cmds;
			fRemover->cmds=cRemover;
		}
		fRemover=fRemover->next;
		delete servicesHead;
		servicesHead=fRemover;
	}
}

int main(){ //Handles the program flow
	bool success;
	qNode test;
	fileArranger(success);
	if (success==true){
		while (true){ //Loop for the main menu - taken from the HW4 pdf
			cout << endl;
			cout << "**********************************************************************" << endl << "**************** 0 - EXIT PROGRAM *************" << endl << "**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************" << endl << "**************** 2 - ADD A STUDENT SERVICE REQUEST *************" << endl << "**************** 3 - SERVE (PROCESS) A REQUEST *************" << endl << "**********************************************************************" << endl; 
			cout << endl;
			int option;
			cout << "Pick an option from above (int number from 0 to 3): ";
			cin>>option;
			switch (option){
			case 0: 
				cout << "PROGRAM EXITING ... " << endl;
				servicesDetonator();
				exit(0);
			case 1: 
				addInstructorRequest();
				break; 
			case 2: 
				addStudentRequest(); 
				break; 
			case 3:
				processARequest(); 
				break; 
			default: 
				cout << "INVALID OPTION!!! Try again" << endl; 
			}
		}
	}else{
		servicesDetonator();
	}
	return 0;
}