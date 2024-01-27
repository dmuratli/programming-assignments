#include <fstream>
#include "MPQ.h"
#include "strutils.h"

struct xcoord{
    int x;
    string side;
    int buildingNo;

    xcoord(): x(-1), side("none"), buildingNo(-1){}
};

void print(const vector<xcoord> &xs){ //Designed for debugging purposes
    for (int i = 0; i < xs.size(); i++){
        cout << xs[i].x;
        
        if (i != xs.size() - 1){
            cout << " ";
        }else{
            cout << endl;
        }
    }
    for (int i = 0; i < xs.size(); i++){
        cout << xs[i].side;
        
        if (i != xs.size() - 1){
            cout << " ";
        }else{
            cout << endl;
        }
    }
    for (int i = 0; i < xs.size(); i++){
        cout << xs[i].buildingNo;
        
        if (i != xs.size() - 1){
            cout << " ";
        }else{
            cout << endl;
        }
    }
}

MPQ inputReader(const string &fileName, vector<xcoord> &xs){ //Reads the input file
    string a, b, c;
    int vectorSize;
    ifstream buildingFile(fileName.c_str());

    //First line
    buildingFile >> a;
    
    MPQ heap(atoi(a));

    vectorSize = 2*(atoi(a));
    vector<xcoord> newXS(vectorSize);
    xs = newXS;

    //Remaining lines
    int buildingNo = 0, idxCnt = 0;
    while (buildingFile >> a >> b >> c){
        int x1 = atoi(a), y = atoi(b), x2 = atoi(c);

        xs[idxCnt].x = x1;
        xs[idxCnt].side = "left";

        xs[idxCnt + 1].x = x2;
        xs[idxCnt + 1].side = "right";

        xs[idxCnt].buildingNo = buildingNo;
        xs[idxCnt + 1].buildingNo = buildingNo;

        heap.insert(y, buildingNo); //Check later whether the heap structure property always holds

        idxCnt = idxCnt + 2;
        buildingNo++;
    }

    return heap;
}

//Credits to Cemal Hoca for the Merge Sort implementation below (merge, mergeSort(single parameter), mergeSort(multiple parameters))
void merge(vector<xcoord> &xs, vector<xcoord> &tmpXS, int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while(leftPos <= leftEnd && rightPos <= rightEnd){
        if(xs[leftPos].x <= xs[rightPos].x){
            tmpXS[tmpPos++] = xs[leftPos++];
        }else{
            tmpXS[tmpPos++] = xs[rightPos++];
        }
    }

    while (leftPos <= leftEnd){
        tmpXS[tmpPos++] = xs[leftPos++];
    }

    while( rightPos <= rightEnd ){
        tmpXS[tmpPos++] = xs[rightPos++];
    }

    for(int i = 0; i < numElements; i++, rightEnd--){
        xs[rightEnd] = tmpXS[rightEnd];
    }
}

void mergeSort(vector<xcoord> &xs, vector<xcoord> &tmpXS, const int &left, const int &right){
    if(left < right){
        int centre = (left + right) / 2;
        mergeSort(xs, tmpXS, left, centre);
        mergeSort(xs, tmpXS, centre + 1, right);
        merge(xs, tmpXS, left, centre + 1, right);
    }else{
        ;
    }
}

void mergeSort(vector<xcoord> &xs){
    vector<xcoord> tmpXS(xs.size());
    mergeSort(xs, tmpXS, 0, xs.size() - 1);
}

void skylineComputer(const vector<xcoord> &xs, MPQ buildingList){ //Computes the skyline
    MPQ buildingsInX(xs.size() / 2);
    int previousH = 0;

    for (int i = 0; i < xs.size(); i++){
        if (xs[i].side == "left"){
            int val = buildingList.remove(xs[i].buildingNo);
            buildingsInX.insert(val, xs[i].buildingNo);
            buildingList.insert(val, xs[i].buildingNo);
            if (i < xs.size()-2 && xs[i].side == "left" && xs[i+1].side == "left" && xs[i].x == xs[i+1].x){
                continue;
            }else{
                ;
            }
            
        }else{
            int rmd = buildingsInX.remove(xs[i].buildingNo);
            if (i < xs.size() - 2 && xs[i].side == "right" && xs[i+1].side == "right" && xs[i].x == xs[i+1].x){
                continue;
            }else{
                ;
            }
        }
        
        if (i == 0 && xs[i].x != 0){
            cout << 0 << " " << 0 << endl;
            cout << xs[i].x << " " << buildingsInX.getMax() << endl;
            previousH = buildingsInX.getMax();
        }else if (i == xs.size() - 1){
            cout << xs[i].x << " " << "0" << endl;
        }else if (buildingsInX.getMax() > previousH){
            cout << xs[i].x << " " << buildingsInX.getMax() << endl;
            previousH = buildingsInX.getMax();
        }else if (buildingsInX.getMax() < previousH){
            if (buildingsInX.isEmpty() && xs[i].x == xs[i+1].x){
                ;
            }else{
                cout << xs[i].x << " " << buildingsInX.getMax() << endl;
                previousH = buildingsInX.getMax();
            }
        }else{
            ;
        }
    }
}

int main(){
    vector<xcoord> xList;
    MPQ buildings = inputReader("input.txt", xList);
    mergeSort(xList);
    skylineComputer(xList, buildings);
    return 0;
}