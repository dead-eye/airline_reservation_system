//implementation file for the CityList class

#include "CityList.h"

//constructor
CityList::CityList()
{
	cities.push_back(City("Atlanta          ", "ATL"));
	cities.push_back(City("Orlando          ", "ORL"));
	cities.push_back(City("Dallas/Fort Worth", "DFW"));
	cities.push_back(City("New York City    ", "NYC"));
	cities.push_back(City("Hawaii           ", "HAW"));
	cities.push_back(City("Chicago          ", "CHI"));
	cities.push_back(City("Los Angeles      ", "LAX"));
}


//setter
void CityList::addCity(string name, string code)
{
	cities.push_back(City(name, code));
}


//getter
void CityList::getCitiesByName()
{
	sort (cities.begin(), cities.end(), City::SortByCityName);
	for (City &c : cities)
		cout << "\t\t\t    " << c.getCityName() << "\t" << c.getCityCode() << endl;
}

void CityList::getCitiesByCode()
{
	sort (cities.begin(), cities.end(), City::SortByCityCode);
	for (City &c : cities)
		cout << "\t\t\t    " << c.getCityCode() << "\t\t" << c.getCityName() << endl;
}