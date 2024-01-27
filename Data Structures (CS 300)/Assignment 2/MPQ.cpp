#include "MPQ.h"

MPQ::MPQ(int size){
    currentSize = 0;

    vector<int> emptyLocations(size, 0);
    vector<building> emptyArray(size);

    locations = emptyLocations;
    array = emptyArray;
}

MPQ::~MPQ(){
    currentSize = 0;
    array.clear();
    locations.clear();
}

void MPQ::percolateUp(int hole){
    while (hole > 0 && array[hole].value >= array[(hole - 1) / 2].value){
        building tmp = array[hole];
        array[hole] = array[(hole - 1) / 2];
        array[(hole - 1) / 2] = tmp;

        int tmpLoc = locations[array[hole].label];
        locations[array[hole].label] = locations[array[(hole - 1) / 2].label];
        locations[array[(hole - 1) / 2].label] = tmpLoc;

        hole = (hole - 1) / 2;
    }
}

bool MPQ::isEmpty(){
    if (currentSize == 0){
        return true;
    }else{
        return false;
    }
}

void MPQ::insert(int value, int label){
    building newBuilding(value, label);
    
    if (currentSize == 0){
        array[0] = newBuilding;
        locations[label] = 0;
    }else{
        int hole = currentSize; // Because my array uses the 0th index
        array[hole] = newBuilding;
        locations[label] = hole;
        percolateUp(hole);
    }
    
    currentSize++;
}

int MPQ::remove(int label){
    building emptyBuilding;
    building removedBuilding;

    if (currentSize == 0){
        return emptyBuilding.value;
    }else if (currentSize == 1){
        removedBuilding = array[0];
        array[0] = emptyBuilding;
        locations[label] = -1;
    }else{
        int lastIdx = currentSize - 1;
        int insertedPos = locations[label];

        removedBuilding = array[locations[label]];
        array[locations[label]] = array[lastIdx];

        locations[array[lastIdx].label] = locations[label];
        
        array[lastIdx] = emptyBuilding;
        locations[label] = -1;

        percolateUp(insertedPos);
    }

    currentSize--;

    return removedBuilding.value;
}

int MPQ::getMax(){
    return array[0].value;
}

void MPQ::printArray(){
    for (int i = 0; i < array.size(); i++){
        cout << array[i].value << ", " << array[i].label;

        if (i != array.size() - 1){
            cout << "   ";
        }else{
            cout << endl;
        }
    }
}

void MPQ::printLocations(){
    for (int i = 0; i < locations.size(); i++){
        cout << locations[i];

        if (i != array.size() - 1){
            cout << " ";
        }else{
            cout << endl;
        }
    }
}