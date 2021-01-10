#include <iostream>
#include "disability.h"
using namespace std;

void Disability:: set_geo_name(string geo_name)
{
	this->geo_name = geo_name;
}

string Disability:: get_geo_name()
{
	return geo_name;
}

void Disability:: set_hearing(int hearing)
{
	this->hearing = hearing;
}

int Disability:: get_hearing()
{
	return hearing;
}

void Disability:: set_vision(int vision)
{
	this->vision = vision;
}

int Disability:: get_vision()
{
	return vision;
}

void Disability:: set_cognitive(int cognitive)
{
	this->cognitive = cognitive;
}

int Disability:: get_cognitive()
{
	return cognitive;
}

void Disability:: set_ambulatory(int ambulatory)
{
	this->ambulatory = ambulatory;
}

int Disability:: get_ambulatory()
{
	return ambulatory;
}

void Disability:: set_self_care(int care)
{
	self_care = care; 
}

int Disability:: get_self_care()
{
	return self_care;
}

void Disability:: set_independent_living(int independent_living)
{
	this-> independent_living = independent_living;
}

int Disability:: get_independent_living()
{
	return independent_living;
}
