#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

struct courseNode{ //Defines a new struct, which will serve as the basis of the nodes of the linked list; taken from the HW2 pdf
    string courseCode, courseName;
    vector<int> studentsAttendingIDs;
    courseNode *next;
    courseNode(){ //Constructs a courseNode object; adapted from the default node constructor in 2.1 slides - VS Code didn't accept courseNode::courseNode()
        courseCode="";
        courseName="";
        vector<int> studentsAttendingIDs;
        courseNode *next=NULL;
    }; 
};

typedef courseNode *nodePtr;

void insertVector(vector<int> &vec, const int &tBA){ //Inserts a new integer to an integer vector in an ordered fashion; adapted from the insertion into a sorted vector code in the slides about vectors in CS 201 (Spring 2021)
    vec.push_back(tBA);
    int temp=vec.size()-1;
    while (temp>0 && vec[temp-1]>tBA){    
        vec[temp]=vec[temp-1]; 
        temp-=1;
    }
    vec[temp]=tBA;
}

void removeVector(vector<int> &vec, const int &pos){ //Removes an element from a sorted integer vector; adapted from the deletion from sorted vector code in the slides about vectors in CS 201 (Spring 2021)
   for (int i=pos; i<vec.size()-1; i++){
        vec[i] = vec[i+1]; 
   }
   vec.pop_back();
}

bool eltFinder(const vector<int> &vec, const int &elt){ //Checks whether an integer is in the given integer vector
    bool check=false;
    for (int i=0; i<vec.size(); i++){
        if (vec[i]==elt){
            check=true;
            break;
        }else{
            ;
        }
    }
    return check;
}

int eltIdxFinder(const vector<int> &vec, const int &elt){ //A different version of eltFinder (this one returns the index of the searched element within the vector); it is assumed that this is used only when the element is in the vector (i.e. eltFinder(vec, elt)==true)
    int eltIdx;
    for (int i=0; i<vec.size(); i++){
        if (vec[i]==elt){
            eltIdx=i;
            break;
        }else{
            ;
        }
    }
    return eltIdx;
}

bool lListChecker(const nodePtr &head, const string &cCode, const int &stuID){ //This function performs 2 tasks:
    nodePtr modifier=head;                                                     //Checks whether a course is already in the linked list; returns true if the course already exists, false if it doesn't
    bool check=false;                                                          //Adds the student ID to the relevant node (if it already exists) in an ordered fashion using insertVector provided that the student ID isn't already there
    while (modifier!=NULL){                                                    
        if (modifier->courseCode==cCode){
            check=true;
            if (eltFinder(modifier->studentsAttendingIDs, stuID)==false){
                insertVector(modifier->studentsAttendingIDs, stuID);
            }else{
                ;
            }
            break;
        }else{
            ;
        }
        modifier=modifier->next;
    }
    return check;
}

bool lListStuChecker(const nodePtr &head, const string &cCode, const int &stuID){ //Very similar to lListChecker, with the only difference being that this one checks whether a student is already enrolled to a course that is known to exist as a node rather than checking whether the node exists; returns true if so, false if not
    nodePtr modifier=head;
    bool check=false;
    while (modifier!=NULL){                                                   
        if (modifier->courseCode==cCode){
            if (eltFinder(modifier->studentsAttendingIDs, stuID)==false){
                insertVector(modifier->studentsAttendingIDs, stuID);
            }else{
                check=true;
            }
            break;
        }else{
            ;
        }
        modifier=modifier->next;
    }
    return check;
}

bool lListStuCheckerWI(const nodePtr &head, const string &cCode, const int &stuID){ //Essentially the same as lListStuChecker; this one just doesn't insert the student ID to the relevant vector
    nodePtr modifier=head;
    bool check=false;
    while (modifier!=NULL){                                                   
        if (modifier->courseCode==cCode){
            if (eltFinder(modifier->studentsAttendingIDs, stuID)==false){
                ;
            }else{
                check=true;
            }
            break;
        }else{
            ;
        }
        modifier=modifier->next;
    }
    return check;
}

bool lListChecker(const nodePtr &head, const string &cCode){ //A different version of lListChecker (this one doesn't add a student ID to any node)
    nodePtr modifier=head;
    bool check=false;
    while (modifier!=NULL){
        if (modifier->courseCode==cCode){
            check=true;
            break;
        }else{
            ;
        }
        modifier=modifier->next;
    }
    return check;
}

nodePtr AddInOrder(const nodePtr &head, const string &cName, const string &cCode, const int &stuID){ //Adds a new node to the linked list in an ordered fashion; adapted from the adding a node to a sorted list code in 2.2 slides
    nodePtr checker=head;
    if (head==NULL || cName<head->courseName){  
		nodePtr temp=new courseNode;
		temp->courseName=cName;
        temp->courseCode=cCode;
        insertVector(temp->studentsAttendingIDs, stuID);
		temp->next=head;
		return temp;
    }else{
        while (checker->next!=NULL && checker->next->courseName<cName){    
		    checker=checker->next;
        }
        nodePtr temp=new courseNode; 
        temp->courseName=cName;
        temp->courseCode=cCode;
        insertVector(temp->studentsAttendingIDs, stuID);
        temp->next=checker->next;
        checker->next=temp;
        return head;
    }
}

void lListStuRemover(const nodePtr &head, const string &cCode, const int &stuID){ //Removes the given student ID from the provided course
    nodePtr modifier=head;
    while (modifier!=NULL){                                                    
        if (modifier->courseCode==cCode){
            int posTBremoved=eltIdxFinder(modifier->studentsAttendingIDs, stuID);
            removeVector(modifier->studentsAttendingIDs, posTBremoved);
            break;
        }else{
            ;
        }
        modifier=modifier->next;
    }
}

void lListSNodeRemover(const nodePtr &tBD, nodePtr &head){ //Removes a node from a linked list; adapted from the deleting a single node code in 2.2 slides
	nodePtr modifier;
	if (tBD==head){     
        head=head->next;
        delete tBD;
	}else{
        modifier=head;
		while (modifier->next!=tBD){
            modifier=modifier->next;
        }
		modifier->next=tBD->next;
		delete tBD;
	}
}

void lListCleaner(nodePtr &head){ //Removes the courses with less than 3 enrolled students from the linked list
    nodePtr modifier=head;
    while (modifier!=NULL){                                                    
        if ((modifier->studentsAttendingIDs).size()<3){
            lListSNodeRemover(modifier, head);
        }else{
            ;
        }
        modifier=modifier->next;
    }
}

void lListPrinter(const nodePtr &head){ //Prints/displays the linked list; adapted from the printing code in 2.1 slides
    nodePtr ptr=head;
    while (ptr!=NULL){
        cout << ptr->courseCode << " " << ptr->courseName << ": ";
        for (int i=0; i<(ptr->studentsAttendingIDs).size(); i++){
            cout << (ptr->studentsAttendingIDs)[i] << " ";
        }
        cout << endl;
        ptr=ptr->next;
    }
}

void lListADPrinter(const nodePtr &head){ //Essentially the same as lListPrinter, but this one also marks the courses to be deleted
    nodePtr ptr=head;
    while (ptr!=NULL){
        if ((ptr->studentsAttendingIDs).size()<3){
            cout << ptr->courseCode << " " << ptr->courseName << " -> This course will be closed" << endl;
        }else{
            cout << ptr->courseCode << " " << ptr->courseName << ": ";
            for (int i=0; i<(ptr->studentsAttendingIDs).size(); i++){
                cout << (ptr->studentsAttendingIDs)[i] << " ";
            }
            cout << endl;
        }
        ptr=ptr->next;
    }
}

void deleteLList(nodePtr &head){ //Detonates the entire linked list
  nodePtr temp;	
  while (head!=NULL){
    temp=head->next;
    delete head;
    head=temp;
  }
}

void menu(bool &exit, nodePtr &head){ //Displays the menu and calls the functions necessary to handle the options and/or processes them through extra code until the exit command is given 
    string option, IDCs, IDCsFull;
    while (exit==false){
        cout << "Please select one of the choices:" << endl;
        cout << "1. Add to List" << endl;
        cout << "2. Drop from List" << endl;
        cout << "3. Display List " << endl;
        cout << "4. Finish Add/Drop and Exit" << endl;
        cin >> option;
        if (option=="1"){
            cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
            cin.clear();
            cin.ignore();
            getline(cin, IDCsFull);
            istringstream eltsILine(IDCsFull);
            string pCode, pName;
            while (eltsILine >> IDCs){
                char fChr=IDCs[0];
                char lChr=IDCs[IDCs.length()-1];
                string cType;
                if ((fChr>64 && fChr<91) && (lChr>47 && lChr<58)){
                    cType="code";
                }else if ((fChr>64 && fChr<91) && (lChr>96 && lChr<123)){
                    cType="name";
                }else if ((fChr>47 && fChr<58) && (lChr>47 && lChr<58)){
                    cType="ID";
                    int stuID=atoi(IDCs);
                    if (lListChecker(head, pCode)==false){
                        head=AddInOrder(head, pName, pCode, stuID);
                        cout << pCode << " does not exist in the list of Courses. It is added up." << endl;
                    }else{
                        if (lListStuChecker(head, pCode, stuID)==false){
                            cout << "Student with id " << stuID << " is enrolled to " << pCode << "." << endl;
                        }else{
                            cout << "Student with id " << stuID << " already is enrolled to " << pCode << ". No action taken." << endl;
                        }
                    }
                }else{
                    ;
                }
                if (cType!="ID" && cType!="name"){
                    pCode=IDCs;
                }else if(cType!="ID" && cType!="code"){
                    pName=IDCs;
                }else{
                    ;
                }
            }
        }else if (option=="2"){
            cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
            cin.clear();
            cin.ignore();
            getline(cin, IDCsFull);
            istringstream eltsILine(IDCsFull);
            string pCode, pName;
            while (eltsILine >> IDCs){
                char fChr=IDCs[0];
                char lChr=IDCs[IDCs.length()-1];
                string cType;
                if ((fChr>64 && fChr<91) && (lChr>47 && lChr<58)){
                    cType="code";
                }else if ((fChr>64 && fChr<91) && (lChr>96 && lChr<123)){
                    cType="name";
                }else if ((fChr>47 && fChr<58) && (lChr>47 && lChr<58)){
                    cType="ID";
                    int stuID=atoi(IDCs);
                    if (lListChecker(head, pCode)==false){
                        cout << "The " << pCode << " course is not in the list, thus student with id " << stuID << " can't be dropped" << endl;
                    }else{
                        if (lListStuCheckerWI(head, pCode, stuID)==false){
                            cout << "Student with id " << stuID << " is not enrolled to " << pCode << ", thus he can't drop that course." << endl;
                        }else{
                            lListStuRemover(head, pCode, stuID);
                            cout << "Student with id " << stuID << " has dropped " << pCode << "." << endl;
                        }
                    }
                }else{
                    ;
                }
                if (cType!="ID" && cType!="name"){
                    pCode=IDCs;
                }else if(cType!="ID" && cType!="code"){
                    pName=IDCs;
                }else{
                    ;
                }
            }
        }else if (option=="3"){
            cout << "The current list of course and the students attending them:" << endl;
            lListPrinter(head);
        }else if (option=="4"){
            cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
            cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
            lListADPrinter(head);
            lListCleaner(head);
            exit=true;
        }else{
            ;
        }
    }
}

int main(){ //Calls functions for the most part
    bool exit=false;
    string courseFileName, lineCourseFile, cCode, cName, stuIDstr;
    nodePtr head=NULL;
    cout << "Please enter file name: ";
    cin >> courseFileName;
    ifstream courseFile;
    courseFile.open(courseFileName.c_str());
    cout << "Successfully opened file " << courseFileName << endl;
    while (getline(courseFile, lineCourseFile)){ //Reads the lines in the .txt file and uses the functions defined above to generate the initial linked list
        istringstream eltsCFile(lineCourseFile);
        eltsCFile >> cCode >> cName >> stuIDstr;
        int stuID=atoi(stuIDstr);
        if (lListChecker(head, cCode, stuID)==false){
            head=AddInOrder(head, cName, cCode, stuID);
        }else{
            ;
        }
    }
    courseFile.close();
    cout << "The linked list is created." << endl;
    cout << "The initial list is:" << endl;
    lListPrinter(head);
    menu(exit, head);
    deleteLList(head);
    return 0;
}