//implementation file for the AircraftB class

#include "AircraftB.h"


void AircraftB::setSeatNumbers()
{
	seats[0]->setSeatNumber("A1");
	seats[1]->setSeatNumber("A2");
	seats[2]->setSeatNumber("A3");
	seats[3]->setSeatNumber("B1");
	seats[4]->setSeatNumber("B2");
	seats[5]->setSeatNumber("B3");
	seats[6]->setSeatNumber("C1");
	seats[7]->setSeatNumber("C2");
	seats[8]->setSeatNumber("C3");
	seats[9]->setSeatNumber("D1");
	seats[10]->setSeatNumber("D2");
	seats[11]->setSeatNumber("D3");
	seats[12]->setSeatNumber("E1");
	seats[13]->setSeatNumber("E2");
	seats[14]->setSeatNumber("E3");
}

void AircraftB::setSeatOccupied(int idx)
{
	if (seats[idx]->getSeatOccupied())
		seats[idx]->setSeatOcupied(false);
	else
		seats[idx]->setSeatOcupied(true);
}

void AircraftB::setSeatName(int idx, string nam)
{
	seats[idx]->setSeatName(nam);
}

string AircraftB::getSeatNumber(int pos)
{
	return seats[pos]->getSeatNumber();
}

void AircraftB::displaySeatGrid()
{
	cout << "\t\t\t      ";
	for (int index = 0; index < 15; index++)
	{
		if (index % 3 == 1)
			cout << "  ";
		cout << "|" << seats[index]->getSeatNumber() << isSeatOccupied(index) << "| ";
		if (index % 3 == 2)
			cout << endl << "\t\t\t      ";
	}
	cout << endl;
}

void AircraftB::displaySeatList()
{
	for (int index = 0; index < 15; index++)
		cout << "\t\t\t" << seats[index]->getSeatNumber() << "\t\t" << seats[index]->getSeatName() << endl;
}

void AircraftB::displayPassengerList()
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

string AircraftB::isSeatOccupied(int idx)
{
	if (seats[idx]->getSeatOccupied())
		return "-X";
	else
		return "- ";
}

bool  AircraftB::determineFlightFull()
{
	int occupiedSeatCount = 0;
	for (int index = 0; index < 15; index++)
	{
		if (seats[index]->getSeatOccupied())
			occupiedSeatCount++;
	}

	if (occupiedSeatCount == 15)
		return true;
	else
		return false;
}

void AircraftB::resetPlane()
{
	for (int idx = 0; idx < 15; idx++)
	{
		if (seats[idx]->getSeatOccupied())
		{
			seats[idx]->setSeatOcupied(false);
			seats[idx]->setSeatName(" ");
		}
	}
}

int AircraftB::seatNumToInt(string stNum)
{
	if (stNum == "A1")
		return 0;
	if (stNum == "A2")
		return 1;
	if (stNum == "A3")
		return 2;
	if (stNum == "B1")
		return 3;
	if (stNum == "B2")
		return 4;
	if (stNum == "B3")
		return 5;
	if (stNum == "C1")
		return 6;
	if (stNum == "C2")
		return 7;
	if (stNum == "C3")
		return 8;
	if (stNum == "D1")
		return 9;
	if (stNum == "D2")
		return 10;
	if (stNum == "D3")
		return 11;
	if (stNum == "E1")
		return 12;
	if (stNum == "E2")
		return 13;
	if (stNum == "E3")
		return 14;
	return -1;
}