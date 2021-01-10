#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip> 
#include "disabilitys.h"
#define ARRAY_SIZE 50
using namespace std;

//Getting the index
int convert_to_ASCII(string letter)
{
	unsigned int result;
	for (int i = 0; i< letter.length(); i++)
	{
		char x = letter.at(i);
		result += pow((((int) (x)) - 64), i+1);
	}
	
	return result;
}

Disabilitys:: Disabilitys()
{
	disability_count = 0;
	disability_capacity = ARRAY_SIZE;
	disability_list = new Disability[ARRAY_SIZE];
	Disability temp;
	temp.set_geo_name("");
	temp.set_hearing(0);
	temp.set_vision(0);
	temp.set_cognitive(0);
	temp.set_ambulatory(0);
	temp.set_self_care(0);
	temp.set_independent_living(0);

	for (int i = 0; i < disability_capacity; i++)
	{
		disability_list[i] = temp;
	}
}

void Disabilitys:: File_Handling(string file_name)
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

void Disabilitys:: insert(string info)
{
	//create vectors
	if (disability_count > disability_capacity)
	{
		Disability *temp;
		disability_capacity += ARRAY_SIZE;
		temp = new Disability[disability_capacity];
		for (int i = 0; i < disability_capacity; i++)
		{
			temp[i] = disability_list[i];
		}
		delete [] disability_list;
		disability_list = temp;
	}

	string temp;
	string geo_name;
	int hearing;
	int vision;
	int cognitive;
	int ambulatory;
	int self_care;
	int independent_living;
	unsigned int key1;
	unsigned int key2;
	unsigned int hash;

	stringstream iss(info);
	getline(iss,temp, ','); 
	getline(iss, geo_name, ',');
	temp = temp + ",";
	geo_name = temp + geo_name;
	geo_name = geo_name.substr(1, geo_name.length() - 2);
	getline(iss, temp, ',');
	hearing = stoi(temp);
	getline(iss, temp, ',');
	vision = stoi(temp);
	getline(iss, temp, ',');
	cognitive = stoi(temp);
	getline(iss, temp, ',');
	ambulatory = stoi(temp);
	getline(iss, temp, ',');
	self_care = stoi(temp);
	getline(iss, temp, ',');
	independent_living = stoi(temp);

	Disability temp_dis;
	temp_dis.set_geo_name(geo_name);
	temp_dis.set_hearing(hearing);
	temp_dis.set_vision(vision);
	temp_dis.set_cognitive(cognitive);
	temp_dis.set_ambulatory(ambulatory);
	temp_dis.set_self_care(self_care);
	temp_dis.set_independent_living(independent_living);

	bool found = false;
	for (int i = 0; i < disability_capacity; i++)
	{
		if (geo_name.compare(disability_list[i].get_geo_name()) == 0)
		{
			found = true;
		}
	}

	//perfect hashing
	int i = 0;
	do
	{
		key1 = (convert_to_ASCII(geo_name)) % disability_capacity;
		key2 = 47 - (convert_to_ASCII(geo_name))%47;	
		hash = (key1 + (i*key2)) % disability_capacity;
		i++; 
	} while(disability_list[hash].get_geo_name().compare("") != 0);

	if(found == true)
	{
		cout << "Failed to insert (" << info << ") into disability" << endl;
	}
	else
	{
		disability_list[hash] = temp_dis;
		cout << "Inserted (" << info << ") into disability" << endl;
		disability_count++;
	}
}

void Disabilitys:: update(string info)
{
	string temp;
	string geo_name = "";
	int hearing = 0;
	int vision = 0;
	int cognitive = 0;
	int ambulatory = 0;
	int self_care = 0;
	int independent_living = 0;
	unsigned int key1;
	unsigned int key2;
	unsigned int hash;

	stringstream iss(info);
	getline(iss,temp, ',');
	if(temp.compare("*") != 0)
	{
		getline(iss, geo_name, ',');
		temp = temp + ",";
		geo_name = temp + geo_name;
		geo_name = geo_name.substr(1, geo_name.length() - 2);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		hearing = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		vision = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		cognitive = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		ambulatory = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		self_care = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		independent_living = stoi(temp);
	}

	//perfect hashing
	int i = 0;
	do
	{
		key1 = (convert_to_ASCII(geo_name)) % disability_capacity;
		key2 = 47 - (convert_to_ASCII(geo_name))%47;	
		hash = (key1 + (i*key2)) % disability_capacity;
		i++; 
	} while(disability_list[hash].get_geo_name().compare(geo_name) != 0);

	if(disability_list[hash].get_geo_name().compare("") != 0)
	{
		disability_list[hash].set_geo_name(geo_name);
		disability_list[hash].set_hearing(hearing);
		disability_list[hash].set_vision(vision);
		disability_list[hash].set_cognitive(cognitive);
		disability_list[hash].set_ambulatory(ambulatory);
		disability_list[hash].set_self_care(self_care);
		disability_list[hash].set_independent_living(independent_living);
		cout << "Updated (" << info << ") in disability" << endl;
	}
	else
	{
		cout << "Failed to update (" << info << ") in disability" << endl;
	}
}

void Disabilitys:: select(string info)
{
	string temp;
	string geo_name = "";
	int hearing = 0;
	int vision = 0;
	int cognitive = 0;
	int ambulatory = 0;
	int self_care = 0;
	int independent_living = 0;
	unsigned int key1;
	unsigned int key2;
	unsigned int hash;
	bool allMatched = true;

	stringstream iss(info);
	getline(iss,temp, ','); //get geo_name
	if(temp.compare("*") != 0)
	{
		getline(iss, geo_name, ',');
		temp = temp + ",";
		geo_name = temp + geo_name;
		geo_name = geo_name.substr(1, geo_name.length() - 2);
	}
	getline(iss, temp, ','); //get hearing_disability
	if (temp.compare("*") != 0)
	{
		hearing = stoi(temp);
	}
	getline(iss, temp, ','); //get vision disability
	if (temp.compare("*") != 0)
	{
		vision = stoi(temp);
	}
	getline(iss, temp, ','); //get cognitive
	if (temp.compare("*") != 0)
	{
		cognitive = stoi(temp);
	}
	getline(iss, temp, ','); //get ambulatory
	if (temp.compare("*") != 0)
	{
		ambulatory = stoi(temp);
	}
	getline(iss, temp, ','); //get self care
	if (temp.compare("*") != 0)
	{
		self_care = stoi(temp);
	}
	getline(iss, temp, ','); //get independent living
	if (temp.compare("*") != 0)
	{
		independent_living = stoi(temp);
	}

	int match_count = 0;
	if(geo_name.compare("") != 0)
	{
		allMatched = true;
		//perfect hashing
		int i = 0;
		do
		{
			key1 = (convert_to_ASCII(geo_name)) % disability_capacity;
			key2 = 47 - (convert_to_ASCII(geo_name))%47;	
			hash = (key1 + (i*key2)) % disability_capacity;
			i++; 
		} while(disability_list[hash].get_geo_name().compare(geo_name) != 0 && i != disability_capacity);
		
		if ( allMatched && hearing != 0 ) 
		{ 
			if ( hearing != disability_list[hash].get_hearing()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && vision != 0 ) 
		{ 
			if ( vision != disability_list[hash].get_vision()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && cognitive != 0 ) 
		{ 
			if ( vision != disability_list[hash].get_cognitive()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && ambulatory != 0 ) 
		{ 
			if ( vision != disability_list[hash].get_ambulatory()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && self_care != 0 ) 
		{ 
			if ( self_care != disability_list[hash].get_self_care()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && independent_living != 0 ) 
		{ 
			if ( independent_living != disability_list[hash].get_independent_living()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched ) 
		{
			// display
			cout << "Found (" << disability_list[hash].get_geo_name() << "," << disability_list[hash].get_hearing() << "," << disability_list[hash].get_vision() << "," 
			<< disability_list[hash].get_cognitive() << disability_list[hash].get_ambulatory() << disability_list[hash].get_self_care() << disability_list[hash].get_independent_living() << endl;
		} 
		else
		{
			cout << "No entries matched (" << info << ") in disability" << endl;
		}
	}
	else
	{
		for (int i = 0; i < disability_capacity; i++)
		{
			if (allMatched && geo_name.compare("") != 0)
			{
				if(geo_name.compare(disability_list[i].get_geo_name()) != 0)
				{
					allMatched = false;
				}
			}
			
			if ( allMatched && hearing != 0 ) 
			{ 
				if ( hearing != disability_list[i].get_hearing()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && vision != 0 ) 
			{ 
				if ( vision != disability_list[i].get_vision()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && cognitive != 0 ) 
			{ 
				if ( cognitive != disability_list[i].get_cognitive()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && ambulatory != 0 ) 
			{ 
				if ( ambulatory != disability_list[i].get_ambulatory()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && self_care != 0 ) 
			{ 
				if ( self_care != disability_list[i].get_self_care()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && independent_living != 0 ) 
			{ 
				if ( independent_living != disability_list[i].get_independent_living()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched ) 
			{
				// display
				cout << "Found (" << disability_list[hash].get_geo_name() << "," << disability_list[hash].get_hearing() << "," << disability_list[hash].get_vision() << "," 
				<< disability_list[hash].get_cognitive() << disability_list[hash].get_ambulatory() << disability_list[hash].get_self_care() << disability_list[hash].get_independent_living() << endl;
				match_count++;
			} 
		}
		if(!allMatched && match_count == 0)
		{
			cout << "No entries matched (" << info << ") in disability" << endl;
		} 
	}
}

//delete function
void Disabilitys:: del(string info)
{
	string temp;
	string geo_name = "";
	int hearing = 0;
	int vision = 0;
	int cognitive = 0;
	int ambulatory = 0;
	int self_care = 0;
	int independent_living = 0;
	unsigned int key1;
	unsigned int key2;
	unsigned int hash;
	bool allMatched = true;

	stringstream iss(info);
	getline(iss,temp, ',');
	if(temp.compare("*") != 0)
	{
		getline(iss, geo_name, ',');
		temp = temp + ",";
		geo_name = temp + geo_name;
		geo_name = geo_name.substr(1, geo_name.length() - 2);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		hearing = stoi(temp); //get hearing
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		vision = stoi(temp); //get vision
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		cognitive = stoi(temp); //get cognitive
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		ambulatory = stoi(temp); //get ambulatory
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		self_care = stoi(temp); //get self care
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		independent_living = stoi(temp); //get independent living
	}

	int match_count = 0;

	Disability temp_dis;
	temp_dis.set_geo_name("");
	temp_dis.set_hearing(0);
	temp_dis.set_vision(0);
	temp_dis.set_cognitive(0);
	temp_dis.set_ambulatory(0);
	temp_dis.set_self_care(0);
	temp_dis.set_independent_living(0);

	if(geo_name.compare("") != 0)
	{
		allMatched = true;
		int i = 0;
		do
		{
			key1 = (convert_to_ASCII(geo_name)) % disability_capacity;
			key2 = 47 - (convert_to_ASCII(geo_name))%47;	
			hash = (key1 + (i*key2)) % disability_capacity;
			i++; 
		} while(disability_list[hash].get_geo_name().compare(geo_name) != 0 && i != disability_capacity);
		
		if ( allMatched && hearing != 0 ) 
		{ 
			if ( hearing != disability_list[hash].get_hearing()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && vision != 0 ) 
		{ 
			if ( vision != disability_list[hash].get_vision()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && cognitive != 0 ) 
		{ 
			if ( cognitive != disability_list[hash].get_cognitive()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && ambulatory != 0 ) 
		{ 
			if ( ambulatory != disability_list[hash].get_ambulatory()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && self_care != 0 ) 
		{ 
			if ( self_care != disability_list[hash].get_self_care()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && independent_living != 0 ) 
		{ 
			if ( independent_living != disability_list[hash].get_independent_living()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && disability_list[hash].get_self_care() > 0) 
		{
			// display
			cout << "Deleted (" << disability_list[hash].get_geo_name() << "," << disability_list[hash].get_hearing() << "," << disability_list[hash].get_vision() << "," 
			<< disability_list[hash].get_cognitive() << disability_list[hash].get_ambulatory() << disability_list[hash].get_self_care() << disability_list[hash].get_independent_living() << ") in disability" << endl;
			disability_list[hash] = temp_dis;
		} 
		else
		{
			cout << "Failed to delete (" << info << ") in disability" << endl;
		}
	}
	else
	{
		for (int i = 0; i < disability_capacity; i++)
		{
			if (allMatched && geo_name.compare("") != 0)
			{
				if(geo_name.compare(disability_list[i].get_geo_name()) != 0)
				{
					allMatched = false;
				}
			}
			
			if ( allMatched && hearing != 0 ) 
			{ 
				if ( hearing != disability_list[i].get_hearing()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && vision != 0 ) 
			{ 
				if ( vision != disability_list[i].get_vision()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && cognitive != 0 ) 
			{ 
				if ( vision != disability_list[i].get_cognitive()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && ambulatory != 0 ) 
			{ 
				if ( ambulatory != disability_list[i].get_ambulatory()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && self_care != 0 ) 
			{ 
				if ( self_care != disability_list[i].get_self_care()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && independent_living != 0 ) 
			{ 
				if ( independent_living != disability_list[i].get_independent_living()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched ) 
			{
				cout << "Deleted (" << disability_list[i].get_geo_name() << "," << disability_list[i].get_hearing() << "," << disability_list[i].get_vision() << "," 
				<< disability_list[i].get_cognitive() << disability_list[i].get_ambulatory() << disability_list[i].get_self_care() << disability_list[i].get_independent_living() << ") in disability" << endl;
				disability_list[i] = temp_dis;
				match_count++;
				disability_count--;
			} 
		}
		if(!allMatched && match_count == 0)
		{
			cout << "Failed to delete (" << info << ") in disability" << endl;
		} 
	}
}

//display table
void Disabilitys:: display()
{
	cout << endl << "geo_name" << setw(10) << "hearing_disability" << setw(10) << "vision_disability" << setw(10) << "cognitive_disability" << setw(10) << "ambulatory_disability" << setw(10) << "self_care_disability" << setw(10) << "independent_living_disability" << endl;

	for (int i = 0; i < disability_capacity; i++)
	{
		if( disability_list[i].get_geo_name().compare("") != 0)
		{
			cout << disability_list[i].get_geo_name() << setw(15) << disability_list[i].get_hearing() << "\t" << disability_list[i].get_vision() << "\t" 
				<< disability_list[i].get_cognitive() << '\t' << disability_list[i].get_ambulatory() << "\t" << disability_list[i].get_self_care() << "\t" << disability_list[i].get_independent_living() << endl;
		}
	}
}

//write table
void Disabilitys:: write()
{
	ofstream fout;
	fout.open("out_disability.csv");
	
	fout << scheme << endl;
	fout << "geo_name,hearing_disability,vision_disability,cognitive_disability,ambulatory_disability,self_care_disability,independent_living_disability" << endl;

	for (int i = 0; i < disability_capacity; i++)
	{
		if( disability_list[i].get_geo_name().compare("") != 0)
		{
			fout << "\"" << disability_list[i].get_geo_name() << "\"," << disability_list[i].get_hearing() << "," << disability_list[i].get_vision() << "," 
				<< disability_list[i].get_cognitive() << "," << disability_list[i].get_ambulatory() << "," << disability_list[i].get_self_care() << "," << disability_list[i].get_independent_living() << endl;
		}
	}


}