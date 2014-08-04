//specification file for the abstract AircraftB class

#ifndef AIRCRAFTB_H
#define AIRCRAFTB_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Aircraft.h"
#include "AircraftFactory.h"

class AircraftB : public Aircraft
{
private:
//	vector <Seat> seats;
//	Seat seats[15];
	
public:
	//Aircraft Type B uses ID Number 1
	AircraftB():Aircraft(1)
	{
		string seatNum;
		for (int index = 0; index < 15; index++)
		{
			Seat* newSeat = new Seat;
			seats.push_back(newSeat);
		}
		setSeatNumbers();
	}


	AircraftB* createAircraft()
	{
		//creates a new AircraftB object
		return new AircraftB();
	}
	
	void setSeatNumbers();
	void setSeatOccupied(int idx);
	void setSeatName(int idx, string nam);
	string getSeatNumber(int idx);
	void displaySeatGrid();
	void displaySeatList();
	void displayPassengerList();
	string isSeatOccupied(int idx);
	bool  AircraftB::determineFlightFull();
	void resetPlane();
	int seatNumToInt(string stNum);
};
#endif