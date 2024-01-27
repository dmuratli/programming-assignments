#include "Reservation.h"

void Boat::setId(int bid){
    id=bid;
}

int Boat::getId(){
    return id;
}

void Boat::setName(string bname){
    name=bname;
}

string Boat::getName(){
    return name;
}

void Boat::setColour(string bcolour){
    color=bcolour;
}

string Boat::getColour(){
    return color;
}

void Sailor::setId(int sid){
    id=sid;
}

int Sailor::getId(){
    return id;
}

void Sailor::setAge(double sage){
    age=sage;
}

double Sailor::getAge(){
    return age;
}

void Sailor::setRating(double srating){
    rank=srating;
}

double Sailor::getRating(){
    return rank;
}

void Sailor::setName(string sname){
    name=sname;
}

string Sailor::getName(){
    return name;
}

Sailor Reservation::getSailor(){
    return sailor;
}

Boat Reservation::getBoat(){
    return boat;
}

Date Reservation::getDate(){
    return resDate;
}

void Reservation::assignBoat(Boat b){
    boat=b;
}

void Reservation::assignSailor(Sailor s){
    sailor=s;
}

void Reservation::assignDate(Date d){
    resDate=d;
}

Reservations::Reservations(vector<Reservation> db){
    reservations=db;
}

void Reservations::Sorter(vector <Reservation> &db){
	if(db.size()>2){
		int minIdx;
		for(int a=0; a<db.size()-1; a++){
			minIdx=a;
			for(int b=a+1; b<db.size(); b++){
                Date currentD=db[b].getDate(), minD=db[minIdx].getDate();
				if (currentD<minD){
					minIdx=b;
				}else if(currentD==minD){
                    Sailor currentS=db[b].getSailor(), minS=db[minIdx].getSailor();
                    string currentSName=currentS.getName(), minSName=minS.getName();
					if(currentSName<minSName){
						minIdx=b;
					}
				}
			}
			Reservation minR = db[a];
			db[a] = db[minIdx];
			db[minIdx] = minR;
		}
	}	
}

void Reservations::AddReservation(Boat b, Sailor s, Date d){
    Reservation newR;
    newR.assignBoat(b);
    newR.assignSailor(s);
    newR.assignDate(d);
    reservations.push_back(newR);
    Sorter(reservations);
}

bool Reservations::DeleteReservations(Boat b){
    bool success=false;
    int originBid=b.getId();
    for (int c=0; c<reservations.size(); c++){
        Boat currentB=reservations[c].getBoat();
        int currentBid=currentB.getId();
        if (currentBid==originBid){
            reservations[c]=reservations[reservations.size()-1];
            reservations.pop_back();
            success=true;
        }else{
            ;
        }
    }
    Sorter(reservations);
    return success;
}

bool Reservations::DeleteReservations(Sailor s){
    bool success=false;
    int originSid=s.getId();
    for (int c=0; c<reservations.size(); c++){
        Sailor currentS=reservations[c].getSailor();
        int currentSid=currentS.getId();
        if (currentSid==originSid){
            reservations[c]=reservations[reservations.size()-1];
            reservations.pop_back();
            success=true;
        }else{
            ;
        }
    }
    Sorter(reservations);
    return success;
}

bool Reservations::DeleteReservations(Date d, Sailor s,  Boat b){
    bool success=false;
    int originSid=s.getId();
    int originBid=b.getId();
    for (int c=0; c<reservations.size(); c++){
        Date currentD=reservations[c].getDate();
        Sailor currentS=reservations[c].getSailor();
        int currentSid=currentS.getId();
        Boat currentB=reservations[c].getBoat();
        int currentBid=currentB.getId();
        if (currentD==d && currentSid==originSid && currentBid==originBid){
            reservations[c]=reservations[reservations.size()-1];
            reservations.pop_back();
            success=true;
        }else{
            ;
        }
    }
    Sorter(reservations);
    return success;
}

vector<Reservation> Reservations::FindReservations(Date SDate, Date EDate){
    vector<Reservation> foundReservations;
    for (int i=0; i<reservations.size(); i++){
        Date currentD=reservations[i].getDate();
        if (SDate==currentD){
            foundReservations.push_back(reservations[i]);
        }else if (SDate<currentD && currentD<EDate){
            foundReservations.push_back(reservations[i]);
        }else if (EDate==currentD){
            foundReservations.push_back(reservations[i]);
        }else{
            ;
        }
    }
    return foundReservations;
}

vector<Reservation> Reservations::FindReservations(Boat b, Date d){
    vector<Reservation> foundReservations;
    int bid=b.getId();
    for (int i=0; i<reservations.size(); i++){
        Boat currentB=reservations[i].getBoat();
        int currentBid=currentB.getId();
        Date currentD=reservations[i].getDate();
        if (bid==currentBid && d==currentD){
            foundReservations.push_back(reservations[i]);
        }else{
            ;
        }
    }
    return foundReservations;
}

vector<Reservation> Reservations::FindReservations(Sailor s, Date d){
    vector<Reservation> foundReservations;
    int sid=s.getId();
    for (int i=0; i<reservations.size(); i++){
        Sailor currentS=reservations[i].getSailor();
        int currentSid=currentS.getId();
        Date currentD=reservations[i].getDate();
        if (sid==currentSid && d==currentD){
            foundReservations.push_back(reservations[i]);
        }else{
            ;
        }
    }
    return foundReservations;
}

void Reservation::Print(Date d, string sname, double age, double rating, string boatname, string boatcolour){
    cout << d.MonthName() << " " << d.Day() << " " << d.Year() << " -> " << sname << "(" << age << "," << rating << ") has reserved " << boatname << "(" << boatcolour << ")" << endl;
}