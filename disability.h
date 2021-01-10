#include <iostream>
#include <string>
using namespace std;

class Disability
{
	private:
	string geo_name;
	int hearing;
	int vision; 
	int cognitive;
	int ambulatory;
	int self_care;
	int independent_living;

	public:
	void set_geo_name(string geo_name);
	string get_geo_name();
	void set_hearing(int hearing);
	int get_hearing();
	void set_vision(int vision);
	int get_vision();
	void set_cognitive(int cognitive);
	int get_cognitive();
	void set_ambulatory(int ambulatory);
	int get_ambulatory();
	void set_self_care(int care);
	int get_self_care();
	void set_independent_living(int independent_living);
	int get_independent_living();
};