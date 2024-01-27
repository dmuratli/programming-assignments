#ifndef _MPQ_H
#define _MPQ_H

#include <iostream>
#include <vector>

using namespace std;

struct building{
    int value;
    int label;

    building(): value(0), label(-1){}
    building(int val, int lab){
        value = val;
        label = lab;
    }
};

class MPQ{
    public:
        MPQ(int size);
        ~MPQ();
        bool isEmpty();
        void insert(int value, int label);
        int remove(int label);
        int getMax();
        void printArray(); //Designed for debugging purposes
        void printLocations(); //Designed for debugging purposes
    private:
        int currentSize; 
        vector<building> array;
        vector<int> locations;
        void percolateUp(int hole); //Designed for convenience
};

#endif