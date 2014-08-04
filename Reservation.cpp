//implementation file for the Reservation class

#include "Reservation.h"

//constructor
	Reservation::Reservation(int confirmNum, string passName, string dte, string flightNum, string seatAssign, int ffpEarned)
	{		
	confirmationNumber = confirmNum;
	passengerName = passName;
	date = dte;
	flightNumber = flightNum;
	seatAssignment = seatAssign;
	freqFlyPointsEarned = ffpEarned;
	}