#include <iostream>
#include "age.h"
using namespace std;

//Setters & Getters
void Age::set_geo_id(string id)
{
	geo_id = id;
}

string Age::get_geo_id()
{
	return geo_id;
}

void Age::set_under_5(int num)
{
	under_5 = num;
}

int Age::get_under_5()
{
	return under_5;
}

void Age::set_under_18(int num)
{
	under_18 = num;
}

int Age::get_under_18()
{
	return under_18;
}

void Age:: set_over_65(int num)
{
	over_65 = num;
}

int Age:: get_over_65()
{
	return over_65;
}