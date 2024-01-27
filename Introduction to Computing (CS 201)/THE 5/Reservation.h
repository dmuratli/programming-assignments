#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "date.h"

class Sailor{
	public:
		Sailor(){
			id = 0;
			name = "Jane Doe";
			age = 0;
			rank = 0;
		}
		void setId(int sid);
		int getId();
		void setName(string sname);
		string getName();
		void setAge(double sage);
		double getAge();
		void setRating(double srating);
		double getRating();
	private:
		int id;
		string name;
		double age;
		double rank;
};

class Boat{
	public:
		Boat(){
			id = 0;
			name = "Default";
			color = "Default";
		}
		void setId(int bid);
		int getId();
		void setName(string bname);
		string getName();
		void setColour(string bcolour);
		string getColour();
	private:
		int id;
		string name;  
		string color;
};

class Reservation{
	public:
		Reservation(){
			Sailor s;
			Boat b;
			Date d(1,1,1900);
			sailor = s;
			boat = b;
			resDate = d;
		}
		void assignSailor(Sailor s);
		Sailor getSailor();
		void assignBoat(Boat b);
		Boat getBoat();
		void assignDate(Date d);
		Date getDate();
		void Print(Date d, string sname, double age, double rating, string boatname, string boatcolour);
	private:
		Date resDate;
		Sailor sailor;
		Boat boat;
};

class Reservations{
	public:
		Reservations(vector<Reservation> db);
		void AddReservation(Boat b, Sailor s, Date d);
		bool DeleteReservations(Boat b);
		bool DeleteReservations(Sailor s);
		bool DeleteReservations(Date d, Sailor s, Boat b);
		vector<Reservation> FindReservations(Date SDate, Date EDate);
		vector<Reservation> FindReservations(Boat b, Date d);
		vector<Reservation> FindReservations(Sailor s, Date d);
	private:
		void Sorter(vector<Reservation> &db);
		vector<Reservation> reservations;
	
};