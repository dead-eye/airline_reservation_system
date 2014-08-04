//specification file for the Flight class

#ifndef FLIGHT_H
#define FLIGHT_H
#include <string>
#include "City.h"
#include "AircraftA.h"
#include "AircraftB.h"

using namespace std;

class Flight
{
protected:
	string departCity;
	string destinationCity;
	string departTime;
	string arrivalTime;
	string flightNumber;
	char aircraftType;
	int freqFlyPoints;
	bool flightFull;
	Aircraft* plane;


public:
	//constructor
	Flight();
	Flight(string depCity, string destCity, string depTime, string arivTime,
			   string flightNum, char planeType, int ffPoints, Aircraft* pln);
	
	//setter
	void setDepartCity(string depCity) { departCity = depCity; }
	void setDestinationCity(string desCity) { destinationCity = desCity; }
	void setDepartTime(string depTime) { departTime = depTime; }
	void setArrivalTime(string arivTime) { arrivalTime = arivTime; }
	void setFlightNumber(string flightNum) { flightNumber = flightNum; }
	void setAircraftType(char planeType) { aircraftType = planeType; }
	void setFreqFlyPoints(int ffPoints) { freqFlyPoints = ffPoints; }
	void setFlightFull(bool full) { flightFull = full; }
	void setPlanePtr(Aircraft* pln) { plane = pln; }

	//getter
	string getDepartCity() { return departCity; }
	string getDestinationCity() { return destinationCity; }
	string getDepartTime() { return departTime; }
	string getArrivalTime() { return arrivalTime; }
	string getFlightNumber() { return flightNumber; }
	char getAircraftType() { return aircraftType; }
	int getFreqFlyPoints() { return freqFlyPoints; }
	bool getFlightFull() { return flightFull; }
	Aircraft* getPlanePtr() { return plane; }



	static bool SortByDepartCity(const Flight* f1, const Flight* f2)
	{
		return f1->departCity < f2->departCity;
	}
	
	static bool SortByDestinationCity(const Flight* f1, const Flight* f2)
	{
		return f1->destinationCity < f2->destinationCity;
	}
	
	static bool SortByDepartTime(const Flight* f1, const Flight* f2)
	{
		return f1->departTime < f2->departTime;
	}
	
	static bool SortByArrivalTime(const Flight* f1, const Flight* f2)
	{
		return f1->arrivalTime < f2->arrivalTime;
	}
	
	static bool SortByFlightNumber(const Flight* f1, const Flight* f2)
	{
		return atoi(f1->flightNumber.c_str()) < atoi(f2->flightNumber.c_str());
	}
	
	static bool SortByAircraftType(const Flight* f1, const Flight* f2)
	{
		return f1->aircraftType < f2->aircraftType;
	}
	
	static bool SortByFreqFlyPoints(const Flight* f1, const Flight* f2)
	{
		return f1->freqFlyPoints > f2->freqFlyPoints;
	}
	
	static bool SortByFlightFull(const Flight* f1, const Flight* f2)
	{
		return f1->flightFull < f2->flightFull;
	}
};
#endif