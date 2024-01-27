#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct kc{ //Provides a node that can store a given string and its corresponding code; kc stands for key-code
    string str;
    int code;

    kc(): str(""), code(-1){} //PROBLEM HERE?

    bool operator==(const kc &rhs){ //Enables comparing two kc objects
        if (this->str == rhs.str){
            return true;
        }else if (this->code == rhs.code){
            return true;
        }else{
            return false;
        }
    }
    bool operator!=(const kc &rhs){ //Enables comparing two kc objects
        if (this->str != rhs.str && this->code != rhs.code){
            return true;
        }else{
            return false;
        }
    }
};

//No extra explanations will be provided for functions taken directly from the slides
template <class HashedObj>
class HashTable{ //Taken from lecture slides; removed unused elements, added extra functionality, and modified certain parts for the task at hand
    public:
        explicit HashTable(const HashedObj &notFound, int size = 4096);
        const HashedObj &find(const HashedObj &x) const;
        void insert(const HashedObj &x);
        const bool inTable(const HashedObj &x) const;
        void printSingleCharacters();
        enum EntryType {ACTIVE, EMPTY, DELETED};
    private:
        struct HashEntry{
            HashedObj element;
            EntryType info;

            HashEntry(const HashedObj &e = HashedObj(), EntryType i = EMPTY): element(e), info(i){}
        };

        vector<HashEntry> array;

        const HashedObj ITEM_NOT_FOUND;
        bool isActive(int currentPos) const;
        int findPos(const HashedObj &x) const;

        /* 
        The hash functions were originally going to be member functions 
        but they did not work for some reason. 
        */

        // int hash(const int &key, const int &tableSize);
        // int hash(const char &key, const int &tableSize);
        // int hash(const string &key, const int &tableSize);
        // int hash(const kc &key, const int &tableSize);
};

template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj &notFound, int size): ITEM_NOT_FOUND(notFound), array(size){}

/*
I could have easily required only one parameter for the following hash functions, but did not risk
messing with the built-in hash() function of C++ (even using the same function name was enough to complicate things).

Still not sure whether the first 3 are necessary, but I did not want to risk missing a test case :)
*/

int hash(const string &key, const int &tableSize){ //Hashes a string to the table
    int chSum = 0;

    for (int i = 0; i < key.length(); i++){
        chSum += (unsigned char)(key.at(i)); //It overflows to negative values unless it's unsigned!
    }

    return (chSum % tableSize);
}

int hash(const int &key, const int &tableSize){ //Hashes an integer to the table
    return (key % tableSize);
}

int hash(const char &key, const int &tableSize){ //Hashes a character to the table
    return ((unsigned char)key % tableSize);
}

template <class HashedObj>
int hash(const HashedObj &key, const int &tableSize){ //Hashes a HashedObj to the table (specifically kc)
    int chSum = 0;

    for (int i = 0; i < key.str.length(); i++){
        chSum += (unsigned char)(key.str.at(i)); //It overflows to negative values unless it's unsigned!
    }

    return (chSum % tableSize);
}

template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const{ //Performs linear probing to resolve collisions; it is a modification of the quadratic prober findPos in the slides
    int i = 0;
    int p = ::hash(x, array.size());

    HashedObj element = array[p].element;

    while (array[p].info != EMPTY && element != x){
        p += 1;

        if (p >= array.size()){
            p = p - array.size();
        }else{
            ;
        }

        element = array[p].element;
    }

	return p;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const{
    return array[currentPos].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj &x){
    int currentPos = findPos(x);

    if(isActive(currentPos))
        return;

    array[currentPos] = HashEntry(x, ACTIVE);
}

template <class HashedObj>
const HashedObj &HashTable<HashedObj>::find(const HashedObj &x) const{
    int currentPos = findPos(x);

    if (isActive(currentPos)) 
       return array[currentPos].element; 

    return ITEM_NOT_FOUND;
}

template <class HashedObj>
const bool HashTable<HashedObj>::inTable(const HashedObj &x) const{ //Determines whether a key is already in the table
    int currentPos = findPos(x);
    
    if (isActive(currentPos)){
        return true;
    }else{
        return false;
    }
}

template <class HashedObj>
void HashTable<HashedObj>::printSingleCharacters(){
    for (int i; i < 256; i++){
        cout << array[i].element.str << " " << array[i].element.code << endl;
    }
}

#endif