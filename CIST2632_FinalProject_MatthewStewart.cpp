/*Name: Matthew Stewart
Class: CIST2362 - C++ II, Spring 2014
Date: April 20, 2014
Program: Final Project - Airline Reservation System
Description:
This program will simulate a Reservation system for an airline.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "City.h"
#include "CityList.h"
#include "Seat.h"
#include "AircraftFactory.h"
#include "AircraftA.h"
#include "AircraftB.h"
#include "Flight.h"
#include "Reservation.h"

using namespace std;

//initializing static variable
AircraftFactory* AircraftFactory::instance = 0;

//function prototypes
char showMainMenu();
void showAvailableCities(CityList);
void showFlightDetails(Flight* flt, list<Reservation>&);
void displayPassengers(Flight* flt);
void displaySeatGrid(Flight* flt);
string randomNameGenerator();
Flight numToFlt(int num);
Flight* retrieveFlight(vector<Flight*>&);
void createReservation(vector<Flight*>&, list<Reservation>&);
int typeASeatNumToInt(string num);
int typeBSeatNumToInt(string num);
void showFlightSchedule(vector<Flight*>&);
void showFlightsFrom(vector<Flight*>&, string, list<Reservation>&, string);
string createDate();
string CorrectSeatNumCase(string num);
void showAllReservations(list<Reservation>&);
void displayReservation(list<Reservation>&);
void cancelReservation(list<Reservation>&);
void showLogo();

int main()
{
	//declare local variables
	char mainChoice;			//menu choice for the main menu
	Flight*    flt;				//variable to look up flight information
	string    flightID;			//used for loading the flightSchedle vector
	string    depCity;			//used for loading the flightSchedle vector
	string    destCity;			//used for loading the flightSchedle vector
	string    depTime;			//used for loading the flightSchedle vector
	string    arivTime;			//used for loading the flightSchedle vector
	string    flightNum;		//used for loading the flightSchedle vector
	char      planeType;		//used for loading the flightSchedle vector
	int       ffPoints;			//used for loading the flightSchedle vectorint confNum;
	int	      confNum;			//used for loading the reservationList list
	string    pNam;				//used for loading the reservationList list
	string    dat;				//used for loading the reservationList list
	string    fltNum;			//used for loading the reservationList list
	string    seatAssgn;		//used for loading the reservationList list
	int       ffPointsEarned;	//used for loading the reservationList list

	//registering the types of aircraft
	AircraftFactory::getInstance()->registerAircraft(0, new AircraftA());
	AircraftFactory::getInstance()->registerAircraft(1, new AircraftB());

	//setting up classes
	CityList ctyLst;
	//	Schedule flightSched;

	//creating a vector of flights
	vector <Flight*> flightSchedule;

	//creating a list of reservations
	list <Reservation> reservationList;

	////////////////////////////////////////////////////////////////////
	//loading flights into flightSchedule vector from file
	//	opening file to read in schedule data
	fstream inputSchedFile;
	inputSchedFile.open("flightSchedule.txt", ios::in);

	//if schedule data file exists, process the file
	if (inputSchedFile)
	{
		//read in the data for a flight into the variables
		while (inputSchedFile >> flightID)
		{
			inputSchedFile >> depCity;
			inputSchedFile >> destCity;
			inputSchedFile >> depTime;
			inputSchedFile >> arivTime;
			inputSchedFile >> flightNum;
			inputSchedFile >> planeType;
			inputSchedFile >> ffPoints;

			//create a flight with the information from the file
			Flight* flightID = new Flight;

			//create plane pointers for the flight
			if (planeType == 'A')
			{
				AircraftA* plane = new AircraftA;
				flightID->setPlanePtr(plane);
			}
			else//(planeType == 'B')
			{
				AircraftB* plane = new AircraftB;
				flightID->setPlanePtr(plane);
			}

			flightID->setDepartCity(depCity);
			flightID->setDestinationCity(destCity);
			flightID->setDepartTime(depTime);
			flightID->setArrivalTime(arivTime);
			flightID->setFlightNumber(flightNum);
			flightID->setAircraftType(planeType);
			flightID->setFreqFlyPoints(ffPoints);
			flightID->setFlightFull(false);

			//push that flight onto the flights vector
			flightSchedule.push_back(flightID);

		}
		//closing the inputFile
		inputSchedFile.close();
	}
	else  //if schedule data file is missing, alert the user and end program
	{
		cout << "ERROR:  Cannot find flightSchedule.txt\n";
		cout << endl << endl;
		system("pause");
		exit (EXIT_FAILURE);
	}
	// Schedule has either been loaded or the program has exited with a
	//	failure to find the flightSchedule.txt file
	////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////
	//checking for reservationList file and creating if needed
	//	loading reservations into reservationList list from file
	//	opening file to read in reservation data

	fstream inputResFile;
	inputResFile.open("reservationList.txt", ios::in);
	if (inputResFile.fail())				//file does not exist, so create it and alert user
	{
		cout << "The system could not find the reservationList.txt file.\n";
		cout << "Empty reservationList.txt has been created.\n\n";
		inputResFile.open("reservationList.txt", ios::out);

		system("pause");
		system("cls");

		inputResFile.close();				//close the file for now
	}

	//if the file exists, read the reservations into the reservationList list
	else
	{
		//read first reservation into reservation list
		inputResFile >> confNum;
		inputResFile.ignore();
		getline(inputResFile, pNam);
		inputResFile >> dat;
		inputResFile >> seatAssgn;
		inputResFile >> fltNum;
		inputResFile >> ffPointsEarned;

		//create reservation
		Reservation res(confNum, pNam, dat, fltNum, seatAssgn, ffPointsEarned);

		//push the reservation on the reservationList list
		reservationList.push_back(res);

		//while more reservations exist in the inputFile file,
		//continue reading reservations into the reservationList list
		while (inputResFile >> confNum)
		{
			inputResFile.ignore();
			getline(inputResFile, pNam);
			inputResFile >> dat;
			inputResFile >> seatAssgn;
			inputResFile >> fltNum;
			inputResFile >> ffPointsEarned;

			//create reservation
			Reservation res(confNum, pNam, dat, fltNum, seatAssgn, ffPointsEarned);

			//push the reservation on the reservationList list
			reservationList.push_back(res);
		}
		
		inputResFile.close();				//close the file for now
	}
	// Reservation list has either been loaded or the program has created a
	//	brand new (empty) reservationList.txt file and alerted the user
	////////////////////////////////////////////////////////////////////
	
	//seed the random function for the confirmation generator
	srand(time(0));

	//starting the main loop of the program
	showLogo();
	cout << endl;
	mainChoice = showMainMenu();

	while (mainChoice != 'X' && mainChoice != 'x')
	{
		switch (mainChoice)
		{
			//book new reservation
		case 'A':
		case 'a':
			createReservation(flightSchedule, reservationList);
			system("cls");
			showLogo();
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//cancel reservation
		case 'B':
		case 'b':
			cancelReservation(reservationList);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//display reservation
		case 'C':
		case 'c':
			displayReservation(reservationList);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//display flight schedule
		case 'D':
		case 'd':
			showFlightSchedule(flightSchedule);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//display available cities
		case 'E':
		case 'e':
			showAvailableCities(ctyLst);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//show flight details
		case 'F':
		case 'f':
			//display header
			system("cls");
			cout << "\n\n\n\t\t\t      SHOW FLIGHT DETAILS\n\n";
			flt = retrieveFlight(flightSchedule);
			showFlightDetails(flt, reservationList);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//show all reservations
		case 'G':
		case 'g':
			showAllReservations(reservationList);
			system("cls");
			showLogo();	
			cout << endl;
			mainChoice = showMainMenu();
			break;

			//this is a hidden choice that is used for testing purposes
//		case 'h':
//
//			system("cls");
//			showLogo();	
//			cout << endl;
//			mainChoice = showMainMenu();
//			break;

			//error trapping invalid menu choices
		default :
			system("cls");
			showLogo();	
			cout << "\n\t\t       You have entered an invalid choice.";
			mainChoice = showMainMenu();
		}
	}

	//deleting the flight schedule
	while (!(flightSchedule.empty()))
	{
		delete flightSchedule.back();
		flightSchedule.pop_back();
	}

	//saving the reservationList to file for later use
	fstream outputResFile;
	outputResFile.open("reservationList.txt", ios::out);
	
	//create an iterator for traversing the flights vector
	list <Reservation> :: iterator itr;

	//read in all data from the reservationList into the file
	for (itr = reservationList.begin(); itr != reservationList.end(); itr++)
	{
		outputResFile << itr->getConfirmationNumber() << " ";
		outputResFile << itr->getPassengerName() << endl;
		outputResFile << itr->getDate() << endl;
		outputResFile << itr->getSeatAssignment() << endl;
		outputResFile << itr->getFlightNumber() << endl;
		outputResFile << itr->getFreqFlyPointsEarned() << endl;
	}
	outputResFile.close();				//close the file for now


	cout << endl << endl;
	return 0;
}


//function char showMainMenu()
// This function displays the main Menu and returns the mainChoice variable
char showMainMenu()
{
	//declare local varaible
	char choice;					//main menu choice

	//display the login menu
	cout << "\n\n\t\t\t      MAIN RESERVATION MENU\n\n";
	cout << "\t\t\t  A -- Book New Reservation\n";
	cout << "\t\t\t  B -- Cancel Reservation\n";
	cout << "\t\t\t  C -- Display Reservation\n";
	cout << "\t\t\t  D -- Display Flight Schedule\n";
	cout << "\t\t\t  E -- Display Available Cities\n";
	cout << "\t\t\t  F -- Show Flight Details\n";
	cout << "\t\t\t  G -- Show All Reservations\n";
	cout << "\t\t\t  X -- Exit System\n\n";
	cout << "   -----------------------------------------------------------------------\n\n";
	cout << "\t\t\t  Enter A, B, C, D, E, F, G or X: ";

	//get choice from user
	cin >> choice;

	//return user's choice to main
	return choice;
}


//this function displays the list of available cities serviced by the airline
void showAvailableCities(CityList ctyLst)
{
	//declare local variables
	char choice = ' ';				//local menu choice
	bool sortByCode = false;		//determines which field to sort by

	//begin local loop
	while (toupper(choice) != 'X')
	{
		//display header
		system("cls");
		cout << "\n\n\t\t\t        AVAILABLE CITIES\n\n";

		//get sorted list of cities
		if (sortByCode == false)
			ctyLst.getCitiesByName();
		else
			ctyLst.getCitiesByCode();

		//display footer
		cout << "\n   -----------------------------------------------------------------------\n\n";
		cout << "\t\t\t    C -- Change Sorting\n";
		cout << "\t\t\t    X -- Exit to Main Menu\n\n";
		cout << "\t\t\t  Enter C or X: ";

		//get choice from user
		cin >> choice;

		//error-trapping loop
		while ((toupper(choice) != 'C') && (toupper(choice) != 'X'))
		{
			cout << "Please choose \"C\" or \"X\": ";
			cin >> choice;
		}

		//changing the sort flag
		if (sortByCode == false)
			sortByCode = true;
		else
			sortByCode = false;
	}
}


//this function displays the list of passengers on a plane
void displayPassengers(Flight* flt)
{
	//declare local variables
	char choice = ' ';				//local menu choice
	bool sortByPass = false;		//determines which field to sort by

	//begin local loop
	while (toupper(choice) != 'X')
	{
		//display header
		system("cls");
		cout << "\n\t\t\t   PASSENGERS ON FLIGHT #" << flt->getFlightNumber() << "\n\n";

		//get sorted list of seats on a flight
		if (sortByPass == false)
			flt->getPlanePtr()->displaySeatList();
		else
			flt->getPlanePtr()->displayPassengerList();

		//display footer
		cout << "\n   -----------------------------------------------------------------------\n\n";
		cout << "\t\t\t    C -- Change Sorting\n";
		cout << "\t\t\t    X -- Exit to Previous Menu\n";
		cout << "\t\t\t  Enter C or X: ";

		//get choice from user
		cin >> choice;

		//error-trapping loop
		while ((toupper(choice) != 'C') && (toupper(choice) != 'X'))
		{
			cout << "Please choose \"C\" or \"X\": ";
			cin >> choice;
		}

		//changing the sort flag
		if (sortByPass == false)
			sortByPass = true;
		else
			sortByPass = false;
	}
}


//this function displays the seating grid of a plane
void displaySeatGrid(Flight* flt)
{
	//display header
	system("cls");
	cout << "\n\t\t\t  SEATING CHART FOR FLIGHT #" << flt->getFlightNumber() << "\n\n";

	//get sorted list of seats on Plane
	flt->getPlanePtr()->displaySeatGrid();
}


//this function displays the details of a single flight including the seating grid
//	and the passenger manifest and the other details of the flight, too
void showFlightDetails(Flight* flt, list<Reservation>& resList)
{
	//declare local variables
	char choice = ' ';				//local menu choice
	bool sortByPass = false;		//determines which field to sort by
	string date;

	//error trapping invalid flights
	if (flt->getFlightNumber() == " ")
	{
		cout << "\n\t\t\t  That is not a valid flight number.\n\n\n";
		delete flt;

		system("pause");
	}
	else
	{
		//get the date from the user
		cout << "\n   Please enter a date to search for:\n";
		date = createDate();
	
		//create an iterator for traversing the flights vector
		list <Reservation> :: iterator itr;

		//read in all data from the reservationList into the file
		for (itr = resList.begin(); itr != resList.end(); itr++)
		{
			if ((date == itr->getDate()) && (flt->getFlightNumber() == itr->getFlightNumber()))
			{
				flt->getPlanePtr()->setSeatName(flt->getPlanePtr()->seatNumToInt(itr->getSeatAssignment()),
					itr->getPassengerName());
				flt->getPlanePtr()->setSeatOccupied(flt->getPlanePtr()->seatNumToInt(itr->getSeatAssignment()));
			}
		}

		//set the flight full flag
		if (flt->getPlanePtr()->determineFlightFull())
			flt->setFlightFull(true);
		else
			flt->setFlightFull(false);

		//begin local loop
		while (toupper(choice) != 'X')
		{
			displaySeatGrid(flt);
			cout << left << endl;
			cout << "     " << setw(7) << "From" << setw(6) << "To" << setw(8) << "Depart" << setw(8) << "Arrive" <<
				setw(8) << "Flight" << setw(12) << "Aircraft" << setw(12) << "Frequent" << setw(6) << "Flight\n";
			cout << "\t\t\t\t  " << setw(10) << "Number" << setw(8) << "Type" << setw(14) << "Flyer Points" << setw(6) << "Status\n";
			cout << "   -----------------------------------------------------------------------\n";
			cout << "     " << setw(7) << flt->getDepartCity() << setw(6) << flt->getDestinationCity() << setw(8) <<
				flt->getDepartTime() << setw(9) << flt->getArrivalTime() << setw(10) << flt->getFlightNumber() << setw(11) <<
				flt->getAircraftType() << setw(11) << flt->getFreqFlyPoints();
			if (flt->getFlightFull())
				cout << setw(6) << "FULL\n\n";
			else
				cout << endl << endl;
			//display footer
			cout << "   -----------------------------------------------------------------------\n\n";
			cout << "\t\t\t  P -- Display Passenger Manifest\n";
			cout << "\t\t\t  X -- Exit to Main Menu\n";
			cout << "\t\t\t  Enter P or X: ";

			//get choice from user
			cin >> choice;

			//error-trapping loop
			while ((toupper(choice) != 'P') && (toupper(choice) != 'X'))
			{
				cout << "Please choose \"P\" or \"X\": ";
				cin >> choice;
			}

			if (toupper(choice) == 'P')
				displayPassengers(flt);
		}
	}
	
	//cleaning out the old data from the flight schedule
	flt->getPlanePtr()->resetPlane();
}



//this function gets a flight number from the user and retrieves
//	the proper flight from the flight schedule
Flight* retrieveFlight(vector<Flight*>& flights)
{
	//declare local variables
	string num;

	//get flight number from the user
	cout << "\n   Please enter a flight number: ";
	cin >> num;

	for (int idx = 0; idx < flights.size(); idx++)
	{
		if (flights[idx]->getFlightNumber() == num)
			return flights[idx];
	}

	Flight* emptyFlight = new Flight();
	return emptyFlight;

}


//this function will ask the user for the needed information to
//	create a new Reservation then create the reservation and store
//	it in a linked list
void createReservation(vector<Flight*>& flights, list<Reservation>& resList)
{
	//declare local variables
	int confirmNum;
	bool validCity;
	bool validFlight = false;
	bool flightFull;
	string date;
	string passName;
	string depCity;
	string fltNum;
	Flight* fltPtr = new Flight;
	Aircraft* planeA = new AircraftA;
	Aircraft* planeB = new AircraftB;
	string seat;
	int seatAccessor;
	char choice = ' ';
	char typ;

	//refresh the screen for entering data for the reervation
	system("cls");
	cout << "\n\n\t\t\t      BOOK NEW RESERVATION\n\n";

	//get the flight and passenger name for the boarding pass and the flight number
	cout << "   Enter the Passenger's name: ";
	cin.ignore();
	getline(cin,passName);
	cout << endl;

	//get the date of the flight
	cout << "   Please enter the date of the flight.\n\n";
	date = createDate();

	//get information for the flight
	cout << "   Enter the departure city: ";
	cin >> depCity;

	//error trapping bad values and correcting case
	if (depCity == "atl")
		depCity = "ATL";
	if (depCity == "nyc")
		depCity = "NYC";
	if (depCity == "orl")
		depCity = "ORL";
	if (depCity == "dfw")
		depCity = "DFW";
	if (depCity == "haw")
		depCity = "HAW";
	if (depCity == "chi")
		depCity = "CHI";
	if (depCity == "lax")
		depCity = "LAX";

	if ((depCity != "ATL") && (depCity != "ORL") && (depCity != "DFW") &&
		(depCity != "HAW") && (depCity != "CHI") && (depCity != "NYC"))
	{
		cout << "\n\t\t\t  We do not offer a flight from " << depCity << ",\n\n\n";
		validCity = false;
		system("pause");
	}
	else
	{
		//look up and retrun all flights with the departure city
		showFlightsFrom(flights, depCity, resList, date);
		validCity = true;
	}

	
	//if the city was validated, proceed
	if (validCity)
	{
		cout << "   Enter the Flight#: ";
		cin >> fltNum;

		//checking for a full flight and not allowing it
		do
		{
			for (int idx = 0; idx < flights.size(); idx++)
			{
				if (flights[idx] ->getFlightNumber() == fltNum)
				{
					if (flights[idx]->getFlightFull())
					{
						flightFull = true;
						cout << "   This flight is full.  Please enter another flight.\n";
					}
					else
					{
						flightFull = false;
						validFlight = true;
						//get flight information from the flight schedule and store it on the flight pointer
						fltPtr->setDepartCity(flights[idx]->getDepartCity());
						fltPtr->setDestinationCity(flights[idx]->getDestinationCity());
						fltPtr->setDepartTime(flights[idx]->getDepartTime());
						fltPtr->setArrivalTime(flights[idx]->getArrivalTime());
						fltPtr->setFlightNumber(flights[idx]->getFlightNumber());
						fltPtr->setAircraftType(flights[idx]->getAircraftType());
						fltPtr->setFreqFlyPoints(flights[idx]->getFreqFlyPoints());
						fltPtr->setFlightFull(false);
						if (fltPtr->getAircraftType() == 'A')
						{
							fltPtr->setPlanePtr(planeA);
							typ = 'A';
						}
						else
						{
							fltPtr->setPlanePtr(planeB);
							typ = 'B';
						}
					}
				}
			}
			//validate the flight number
			while (!(validFlight))
			{
				cout << "   Invalid flight number entered.\n";
				cout << "   Enter the Flight#: ";
				cin >> fltNum;
				for (int idx = 0; idx < flights.size(); idx++)
				{
					if (flights[idx] ->getFlightNumber() == fltNum)
					{
						if (flights[idx]->getFlightFull())
						{
							flightFull = true;
							cout << "   This flight is full.  Please enter another flight.\n";
						}
						else
						{
							flightFull = false;
							validFlight = true;				
							//get flight information from the flight schedule and store it on the flight pointer
							fltPtr->setDepartCity(flights[idx]->getDepartCity());
							fltPtr->setDestinationCity(flights[idx]->getDestinationCity());
							fltPtr->setDepartTime(flights[idx]->getDepartTime());
							fltPtr->setArrivalTime(flights[idx]->getArrivalTime());
							fltPtr->setFlightNumber(flights[idx]->getFlightNumber());
							fltPtr->setAircraftType(flights[idx]->getAircraftType());
							fltPtr->setFreqFlyPoints(flights[idx]->getFreqFlyPoints());
							fltPtr->setFlightFull(flights[idx]->getFlightFull());
							fltPtr->setPlanePtr(flights[idx]->getPlanePtr());
						}
					}
				}
			}
		} while (flightFull);

		//cleaning out the old data from the flight schedule
		for (int idx = 0; idx < flights.size(); idx++)
		{
			flights[idx]->getPlanePtr()->resetPlane();
		}
		

		//now working with the fltPtr flight pointer
		//search through the reservation list.  If reservations are found that match the date and flight numbers,
		//	update the seatNames and seat occupied elements of the fltPtr.  If the flight is full, indicate that and suggest
		//	another flight that matches departure city and destination city (will need to reset all seat names and seat 
		//	occupied variables to " " and false before saving the reservation to preserve integrity for the next time
		//	this information is accessed)
	
		//create an iterator for traversing the flights vector
		list <Reservation> :: iterator itr;

		//read in all data from the reservationList into the file
		for (itr = resList.begin(); itr != resList.end(); itr++)
		{
			if ((date == itr->getDate()) && (fltNum == itr->getFlightNumber()))
			{
				fltPtr->getPlanePtr()->setSeatName(fltPtr->getPlanePtr()->seatNumToInt(itr->getSeatAssignment()),
					itr->getPassengerName());
				fltPtr->getPlanePtr()->setSeatOccupied(fltPtr->getPlanePtr()->seatNumToInt(itr->getSeatAssignment()));
			}
		}

		//set the flight full flag
		if (fltPtr->getPlanePtr()->determineFlightFull())
			fltPtr->setFlightFull(true);
		else
			fltPtr->setFlightFull(false);

		displaySeatGrid(fltPtr);
		cout << left << endl;
		cout << "     " << setw(7) << "From" << setw(6) << "To" << setw(8) << "Depart" << setw(8) << "Arrive" <<
			setw(8) << "Flight" << setw(12) << "Aircraft" << setw(12) << "Frequent" << setw(6) << "Flight\n";
		cout << "\t\t\t\t  " << setw(10) << "Number" << setw(8) << "Type" << setw(14) << "Flyer Points" << setw(6) << "Status\n";
		cout << "   -----------------------------------------------------------------------\n";
		cout << "     " << setw(7) << fltPtr->getDepartCity() << setw(6) << fltPtr->getDestinationCity() << setw(8) <<
			fltPtr->getDepartTime() << setw(9) << fltPtr->getArrivalTime() << setw(10) << fltPtr->getFlightNumber() << setw(11) <<
			fltPtr->getAircraftType() << setw(11) << fltPtr->getFreqFlyPoints();
		if (fltPtr->getFlightFull())
			cout << setw(6) << "FULL\n\n";
		else
			cout << endl << endl;
		cout << "   -----------------------------------------------------------------------\n\n";

		do
		{
			cout << "   Enter the seat assignment: ";
			cin >> seat;
			seat = CorrectSeatNumCase(seat);
			seatAccessor = fltPtr->getPlanePtr()->seatNumToInt(seat);
			if (seatAccessor == -1)
				cout << "   Invalid seat assignment.\n";
			else
				if (fltPtr->getPlanePtr()->isSeatOccupied(seatAccessor) == "-X")
					cout << "   That seat is occupied.\n";
		} while ((seatAccessor == -1) || (fltPtr->getPlanePtr()->isSeatOccupied(seatAccessor) == "-X"));

		//assign passenger's name to the seat and set seat to occupied////				
		fltPtr->getPlanePtr()->setSeatName(seatAccessor, passName);
		fltPtr->getPlanePtr()->setSeatOccupied(seatAccessor);

		//display updated seating and flight information
		system("cls");
		displaySeatGrid(fltPtr);
		cout << left << endl;
		cout << "     " << setw(7) << "From" << setw(6) << "To" << setw(8) << "Depart" << setw(8) << "Arrive" <<
			setw(8) << "Flight" << setw(12) << "Aircraft" << setw(12) << "Frequent" << setw(6) << "Flight\n";
		cout << "\t\t\t\t  " << setw(10) << "Number" << setw(8) << "Type" << setw(14) << "Flyer Points" << setw(6) << "Status\n";
		cout << "   -----------------------------------------------------------------------\n";
		cout << "     " << setw(7) << fltPtr->getDepartCity() << setw(6) << fltPtr->getDestinationCity() << setw(8) <<
			fltPtr->getDepartTime() << setw(9) << fltPtr->getArrivalTime() << setw(10) << fltPtr->getFlightNumber() << setw(11) <<
			fltPtr->getAircraftType() << setw(11) << fltPtr->getFreqFlyPoints();
		if (fltPtr->getFlightFull())
			cout << setw(6) << "FULL\n\n";
		else
		{
			cout << endl << endl;
		}
		cout << "   -----------------------------------------------------------------------\n\n";
		cout << "\t\t\t  P -- Display Passenger Manifest\n";
		cout << "\t\t\t  X -- Exit to Main Menu\n";
		cout << "\t\t\t  Enter P or X: ";
				

		//get choice from user
		cin >> choice;

		//error-trapping loop
		while ((toupper(choice) != 'P') && (toupper(choice) != 'X'))
		{
			cout << "   Please choose \"P\" or \"X\": ";
			cin >> choice;
		}

		if (toupper(choice) == 'P')
			displayPassengers(fltPtr);

		//generate the random confirmation number and store all reservation information
		//	in the reservation list for later retreival
		confirmNum = ((rand() % 99999) + 10000);

		//display reservation information
		system("cls");
		cout << "\n\n\t\t\t      BOOK NEW RESERVATION\n\n";
		cout << "   Confirmation #: " << confirmNum << "\t\t\t\tDate : " << date << endl;
		cout << "   Passenger Name: " << passName << endl << endl;
		cout << "   Flight #:       " << fltNum << "\t\t\t\t\tSeat Assignment: " << seat << endl << endl;
		cout << "   Departing:      " << fltPtr->getDepartCity() << " at " << fltPtr->getDepartTime() << endl;
		cout << "   Arriving:       " << fltPtr->getDestinationCity() << " at " << fltPtr->getArrivalTime() << endl << endl;
		cout << "   Frequent Flyer Points earned for this flight: " << fltPtr->getFreqFlyPoints() << endl << endl;
		
		system("pause");

		//create new reservation and
		//save reservation to the reservation list
		Reservation res(confirmNum, passName, date, fltNum, seat, fltPtr->getFreqFlyPoints());
		resList.push_back(res);
		
	}

	// delete the pointers
	delete fltPtr;
	delete planeA;
	delete planeB;

	//system("pause");
}


//this function takes a seat number and corrects the case of the letter
string CorrectSeatNumCase(string num)
{
	if (num == "a1")
		return "A1";
	if (num == "a2")
		return "A2";
	if (num == "a3")
		return "A3";
	if (num == "a4")
		return "A4";
	if (num == "b1")
		return "B1";
	if (num == "b2")
		return "B2";
	if (num == "b3")
		return "B3";
	if (num == "b4")
		return "B4";
	if (num == "c1")
		return "C1";
	if (num == "c2")
		return "C2";
	if (num == "c3")
		return "C3";
	if (num == "c4")
		return "C4";
	if (num == "d1")
		return "D1";
	if (num == "d2")
		return "D2";
	if (num == "d3")
		return "D3";
	if (num == "d4")
		return "D4";
	if (num == "e1")
		return "E1";
	if (num == "e2")
		return "E2";
	if (num == "e3")
		return "E3";
	if (num == "e4")
		return "E4";
	return num;
}


//this function displays the flight schedule and sorts it by any field
void showFlightSchedule(vector<Flight*>& flights)
{
	//declare local variables
	char choice = ' ';
	int sortCriteria = 1;

	while (toupper(choice) != 'X')
	{
		//choosing which field to sort the schedule by
		switch (sortCriteria)
		{
		case 1:
			sort (flights.begin(), flights.end(), Flight::SortByDepartCity);
			break;
		case 2:
			sort (flights.begin(), flights.end(), Flight::SortByDestinationCity);
			break;
		case 3:
			sort (flights.begin(), flights.end(), Flight::SortByDepartTime);
			break;
		case 4:
			sort (flights.begin(), flights.end(), Flight::SortByArrivalTime);
			break;
		case 5:
			sort (flights.begin(), flights.end(), Flight::SortByFlightNumber);
			break;
		case 6:
			sort (flights.begin(), flights.end(), Flight::SortByAircraftType);
			break;
		case 7:
			sort (flights.begin(), flights.end(), Flight::SortByFreqFlyPoints);
			break;
		}

		//display header
		system("cls");
		cout << left << endl;
		cout << "      " << setw(8) << "From" << setw(7) << "To" << setw(9) << "Depart" << setw(9) << "Arrive" <<
			setw(9) << "Flight" << setw(13) << "Aircraft" << setw(13) << "Frequent\n";
		cout << "\t\t\t\t       " << setw(11) << "Number" << setw(9) << "Type" << setw(15) << "Flyer Points\n";

		//slightly altering the header to indicate how the list is sorted
		switch (sortCriteria)
		{
		case 1:
			cout << " ---\\_/-----------------------------------------------------------------\n\n";
			break;
		case 2:
			cout << " -----------\\_/---------------------------------------------------------\n\n";
			break;
		case 3:
			cout << " -------------------\\_/-------------------------------------------------\n\n";
			break;
		case 4:
			cout << " ----------------------------\\_/----------------------------------------\n\n";
			break;
		case 5:
			cout << " -------------------------------------\\_/-------------------------------\n\n";
			break;
		case 6:
			cout << " -----------------------------------------------\\_/---------------------\n\n";
			break;
		case 7:
			cout << " ------------------------------------------------------------\\_/--------\n\n";
			break;
		}

		//step through the flights vector displaying the information
		for (int idx = 0; idx < flights.size(); idx++)
		{
			cout << "      " << setw(8) << flights[idx]->getDepartCity() << setw(7) << flights[idx]->getDestinationCity() << setw(9) <<
				flights[idx]->getDepartTime() << setw(10) << flights[idx]->getArrivalTime() << setw(11) << flights[idx]->getFlightNumber() << setw(12) <<
				flights[idx]->getAircraftType() << setw(11) << flights[idx]->getFreqFlyPoints() << endl << endl;
		}

		//display footer
		cout << "   -----------------------------------------------------------------------\n\n";
		cout << "\t\t\t  C -- Change Sorting\n";
		cout << "\t\t\t  X -- Exit to Main Menu\n";
		cout << "\t\t\t  Enter C or X: ";

		//get choice from user
		cin >> choice;

		//error-trapping loop
		while ((toupper(choice) != 'C') && (toupper(choice) != 'X'))
		{
			cout << "Please choose \"C\" or \"X\": ";
			cin >> choice;
		}

		//changing the sort flag
		if (sortCriteria == 7)
			sortCriteria = 1;
		else
			sortCriteria++;		
	}
}


//this function displays the flights originating from a specified departure city
void showFlightsFrom(vector<Flight*>& flights, string depCty, list<Reservation>& resList, string date)
{
	//declare local variables
	int seatAccessor;

//	//create an iterator for traversing the reservation list
	list <Reservation> :: iterator itr;

	//display header
	system("cls");
	cout << left << endl;
	cout << "     " << setw(7) << "From" << setw(6) << "To" << setw(8) << "Depart" << setw(8) << "Arrive" <<
		setw(8) << "Flight" << setw(12) << "Aircraft" << setw(12) << "Frequent" << setw(6) << "Flight\n";
	cout << "\t\t\t\t  " << setw(10) << "Number" << setw(8) << "Type" << setw(14) << "Flyer Points" << setw(6) << "Status\n";
	cout << "   -----------------------------------------------------------------------\n\n";

	//step through the flights vector displaying the information requested
	for (int idx = 0; idx < flights.size(); idx++)
	{
		if (flights[idx]->getDepartCity() == depCty)
		{
			//read in all data from the reservationList into the file
			for (itr = resList.begin(); itr != resList.end(); itr++)
			{
				if ((date == itr->getDate()) && (flights[idx]->getFlightNumber() == itr->getFlightNumber()))
				{
					flights[idx]->getPlanePtr()->setSeatOccupied(flights[idx]->getPlanePtr()->seatNumToInt(itr->getSeatAssignment()));
				}
			}

			//set the flight full flag
			if (flights[idx]->getPlanePtr()->determineFlightFull())
				flights[idx]->setFlightFull(true);
			else
				flights[idx]->setFlightFull(false);

			cout << "     " << setw(7) << flights[idx]->getDepartCity() << setw(6) << flights[idx]->getDestinationCity() << setw(8) <<
				flights[idx]->getDepartTime() << setw(9) << flights[idx]->getArrivalTime() << setw(10) << flights[idx]->getFlightNumber() << setw(11) <<
				flights[idx]->getAircraftType() << setw(11) << flights[idx]->getFreqFlyPoints();
			if (flights[idx]->getFlightFull())
				cout << setw(5) << "FULL\n";
			else
				cout << endl;
		}
	}

	//display footer
	cout << "\n   -----------------------------------------------------------------------\n\n";

}


//this function will validate a date and return a string representation of the date
//	this will be used to create a date for the reservations
string createDate()
{
	//declare local variables
	int month;
	int day;
	int year;
	string date;
	int daysPerMonth [] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool dayValid = false;

	//get input from user for the month and validate
	cout << "   Enter the year (YYYY): ";
	cin >> year;
	while (year < 2014)
	{
		cout << "   Invalid year entered.\n   Please enter year (YYYY): ";
		cin >> year;
	}
	cout << endl;

	//get input from user for the month and validate
	cout << "   Enter the month (MM): ";
	cin >> month;
	while (month < 0 || month > 12)
	{
		cout << "   Invalid month entered.\n   Please enter month (MM): ";
		cin >> month;
	}
	cout << endl;
	
	//get input from user for the day and validate
	while (!(dayValid))
	{
		cout << "   Enter the day (DD): ";
		cin >> day;
	        
		//check if day in range for month
		if (day > 0 && day <= daysPerMonth[month])
			dayValid = true;
        
		//check for leap year
		else if (month == 2 && day == 29 && (year % 400 == 0 ||
				(year % 4 == 0 && year % 100 != 0)))
			dayValid = true;
		else
			cout << "   Invalid day entered.\n";
	}
	cout << endl;

	date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

	return date;
}


//this function shows a listing of all the reservations
void showAllReservations(list<Reservation>& resList)
{
	//create an iterator for traversing the flights vector
	list <Reservation> :: iterator itr;

	system("cls");
	cout << "\n\n\n\t\t\t      SHOW ALL RESERVATIONS\n\n";
	for (itr = resList.begin(); itr != resList.end(); itr++)
	{
		cout << "   Confirm #: " << itr->getConfirmationNumber() << "\tDate: " << itr->getDate()
			<< "\t     Flight#: " << itr->getFlightNumber() << "\tSeat#: " << itr->getSeatAssignment() << endl;
		cout << "   Passenger Name: " << itr->getPassengerName() << endl;
		cout << "   Frequent Flyer Points Earned for this trip: " << itr->getFreqFlyPointsEarned() << endl << endl;
	}

	cout << endl << endl;
	system("pause");
}


//this function shows a single reservation
void displayReservation(list<Reservation>& resList)
{
	//declare local variable
	bool reservatonFound = false;
	int confirmNum;

	//get the confirmation number to search for
	system("cls");
	cout << "\n\n\n\t\t\t       DISPLAY RESERVATION\n\n";
	cout << "   Enter the confirmation #: ";
	cin >> confirmNum;

	//create an iterator for traversing the flights vector
	list <Reservation> :: iterator itr;

	system("cls");
	cout << "\n\n\n\t\t\t       DISPLAY RESERVATION\n\n";

	//traverse the list looking for the specified confirmation number. if found, display the information
	for (itr = resList.begin(); itr != resList.end(); itr++)
	{
		if (itr->getConfirmationNumber() == confirmNum)
		{
			cout << "   Confirm #: " << itr->getConfirmationNumber() << "\tDate: " << itr->getDate()
				<< "\t     Flight#: " << itr->getFlightNumber() << "\tSeat#: " << itr->getSeatAssignment() << endl;
			cout << "   Passenger Name: " << itr->getPassengerName() << endl;
			cout << "   Frequent Flyer Points Earned for this trip: " << itr->getFreqFlyPointsEarned() << endl << endl;

			//set found flag to true
			reservatonFound = true;
		}
	}

	//if confirmation number is not found, display a message
	if (!reservatonFound)
		cout << "   That reservation number could not be found.\n\n   ";

	system("pause");
}


//this function shows a single reservation
void cancelReservation(list<Reservation>& resList)
{
	//declare local variable
	bool reservatonFound = false;
	int confirmNum;
	string cancel;

	//get the confirmation number to search for
	system("cls");
	cout << "\n\n\n\t\t\t        CANCEL RESERVATION\n\n";
	cout << "   Enter the confirmation #: ";
	cin >> confirmNum;

	//create an iterator for traversing the flights vector
	list <Reservation> :: iterator itr;

	system("cls");
	cout << "\n\n\n\t\t\t        CANCEL RESERVATION\n\n";

	//traverse the list looking for the specified confirmation number. if found, display the information
	for (itr = resList.begin(); itr != resList.end(); itr++)
	{
		if (itr->getConfirmationNumber() == confirmNum)
		{
			cout << "   Confirm #: " << itr->getConfirmationNumber() << "\tDate: " << itr->getDate()
				<< "\t     Flight#: " << itr->getFlightNumber() << "\tSeat#: " << itr->getSeatAssignment() << endl;
			cout << "   Passenger Name: " << itr->getPassengerName() << endl;
			cout << "   Frequent Flyer Points Earned for this trip: " << itr->getFreqFlyPointsEarned() << endl << endl;

			//set found flag to true
			reservatonFound = true;

			//ask to confirm cancellation
			cout << "   To confirm cancellation, type \"YES\"\n   or anything else to abort cancellation. ";
			cin >> cancel;

			if (cancel == "YES")
			{
				//delete this item from the reservation list
				itr = resList.erase (itr);
				cout << "\n   Reservation # " << confirmNum << " has been cancelled.\n\n   ";
				itr = resList.begin();
			}
			else
			{
				cout << "\n   Reservation # " << confirmNum << " has NOT been cancelled.\n\n   ";
			}
		}
	}

	//if confirmation number is not found, display a message
	if (!reservatonFound)
		cout << "   That reservation number could not be found.\n\n   ";

	system("pause");
}


//This function will show the airline's logo for the main menu.
void showLogo()
{
	cout << "\t\t         ________________________   _    \n";
	cout << "\t\t        / ___/  _/ __/_  __/ / _ | (_)___\n";
	cout << "\t\t       / /___/ /_\\ \\  / / / / __ |/ / __/\n";
	cout << "\t\t       \\___/___/___/ /_/ / /_/ |_/_/_/   \n";
	cout << "\t\t                        /_/              \n";
}