#ifndef FUNCCMDQ_H
#define FUNCCMDQ_H

#include <iostream>
#include <string>

using namespace std;

struct command{ //Serves as a node for the commands under functions
	string cName;
	command *next;
	command(): cName(""), next(NULL){}
	//TEMPORARY NOTE: USE THE FOLLOWING WHILE RUNNING THE CODE ON LINUX
	/*
	command(){
		cName="";
		next=NULL;
	};
	*/
};

struct function{ //Serves as a node for functions
	string fName;
	function *next;
	command *cmds;
	function(): fName(""), next(NULL), cmds(NULL){}
	//TEMPORARY NOTE: USE THE FOLLOWING WHILE RUNNING THE CODE ON LINUX
	/*
	function(){
		fName="";
		next=NULL;
		cmds=NULL;
	};
	*/
};

typedef function *fPtr;
typedef command *cPtr;

struct qNode{ //Serves as an information storage node for the queues
	string name;
	int ID;
	qNode *next;
	fPtr cFunc;
	qNode(): name(""), ID(NULL), next(NULL), cFunc(NULL){}
	//TEMPORARY NOTE: USE THE FOLLOWING WHILE RUNNING THE CODE ON LINUX
	/*
	qNode(){
		name="";
		ID=NULL;
		next=NULL;
		cFunc=NULL;
	};
	*/
};

typedef qNode *qPtr;

#endif