#include "Car.h"

Car::Car(const int &maxFuel, const int &totalIns, const int &distanceSF): fuelLvl(maxFuel), insFee(totalIns), totalDist(distanceSF){}

void Car::addDist(const int &distance){
    totalDist+=distance;
}

void Car::consumeFuel(const int &distance){
    fuelLvl-=(distance*0.25);
}

void Car::reflectDamageCost(const string &damageLvl){
    if (damageLvl=="SMALL"){
        insFee*=1.05;
    }else if (damageLvl=="MEDIUM"){
        insFee*=1.10;
    }else if (damageLvl=="LARGE"){
        insFee*=1.20;
    }else{
        ;
    }
}

double Car::currentInsFee(){
    return insFee;
}

double Car::currentFuelLvl(){
    return fuelLvl;
}

void Car::display(){
    cout << "Fuel Level: " << fuelLvl << endl;
    cout << "Insurance Fee: " << insFee << endl;
    cout << "Total distance that the car has travelled: " << totalDist << endl << endl;
}

void Car::fuelUp(const double &fuelWorth){
    fuelLvl=fuelWorth;
}