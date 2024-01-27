#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
    string dictionary[4096];

    ifstream inputFile;
    ofstream outputFile;

    //Code below is adapted from its equivalent in compress.cpp.
    inputFile.open("compout");
    outputFile.open("decompout");

    string strToBeInserted;

    int i = 0;
    while (i < 256){ 
        unsigned char singleChr = (unsigned char)(i);
        strToBeInserted.push_back(singleChr); //Creates a string to be fitted into the struct

        dictionary[i] = strToBeInserted;

        strToBeInserted.pop_back(); //Clears the string for the next iteration
        i++;
    }
    
    char ch;
    string outputStr;
    int code, prevCode;

    int count = 256; //Starting index for new strings
    int codeCount = 0; //Number of characters; is meant to track whether the program is processing the first code (an exception) or not and is not constantly updated
    while (inputFile >> code){ //Continues as long as integers are received; avoids taking spaces in the input file into consideration
        if (codeCount == 0){ //First code is encountered, so the relevant piece of the array will be directly outputted.
            outputStr = dictionary[code]; //Sets text(code) as output
            outputFile << outputStr;
            codeCount++;
        }else{
            if (dictionary[code] == ""){ //The code is not in the dictionary.
                outputStr = dictionary[prevCode] + dictionary[prevCode].substr(0, 1); //Sets text(prevCode) + fc(prevCode) as output
                outputFile << outputStr;
                if (count < 4096){dictionary[code] = outputStr; /*Makes a new entry in the dictionary with the output*/}
            }else{ //The code is in the dictionary.
                outputStr = dictionary[code]; //Sets text(code) as output
                outputFile << outputStr;
                if (count < 4096){dictionary[count] = dictionary[prevCode] + dictionary[code].substr(0, 1); /*Makes a new entry in the dictionary with text(prevCode) + fc(code)*/}
            }
            count++;
        }
        prevCode = code; //Keeps the previous code in memory
    }

    inputFile.close();
    outputFile.close();

    return 0;
}