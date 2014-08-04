//specification file for the City class

#ifndef CITY_H
#define CITY_H
#include <string>

using namespace std;

class City
{
protected:
	string cityName;
	string cityCode;

public:
	//constructor
	City();
	City(string name, string code);
	
	//setter
	void setCityName(string name);
	void setCityCode(string code);

	//getter
	string getCityName();
	string getCityCode();


	static bool SortByCityName(const City & c1, const City & c2)
	{
		return c1.cityName < c2.cityName;
	}

	static bool SortByCityCode(const City & c1, const City & c2)
	{
		return c1.cityCode < c2.cityCode;
	}
};
#endif