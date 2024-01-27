#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

bool wordChecker(string word){
    bool true_false;
    for (int test=0; test<=word.length()-1; test++){
        char character=word.at(test);
        if ((character>=65 && character<=90) || (character>=97 && character<=122)){
            true_false=true;
        }else{
            true_false=false;
            break;
        }
    }
    return true_false;
}

string secretiser(string word){
    string secretword;
    for (int test=1; test<=word.length(); test++){
       char character='-';
       secretword+=character;
    }
    return secretword;
}

bool formatCheckerL(string letter_guess){
    if (wordChecker(letter_guess)==true){
        if (letter_guess.length()==1){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool wordGuessChecker(string word, string word_guess){
    if (word==word_guess){
        return true;
    }else{
        return false;
    }
}

bool memoryChecker(string letter_guess, string &memory){
    if (memory.find(letter_guess)==string::npos){
        memory.append(letter_guess);
        return true;
    }else{
        return false;
    }
}

bool letterGuessChecker(string word, string letter_guess){
    if (word.find(letter_guess)==string::npos){
        return false;
    }else{
        return true;
    }

}

bool choiceChecker(string choice){
    if (choice=="1" || choice=="2"){
        return true;
    }else{
        return false;
    }
}

void secretWordUpdater(string word, string letter_guess, string &secretword){
    string indices, stringified_ch_ext, stringified_ch_int;
    int ch_ext, ch_int;
    ch_ext=word.find(letter_guess);
    stringified_ch_ext=itoa(ch_ext);
    indices.append(stringified_ch_ext);
    for (int test=0; test<=word.length()-1; test++){
        if (word.substr(test, 1)==letter_guess){
            if (test!=word.find(letter_guess)){
                ch_int=test;
                stringified_ch_int=itoa(ch_int);
                indices.append(stringified_ch_int);
            }else{
                ;
            }
        }else{
            ;
        }
    }
    for (int test=0; test<=indices.length()-1; test++){
        int idx=atoi(indices.substr(test, 1));
        secretword.replace(idx, 1, letter_guess);
    }
}

void lifeUpdater(int &lives){
    if (lives==6){
        lives-=1;
        cout << "You have no free guess left." << endl;
    }else if (5>=lives && lives>3){
        lives-=1;
        cout << "You have lost a leg!" << endl;
    }else if (3>=lives && lives>1){
        lives-=1;
        cout << "You have lost an arm!" << endl;
    }else{
        lives-=1;
        cout << "You have lost a head! GAME OVER!" << endl;
    }
}

int main(){
    int lives=6;
    string name1, name2, word, secretword, letter_guess, word_guess, memory, choice;
    bool wordcheck, word_format, letter_format, word_guess_check, letter_guess_check, memorycheck, choicecheck;
    cout << "Welcome to the HANGMAN GAME" << endl;
    cout << "---------------------------" << endl;
    cout << "Player one, please enter your name: ";
    cin >> name1;
    cout << "Player two, please enter your name: ";
    cin >> name2;
    cout << "OK " << name1 << " and " << name2 << ". Let's start the game!" << endl;
    cout << name1 << ", please input the word you want " << name2 << " to guess: ";
    cin >> word;
    wordcheck=wordChecker(word);
    if (wordcheck==true){
        ToLower(word);
    }else{
        while (wordcheck==false){
            cout << "Invalid word! Try again." << endl;
            cout << name1 << ", please input the word you want " << name2 << " to guess: ";
            cin >> word;
            wordcheck=wordChecker(word);
        }
        ToLower(word);
    }
    cout << name2 << ", you have 1 free guess, after that you will lose limbs!" << endl;
    secretword=secretiser(word);

    while (lives!=0){
        cout << "The word is: " << secretword << endl;
        if (secretword!=word){
            cout << name2 << ", do you want to guess the word(1) or guess a letter(2)? ";
            cin >> choice;
            choicecheck=choiceChecker(choice);
            if (choicecheck==true){
                if (choice=="1"){
                    cout << "Your guess: ";
                    cin >> word_guess;
                    ToLower(word_guess);
                    word_format=wordChecker(word_guess);
                    if (word_format==true){
                        word_guess_check=wordGuessChecker(word, word_guess);
                        if (word_guess_check==true){
                            cout << "The word is: " << word << endl;
                            cout << "Congratulations " << name2 << ", you won!" << endl;
                            cout << name2 << " won the game!";
                            break;
                        }else{
                            lifeUpdater(lives);
                            if (lives==0){
                                cout << name2 << " lost the game :(";
                            }else{
                                ;
                            }
                        }
                    }else{
                        cout << "Invalid entry! Try again." << endl;
                    }
                }else{
                    cout << "Your guess: ";
                    cin >> letter_guess;
                    ToLower(letter_guess);
                    letter_format=formatCheckerL(letter_guess);
                    if (letter_format==true){
                        letter_guess_check=letterGuessChecker(word, letter_guess);
                        if (letter_guess_check==true){
                            memorycheck=memoryChecker(letter_guess, memory);
                            if (memorycheck==true){
                                secretWordUpdater(word, letter_guess, secretword);
                            }else{
                                cout << "Guess entered before! Try again." << endl;
                            }
                        }else{
                            memorycheck=memoryChecker(letter_guess, memory);
                            if (memorycheck==true){
                                lifeUpdater(lives);
                                if (lives==0){
                                    cout << name2 << " lost the game :(";
                                }else{
                                    ;
                                }
                            }else{
                                cout << "Guess entered before! Try again." << endl;
                            }
                        }
                    }else{
                        cout << "Invalid entry! Try again." << endl;
                    }
                }
            }else{
                cout << "Invalid option!" << endl;
            }
        }else{
            cout << "Congratulations " << name2 << ", you won!" << endl;
            cout << name2 << " won the game!";
            break;
        }
    }
}

//Deniz Muratli