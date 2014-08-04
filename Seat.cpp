//implementation file for the Seat class

#include "Seat.h"

//constructor
Seat::Seat()
{
	seatOccupied = false;
	seatNumber = " ";
	seatName = " ";
}

Seat::Seat(string num)
{
	seatOccupied = false;
	seatNumber = num;
	seatName = " ";
}


//setter
void Seat::setSeatOcupied(bool occ)
{
	seatOccupied = occ;
}

void Seat::setSeatNumber(string num)
{
	seatNumber = num;
}

void Seat::setSeatName(string name)
{
	seatName = name;
}


//getter
bool Seat::getSeatOccupied()
{
	return seatOccupied;
}

string Seat::getSeatNumber()
{
	return seatNumber;
}

string Seat::getSeatName()
{
	return seatName;
}


string Seat::determineSeatNumber(int row, int col)
{
	if (row == 1)
	{
		if (col == 1)
		{
			return "1A";
		}
		else if (col == 2)
		{
			return "1B";
		}
		else if (col == 3)
		{
			return "1C";
		}
		else
		{
			return "1D";
		}
	}
	else if (row == 2)
	{
		if (col == 1)
		{
			return "2A";
		}
		else if (col == 2)
		{
			return "2B";
		}
		else if (col == 3)
		{
			return "2C";
		}
		else
		{
			return "2D";
		}
	}
	else if (row == 3)
	{
		if (col == 1)
		{
			return "3A";
		}
		else if (col == 2)
		{
			return "3B";
		}
		else if (col == 3)
		{
			return "3C";
		}
		else
		{
			return "3D";
		}
	}
	else if (row == 4)
	{
		if (col == 1)
		{
			return "4A";
		}
		else if (col == 2)
		{
			return "4B";
		}
		else if (col == 3)
		{
			return "4C";
		}
		else
		{
			return "4D";
		}
	}
	else
	{
		if (col == 1)
		{
			return "5A";
		}
		else if (col == 2)
		{
			return "5B";
		}
		else if (col == 3)
		{
			return "5C";
		}
		else
		{
			return "5D";
		}
	}
}