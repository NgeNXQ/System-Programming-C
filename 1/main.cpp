#include <iostream>
#include <stdexcept>
#include <string>
#include "Database.h"

using namespace LibraryDatabase;

int displayMenu();
void hire(Database& inDB);
void fire(Database& inDB);
void promote(Database& inDB);
void demote(Database& inDB);

int main()
{
	Database employeeDB;
	bool done = false;

	while (!done) 
	{
		int selection = displayMenu();

		switch (selection) 
		{
		case 1:
			hire(employeeDB);
			break;
		case 2:
			fire(employeeDB);
			break;
		case 3:
			promote(employeeDB);
			break;
		case 4:
			employeeDB.showAll();
			break;
		case 5:
			employeeDB.showCurrent();
			break;
		case 6:
			employeeDB.showFormer();
			break;
		case 0:
			done = true;
			break;
		default:
			std::cerr << "Unknown command." << std::endl;
		}
	}

	return EXIT_SUCCESS;
}

int displayMenu()
{
	int selection;

	std::cout << std::endl;
	std::cout << "Employee Database" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "1) Hire a new employee" << std::endl;
	std::cout << "2) Fire an employee" << std::endl;
	std::cout << "3) Promote an employee" << std::endl;
	std::cout << "4) List all employees" << std::endl;
	std::cout << "5) List all current employees" << std::endl;
	std::cout << "6) List all previous employees" << std::endl;
	std::cout << "0) Quit" << std::endl;
	std::cout << std::endl;

	std::cout << "---> ";
	std::cin >> selection;

	return selection;
}

void hire(Database& inDB)
{
	std::string firstName;
	std::string middleName;
	std::string lastName;

	std::cout << "Last name? ";
	std::cin >> lastName;
	std::cout << "First name? ";
	std::cin >> firstName;
	std::cout << "Middle name? ";
	std::cin >> middleName;

	try 
	{
		inDB.addEmployee(firstName, middleName, lastName);
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to add new employee!" << std::endl;
	}
}

void fire(Database& inDB)
{
	int employeeNumber;
	std::cout << "Employee number? ";
	std::cin >> employeeNumber;

	try 
	{
		Employee& emp = inDB.getEmployee(employeeNumber);
		emp.fire();
		std::cout << "Employee " << employeeNumber << " has been terminated." << std::endl;
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to terminate employee!" << std::endl;
	}
}

void promote(Database& inDB)
{
	int employeeNumber;
	int raiseAmount;
	std::cout << "Employee number? ";
	std::cin >> employeeNumber;
	std::cout << "How much of a raise? ";
	std::cin >> raiseAmount;

	try 
	{
		Employee& emp = inDB.getEmployee(employeeNumber);
		emp.promote(raiseAmount);
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to promote employee!" << std::endl;
	}
}

void demote(Database& inDB)
{
	int employeeNumber;
	int reduceAmount;
	std::cout << "Employee number? ";
	std::cin >> employeeNumber;
	std::cout << "How much of a reduce? ";
	std::cin >> reduceAmount;

	try
	{
		Employee& emp = inDB.getEmployee(employeeNumber);
		emp.demote(reduceAmount);
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to demote employee!" << std::endl;
	}
}