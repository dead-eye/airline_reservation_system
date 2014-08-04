//specification file for the Seat class

#ifndef SEAT_H
#define SEAT_H
#include <string>

using namespace std;

class Seat
{
protected:
	bool seatOccupied;
	string seatNumber;
	string seatName;

public:
	//constructor
	Seat();
	Seat(string num);
	
	//setter
	void setSeatOcupied(bool occ);
	void setSeatNumber(string num);
	void setSeatName(string name);

	//getter
	bool getSeatOccupied();
	string getSeatNumber();
	string getSeatName();

	string determineSeatNumber(int row, int col);

	static bool SortBySeatName(const Seat* s1, const Seat* s2)
	{
		return s1->seatName < s2->seatName;
	}

	static bool SortBySeatNumber(const Seat* s1, const Seat* s2)
	{
		return s1->seatNumber < s2->seatNumber;
	}
};
#endif