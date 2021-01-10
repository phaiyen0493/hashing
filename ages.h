#include <iostream>
#include <string>
#include "age.h"
using namespace std;

class Ages
{
	private:
	//variables
	string scheme;
	int age_count;
	int age_capacity;
	Age *age_list;
	
	public:
	Ages(); //constructor
	void File_Handling(string file_name);
	void insert(string info);
	void update(string info);
	void select(string info);
	void del(string info);
	void display();
	void write();
};