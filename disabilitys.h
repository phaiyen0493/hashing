#include <iostream>
#include "disability.h"

class Disabilitys
{
	private:
	string scheme;
	int disability_count;
	int disability_capacity;
	Disability *disability_list;
	
	public:
	Disabilitys();
	void File_Handling(string file_name);
	void insert(string info);
	void update(string info);
	void select(string info);
	void del(string info);
	void display();
	void write();
};
