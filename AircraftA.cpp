//implementation file for the AircraftA class

#include "AircraftA.h"


void AircraftA::setSeatNumbers()
{
	seats[0]->setSeatNumber("A1");
	seats[1]->setSeatNumber("A2");
	seats[2]->setSeatNumber("A3");
	seats[3]->setSeatNumber("A4");
	seats[4]->setSeatNumber("B1");
	seats[5]->setSeatNumber("B2");
	seats[6]->setSeatNumber("B3");
	seats[7]->setSeatNumber("B4");
	seats[8]->setSeatNumber("C1");
	seats[9]->setSeatNumber("C2");
	seats[10]->setSeatNumber("C3");
	seats[11]->setSeatNumber("C4");
	seats[12]->setSeatNumber("D1");
	seats[13]->setSeatNumber("D2");
	seats[14]->setSeatNumber("D3");
	seats[15]->setSeatNumber("D4");
	seats[16]->setSeatNumber("E1");
	seats[17]->setSeatNumber("E2");
	seats[18]->setSeatNumber("E3");
	seats[19]->setSeatNumber("E4");
}

void AircraftA::setSeatOccupied(int idx)
{
	if (seats[idx]->getSeatOccupied())
		seats[idx]->setSeatOcupied(false);
	else
		seats[idx]->setSeatOcupied(true);
}

void AircraftA::setSeatName(int idx, string nam)
{
	seats[idx]->setSeatName(nam);
}

string AircraftA::getSeatNumber(int pos)
{
	return seats[pos]->getSeatNumber();
}

void AircraftA::displaySeatGrid()
{
	cout << "\t\t\t";
	for (int index = 0; index < 20; index++)
	{
		if (index % 2 == 0)
			cout << "  ";
		cout << "|" << seats[index]->getSeatNumber() << isSeatOccupied(index) << "| ";
		if (index % 4 == 3)
			cout << endl << "\t\t\t";
	}
	cout << endl;
}

void AircraftA::displaySeatList()
{
	
	for (int index = 0; index < 20; index++)
		cout << "\t\t\t" << seats[index]->getSeatNumber() << "\t\t" << seats[index]->getSeatName() << endl;
}

void AircraftA::displayPassengerList()
{
	sort (seats.begin(), seats.end(), Seat::SortBySeatName);
	vector <Seat*> :: iterator itr;
	itr = seats.begin();
	for (Seat* &s : seats)
	{
		if ((*itr)->getSeatOccupied())
			cout << "\t\t\t" << (*itr)->getSeatNumber() << "\t\t" << (*itr)->getSeatName() << endl;
		itr++;
	}
	sort (seats.begin(), seats.end(), Seat::SortBySeatNumber);
}

string AircraftA::isSeatOccupied(int idx)
{
	if (seats[idx]->getSeatOccupied())
		return "-X";
	else
		return "- ";
}

bool  AircraftA::determineFlightFull()
{
	int occupiedSeatCount = 0;
	for (int index = 0; index < 20; index++)
	{
		if (seats[index]->getSeatOccupied())
			occupiedSeatCount++;
	}

	if (occupiedSeatCount == 20)
		return true;
	else
		return false;
}

void AircraftA::resetPlane()
{
	for (int idx = 0; idx < 20; idx++)
	{
		if (seats[idx]->getSeatOccupied())
		{
			seats[idx]->setSeatOcupied(false);
			seats[idx]->setSeatName(" ");
		}
	}
}

int AircraftA::seatNumToInt(string stNum)
{
	if (stNum == "A1")
		return 0;
	if (stNum == "A2")
		return 1;
	if (stNum == "A3")
		return 2;
	if (stNum == "A4")
		return 3;
	if (stNum == "B1")
		return 4;
	if (stNum == "B2")
		return 5;
	if (stNum == "B3")
		return 6;
	if (stNum == "B4")
		return 7;
	if (stNum == "C1")
		return 8;
	if (stNum == "C2")
		return 9;
	if (stNum == "C3")
		return 10;
	if (stNum == "C4")
		return 11;
	if (stNum == "D1")
		return 12;
	if (stNum == "D2")
		return 13;
	if (stNum == "D3")
		return 14;
	if (stNum == "D4")
		return 15;
	if (stNum == "E1")
		return 16;
	if (stNum == "E2")
		return 17;
	if (stNum == "E3")
		return 18;
	if (stNum == "E4")
		return 19;
	return -1;
}