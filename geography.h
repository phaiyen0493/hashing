#include <iostream>
using namespace std;

class Geography
{
	private:
	//stores the data from the tuple
	int replan_id;
	string geo_name;
	string geo_stusab;
	int geo_sumlev;
	int geo_state;
	int geo_county;
	string geo_geoid;
	int population;

	public:
	//modifiers and accessors
	void set_replan_id(int id);
	int get_replan_id();
	void set_geo_name(string name);
	string get_geo_name();
	void set_geo_stusab(string stusab);
	string get_geo_stusab();
	void set_geo_sumlev(int sumlev);
	int get_geo_sumlev();
	void set_geo_state(int geo_state);
	int get_geo_state();
	void set_geo_county(int geo_county);
	int get_geo_county();
	void set_geo_id(string geo_id);
	string get_geo_id();
	void set_population(int population);
	int get_population();
};
