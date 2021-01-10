#include <iostream>
#include <string>
using namespace std;

class Age
{
	private:
	//variables
	string geo_id;
	int under_5;
	int under_18;
	int over_65;

	public:
	//setters & getters
	void set_geo_id(string id);
	string get_geo_id();
	void set_under_5(int num);
	int get_under_5();
	void set_under_18(int num);
	int get_under_18();
	void set_over_65(int num);
	int get_over_65();
};