#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip> 
#include "ages.h"
#define ARRAY_SIZE 50
using namespace std;

//converts the key that is a string into a int by substringing the part that is always the same then converting it to ascii
int convertToASCII(string letter)
{
	letter=letter.substr(7, 5);
	unsigned int result;
	for (int i = 0; i< letter.length(); i++)
	{
		char x = letter.at(i);
		result += pow((((int) (x)) - 64), i+1);
	}
	
	return result;
}

//constructor
Ages:: Ages()
{
	age_count = 0;
	age_capacity = ARRAY_SIZE;
	age_list = new Age[ARRAY_SIZE];
	Age temp;
	temp.set_geo_id("");
	temp.set_under_5(-1);
	temp.set_under_18(-1);
	temp.set_over_65(-1);

	for (int i = 0; i < age_capacity; i++)
	{
		age_list[i] = temp;
	}
}

//function to read a file
void Ages:: File_Handling(string file_name)
{
	ifstream fin;
	fin.open(file_name);
	if (fin.fail())
	{
		cout << "Cannot open the file " << file_name;
		exit(0);
	}

	string line;
	fin >> scheme;
	fin.ignore();
	getline(fin, line, '\n'); //take out line geo_geoid,under_5,under_18,over_65
	while(getline(fin, line, '\n'))
	{
		insert(line);	
	}
}

//function to insert a tuple into the hash table
void Ages:: insert(string info)
{
	//initializing variables
	string geo_id;
	string temp;
	int under_5;
	int under_18;
	int over_65;
	unsigned int key;
	unsigned int hash;

	//increases the capacity if the number of objects is above the cap
	if (age_count > age_capacity)
	{
		Age *temp;
		age_capacity += ARRAY_SIZE;
		temp = new Age[age_capacity];
		for (int i = 0; i < age_capacity; i++)
		{
			temp[i] = age_list[i];
		}
		delete [] age_list;
		age_list = temp;
	}

	stringstream iss(info);
	getline(iss, geo_id, ','); //get geo_id
	getline(iss, temp, ','); //get under_5
	under_5 = stoi(temp); //convert under_5 to number
	getline(iss, temp, ','); //get under_18
	under_18 = stoi(temp); //convert under_18 to number
	getline(iss, temp, '\n'); //convert over_65
	over_65 = stoi(temp); //convert over_65 to number

	bool found = false;
	//runs through age_list looking for a match
	for (int i = 0; i < age_capacity; i++)
	{
		if (geo_id.compare(age_list[i].get_geo_id()) == 0)
		{
			found = true;
			break;
		}
	}
	//if theres a match reports that it failed to insert
	if (found == true)
	{
		cout << "Failed to insert (" << info << ") into age" << endl;
	}
	else //add age info
	{
		Age temp;
		temp.set_geo_id(geo_id);
		temp.set_under_5(under_5);
		temp.set_under_18(under_18);
		temp.set_over_65(over_65);	

		//covert scheme to ASCII value
		key = convertToASCII(geo_id);
		//modulo hashing
		hash = key % age_capacity;

		do
		{
			if (age_list[hash].get_under_5() == -1)
			{
				age_list[hash] = temp;
				cout << "Inserted (" << info << ") into age" << endl;
				age_count++;
			}
			else
			{
				hash +=1;
			}
		} while(age_list[hash].get_under_5() != -1);
	}
}


//function to edit a tuple on the hash table
void Ages:: update(string info)
{
	//initializing variables
	string geo_id;
	string temp;
	int under_5 = -1;
	int under_18 = -1;
	int over_65 = -1;
	unsigned int key;
	unsigned int hash;
	stringstream iss(info);

	getline(iss, geo_id, ','); //get geo_id
	getline(iss, temp, ','); //get under_5
	if (temp.compare("*") != 0)
	{
		under_5 = stoi(temp); //convert under_5 to number
	}
	getline(iss, temp, ','); //get under_18
	if (temp.compare("*") != 0)
	{
		under_18 = stoi(temp); //convert under_18 to number
	}
	getline(iss, temp, '\n'); //convert over_65
	if (temp.compare("*") != 0)
	{
		over_65 = stoi(temp); //convert over_65 to number
	}

	//gets key
	key = convertToASCII(geo_id);
	hash = key % age_capacity;
	//replaces the tuple at the given key
	if (age_list[hash].get_geo_id() != "")
	{
		age_list[hash].set_geo_id(geo_id);
		age_list[hash].set_under_5(under_5);	
		age_list[hash].set_under_18(under_18);	
		age_list[hash].set_over_65(over_65);
		cout << "Updated (" << info << ") in age" << endl;
	}
	else //nothing is at the given key so update fails
	{
		cout << "Failed to update (" << info << ") in age" << endl;
	}
}

//function to search the hash table
void Ages:: select(string info)
{
	//initializing variables
	string geo_id;
	string temp;
	int under_5 = -1;
	int under_18 = -1;
	int over_65 = -1;
	bool allMatched = true;
	unsigned int key;
	unsigned int hash;

	stringstream iss(info);
	getline(iss, geo_id, ','); //get geo_id
	getline(iss, temp, ','); //get under_5
	if (temp.compare("*") != 0)
	{
		under_5 = stoi(temp); //convert under_5 to number
	}
	getline(iss, temp, ','); //get under_18
	if (temp.compare("*") != 0)
	{
		under_18 = stoi(temp); //convert under_18 to number
	}
	getline(iss, temp, '\n'); //convert over_65
	if (temp.compare("*") != 0)
	{
		over_65 = stoi(temp); //convert over_65 to number
	}
	int match_count = 0;
	if (geo_id.compare("*") != 0)
	{	
		allMatched = true;
		key = convertToASCII(geo_id);
		hash = key % age_capacity;
		if ( allMatched && under_5 > -1 ) 
		{ 
			if ( age_list[hash].get_under_5() != under_5 ) 
			{
				allMatched = false;
			}
		}
	
		if ( allMatched && under_18 > -1 ) 
		{ 
			if ( age_list[hash].get_under_18() != under_18) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && over_65 > -1 ) 
		{ 
			if (age_list[hash].get_over_65() != over_65) 
			{
				allMatched = false;
			}
		}
		
		if ( allMatched ) 
		{
			// display
			cout << "Found (" << age_list[hash].get_geo_id() << ", " << age_list[hash].get_under_5() << ", " << age_list[hash].get_under_18() << ", " << age_list[hash].get_over_65() << ") in age" << endl;
		} 
		else
		{
			cout << "Failed to find (" << info << ") in age" << endl;
		}
	}
	else
	{
		for (int i = 0; i < age_capacity; i++)
		{
			allMatched = true;
			if ( allMatched && geo_id.compare("*") != 0) 
			{ 
				if (geo_id.compare(age_list[i].get_geo_id()) != 0) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && under_5 > -1 ) 
			{ 
				if ( age_list[i].get_under_5() != under_5 ) 
				{
					allMatched = false;
				}
			}
	
			if ( allMatched && under_18 > -1 ) 
			{ 
				if ( age_list[i].get_under_18() != under_18) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && over_65 > -1 ) 
			{ 
				if (age_list[i].get_over_65() != over_65) 
				{
					allMatched = false;
				}
			}
		
			if ( allMatched ) 
			{
				cout << "Found (" << age_list[i].get_geo_id() << ", " << age_list[i].get_under_5() << ", " << age_list[i].get_under_18() << ", " << age_list[i].get_over_65() << ") in age" << endl;
				match_count++;
			}
		}
		if (!allMatched && match_count == 0)
		{
			cout << "Failed to find (" << info << ") in age" << endl;
		}
	}
}
//function to delete tuple(s) from the hash table
void Ages:: del(string info)
{
	//initializing variables
	string geo_id;
	string temp;
	int under_5 = -1;
	int under_18 = -1;
	int over_65 = -1;
	bool allMatched = true;
	unsigned int key;
	unsigned int hash;

	stringstream iss(info);
	getline(iss, geo_id, ','); //get geo_id
	getline(iss, temp, ','); //get under_5
	if (temp.compare("*") != 0)
	{
		under_5 = stoi(temp); //convert under_5 to number
	}
	getline(iss, temp, ','); //get under_18
	if (temp.compare("*") != 0)
	{
		under_18 = stoi(temp); //convert under_18 to number
	}
	getline(iss, temp, '\n'); //convert over_65
	if (temp.compare("*") != 0)
	{
		over_65 = stoi(temp); //convert over_65 to number
	}

	int match_count = 0;
	Age temp_age;
	temp_age.set_geo_id("");
	temp_age.set_under_5(-1);
	temp_age.set_under_18(-1);
	temp_age.set_over_65(-1);

	if (geo_id.compare("*") != 0)
	{	
		allMatched = true;
		key = convertToASCII(geo_id);
		hash = key % age_capacity;
		if ( allMatched && under_5 > -1 ) 
		{ 
			if ( age_list[hash].get_under_5() != under_5 ) 
			{
				allMatched = false;
			}
		}
	
		if ( allMatched && under_18 > -1 ) 
		{ 
			if ( age_list[hash].get_under_18() != under_18) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && over_65 > -1 ) 
		{ 
			if (age_list[hash].get_over_65() != over_65) 
			{
				allMatched = false;
			}
		}
		
		if ( allMatched ) 
		{
			// delete
			cout << "Deleted (" << age_list[hash].get_geo_id() << "," << age_list[hash].get_under_5() << age_list[hash].get_under_18() << age_list[hash].get_over_65() << ") in age" << endl;
			age_list[hash] = temp_age;
			age_count--;
		}
		else
		{
			cout << "Failed to delete (" << info << ") in age" << endl;
		}
	}
	else
	{
		for (int i = 0; i < age_capacity; i++)
		{
			allMatched = true;
			if ( allMatched && geo_id.compare("*") != 0) 
			{ 
				if (geo_id.compare(age_list[i].get_geo_id()) != 0) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && under_5 > -1 ) 
			{ 
				if ( age_list[i].get_under_5() != under_5 ) 
				{
					allMatched = false;
				}
			}
	
			if ( allMatched && under_18 > -1 ) 
			{ 
				if ( age_list[i].get_under_18() != under_18) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && over_65 > -1 ) 
			{ 
				if (age_list[i].get_over_65() != over_65) 
				{
					allMatched = false;
				}
			}
		
			if ( allMatched  && age_list[i].get_under_5() > -1) 
			{
				// delete
				cout << "Deleted (" << age_list[i].get_geo_id() << "," << age_list[i].get_under_5() << age_list[i].get_under_18() << age_list[i].get_over_65() << ") in age" << endl;
				age_list[i] = temp_age;
				match_count++;
				age_count--;
			}
		}
		if(!allMatched && match_count == 0)
		{
			cout << "Failed to delete (" << info << ") in age" << endl;
		} 
	}
}
//function to print the hash table
void Ages::display()
{
	cout << "geo_geoid" << setw(15) << right << "under_5\t" << setw(10) << right << "under_18" << setw(10) << right << "over_65\n";
	for (int i = 0; i < age_capacity; i++)
	{
		if (age_list[i].get_under_5() != -1)
		{	
			cout << age_list[i].get_geo_id() << setw(10) << age_list[i].get_under_5() << setw(10) << age_list[i].get_under_18() << setw(10) << age_list[i].get_over_65() << endl;	
		}
	}
}
//function to write the data of the hash table into a separate file.
void Ages:: write()
{
	ofstream fout;
	fout.open("out_age.csv");
	
	fout << scheme << endl;
	fout << "geo_geoid,under_5,under_18,over_65" << endl;
	for (int i = 0; i < age_capacity; i++)
	{
		if (age_list[i].get_under_5() != -1)
		{	
			fout << age_list[i].get_geo_id() << "," << age_list[i].get_under_5() << "," << age_list[i].get_under_18() << "," << age_list[i].get_over_65() << endl;	
		}
	}
	fout.close();

}