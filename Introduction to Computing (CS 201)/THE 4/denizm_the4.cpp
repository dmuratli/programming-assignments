#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "strutils.h"
using namespace std;

struct sailor{
    string name, boat, colour, date;
    double age, rating;
};

void vectorPrinter(vector<sailor> sailorSets){
    for (int i=0; i<sailorSets.size(); i++){
        cout << sailorSets[i].date << " -> " << sailorSets[i].name << "(" << sailorSets[i].age << "," << sailorSets[i].rating << ") has reserved " << sailorSets[i].boat << "(" << sailorSets[i].colour << ")" << endl;
    }
}

void vectorSorter(vector<sailor> &sailorSets){
    for (int a=0; a<sailorSets.size()-1; a++){
        int minIdx=a;
        for (int b=a+1; b<sailorSets.size(); b++){
            if (sailorSets[b].date<sailorSets[minIdx].date){
                minIdx=b;
            }else if (sailorSets[b].date==sailorSets[minIdx].date){
                if (sailorSets[b].name<sailorSets[minIdx].name){
                    minIdx=b;   
                }else{
                    ;
                }
            }else{
                ;
            }
        }
        sailor minS=sailorSets[minIdx];
        sailorSets[minIdx]=sailorSets[a];
        sailorSets[a]=minS;
    } 
}

int vectorEltFinder(vector<int> idSet, int intToBeFound){
    int idx;
    for (int i=0; i<idSet.size(); i++){
        if (idSet[i]==intToBeFound){
            idx=i;
        }else{
            ;
        }
    }
    return idx;
}

int main(){
    ifstream boats, sailors, reservation;
    string lineBoats, lineSailors, lineReservation, bid, bname, bcolour, sid, sname, rating, age, filename, date;
    int bidInt, sidInt, idx, lineBoatsCounter=1, lineSailorsCounter=1, lineReservationCounter=1;
    double ratingDouble, ageDouble;
    vector<int> bids, sids;
    vector<double> ratings, ages;
    vector<string> bnames, bcolours, snames, dates;
    vector<sailor> sailorSets;
    sailor s;
    boats.open("Boats.txt");
    if (boats.fail()){
        boats.close();
        cout << "Cannot open the files. Exiting..." << endl;
    }else{
        while (getline(boats, lineBoats)){
            if (lineBoatsCounter==1){
                lineBoatsCounter+=1;
            }else{
                istringstream eltsBoats(lineBoats);
                eltsBoats >> bid >> bname >> bcolour;
                bidInt=atoi(bid);
                bids.push_back(bidInt);
                bnames.push_back(bname);
                bcolours.push_back(bcolour);
                lineBoatsCounter+=1;
            }
        }
        boats.close();
    }
    sailors.open("Sailors.txt");
    if (sailors.fail()){
        sailors.close();
        cout << "Cannot open the files. Exiting..." << endl;
    }else{
        while (getline(sailors, lineSailors)){
            if (lineSailorsCounter==1){
                lineSailorsCounter+=1;
            }else{
                istringstream eltsSailors(lineSailors);
                eltsSailors >> sid >> sname >> rating >> age;
                sidInt=atoi(sid);
                ratingDouble=atof(rating);
                ageDouble=atof(age);
                sids.push_back(sidInt);
                snames.push_back(sname);
                ratings.push_back(ratingDouble);
                ages.push_back(ageDouble);
                lineSailorsCounter+=1;
            }
        }
        sailors.close();
    }
    cout << "Enter filename for reservation database: ";
    cin >> filename;
    reservation.open(filename.c_str());
    if (reservation.fail()){
        reservation.close();
        cout << "Cannot open the files. Exiting..." << endl;
    }else{
        while (getline(reservation, lineReservation)){
            if (lineReservationCounter==1){
                lineReservationCounter+=1;
            }else{
                istringstream eltsReservation(lineReservation);
                eltsReservation >> sid >> bid >> date;
                sidInt=atoi(sid);
                idx=vectorEltFinder(sids, sidInt);
                s.name=snames[idx];
                s.age=ages[idx];
                s.rating=ratings[idx];
                bidInt=atoi(bid);
                idx=vectorEltFinder(bids, bidInt);
                s.boat=bnames[idx];
                s.colour=bcolours[idx];
                s.date=date;
                sailorSets.push_back(s);
                lineReservationCounter+=1;
            }
        }
        reservation.close();
        vectorSorter(sailorSets);
        vectorPrinter(sailorSets);
    }
    return 0;
}

//Deniz Muratli