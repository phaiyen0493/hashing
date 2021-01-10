#include <iostream>
#include <string>
#include "geography.h"

class Geographys
{
	private:
	string scheme; //scheme of table (given in file)
	int geo_count; //number of entries
	int geo_capacity; //number of spaces
	Geography *geo_list; //primary index (stores table info)

	public:
	Geographys(); //constructor
	void File_Handling(string file_name); //reads file
	void insert(string info); //adds entries
	void update(string info); //mofies entries
	void select(string info); //displays matching entries
	void del(string info); //removes matching entries
	void display(); //displays all info to terminal
	void write(); //outputs all data to file
};
