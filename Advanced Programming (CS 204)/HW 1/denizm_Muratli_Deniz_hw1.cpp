#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "randgen.h"

using namespace std;

string inputChecker(const int &noRows, const int &noCols, const int &noBombs){ //Checks whether the inputs are valid
    if (noBombs<1){
        return "lessThanOne";
    }else if (noBombs>((noRows*noCols)-1)){
        return "moreThanRowsTimesColsM1";
    }else{
        return "ok";
    }
}

void inputTaker(int &noRows, int &noCols, int &noBombs){ //Takes the initial inputs
    cout << "Give the dimensions of the matrix: ";
    cin >> noRows >> noCols;
    cout << "How many bombs: ";
    cin >> noBombs;
    string check=inputChecker(noRows, noCols, noBombs);
    while (check!="ok"){
        if (check=="lessThanOne"){
            cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
            cin >> noBombs;
            check=inputChecker(noRows, noCols, noBombs);
        }else if (check=="moreThanRowsTimesColsM1"){
            cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
            cin >> noBombs;
            check=inputChecker(noRows, noCols, noBombs);
        }
    }
    cout << endl;
}

bool vectorSearcher(const vector<int> &vec, const int &sKey){ //Searches the provided search key in a given vector
    bool check=false;
    for (int i=0; i<vec.size(); i++){
        if (vec[i]==sKey){
            check=true;
            break;
        }else{
            ;
        }
    }
    return check;
}

string intToStr(const int &n){ //Converts integers into strings
    ostringstream temp;
    temp << n;
    return temp.str();
}

string adjacentBombCounter(const vector<vector<string>> &board, const int &x, const int &y){ //Counts the number of adjacent bombs
    int count=0;
    if (board[0].size()>1){
        if (y==0 && x==0){
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y+1][x+1]);
            for (int a=0; a<pslPts.size(); a++){
                if (pslPts[a]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (y==board.size()-1 && x==0){
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y-1][x]);
            pslPts.push_back(board[y-1][x+1]);
            for (int b=0; b<pslPts.size(); b++){
                if (pslPts[b]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (y==0 && x==board[0].size()-1){
            vector<string> pslPts;
            pslPts.push_back(board[y][x-1]);
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y+1][x-1]);
            for (int c=0; c<pslPts.size(); c++){
                if (pslPts[c]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (y==board.size()-1 && x==board[0].size()-1){
            vector<string> pslPts;
            pslPts.push_back(board[y-1][x]);
            pslPts.push_back(board[y][x-1]);
            pslPts.push_back(board[y-1][x-1]);
            for (int d=0; d<pslPts.size(); d++){
                if (pslPts[d]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (y==0){
            vector<string> pslPts;
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y+1][x+1]);
            pslPts.push_back(board[y+1][x-1]);
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y][x-1]);
            for (int e=0; e<pslPts.size(); e++){
                if (pslPts[e]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (x==0){
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y+1][x+1]);
            pslPts.push_back(board[y-1][x+1]);
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y-1][x]);
            for (int f=0; f<pslPts.size(); f++){
                if (pslPts[f]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (y==board.size()-1){
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y][x-1]);
            pslPts.push_back(board[y-1][x]);
            pslPts.push_back(board[y-1][x+1]);
            pslPts.push_back(board[y-1][x-1]);
            for (int g=0; g<pslPts.size(); g++){
                if (pslPts[g]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (x==board[0].size()-1){
            vector<string> pslPts;
            pslPts.push_back(board[y-1][x]);
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y][x-1]);
            pslPts.push_back(board[y+1][x-1]);
            pslPts.push_back(board[y-1][x-1]);
            for (int h=0; h<pslPts.size(); h++){
                if (pslPts[h]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else{
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y][x-1]);
            pslPts.push_back(board[y+1][x+1]);
            pslPts.push_back(board[y+1][x]);
            pslPts.push_back(board[y+1][x-1]);
            pslPts.push_back(board[y-1][x]);
            pslPts.push_back(board[y-1][x+1]);
            pslPts.push_back(board[y-1][x-1]);
            for (int i=0; i<pslPts.size(); i++){
                if (pslPts[i]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }
    }else if (board[0].size()==1){
        if (x==0){
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            for (int a=0; a<pslPts.size(); a++){
                if (pslPts[a]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else if (x==board[0].size()-1){
            vector<string> pslPts;
            pslPts.push_back(board[y][x-1]);
            for (int b=0; b<pslPts.size(); b++){
                if (pslPts[b]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }else{
            vector<string> pslPts;
            pslPts.push_back(board[y][x+1]);
            pslPts.push_back(board[y][x-1]);
            for (int c=0; c<pslPts.size(); c++){
                if (pslPts[c]=="B"){
                    count+=1;
                }else{
                    ;
                }
            }
        }
    }
    string countStr=intToStr(count);
    return countStr;
}

vector<vector<string>> boardGenerator(const int &noRows, const int &noCols, const int &noBombs){ //Generates the game board
    vector<vector<string>> board(noRows, vector<string> (noCols));
    RandGen gen;
    vector<int> bombCrdsX, bombCrdsY;
    int randX, randY;
    for (int i=0; i<noBombs; i++){
        do{
            randX=gen.RandInt(noCols);
        }while (vectorSearcher(bombCrdsX, randX)==true);
        bombCrdsX.push_back(randX);
        do{
            randY=gen.RandInt(noRows);
        }while (vectorSearcher(bombCrdsY, randY)==true);
        bombCrdsY.push_back(randY);
        board[bombCrdsY[i]][bombCrdsX[i]]="B";
    }
    for (int a=0; a<noRows; a++){
        for (int b=0; b<noCols; b++){
            if (board[a][b]!="B"){
                board[a][b]=adjacentBombCounter(board, b, a);
            }else{
                ;
            }
        }
    }
    return board;
}

vector<vector<string>> hiddenBoardGenerator(const vector<vector<string>> &board){ //Generates a hidden board for display
    vector<vector<string>> hiddenBoard(board.size(), vector<string> (board[0].size()));
    for (int a=0; a<hiddenBoard.size(); a++){
        for (int b=0; b<hiddenBoard[0].size(); b++){
            hiddenBoard[a][b]="X";
        }
    }
    return hiddenBoard;
}

void hiddenBoardUpdater(const vector<vector<string>> &board, vector<vector<string>> &hiddenBoard, const string &option, const int &y, const int &x){ //Updates the hidden board based on the choice and coordinates entered by the user
    if (option=="1"){
        hiddenBoard[y][x]=adjacentBombCounter(board, x, y);
    }else if (option=="2"){
        hiddenBoard[y][x]=board[y][x];
    }else{
        ;
    }
}

bool winChecker(const vector<vector<string>> &board, const vector<vector<string>> &hiddenBoard){ //Checks whether the user has won the game
    bool win=false;
    int doneCount=0;
    vector<vector<string>> boardCopy=board;
    for (int r=0; r<boardCopy.size(); r++){
        for (int elt=0; elt<boardCopy[r].size(); elt++){
            if (boardCopy[r][elt]=="B"){
                boardCopy[r][elt]="X";
            }else{
                ;
            }
        }
    }
    for (int o=0; o<hiddenBoard.size(); o++){
        for (int p=0; p<hiddenBoard[0].size(); p++){
            if (hiddenBoard[o][p]==boardCopy[o][p]){
                doneCount+=1;
            }else{
                ;
            }
        }
    }
    if (doneCount==board.size()*board[0].size()){
        win=true;
        cout << "Congratulations! All the non-mined cells opened successfully" << endl << "You won!" << endl << ">>>>> Game Over! <<<<<" << endl;
    }else{
        ;
    }
    return win;
}

void matrixPrinter(const vector<vector<string>> &mat){ //Taken from Week 1 lecture materials, slightly modified by me; prints the provided matrix
    for (int i=0; i<mat.size(); i++){   
		for (int j=0; j<mat[0].size(); j++){
            if (j!=0){
                cout << setw(4) << mat[i][j];
            }else{
                cout << mat[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void inputTaker(const int &noRows, const int &noCols, bool &exit, const vector<vector<string>> &board, vector<vector<string>> &hiddenBoard){ //Takes the rest of the inputs; basically the body of the code
    string option;
    bool win;
    cout << "Press:" << endl << "1. If you want to find out the surrounding of a cell" << endl << "2. If you want to open the cell" << endl << "3. If you want to exit." << endl;
    cin >> option;
    while (option!="1" && option!="2" && option!="3"){
        cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
        cin >> option;
    }
    if (option=="1"){
        int y, x;
        cout << "Give the coordinates: ";
        cin >> y >> x;
        while (y>=noRows || x>=noCols || y<0 || x<0){
            cout << "It is out of range. Please give a valid coordinates: ";
            cin >> y >> x;
        }
        hiddenBoardUpdater(board, hiddenBoard, option, y, x);
        cout << "Displaying the surrounding of (" << y << "," << x << "):" << endl; 
        matrixPrinter(hiddenBoard);
        cout << "Around (" << y << "," << x << ") you have " << hiddenBoard[y][x] << " bomb(s)" << endl;
    }else if (option=="2"){
        int y, x;
        cout << "Give the coordinates: ";
        cin >> y >> x;
        while (y>=noRows || x>=noCols || y<0 || x<0){
            cout << "It is out of range. Please give a valid coordinates: ";
            cin >> y >> x;
        }
        hiddenBoardUpdater(board, hiddenBoard, option, y, x);
        cout << endl << "Opening cell (" << y << "," << x << "):" << endl; 
        matrixPrinter(hiddenBoard);
        if (hiddenBoard[y][x]=="B"){
            cout << "Unfortunately, you stepped on a mine" << endl;
            cout << "Arrangement of mines:" << endl;
            matrixPrinter(board);
            cout << ">>>>> Game Over! <<<<<" << endl;
            exit=true;
        }else{
            exit=winChecker(board, hiddenBoard);
        }
    }else if (option=="3"){
        cout << "Program exiting ..." << endl;
        exit=true;
    }else{
        ;
    }
}

int main(){ //Runs the functions
    int noRows, noCols, noBombs;
    bool exit=false;
    inputTaker(noRows, noCols, noBombs);
    vector<vector<string>> board=boardGenerator(noRows, noCols, noBombs);
    vector<vector<string>> hiddenBoard=hiddenBoardGenerator(board);
    matrixPrinter(hiddenBoard);
    while (exit==false){
        inputTaker(noRows, noCols, exit, board, hiddenBoard);
    }
    return 0;
}