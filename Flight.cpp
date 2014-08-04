//implementation file for the Flight class

#include "Flight.h"

//constructor
Flight::Flight()
{
	departCity = " ";
	destinationCity = " ";
	departTime = " ";
	arrivalTime = " ";
	flightNumber = " ";
	aircraftType = ' ';
	freqFlyPoints = 0;
	flightFull = false;
}


Flight::Flight(string depCity, string destCity, string depTime, string arivTime,
			   string flightNum, char planeType, int ffPoints, Aircraft* pln)
{
	departCity = depCity;
	destinationCity = destCity;
	departTime = depTime;
	arrivalTime = arivTime;
	flightNumber = flightNum;
	aircraftType = planeType;
	freqFlyPoints = ffPoints;
	flightFull = false;



	if (planeType == 'A')
		pln = new AircraftA();
		pln->setSeatNumbers();

	if (planeType == 'B')
		pln = new AircraftB();
		pln->setSeatNumbers();

}