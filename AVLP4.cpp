/*  Program: Project 4 Driver
	Author: Ariella Navarro
	Class: CSCI 220
	Date: 12/3/2019
	Description: Implements AVL Tree with file input

	I certify that the code below is my own work.

	Exception(s): N/A

*/

#include <iostream>
#include "AVL.h"
#include <string>

using namespace std;

void drawDebug(AVLTree &a);
void print(AVLTree &a);
void erase(AVLTree &a);
void insert(AVLTree &a);
void search(AVLTree &a);
void selectOption(AVLTree &a);
void displayMenu();

int main()
{

	cout << "Author: Ariella Navarro\n" << endl;

	AVLTree myAVL("p4small.txt");

	displayMenu();
	selectOption(myAVL);

	return 0;
}

void displayMenu()
{
	cout << "Menu: " << endl;
	cout << "1. Search for a record" << endl;
	cout << "2. Insert a record" << endl;
	cout << "3. Delete a record" << endl;
	cout << "4. List all records" << endl;
	cout << "5. Exit" << endl;
	cout << endl;
}

void selectOption(AVLTree &a)
{
	string userInput;

	cout << "Select on option from the menu to perform an action (1-5): ";
	std::getline(std::cin, userInput);

	while (userInput != "5")
	{
		if (userInput == "0")
		{
			drawDebug(a);
		}
		else if (userInput == "1")
		{
			search(a);
		}
		else if (userInput == "2")
		{
			insert(a);
		}
		else if (userInput == "3")
		{
			erase(a);
		}
		else if (userInput == "4")
		{
			print(a);
		}
		else
		{
			cout << "Invalid Option. Try again." << endl;
		}
		
		cout << endl;
		cout << "Select on option from the menu to perform an action (1-5): ";
		std::getline(std::cin, userInput);
	}

}

void search(AVLTree &a)
{
	string c;
	int code, nodes = 0;
	bool found = false;
	istringstream ss;
	cout << "Enter a record code to search for: ";
	std::getline(std::cin, c);
	ss.str(c);
	ss >> code;

	found = a.find(code, nodes);

	cout << "Nodes examined: " << nodes << endl;
}

void insert(AVLTree &a)
{
	int code, pop = -1;
	string record, temp;
	string location = "-1";

	cout << "Enter a record: ";
	std::getline(std::cin, record);

	istringstream ss(record);
	ss >> code;

	int count = 0;
	while (getline(ss, temp, ','))
	{
		if (count == 0)
		{
			ss >> pop;
			count++;
		}
		else if (count == 1)
		{
			std::getline(ss, location);
			a.insert2(code, pop, location);
			count++;
			cin.clear();
		}
		else if (count == 2)
		{
			count = 0;
			cin.clear();
		}
	}
	//Input checking
	if (code == -1 || pop == -1 || location == "-1" || location == "")
	{
		cout << "Incomplete record. Returning to menu." << endl;
		return;
	}
}

void erase(AVLTree &a)
{
	string c;
	int code, nodes = 0;
	bool found = false;
	istringstream ss;
	cout << "Enter a record code to delete: ";
	std::getline(std::cin, c);
	ss.str(c);
	ss >> code;
	found = a.find(code, nodes);
	if (found)
	{
		cout << "Deleting this record..." << endl;
		a.erase(code);
	}
	cout << "Nodes examined: " << nodes + 1 << endl;

}

void print(AVLTree &a)
{
	a.print();
}

void drawDebug(AVLTree &a)
{
	a.draw();
}