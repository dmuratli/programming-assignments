#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"

using namespace std;

struct busStop{ //Defines a new struct to serve as the basis of the nodes (bus stops) of doubly linked lists; taken from the HW3 pdf
    string busStopName;
    busStop *left;
    busStop *right;
    busStop():right(NULL),left(NULL){} 
};

struct busLine{ //Defines a new struct to serve as the basis of the nodes (bus lines) of the regular linked list; taken from the HW3 pdf
    string busLineName;
    busLine *next;
    busStop *busStops;
    busLine():next(NULL),busStops(NULL){}
};

typedef busStop *BSptr;
typedef busLine *BLptr;

BLptr head=nullptr;

void printMainMenu(){ //Simply prints the options for the user; taken from the HW3 pdf
    cout << endl;
    cout << "I***********************************************I" << endl << "I 0 - EXIT PROGRAM I"<< endl << "I 1 - PRINT LINES I"<< endl << "I 2 - ADD BUS LINE I"<< endl << "I 3 - ADD BUS STOP I"<< endl << "I 4 - DELETE BUS LINE I"<< endl << "I 5 - DELETE BUS STOP I" << endl << "I 6 - PATH FINDER I" << endl <<"I***********************************************I" << endl << ">>";
    cout << endl;
}

bool consistencyCheck(){ //Checks the integrity of the extended linked list; a slightly modified version of the one in the HW3 pdf to deal with potential errors
    busLine* currBL=head;
        while (currBL){
            busStop* currBS=currBL->busStops;
            while (currBS){
                busStop* rightBS=currBS->right;
                if (rightBS!=NULL){
                    if (rightBS!=currBS && rightBS->left!=currBS){
                        cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
                        return false;
                    }else{
                        ;
                    }
                }else{
                    ;
                }
                currBS=currBS->right;
            }
            currBL=currBL->next;
        }
        return true;
}

void lineFinder(const string &bLine, BLptr &sLine, bool &check){ //Checks the bus lines list for the given line name; returns whether it is in the list, and, if so, its location
    check=false;
    BLptr checker=head;
    while (checker->next!=NULL){
        if (checker->busLineName==bLine){
            check=true;
            sLine=checker;
            break;
        }else{
            ;
        }
        checker=checker->next;
    }
    if (checker->busLineName==bLine){
        if (check!=true){
            check=true;
            sLine=checker;
        }else{
            ;
        }
    }else{
        ;
    }
}

void stopFinder(const string &bStop, const BLptr &bLine, BSptr &sLocation, bool &check){ //Checks a bus line for the given bus stop (goes both ways in the bus line)
    check=false;
    BSptr checker=bLine->busStops;
    while (checker->right!=NULL){
        if (checker->busStopName==bStop){
            check=true;
            sLocation=checker;
            break;
        }else{
            checker=checker->right;
        }
    }
    if (checker->busStopName==bStop){
        if (check!=true){
            check=true;
            sLocation=checker;
        }else{
            ;
        }
    }else{
        ;
    }
    if (check==false){
        while (checker->left!=NULL){
            if (checker->busStopName==bStop){
                check=true;
                sLocation=checker;
                break;
            }else{
                checker=checker->left;
            }
        }
        if (checker->busStopName==bStop){
            if (check!=true){
                check=true;
                sLocation=checker;
            }else{
                ;
            }
        }else{
            ;
        }
    }else{
        ;
    }
}

void printSBusLine(const BLptr &BL){ //Prints a single bus line - a modified version of printBusLines
    BLptr ptr=BL;
    cout << ptr->busLineName << ": ";
    BSptr ptr2=ptr->busStops;
    while (ptr2!=NULL){
        if (ptr2->right!=NULL){
            cout << ptr2->busStopName << " <-> ";
        }else{
            cout << ptr2->busStopName;
        }
        ptr2=ptr2->right;
    }
    cout << endl;
}

void printBusLines(){ //Prints the extended linked list - inspired from the code in 2.1 slides
    BLptr ptr=head;
    while (ptr!=NULL){
        if (ptr->busLineName!=""){
            cout << ptr->busLineName << ": ";
            BSptr ptr2=ptr->busStops;
            while (ptr2!=NULL){
                if (ptr2->right!=NULL){
                    cout << ptr2->busStopName << " <-> ";
                }else{
                    cout << ptr2->busStopName;
                }
                ptr2=ptr2->right;
            }
            cout << endl;
        }else{
            ;
        }
        ptr=ptr->next;
    }
}

void initialDBBuilder(){ //Constructs the initial extended linked list from the text file - inspired by the AddInOrder function shown in 2.2 slides
    string lineBLines, lElt, bLine, bStop;
    ifstream initialBusLines;
    initialBusLines.open("busLines.txt");
    while (getline(initialBusLines, lineBLines)){
        BLptr bLHead=new busLine;
        int eltCounter=0;
        istringstream eltsTxtLine(lineBLines);
        while (eltsTxtLine >> lElt){
            if (lElt[lElt.length()-1]==':'){
                bLine=lElt.substr(0, lElt.length()-1);
                BLptr checker=head;
                if (head==nullptr){  
                    BLptr temp=new busLine;
                    temp->busLineName=bLine;
                    temp->next=head;
                    head=temp;
                }else{
                    while (checker->next!=NULL){
                        checker=checker->next;
                    }
                    BLptr temp=new busLine;
                    temp->busLineName=bLine;
                    temp->next=checker->next;
                    checker->next=temp;
                }
            }else{
                bStop=lElt;
                if (eltCounter==1){
                    BLptr checker=head;
                    while (checker->next!=NULL){
                        checker=checker->next;
                    }
                    bLHead=checker;
                    BSptr fBS=new busStop;
                    fBS->busStopName=bStop;
                    bLHead->busStops=fBS;
                }else{
                    BSptr pBS=bLHead->busStops;
                    while (pBS->right!=NULL){
                        pBS=pBS->right;
                    }
                    BSptr nBS=new busStop;
                    nBS->busStopName=bStop;
                    nBS->left=pBS;
                    pBS->right=nBS;
                }
            }
            eltCounter+=1;
        }
        bLine="";
    }
    initialBusLines.close();
}

void deleteBusLineWI(const string &bLine){ //Basically deleteBusLine, but it doesn't require input from the user (coded only for use in other functions)
    BLptr sLine=NULL;
    bool check;
    lineFinder(bLine, sLine, check);
    if (check==true){
        BLptr checker=head;
        while (checker->next!=sLine){
            if (checker==sLine){
                break;
            }else{
                checker=checker->next;
            }
        }
        checker->next=sLine->next;
        BSptr temp=NULL;
        while (sLine->busStops!=NULL){
            temp=sLine->busStops->right;
            delete sLine->busStops;
            sLine->busStops=temp;
        }
        if (sLine!=head){
            delete sLine;
        }else{
            sLine->busLineName="";
        }
        cout << endl;
    }else{
        ;
    }
}

void addBusLine(){ //Adds a new line and the corresponding bus stops based on user input
    string bLine, bStop, confirmation;
    int stopCounter=0;
    bool aeCheckStop, aeCheckLine;
    BSptr redundantPtrStop=new busStop;
    BLptr redundantPtrLine=new busLine;
    cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
    cin >> bLine;
    lineFinder(bLine, redundantPtrLine, aeCheckLine);
    if (bLine=="0"){
        return;
    }else if (aeCheckLine==true){
        do{
            cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
            cin >> bLine;
            lineFinder(bLine, redundantPtrLine, aeCheckLine);
        }while (bLine!="0" && aeCheckLine==true);
        BLptr temp=new busLine;
        temp->busLineName=bLine;
        temp->next=head;
        head=temp;
        do{
            cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
            cin >> bStop;
            BSptr BS=new busStop;
            BS->busStopName=bStop;
            if (bStop=="0"){
                if (stopCounter==0){
                    cout << "You are not allowed to add an empty bus line" << endl;
                    deleteBusLineWI(bLine);
                }else{
                    cout << "The bus line information is shown below" << endl;
                    BLptr sLine=NULL;
                    bool redundantCheck;
                    lineFinder(bLine, sLine, redundantCheck);
                    printSBusLine(sLine);
                    cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
                    cin >> confirmation;
                    ToLower(confirmation);
                    if (confirmation=="y"){
                        printBusLines();
                    }else{
                        deleteBusLineWI(bLine);
                    }
                }
            }else{
                if (temp->busStops==NULL){
                    temp->busStops=BS;
                }else{
                    stopFinder(bStop, temp, redundantPtrStop, aeCheckStop);
                    if (aeCheckStop==false){
                        BSptr checker2=temp->busStops;
                        while (checker2->right!=NULL){
                            checker2=checker2->right;
                        }
                        checker2->right=BS;
                        checker2->right->left=checker2;
                    }else{
                        cout << "Bus stop already exists in the line" << endl;
                    }
                }
            }
            stopCounter+=1;
        }while (bStop!="0");
    }else{
        BLptr temp=new busLine;
        temp->busLineName=bLine;
        temp->next=head;
        head=temp;
        do{
            cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
            cin >> bStop;
            BSptr BS=new busStop;
            BS->busStopName=bStop;
            if (bStop=="0"){
                if (stopCounter==0){
                    cout << "You are not allowed to add an empty bus line" << endl;
                    deleteBusLineWI(bLine);
                }else{
                    cout << "The bus line information is shown below" << endl;
                    BLptr sLine=NULL;
                    bool redundantCheck;
                    lineFinder(bLine, sLine, redundantCheck);
                    printSBusLine(sLine);
                    cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
                    cin >> confirmation;
                    ToLower(confirmation);
                    if (confirmation=="y"){
                        printBusLines();
                    }else{
                        deleteBusLineWI(bLine);
                    }
                }
            }else{
                if (temp->busStops==NULL){
                    temp->busStops=BS;
                }else{
                    stopFinder(bStop, temp, redundantPtrStop, aeCheckStop);
                    if (aeCheckStop==false){
                        BSptr checker2=temp->busStops;
                        while (checker2->right!=NULL){
                            checker2=checker2->right;
                        }
                        checker2->right=BS;
                        checker2->right->left=checker2;
                    }else{
                        cout << "Bus stop already exists in the line" << endl;
                    }
                }
            }
            stopCounter+=1;
        }while (bStop!="0");
    }
}

void addBusStop(){ //Adds a new bus stop to the given line
    string bLine, bStop;
    bool checkLine, checkStop;
    BLptr sLine=NULL;
    cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
    cin >> bLine;
    lineFinder(bLine, sLine, checkLine);
    if (checkLine==true){
        cout << "The bus line information is shown below" << endl;
        printSBusLine(sLine);
        cout << "Enter the name of the new bus stop" << endl;
        cin >> bStop;
        BSptr sLocation=NULL;
        stopFinder(bStop, sLine, sLocation, checkStop);
        if (checkStop==true){
            cout << "Bus stop already exists. Going back to previous menu." << endl;
            return;
        }else{
            string pStop;
            cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
            cin >> pStop;
            if (pStop=="0"){
                BSptr newS=new busStop;
                newS->busStopName=bStop;
                newS->right=sLine->busStops;
                newS->right->left=newS;
                sLine->busStops=newS;
            }else{
                bool prevCheck;
                BSptr newS=new busStop;
                stopFinder(pStop, sLine, sLocation, prevCheck);
                if (prevCheck==true){
                    if (sLocation->right!=NULL){
                        newS->busStopName=bStop;
                        newS->left=sLocation;
                        newS->right=sLocation->right;
                        newS->right->left=newS;
                        sLocation->right=newS;
                    }else{
                        newS->busStopName=bStop;
                        newS->left=sLocation;
                        newS->right=sLocation->right;
                        sLocation->right=newS;
                    }
                }else{
                    do{
                        cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
                        cin >> pStop;
                        if (pStop=="0"){
                            return;
                        }else{
                            stopFinder(pStop, sLine, sLocation, prevCheck);
                        }
                    }while (prevCheck==false);
                }
            }
        }
    }else{
        if (bLine=="0"){
            ;
        }else{
            cout << "Bus line cannot be found. Going back to previous menu." << endl;
        }
        return;
    }
    cout << endl;
    printBusLines();
}

void deleteBusLine(){ //Deletes the given bus line (with the only exception being when the bus line is the head) along with all of its stops
    string bLine;
    BLptr sLine=NULL;
    bool check;
    cout << "Enter the name of the bus line to delete" << endl;
    cin >> bLine;
    lineFinder(bLine, sLine, check);
    if (check==true){
        BLptr checker=head;
        while (checker->next!=sLine){
            if (checker==sLine){
                break;
            }else{
                checker=checker->next;
            }
        }
        checker->next=sLine->next;
        BSptr temp=new busStop;
        while (sLine->busStops!=NULL){
            temp=sLine->busStops->right;
            delete sLine->busStops;
            sLine->busStops=temp;
        }
        if (sLine!=head){
            delete sLine;
        }else{
            sLine->busLineName="";
        }
        cout << endl;
        printBusLines();
    }else{
        cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
        return;
    }
}

void deleteBusStop(){ //Deletes the given bus stop from the given bus line
    string bLine, bStop;
    BLptr sLine=NULL;
    BSptr sLocation=NULL;
    bool lineCheck, stopCheck;
    cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
    cin >> bLine;    
    lineFinder(bLine, sLine, lineCheck);
    if (lineCheck==true){
        cout << "The bus line information is shown below" << endl;
        printSBusLine(sLine);
        cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
        cin >> bStop;
        if (bStop=="0"){
            return;
        }else{
            stopFinder(bStop, sLine, sLocation, stopCheck);
            if (stopCheck==true){
                BSptr modifier=sLine->busStops;
                while (modifier!=sLocation){
                    modifier=modifier->right;
                }
                if (modifier->right!=NULL && modifier->left!=NULL){
                    modifier->left->right=modifier->right;
                    modifier->right->left=modifier->left;
                }else if (modifier->right==NULL){
                    modifier->left->right=modifier->right;
                }else if (modifier->left==NULL){
                    modifier->right->left=modifier->left;
                    sLine->busStops=modifier->right;
                }else{
                    ;
                }
                delete modifier;
                printBusLines();
            }else{
                do{
                    cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
                    cin >> bStop;
                    if (bStop=="0"){
                        return;
                    }else{
                        stopFinder(bStop, sLine, sLocation, stopCheck);
                    }
                }while (stopCheck==false);
            }
        }
    }else{
        cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
        return;
    }
}

void pathFinder(){ //Finds the path by which the user can go from one bus stop to another - works only if both stops are found in a single bus line (interchanging isn't implemented)
    string cStop, nStop;
    cout << "Where are you now?" << endl;
    cin >> cStop;
    BLptr checker=head, cLine=NULL, nLine=NULL;
    BSptr cLocation=NULL, nLocation=NULL;
    bool cStopCheck, nStopCheck;
    while (checker!=NULL){
        stopFinder(cStop, checker, cLocation, cStopCheck);
        if (cStopCheck==true){
            cLine=checker;
            break;
        }else{
            checker=checker->next;
        }
    }
    cout << "Where do you want to go?" << endl;
    cin >> nStop;
    checker=head;
    while(checker!=NULL){
        stopFinder(nStop, checker, nLocation, nStopCheck);
        if (nStopCheck==true){
            nLine=checker;
            break;
        }else{
            checker=checker->next;
        }
    }
    if (cStopCheck==false || nStopCheck==false){
        cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
    }else{
        string done="no";
        BLptr lChecker=head;
        BSptr sPt=NULL;
        BSptr ePt=NULL;
        bool sCheck, eCheck;
        while (lChecker!=NULL){                    
            stopFinder(cStop, lChecker, sPt, sCheck);
            if (sCheck==true){
                stopFinder(nStop, lChecker, ePt, eCheck);
                if (eCheck==true){
                    cout << "You can go there by " << lChecker->busLineName << ": ";
                    done="yes";
                    BSptr curr=sPt;
                    string direction;
                    while (curr!=NULL){
                        if (curr->busStopName==ePt->busStopName){
                            direction="right";
                            curr=sPt;
                            while (curr!=ePt){
                                cout << curr->busStopName << " -> ";
                                curr=curr->right;
                            }
                            cout << ePt->busStopName << endl;
                            break;
                        }else{
                            curr=curr->right;
                        }
                    }
                    if (direction!="right"){
                        curr=sPt;
                        while (curr!=NULL){
                            if (curr->busStopName==ePt->busStopName){
                                direction="left";
                                curr=sPt;
                                while (curr!=ePt){
                                    cout << curr->busStopName << " -> ";
                                    curr=curr->left;
                                }
                                cout << ePt->busStopName << endl;
                                break;
                            }else{
                                curr=curr->left;
                            }
                        }
                    }else{
                        ;
                    }
                }else{
                    ;
                }
            }else{
                ;
            }
            if (lChecker->next!=NULL){
                lChecker=lChecker->next;
            }else{
                break;
            }
        }
        if (done=="yes"){
            ;
        }else{
            cout << "Sorry no path from " << cStop << " to " << nStop << " could be found." << endl;
        }
    }
}

void listDetonator(){ //Detonates the entire linked list, freeing the memory used for its storage
    BLptr tempBL;	
    while (head!=NULL){
        BSptr BS=head->busStops;
        while (BS!=NULL){
            BSptr tempBS=BS->right;
            delete BS;
            BS=tempBS;
        }	
        tempBL=head->next;
        delete head;
        head=tempBL;
    }
}

void processMainMenu(){ //Takes and processes inputs from the user
    char input;
    do{
        if (consistencyCheck()==false){
            cout << "There are inconsistencies. Exit." << endl;
            return;
        }else{
            ;
        }
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input){
            case '0':
                cout << "Thanks for using our program" << endl;
                return;
            case '1':
                printBusLines();
                break;
            case '2':
                addBusLine();
                break;
            case '3':
                addBusStop();
                break;
            case '4':
                deleteBusLine();
                break;
            case '5':
                deleteBusStop();
                break;
            case '6':
                pathFinder();
                break;
            default:
                cout << "Invalid option: please enter again" << endl;
        }
    }while (true);
}

int main(){ //Calls the functions necessary to move the program forward
    initialDBBuilder();
    processMainMenu();
    listDetonator();
    return 0;
}