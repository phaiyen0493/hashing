#include <iostream>
#include "geography.h"
using namespace std;

void Geography:: set_replan_id(int id)
{
	replan_id = id;
}

int Geography::get_replan_id()
{
	return replan_id;
}

void Geography:: set_geo_name(string name)
{
	geo_name = name;
}

string Geography:: get_geo_name()
{
	return geo_name;
}

void Geography:: set_geo_stusab(string stusab)
{
	geo_stusab = stusab;
}

string Geography:: get_geo_stusab()
{
	return geo_stusab;
}

void Geography:: set_geo_sumlev(int sumlev)
{
	geo_sumlev = sumlev;
}

int Geography:: get_geo_sumlev()
{
	return geo_sumlev;
}

void Geography:: set_geo_state(int geo_state)
{
	this->geo_state = geo_state;
}

int Geography:: get_geo_state()
{
	return geo_state;
}

void Geography:: set_geo_county(int geo_county)
{
	this->geo_county = geo_county;
}

int Geography:: get_geo_county()
{
	return geo_county;
}

void Geography:: set_geo_id(string geo_id)
{
	geo_geoid = geo_id;
}

string Geography:: get_geo_id()
{
	return geo_geoid;
}

void Geography:: set_population(int population)
{
	this->population = population;
}

int Geography:: get_population()
{
	return population;
}
