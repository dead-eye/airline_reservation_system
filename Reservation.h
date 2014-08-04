//specification file for the Reservation class

#ifndef RESERVARION_H
#define RESERVATION_H
#include <string>

using namespace std;

class Reservation
{
protected:
	int confirmationNumber;
	string passengerName;
	string date;
	string flightNumber;
	string seatAssignment;
	int freqFlyPointsEarned;

public:
	//constructor
	Reservation(int confirmNum, string passName, string dte, string flightNum, string seatAssign, int ffpEarned);

	//setters
	void setConfirmationNumber(int confirmNum) { confirmationNumber = confirmNum; }
	void setPassengerName(string passName) { passengerName = passName; }
	void setDate(string dte) { date = dte; }
	void setFlightNumber(string flightNum) { flightNumber = flightNum; }
	void setSeatAssignment (string seatAssign) { seatAssignment = seatAssign; }
	void setFreqFlyPointsEarned (int ffpEarned) { freqFlyPointsEarned = ffpEarned; }

	//getters
	int getConfirmationNumber() { return confirmationNumber; }
	string getPassengerName() { return passengerName; }
	string getDate() { return date; }
	string getFlightNumber() { return flightNumber; }
	string getSeatAssignment() { return seatAssignment; }
	int getFreqFlyPointsEarned() { return freqFlyPointsEarned; }

};
#endif