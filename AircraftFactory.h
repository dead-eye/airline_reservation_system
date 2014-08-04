//specification file for the Aircraft Facotry class

#ifndef AIRCRAFTFACTORY_H
#define AIRCRAFTFACTORY_H
#include "Aircraft.h"
#include <vector>

using namespace std;

class AircraftFactory
{
private:
	vector<Aircraft*> m_RegisteredAircraft;
	static AircraftFactory* instance;

	//constructor
	AircraftFactory()
	{
		m_RegisteredAircraft.resize(2);
	}

public:
	//registers aircraft types into a vector of Aircraft pointers
	void registerAircraft(int aircraftID, Aircraft* a)
	{
		m_RegisteredAircraft[aircraftID] = a;
	}

	//the schedule class uses this function to create the Aircraft pointers
	//	that it stores in the flights vector
	Aircraft* createAircraft(int aircraftID)
	{
		return (Aircraft*)(m_RegisteredAircraft[aircraftID]->createAircraft());
	}

	//this function allows the Schedule class to use the AircraftFactory singleton
	static AircraftFactory* getInstance()
	{
		if (instance == NULL)
			instance = new AircraftFactory();
		return instance;
	}
};
#endif