//specification file for the abstract Aircraft class

#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include "Seat.h"

class Aircraft
{
public:
	//constructors
	Aircraft() : id_number(0) {}
	Aircraft(int a) : id_number(a) {}

	//destructor
	~Aircraft()
	{
		while (!(seats.empty()))
		{
			delete seats.back();
			seats.pop_back();
		}
	}

	//operation overloads
	int id() {return id_number;}

	void operator = (Aircraft & rhs)
	{id_number = rhs.id_number;}

	bool operator == (Aircraft & rhs)
	{
		if (id_number == rhs.id_number)
			return true;
		else
			return false;
	}

	bool operator < (Aircraft & rhs)
	{
		if (id_number < rhs.id_number)
			return true;
		else
			return false;
	}

	virtual Aircraft* createAircraft() = 0;
	virtual void setSeatNumbers() = 0;
	virtual void setSeatOccupied(int idx) = 0;
	virtual void setSeatName(int idx, string nam) = 0;
	virtual string getSeatNumber(int idx) = 0;
	virtual void displaySeatGrid() = 0;
	virtual void displaySeatList() = 0;
	virtual void displayPassengerList() = 0;
	virtual string isSeatOccupied(int idx) = 0;
	virtual bool determineFlightFull() = 0;
	virtual void resetPlane() = 0;
	virtual int seatNumToInt(string stNum) = 0;

protected:
	int id_number;		//aircraft identification number
	vector <Seat*> seats;

};
#endif