<<<<<<< Updated upstream
// Labwork2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
=======
﻿#include "Flags.h"
#include "Database.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace LibraryDatabase;

void clear();
int displayMenu();
void hire(Database&);
void fire(Database&);
void edit(Database&);
void demote(Database&);
void promote(Database&);
int readIntInput(const std::string&, int, int);

int main()
{
#ifdef STACK
	Database employeeDB;
#endif // STACK

#ifdef HEAP
	Database* employeeDB = new Database();
#endif // HEAP

	bool done = false;

	while (!done)
	{
		switch (displayMenu())
		{
		case 1:
#ifdef STACK
			hire(employeeDB);
#endif // STACK

#ifdef HEAP
			hire(*employeeDB);
#endif // HEAP
			break;
		case 2:
#ifdef STACK
			fire(employeeDB);
#endif // STACK

#ifdef HEAP
			fire(*employeeDB);
#endif // HEAP
			break;
		case 3:
#ifdef STACK
			promote(employeeDB);
#endif // STACK

#ifdef HEAP
			promote(*employeeDB);
#endif // HEAP
			break;
		case 4:
#ifdef STACK
			demote(employeeDB);
#endif // STACK

#ifdef HEAP
			demote(*employeeDB);
#endif // HEAP
			break;
		case 5:
			clear();
#ifdef STACK
			employeeDB.showAll();
#endif // STACK

#ifdef HEAP
			employeeDB->showAll();
#endif // HEAP
			break;
		case 6:
			clear();
#ifdef STACK
			employeeDB.showCurrent();
#endif // STACK

#ifdef HEAP
			employeeDB->showCurrent();
#endif // HEAP
			break;
		case 7:
			clear();
#ifdef STACK
			employeeDB.showFormer();
#endif // STACK

#ifdef HEAP
			employeeDB->showFormer();
#endif // HEAP	
			break;
		case 8:
#ifdef STACK
			edit(employeeDB);
#endif // STACK

#ifdef HEAP
			edit(*employeeDB);
#endif // HEAP
			break;
		case 0:
			done = true;
			break;
		default:
			std::cerr << "Unknown command." << std::endl;
		}
	}

#ifdef HEAP
	delete employeeDB;
#endif // HEAP

	return EXIT_SUCCESS;
}

int displayMenu()
{
	int choice;

	std::cout << std::endl;
	std::cout << "Employee Database" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "1) Hire a new employee" << std::endl;
	std::cout << "2) Fire an employee" << std::endl;
	std::cout << "3) Promote an employee" << std::endl;
	std::cout << "4) Demote an employee" << std::endl;
	std::cout << "5) List all employees" << std::endl;
	std::cout << "6) List all current employees" << std::endl;
	std::cout << "7) List all previous employees" << std::endl;
	std::cout << "8) Edit employee record" << std::endl;
	std::cout << "0) Quit" << std::endl;
	std::cout << std::endl;

	std::cout << "---> ";
	std::cin >> choice;

	return choice;
}

void hire(Database& inDB)
{
	std::string firstName;
	std::string middleName;
	std::string lastName;

	std::cout << "Last name: ";
	std::cin >> lastName;
	std::cout << "First name: ";
	std::cin >> firstName;
	std::cout << "Middle name: ";
	std::cin >> middleName;

	unsigned char positionId = readIntInput("Employee position: ", 1, 7);

	try 
	{
		clear();
		inDB.addEmployee(firstName, middleName, lastName, (Employee::Position)positionId);
		std::cout << "Employee has been added." << std::endl;
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to add new employee!" << std::endl;
	}
}

void fire(Database& inDB)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

	try 
	{
		clear();
		inDB.getEmployee(employeeNumber).fire();
		std::cout << "Employee " << employeeNumber << " has been terminated." << std::endl;
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to terminate employee!" << std::endl;
	}
}

void promote(Database& inDB)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
	int raiseAmount = readIntInput("How much of a raise: ", 0, std::numeric_limits<int>::max());

	try 
	{
		clear();
		inDB.getEmployee(employeeNumber).promote(raiseAmount);
		std::cout << "Employee has been promoted." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to promote employee!" << std::endl;
	}
}

void demote(Database& inDB)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
	int reduceAmount = readIntInput("How much of a reduce: ", 0, std::numeric_limits<int>::max());

	try
	{
		clear();
		inDB.getEmployee(employeeNumber).demote(reduceAmount);
		std::cout << "Employee has been demoted." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to demote employee!" << std::endl;
	}
}

void edit(Database& inDB) 
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

	try
	{
		Employee& emp = inDB.getEmployee(employeeNumber);

		int age = readIntInput("Employee age: ", 18, 100);
		emp.setAge(age);

		unsigned char sex = readIntInput("Employee sex? Enter 0 for Male, 1 for Female: ", 0, 1);
		emp.setSex((Employee::Sex)sex);

		int passportId = readIntInput("Employee passport ID: ", 0, std::numeric_limits<int>::max());
		emp.setPassportId(passportId);

		std::string address;
		std::cout << "Employee address: ";
		std::cin.ignore();
		std::getline(std::cin, address);
		emp.setAddress(address);

		unsigned char positionId = readIntInput("Employee position: ", 1, 7);
		emp.setPosition((Employee::Position)positionId);

		int salary = readIntInput("Employee salary: ", 0, std::numeric_limits<int>::max());
		emp.setSalary(salary);

		clear();
		std::cout << "Employee has been updated." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to find specified employee!" << std::endl;
	}
}

int readIntInput(const std::string& inputInvitation, int min, int max)
{
	std::string userInput;

	while (true) 
	{
		std::cout << inputInvitation;
		std::cin >> userInput;

		if (!userInput.empty() &&
			(userInput[0] == '-' || (userInput[0] >= '0' && userInput[0] <= '9')) &&
			(userInput.find_first_not_of("0123456789", 1) == std::string::npos))
		{
			int result = std::stoi(userInput);

			if (result >= min && result <= max)
				return result;
			else 
				std::cout << "Input is not within the specified range. [" << min << ";" << max << "]." << std::endl;
		}
		else 
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void clear()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
>>>>>>> Stashed changes
