#ifndef DRIVER_H
#define DRIVER_H
#endif
#include <iostream>
#include <string>
#include "Car.h"

using namespace std;

class Driver{
    public:
        Driver(Car &, const double &);
        void drive(const int &);
        void repairCar(const string &);
        void display();
        void fullFuel();
    private:
        Car &car;
        double budget;
};