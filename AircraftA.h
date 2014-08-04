//specification file for the AircraftA class

#ifndef AIRCRAFTA_H
#define AIRCRAFTA_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Aircraft.h"
#include "AircraftFactory.h"

class AircraftA : public Aircraft
{
private:
//	vector <Seat> seats;
//	Seat seats[20];

public:
	//Aircraft Type A uses ID Number 0
	AircraftA():Aircraft(0)
	{
		string seatNum;
		for (int index = 0; index < 20; index++)
		{
			Seat* newSeat = new Seat;
			seats.push_back(newSeat);
		}
		setSeatNumbers();
	}

     
	AircraftA* createAircraft()
	{
		//creates a new AircraftA object
		return new AircraftA();
	}
	
	void setSeatNumbers();
	void setSeatOccupied(int idx);
	void setSeatName(int idx, string nam);
	string getSeatNumber(int idx);
	void displaySeatGrid();
	void displaySeatList();
	void displayPassengerList();
	string isSeatOccupied(int idx);
	bool determineFlightFull();
	void resetPlane();
	int seatNumToInt(string stNum);
};
#endif