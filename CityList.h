//specification file for the CityList class

#ifndef CITYLIST_H
#define CITYLIST_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "City.h"

using namespace std;

class CityList
{
private:
	vector<City> cities;

public:
	//constructor
	CityList();
	
	//setter
	void addCity(string name, string code);

	//getter
	void getCitiesByName();
	void getCitiesByCode();

};
#endif