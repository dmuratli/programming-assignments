#include <sstream>
#include "Reservation.h"
#include "date.h"
#include "strutils.h"
using namespace std;

int main(){
    string boatsFileName="Boats.txt", sailorsFileName="Sailors.txt", lineBoats, reservationsFileName, 
    lineSailors, lineReservations, bid, bname, bcolour, sid, sname, srating, sage, cmd, rdate, rdate2="";
    ifstream boatsText, sailorsText, reservationsText;
    int lineBoatsCounter=1, lineSailorsCounter=1, bidInt, sidInt, yearInt, monthInt, dayInt,
    yearInt2, monthInt2, dayInt2;
    double sratingDouble, sageDouble;
    cout << "Enter filename for reservation database: ";
    cin >> reservationsFileName;
    boatsText.open(boatsFileName.c_str());
    if (boatsText.fail()){
        boatsText.close();
        cout << "Cannot open the files. Exiting..." << endl << endl;
    }else{
        vector<Boat> BoatsDB;
        while (getline(boatsText, lineBoats)){
            if (lineBoatsCounter==1){
                lineBoatsCounter+=1;
            }else{
                istringstream boatsLineReader(lineBoats);
                Boat gBoat;
                boatsLineReader >> bid >> bname >> bcolour;
                bidInt=atoi(bid);
                gBoat.setId(bidInt);
                gBoat.setName(bname);
                gBoat.setColour(bcolour);
                BoatsDB.push_back(gBoat);
            }
        }
        boatsText.close();
        sailorsText.open(sailorsFileName.c_str());
        if (sailorsText.fail()){
            sailorsText.close();
            cout << "Cannot open the files. Exiting..." << endl << endl;
        }else{
            vector<Sailor> SailorsDB;
            while (getline(sailorsText, lineSailors)){
                if (lineSailorsCounter==1){
                    lineSailorsCounter+=1;
                }else{
                    istringstream sailorsLineReader(lineSailors);
                    Sailor gSailor;
                    sailorsLineReader >> sid >> sname >> srating >> sage;
                    sidInt=atoi(sid);
                    sratingDouble=atof(srating);
                    sageDouble=atof(sage);
                    gSailor.setId(sidInt);
                    gSailor.setName(sname);
                    gSailor.setAge(sageDouble);
                    gSailor.setRating(sratingDouble);
                    SailorsDB.push_back(gSailor);
                }
            }
            sailorsText.close();
            reservationsText.open(reservationsFileName.c_str());
            if (reservationsText.fail()){
                reservationsText.close();
                cout << "Cannot open the files. Exiting..." << endl << endl;
            }else{
                vector<Reservation> reservations;
                Reservations processor(reservations);
                while (getline(reservationsText, lineReservations)){
                    if (lineReservations!="\r" && lineReservations!=""){
                        istringstream reservationsFileReader(lineReservations);
                        reservationsFileReader >> cmd >> sid >> bid >> rdate >> rdate2;
                        if (cmd=="A"){
                            Boat b;
                            Sailor s;
                            bidInt=atoi(bid);
                            b.setId(bidInt);
                            sidInt=atoi(sid);
                            s.setId(sidInt);
                            yearInt=atoi(rdate.substr(0, rdate.find("-")));
                            monthInt=atoi(rdate.substr(rdate.find("-")+1, 2));
                            dayInt=atoi(rdate.substr(rdate.find("-")+4, 2));
                            Date d(monthInt, dayInt, yearInt);
                            processor.AddReservation(b, s, d);
                        }else if (cmd=="D"){
                            bool success;
                            if (sid!="0" && bid!="0" && rdate!="0000-00-00"){
                                Boat b;
                                Sailor s;
                                bidInt=atoi(bid);
                                b.setId(bidInt);
                                sidInt=atoi(sid);
                                s.setId(sidInt);
                                yearInt=atoi(rdate.substr(0, rdate.find("-")));
                                monthInt=atoi(rdate.substr(rdate.find("-")+1, 2));
                                dayInt=atoi(rdate.substr(rdate.find("-")+4, 2));
                                Date d(monthInt, dayInt, yearInt);
                                success=processor.DeleteReservations(d, s, b);
                                if (success==true){
                                    ;
                                }else{
                                    cout << "Error: Could not delete reservation \"" << sid << " " << bid << " " << rdate << "\"" << endl << endl;
                                }
                            }else if (sid=="0" && bid!="0" && rdate=="0000-00-00"){
                                Boat b;
                                bidInt=atoi(bid);
                                b.setId(bidInt);
                                success=processor.DeleteReservations(b);
                                if (success==true){
                                    ;
                                }else{
                                    cout << "Error: Could not delete reservation for boat id " << bid << endl << endl;
                                }
                            }else if (sid!="0" && bid=="0" && rdate=="0000-00-00"){
                                Sailor s;
                                sidInt=atoi(sid);
                                s.setId(sidInt);
                                success=processor.DeleteReservations(s);
                                if (success==true){
                                    ;
                                }else{
                                    cout << "Error: Could not delete reservation for sailor id " << sid << endl << endl;
                                }
                            }else{
                                ;
                            }
                        }else if (cmd=="F"){
                            if (sid=="0" && bid=="0" && rdate!="0000-00-00" && rdate2!=""){
                                vector<Reservation> foundReservations;
                                yearInt=atoi(rdate.substr(0, rdate.find("-")));
                                monthInt=atoi(rdate.substr(rdate.find("-")+1, 2));
                                dayInt=atoi(rdate.substr(rdate.find("-")+4, 2));
                                yearInt2=atoi(rdate2.substr(0, rdate2.find("-")));
                                monthInt2=atoi(rdate2.substr(rdate2.find("-")+1, 2));
                                dayInt2=atoi(rdate2.substr(rdate2.find("-")+4, 2));
                                Date sd(monthInt, dayInt, yearInt);
                                Date ed(monthInt2, dayInt2, yearInt2);
                                foundReservations=processor.FindReservations(sd, ed);
                                if (foundReservations.size()>0){
                                    cout << "Find Results:" << endl;
                                    for (int i=0; i<foundReservations.size(); i++){
                                        Date dinfo=foundReservations[i].getDate();
                                        Sailor sinfo=foundReservations[i].getSailor();
                                        Boat binfo=foundReservations[i].getBoat();
                                        int sidNo=sinfo.getId(), bidNo=binfo.getId();
                                        double age, rating;
                                        string boatname, boatcolour, sailorname;
                                        for (int a=0; a<SailorsDB.size(); a++){
                                            int tempSid=SailorsDB[a].getId();
                                            if (tempSid==sidNo){
                                                age=SailorsDB[a].getAge();
                                                rating=SailorsDB[a].getRating();
                                                sailorname=SailorsDB[a].getName();
                                            }else{
                                                ;
                                            }
                                        }
                                        for (int b=0; b<BoatsDB.size(); b++){
                                            int tempBid=BoatsDB[b].getId();
                                            if (tempBid==bidNo){
                                                boatname=BoatsDB[b].getName();
                                                boatcolour=BoatsDB[b].getColour();
                                            }else{
                                                ;
                                            }
                                        }
                                        Reservation printer;
                                        printer.Print(dinfo, sailorname, age, rating, boatname, boatcolour);
                                    }
                                    cout << endl;
                                }else{
                                    cout << "Find Results:" << endl;
                                    cout << "Error: No matching reservation found between dates " << rdate << " & " << rdate2 << endl << endl;
                                }
                                rdate2="";
                            }else if(sid=="0" && bid!="0" && rdate!="0000-00-00" && rdate2==""){
                                vector<Reservation> foundReservations;
                                Boat b;
                                bidInt=atoi(bid);
                                b.setId(bidInt);
                                yearInt=atoi(rdate.substr(0, rdate.find("-")));
                                monthInt=atoi(rdate.substr(rdate.find("-")+1, 2));
                                dayInt=atoi(rdate.substr(rdate.find("-")+4, 2));
                                Date d(monthInt, dayInt, yearInt);
                                foundReservations=processor.FindReservations(b, d);
                                if (foundReservations.size()>0){
                                    cout << "Find Results:" << endl;
                                    for (int i=0; i<foundReservations.size(); i++){
                                        Date dinfo=foundReservations[i].getDate();
                                        Sailor sinfo=foundReservations[i].getSailor();
                                        Boat binfo=foundReservations[i].getBoat();
                                        int sidNo=sinfo.getId(), bidNo=binfo.getId();
                                        double age, rating;
                                        string boatname, boatcolour, sailorname;
                                        for (int a=0; a<SailorsDB.size(); a++){
                                            int tempSid=SailorsDB[a].getId();
                                            if (tempSid==sidNo){
                                                age=SailorsDB[a].getAge();
                                                rating=SailorsDB[a].getRating();
                                                sailorname=SailorsDB[a].getName();
                                            }else{
                                                ;
                                            }
                                        }
                                        for (int b=0; b<BoatsDB.size(); b++){
                                            int tempBid=BoatsDB[b].getId();
                                            if (tempBid==bidNo){
                                                boatname=BoatsDB[b].getName();
                                                boatcolour=BoatsDB[b].getColour();
                                            }else{
                                                ;
                                            }
                                        }
                                        Reservation printer;
                                        printer.Print(dinfo, sailorname, age, rating, boatname, boatcolour);
                                    }
                                    cout << endl;
                                }else{
                                    cout << "Find Results:" << endl;
                                    cout << "Error: No matching reservation found for boat id " << bid << " on " << rdate << endl << endl;
                                }
                            }else if (sid!="0" && bid=="0" && rdate!="0000-00-00" && rdate2==""){
                                vector<Reservation> foundReservations;
                                Sailor s;
                                sidInt=atoi(sid);
                                s.setId(sidInt);
                                yearInt=atoi(rdate.substr(0, rdate.find("-")));
                                monthInt=atoi(rdate.substr(rdate.find("-")+1, 2));
                                dayInt=atoi(rdate.substr(rdate.find("-")+4, 2));
                                Date d(monthInt, dayInt, yearInt);
                                foundReservations=processor.FindReservations(s, d);
                                if (foundReservations.size()>0){
                                    cout << "Find Results:" << endl;
                                    for (int i=0; i<foundReservations.size(); i++){
                                        Date dinfo=foundReservations[i].getDate();
                                        Sailor sinfo=foundReservations[i].getSailor();
                                        Boat binfo=foundReservations[i].getBoat();
                                        int sidNo=sinfo.getId(), bidNo=binfo.getId();
                                        double age, rating;
                                        string boatname, boatcolour, sailorname;
                                        for (int a=0; a<SailorsDB.size(); a++){
                                            int tempSid=SailorsDB[a].getId();
                                            if (tempSid==sidNo){
                                                age=SailorsDB[a].getAge();
                                                rating=SailorsDB[a].getRating();
                                                sailorname=SailorsDB[a].getName();
                                            }else{
                                                ;
                                            }
                                        }
                                        for (int b=0; b<BoatsDB.size(); b++){
                                            int tempBid=BoatsDB[b].getId();
                                            if (tempBid==bidNo){
                                                boatname=BoatsDB[b].getName();
                                                boatcolour=BoatsDB[b].getColour();
                                            }else{
                                                ;
                                            }
                                        }
                                        Reservation printer;
                                        printer.Print(dinfo, sailorname, age, rating, boatname, boatcolour);
                                    }
                                    cout << endl;
                                }else{
                                    cout << "Find Results:" << endl;
                                    cout << "Error: No matching reservation found for sailor id " << sid << " on " << rdate << endl << endl;
                                }
                            }else{
                                ;
                            }
                        }else{
                            ;
                        }
                    }else{
                        ;
                    }
                }
                reservationsText.close();
            }
        }
    }
    return 0;
}