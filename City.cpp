//implementation file for the City class

#include "City.h"

//constructor
City::City()
{
	cityName = "";
	cityCode = "";
}

City::City(string name, string code)
{
	cityName = name;
	cityCode = code;
}


//setter
void City::setCityName(string name)
{
	cityName = name;
}

void City::setCityCode(string code)
{
	cityCode = code;
}


//getter
string City::getCityName()
{
	return cityName;
}

string City::getCityCode()
{
	return cityCode;
}