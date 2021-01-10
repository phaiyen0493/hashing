#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "ages.h"
#include "disabilitys.h"
#include "geographys.h"
using namespace std;

int main()
{
	//initializing variables
	string word;
	string line;
	Ages age;
	Geographys geography;
	Disabilitys disability;
	string input_filename;
	string filename;
	cout << "Please enter the main file's name: "; //get input
	cin >> input_filename;
	ifstream fin;

	fin.open(input_filename);
	if(fin.fail())
	{
		cout << "Cannot open the file " << input_filename;
		exit(0);
	}
	//check which hash table it goes to
	for (int i = 0 ; i < 3; i++)
	{
		fin >> filename;
		//cout << filename << endl;
		fin >> word;
		//cout << word << endl;
		
		if (word.compare("age") == 0)
		{
			age.File_Handling(filename);
		}
		else if(word.compare("geography") == 0)
		{
			geography.File_Handling(filename);
		}
		else if(word.compare("disability") == 0)
		{
			disability.File_Handling(filename);
		}
		
	}
	fin.ignore();
	string command_type;
	string info;
	getline(fin, line);

	//checks which command is called and calls it
	while(getline(fin, line, '\n'))
	{
		stringstream iss(line);
		getline(iss, command_type, '(');
		//cout << command_type << endl;
		if (command_type.compare("DISPLAY") != 0 && command_type.compare("WRITE") != 0)
		{
			getline(iss, info, ')');
			if (info != "")
			{
				info = info.substr(1, info.length()-1);
				//cout << info << endl;
			}
			getline(iss, word, ')');
			word = word.substr(1, word.length()-1);
			//cout << word << endl;
			
			if (command_type.compare("INSERT") == 0)
			{
				if (word.compare("age") == 0)
				{
					age.insert(info);
				}
				else if (word.compare("geography") == 0)
				{
					geography.insert(info);
				}
				else if (word.compare("disability") == 0)
				{
					disability.insert(info);
				}
			}
			if (command_type.compare("UPDATE") == 0)
			{
				if (word.compare("age") == 0)
				{
					age.update(info);
				}
				else if (word.compare("geography") == 0)
				{
					geography.update(info);
				}
				else if (word.compare("disability") == 0)
				{
					disability.update(info);
				}
			}
			else if (command_type.compare("SELECT") == 0)
			{
				if (word.compare("age") == 0)
				{
					age.select(info);
				}
				else if (word.compare("geography") == 0)
				{
					geography.select(info);
				}
				else if (word.compare("disability") == 0)
				{
					disability.select(info);
				}
			}

			else if (command_type.compare("DELETE") == 0)
			{
				if (word.compare("age") == 0)
				{
					age.del(info);
				}
				else if (word.compare("geography") == 0)
				{
					geography.del(info);
				}
				else if (word.compare("disability") == 0)
				{
					disability.del(info);
				}
			}
		}
		else if (command_type.compare("DISPLAY") == 0)
		{
			cout << "DISPLAY" << endl;
			age.display();
			geography.display();
			disability.display();
		}
		else if (command_type.compare("WRITE") == 0)
		{
			cout << "WRITE" << endl;
			age.write();
			geography.write();
			disability.write();
		}
	}

	cout << "Process complete!" << endl;
	return 0;
}