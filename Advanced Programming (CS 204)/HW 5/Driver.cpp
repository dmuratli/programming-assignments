#include "Driver.h"

Driver::Driver(Car &dCar, const double &dBudget): car(dCar), budget(dBudget){}

void Driver::drive(const int &distance){
    car.addDist(distance);
    car.consumeFuel(distance);
}

void Driver::repairCar(const string &damageLvl){
    if (damageLvl=="SMALL"){
        budget-=50;
        car.reflectDamageCost(damageLvl);
        double insFee=car.currentInsFee();
        cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl;
        cout << "Yearly insurance fee is increased to " << insFee << " because of the SMALL accident" << endl;
    }else if (damageLvl=="MEDIUM"){
        budget-=150;
        car.reflectDamageCost(damageLvl);
        double insFee=car.currentInsFee();
        cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl;
        cout << "Yearly insurance fee is increased to " << insFee << " because of the MEDIUM accident" << endl;
    }else if (damageLvl=="LARGE"){
        budget-=300;
        car.reflectDamageCost(damageLvl);
        double insFee=car.currentInsFee();
        cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl;
        cout << "Yearly insurance fee is increased to " << insFee << " because of the LARGE accident" << endl;
    }else{
        ;
    }
}

void Driver::display(){
    cout << "Driver Budget: " << budget << endl << endl;
}

void Driver::fullFuel(){
    double remainingFuel=car.currentFuelLvl();
    double leftToFull=(300-remainingFuel);
    budget-=leftToFull;
    car.fuelUp(300);
    cout << "Fuel is full" << endl << endl;
}