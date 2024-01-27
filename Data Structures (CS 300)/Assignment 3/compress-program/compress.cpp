#include "HashTable.h"
#include <fstream>

int main(){
    kc empty;
    HashTable<kc> dictionary(empty);

    //Code below fills the first 256 indices of the hash table (dictionary) with single characters in the ASCII table; they must be generated before the Ziv-Lempel Rule is followed.
    string strToBeInserted;
    kc toBeInserted;
    int i = 0;
    while (i < 256){
        unsigned char singleChr = (unsigned char)(i);
        strToBeInserted.push_back(singleChr); //Creates a string to be fitted into the struct

        toBeInserted.str = strToBeInserted;
        toBeInserted.code = i;

        dictionary.insert(toBeInserted);

        strToBeInserted.pop_back(); //Clears the string for the next iteration
        i++;
    }
    
    dictionary.printSingleCharacters();

    //Code below is a modification of that provided in the guide PDF so that the output file is a [pseudo]compressed version of the input file (following the Ziv-Lempel Rule).
    ifstream inputFile;
    ofstream outputFile;

    char ch;
    string newStr;
    kc newInsert;

    inputFile.open("compin");
    outputFile.open("compout");

    int count = 256; //Starting index for new strings
    while (!inputFile.eof()){
        inputFile.get(ch);
        ch = (unsigned char)ch;

        if (count < 4096){
            newStr.push_back(ch);
            newInsert.str = newStr;
            newInsert.code = count;

            while (dictionary.inTable(newInsert)){ //Repetitively finds the longest prefix not found in the dictionary
                inputFile.get(ch);
                ch = (unsigned char)ch;
                newStr.push_back(ch);
                newInsert.str = newStr;
            }

            kc output;
            string strOutput = (newInsert.str).substr(0, (newInsert.str).length() - 1); //Output string is the one that was previously inserted into the dictionary.
            int codeOutput;
            output.str = strOutput; //No need to set the code; the find() function only uses the string associated with the struct to search
            codeOutput = dictionary.find(output).code; //Output code is the one associated with the output string (details of which are already stored in the dictionary).

            outputFile << codeOutput << " ";
            
            dictionary.insert(newInsert); //Adds a new string to the dictionary
            count++;
            newStr = newStr.substr((newInsert.str).length() - 1, 1); //"Next" character becomes the "current" character of the next search (using the terminology used in https://www.youtube.com/watch?v=j2HSd3HCpDs).
        }else{
            kc output; string singleCh; singleCh.push_back(ch); output.str = singleCh; int codeOutput = dictionary.find(output).code;
            outputFile << codeOutput << " ";
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}