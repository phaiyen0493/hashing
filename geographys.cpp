#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip> 
#include "geographys.h"
#define ARRAY_SIZE 50

Geographys::Geographys()
{
	//initializes table and allocates memory
	geo_count = 0;
	geo_capacity = ARRAY_SIZE;
	geo_list = new Geography[ARRAY_SIZE];
	Geography temp;
	temp.set_replan_id(0);
	temp.set_geo_name("");
	temp.set_geo_stusab("");
	temp.set_geo_sumlev(0);
	temp.set_geo_state(0);
	temp.set_geo_county(0);
	temp.set_geo_id("");
	temp.set_population(0);
}

void Geographys:: File_Handling(string file_name)
{
	ifstream fin;
	fin.open(file_name);
	if (fin.fail()) //if the file cannot open, quit
	{
		cout << "Cannot open the file " << file_name;
		exit(0);
	}

	string line;
	fin >> scheme; //read in scheme
	fin.ignore();
	getline(fin, line, '\n'); //take out line geo_geoid,under_5,under_18,over_65
	while(getline(fin, line, '\n'))
	{
		insert(line); //call insert for each line of data
	}
}

void Geographys:: insert(string info)
{
	//temp vars for reading in
	int replan_id;
	string geo_name;
	string geo_stusab;
	int geo_sumlev;
	int geo_state;
	int geo_county;
	string geo_id;
	int population;
	//used for hash function
	unsigned int key;
	unsigned int hash;

	//if there are more entries than spaces, double the array size
	if (geo_count > geo_capacity)
	{
		Geography *temp;
		geo_capacity += ARRAY_SIZE;
		temp = new Geography[geo_capacity];
		for (int i = 0; i < geo_capacity; i++)
		{
			temp[i] = geo_list[i];
		}
		delete [] geo_list;
		geo_list = temp;
	}

	//reads in the info from the tuple
	stringstream iss(info);
	string temp;
	getline(iss, temp, ',');
	replan_id = stoi(temp);
	getline(iss, temp, ',');
	temp = temp.substr(1, temp.length() - 1);
	getline(iss, geo_name, ',');
	geo_name = geo_name.substr(0, geo_name.length() - 1);
	geo_name = "," + geo_name;
	geo_name = temp + geo_name;
	getline(iss, geo_stusab, ',');
	getline(iss, temp, ',');
	geo_sumlev = stoi(temp);
	getline(iss, temp, ',');
	geo_state = stoi(temp);
	getline(iss, temp, ',');
	geo_county = stoi(temp);
	getline(iss, geo_id, ',');
	getline(iss, temp, '\n');
	population = stoi(temp);

	bool found = false;
	//makes sure there aren't repeats of the replan id
	for (int i = 0; i < geo_capacity; i++)
	{
		if (replan_id == geo_list[i].get_replan_id())
		{
			found = true;
			break;
		}
	}

	if(found == true) //error message if entry cannot be inserted
	{
		cout << "Failed to insert (" << info << ") into geography" << endl;
	}
	else
	{
		Geography temp;
		temp.set_replan_id(replan_id);
		temp.set_geo_name(geo_name);
		temp.set_geo_stusab(geo_stusab);
		temp.set_geo_sumlev(geo_sumlev);
		temp.set_geo_state(geo_state);
		temp.set_geo_county(geo_county);
		temp.set_geo_id(geo_id);
		temp.set_population(population);
		int i = 0;
		//hash with quadratic probing collision strategy
		do
		{
			key = replan_id % geo_capacity;
			hash = key + pow(i, 2);
			hash = hash % geo_capacity;
			i++;	
		} while(geo_list[hash].get_replan_id() != 0);

		geo_list[hash] = temp; //insert information
		cout << "Inserted (" << info << ") into geography" << endl; //print success message
		geo_count++; //increase count
	}
}

void Geographys:: update(string info)
{
	//temp vars
	int replan_id;
	string geo_name="";
	string geo_stusab="";
	int geo_sumlev=0;
	int geo_state=0;
	int geo_county=0;
	string geo_id="";
	int population=0;
	//used for hashing
	unsigned int key;
	unsigned int hash;

	//read in info from the tuple (checking for tombstones)
	stringstream iss(info);
	string temp;
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		replan_id = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		temp = temp.substr(1, temp.length() - 1);
		getline(iss, geo_name, ',');
		geo_name = geo_name.substr(0, geo_name.length() - 1);
		geo_name = "," + geo_name;
		geo_name = temp + geo_name;
	}
	getline(iss, geo_stusab, ',');
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_sumlev = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_state = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_county = stoi(temp);
	}
	getline(iss, geo_id, ',');
	getline(iss, temp, '\n');
	if (temp.compare("*") != 0)
	{
		population = stoi(temp);
	}
	int i = 0;
	//find the entry using the hash key
	do
	{
		key = replan_id % geo_capacity;
		hash = key + pow(i, 2);
		hash = hash % geo_capacity;
		i++;	
	} while(geo_list[hash].get_replan_id() != 0);

	if (geo_list[hash].get_replan_id() != 0)
	{
		geo_list[hash].set_replan_id(replan_id);
		geo_list[hash].set_geo_name(geo_name);
		geo_list[hash].set_geo_stusab(geo_stusab);
		geo_list[hash].set_geo_sumlev(geo_sumlev);
		geo_list[hash].set_geo_state(geo_state);
		geo_list[hash].set_geo_county(geo_county);
		geo_list[hash].set_geo_id(geo_id);
		geo_list[hash].set_population(population);
		cout << "Updated (" << info << ") in geography" << endl;
	}
	//failed, error message
	else
	{
		cout << "Failed to update (" << info << ") in geography" << endl;
	}
}

void Geographys:: select(string info)
{
	//temp vars
	int replan_id = 0;
	string geo_name="*";
	string geo_stusab="*";
	int geo_sumlev=0;
	int geo_state=0;
	int geo_county=0;
	string geo_id="*";
	int population=0;
	//used for hashing
	unsigned int key;
	unsigned int hash;
	bool allMatched = true; //used to find matches

	//read in the info from the tuple (check for tombstones)
	stringstream iss(info);
	string temp;
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		replan_id = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		temp = temp.substr(1, temp.length() - 1);
		getline(iss, geo_name, ',');
		geo_name = geo_name.substr(0, geo_name.length() - 1);
		geo_name = "," + geo_name;
		geo_name = temp + geo_name;
	}
	getline(iss, geo_stusab, ',');
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_sumlev = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_state = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_county = stoi(temp);
	}
	getline(iss, geo_id, ',');
	getline(iss, temp, '\n');
	if (temp.compare("*") != 0)
	{
		population = stoi(temp);
	}
	int match_count = 0;
	if (replan_id != 0)  //check for matches within the table
	{	
		allMatched = true; //if anything doesn't match, this is false
		int i = 0;
		do //compare replan id (also hash key) to find an entry to compare
		{
			key = replan_id % geo_capacity;
			hash = key + pow(i, 2);
			hash = hash % geo_capacity;
			i++;	
		} while(geo_list[hash].get_replan_id() != 0);

		if ( allMatched && geo_name.compare("*") != 0 ) //compare name
		{ 
			if ( geo_name.compare(geo_list[hash].get_geo_name()) != 0 ) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_stusab.compare("*") != 0 ) //compare stusab
		{ 
			if ( geo_stusab.compare(geo_list[hash].get_geo_stusab()) != 0 ) 
			{
				allMatched = false;
			}
		}
	
		if ( allMatched && geo_sumlev != 0) //compare sumlev
		{ 
			if ( geo_sumlev != geo_list[hash].get_geo_sumlev()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_state != 0) //compare state
		{ 
			if (geo_state != geo_list[hash].get_geo_state()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_county != 0) //comapre country
		{ 
			if (geo_county != geo_list[hash].get_geo_county()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_id.compare("*") != 0) //compare geoid
		{ 
			if (geo_id.compare(geo_list[hash].get_geo_id()) != 0) 
			{
				allMatched = false;
			}
		}


		if ( allMatched && population != 0) //compare pop
		{ 
			if (geo_county != geo_list[hash].get_population()) 
			{
				allMatched = false;
			}
		}
		
		if ( allMatched ) //if the correct entry is found
		{
			// display
			cout << "Found (" << geo_list[hash].get_replan_id() << ", " << geo_list[hash].get_geo_name() << ", " << geo_list[hash].get_geo_stusab() << ", " << geo_list[hash].get_geo_sumlev() << "," << geo_list[hash].get_geo_state() << "," << geo_list[hash].get_geo_county() << "," << geo_list[hash].get_geo_id() << geo_list[hash].get_population() << ") in geography" << endl;
		} 
		else
		{
			//no match, error message
			cout << "No entries matched (" << info << ") in geography" << endl;
		}
	}
	//repeat process for multiple selections
	else
	{
		for (int i = 0; i < geo_capacity; i++) //compare replan id
		{
			allMatched = true;
			if ( allMatched && replan_id != 0) 
			{ 
				if (replan_id != geo_list[i].get_replan_id()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_name.compare("*") != 0 ) //compare name
			{ 
				if ( geo_name.compare(geo_list[i].get_geo_name()) != 0 ) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_stusab.compare("*") != 0 ) //compare stusab
			{ 
				if ( geo_stusab.compare(geo_list[i].get_geo_stusab()) != 0 ) 
				{
					allMatched = false;
				}
			}
			
			if ( allMatched && geo_sumlev != 0) //compare sumlev
			{ 
				if ( geo_sumlev != geo_list[i].get_geo_sumlev()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_state != 0) //compare state
			{ 
				if (geo_state != geo_list[i].get_geo_state()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_county != 0) //compare county
			{ 
				if (geo_county != geo_list[i].get_geo_county()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_id.compare("*") != 0) //compare geoid
			{ 
				if (geo_id.compare(geo_list[i].get_geo_id()) != 0) 
				{
					allMatched = false;
				}
			}


			if ( allMatched && population != 0) //compare pop
			{ 
				if (geo_county != geo_list[i].get_population()) 
				{
					allMatched = false;
				}
			}
					
			if ( allMatched ) //report entry found
			{
				cout << "Found entry (" << geo_list[i].get_replan_id() << "," << geo_list[i].get_geo_name() << ", " << geo_list[i].get_geo_stusab() << ", " << geo_list[i].get_geo_sumlev() << "," << geo_list[i].get_geo_state() << "," << geo_list[i].get_geo_county() << "," << geo_list[i].get_geo_id() << geo_list[i].get_population() << ") in geography" << endl;
				match_count++;
			}
		}
		if(!allMatched && match_count == 0) //error message
		{
			cout << "No entries matched (" << info << ") in geography" << endl;
		} 
	}
}

void Geographys:: del(string info)
{
	//temp vars
	int replan_id = 0;
	string geo_name="*";
	string geo_stusab="*";
	int geo_sumlev=0;
	int geo_state=0;
	int geo_county=0;
	string geo_id="*";
	int population=0;
	//used for hashing
	unsigned int key;
	unsigned int hash;

	//used to find matches
	bool allMatched = true;

	//read in the info from the tuple
	stringstream iss(info);
	string temp;
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		replan_id = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		temp = temp.substr(1, temp.length() - 1);
		getline(iss, geo_name, ',');
		geo_name = geo_name.substr(0, geo_name.length() - 1);
		geo_name = "," + geo_name;
		geo_name = temp + geo_name;
	}
	getline(iss, geo_stusab, ',');
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_sumlev = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_state = stoi(temp);
	}
	getline(iss, temp, ',');
	if (temp.compare("*") != 0)
	{
		geo_county = stoi(temp);
	}
	getline(iss, geo_id, ',');
	getline(iss, temp, '\n');
	if (temp.compare("*") != 0)
	{
		population = stoi(temp);
	}

	Geography temp_geo; //create a temporary object
	temp_geo.set_replan_id(0);
	temp_geo.set_geo_name("");
	temp_geo.set_geo_stusab("");
	temp_geo.set_geo_sumlev(0);
	temp_geo.set_geo_state(0);
	temp_geo.set_geo_county(0);
	temp_geo.set_geo_id("");
	temp_geo.set_population(0);

	int match_count = 0;
	if (replan_id != 0) //check for matches
	{	
		allMatched = true; //will become false if anything does not match
		int i = 0;
		do //compare replan id
		{
			key = replan_id % geo_capacity;
			hash = key + pow(i, 2);
			hash = hash % geo_capacity;
			i++;	
		} while(geo_list[hash].get_replan_id() != 0);

		if ( allMatched && geo_name.compare("*") != 0 ) //compare name
		{ 
			if ( geo_name.compare(geo_list[hash].get_geo_name()) != 0 ) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_stusab.compare("*") != 0 ) //compare stusab
		{ 
			if ( geo_stusab.compare(geo_list[hash].get_geo_stusab()) != 0 ) 
			{
				allMatched = false;
			}
		}
	
		if ( allMatched && geo_sumlev != 0) //compare sumlev
		{ 
			if ( geo_sumlev != geo_list[hash].get_geo_sumlev()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_state != 0) //compare state
		{ 
			if (geo_state != geo_list[hash].get_geo_state()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_county != 0) //compare country
		{ 
			if (geo_county != geo_list[hash].get_geo_county()) 
			{
				allMatched = false;
			}
		}

		if ( allMatched && geo_id.compare("*") != 0) //compare geoid
		{ 
			if (geo_id.compare(geo_list[hash].get_geo_id()) != 0) 
			{
				allMatched = false;
			}
		}


		if ( allMatched && population != 0) //compare pop
		{ 
			if (geo_county != geo_list[hash].get_population()) 
			{
				allMatched = false;
			}
		}
		
		if ( allMatched ) //if the entry is found
		{
			cout << "Deleted (" << geo_list[hash].get_replan_id() << "," << geo_list[hash].get_geo_name() << ", " << geo_list[hash].get_geo_stusab() << ", " << geo_list[hash].get_geo_sumlev() << "," << geo_list[hash].get_geo_state() << "," << geo_list[hash].get_geo_county() << "," << geo_list[hash].get_geo_id() << geo_list[hash].get_population() << ") in geography" << endl;
			geo_list[hash] = temp_geo;
			geo_count--;
		} 
		else //no match, print error message
		{
			cout << "Failed to delete (" << info << ") in geography" << endl;
		}
	}
	else //repeat process for multiple entries
	{
		for (int i = 0; i < geo_capacity; i++)
		{
			allMatched = true;
			if ( allMatched && replan_id != 0) //compare replan id
			{ 
				if (replan_id != geo_list[i].get_replan_id()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_name.compare("*") != 0 ) //compare name
			{ 
				if ( geo_name.compare(geo_list[i].get_geo_name()) != 0 ) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_stusab.compare("*") != 0 ) //compare stusab
			{ 
				if ( geo_stusab.compare(geo_list[i].get_geo_stusab()) != 0 ) 
				{
					allMatched = false;
				}
			}
			
			if ( allMatched && geo_sumlev != 0) //compare sumlev
			{ 
				if ( geo_sumlev != geo_list[i].get_geo_sumlev()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_state != 0) //compare state
			{ 
				if (geo_state != geo_list[i].get_geo_state()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_county != 0) //compare county
			{ 
				if (geo_county != geo_list[i].get_geo_county()) 
				{
					allMatched = false;
				}
			}

			if ( allMatched && geo_id.compare("*") != 0) //compare geoid
			{ 
				if (geo_id.compare(geo_list[i].get_geo_id()) != 0) 
				{
					allMatched = false;
				}
			}


			if ( allMatched && population != 0) //compare pop
			{ 
				if (geo_county != geo_list[i].get_population()) 
				{
					allMatched = false;
				}
			}
					
			if ( allMatched ) //if match found
			{
				cout << "Deleted (" << geo_list[i].get_replan_id() << "," << geo_list[i].get_geo_name() << ", " << geo_list[i].get_geo_stusab() << ", " << geo_list[i].get_geo_sumlev() << "," << geo_list[i].get_geo_state() << "," << geo_list[i].get_geo_county() << "," << geo_list[i].get_geo_id() << geo_list[i].get_population() << ") in geography" << endl;
				geo_list[i] = temp_geo;
				geo_count--;
				match_count++;
			}
		}
		if(!allMatched && match_count == 0) //no matches, print error message
		{
			cout << "Failed to delete (" << info << ") in geography" << endl;
		} 
	}
}

void Geographys:: display()
{
	//output scheme
	cout << "replan_id" << setw(15) << "geo_name" << setw(30) << "geo_stusab" << setw(12) << "geo_sumlev" << setw(10) << "geo_state" << setw(15) << "geo_county" << setw(15) << "geo_geoid" << setw(15) << "population" << endl;
	for (int i = 0; i < geo_capacity; i++)
	{
		if (geo_list[i].get_replan_id() != 0) //skip tombstones
		{
			cout << geo_list[i].get_replan_id() << setw(35) << geo_list[i].get_geo_name() << setw(10) << geo_list[i].get_geo_stusab() << setw(10) << geo_list[i].get_geo_sumlev() << setw(10) 
			 << geo_list[i].get_geo_state() << setw(10) << geo_list[i].get_geo_county() << setw(20) << geo_list[i].get_geo_id() << setw(20) << geo_list[i].get_population() << endl;
		}
	}
}

void Geographys:: write()
{
	ofstream fout;
	fout.open("out_geography.csv"); //declare outstream to file

	fout << scheme << endl;
	fout << "replan_id,geo_name,geo_stusab,geo_sumlev,geo_state,geo_county,geo_geoid,population" << endl;
	for (int i = 0; i < geo_capacity; i++) //output all data in table
	{
		if (geo_list[i].get_replan_id() != 0) //skip the tombstones
		{
			fout << geo_list[i].get_replan_id() << "," << geo_list[i].get_geo_name() << "," << geo_list[i].get_geo_stusab() << "," << geo_list[i].get_geo_sumlev() << "," 
			 << geo_list[i].get_geo_state() << "," << geo_list[i].get_geo_county() << "," << geo_list[i].get_geo_id() << "," << geo_list[i].get_population() << endl;
		}
	}


}