#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void houseChecker(int points, string &house){
    if (points<10){
        house="Hufflepuff";
    }else if (10<=points && points<15){
        house="Ravenclaw";
    }else if (15<=points && points<21){
        house="Gryffindor";
    }else if (21<=points){
        house="Slytherin";
    }else{
        ;
    }
}

int main(){
    string name, lastname, keyFile, answerFile, lineAnswers, lineKey, house, answer1, answer2, answer3, answer4, answer5, answer6, choice;
    ifstream answers, key;
    int lineCounter=1;
    cout << "Hello and welcome to the Hogwarts house sorting hat program!" << endl;
    cout << "When I call your name, you'll come forth, I shall place the sorting hat on your head, and you will be sorted into your houses." << endl;
    cout << "Enter the name of the key file: ";
    cin >> keyFile;
    key.open(keyFile.c_str());
    while (key.fail()){
        key.close();
        cout << "Error: Cannot open file " << keyFile << endl;
        cout << "Enter the name of the key file: ";
        cin >> keyFile;
        key.open(keyFile.c_str());
    }
    cout << "Enter the name of the answer file: ";
    cin >> answerFile;
    answers.open(answerFile.c_str());
    while (answers.fail()){
        answers.close();
        cout << "Error: Cannot open file " << answerFile << endl;
        cout << "Enter the name of the answer file: ";
        cin >> answerFile;
        answers.open(answerFile.c_str());
    }
    while (getline(answers, lineAnswers)){
        int choiceCounter, points=0;
        if (lineAnswers!="\r" && lineAnswers!=""){
            istringstream a(lineAnswers);
            a >> name >> lastname >> answer1 >> answer2 >> answer3 >> answer4 >> answer5 >> answer6;
            if (lineCounter>6){
                lineCounter=1;
                key.close();
                key.open(keyFile.c_str());
            }else{
                ;
            }
            while (getline(key, lineKey)){
                choiceCounter=1;
                istringstream k(lineKey);
                while (k >> choice){
                    if (lineCounter==1 && answer1==choice){
                        points+=choiceCounter;
                    }else if (lineCounter==2 && answer2==choice){
                        points+=choiceCounter;
                    }else if (lineCounter==3 && answer3==choice){
                        points+=choiceCounter;
                    }else if (lineCounter==4 && answer4==choice){
                        points+=choiceCounter;
                    }else if (lineCounter==5 && answer5==choice){
                        points+=choiceCounter;
                    }else if (lineCounter==6 && answer6==choice){
                        points+=choiceCounter;
                    }else{
                        ;
                    }
                    choiceCounter+=1;
                }
                lineCounter+=1;
            }
            houseChecker(points, house);
            cout << "Oh! we have " << name << " " << lastname << " under the sorting hat. " << name << ", you scored " << points << " points, you are a " << house << "!" << endl;
        }else{
            ;
        }
    }
    answers.close();
    return 0;
}

//Deniz Muratli