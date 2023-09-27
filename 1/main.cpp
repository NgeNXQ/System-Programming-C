#define STACK
//#define HEAP

#include <iostream>
#include <stdexcept>
#include <string>
#include "Database.h"

using namespace LibraryDatabase;

void clear();
int displayMenu();
void hire(Database& inDB);
void fire(Database& inDB);
void edit(Database& inDB);
void demote(Database& inDB);
void promote(Database& inDB);

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
			clear();
#ifdef STACK
			employeeDB.showAll();
#endif // STACK

#ifdef HEAP
			employeeDB->showAll();
#endif // HEAP
			break;
		case 5:
			clear();
#ifdef STACK
			employeeDB.showCurrent();
#endif // STACK

#ifdef HEAP
			employeeDB->showCurrent();
#endif // HEAP
			break;
		case 6:
			clear();
#ifdef STACK
			employeeDB.showFormer();
#endif // STACK

#ifdef HEAP
			employeeDB->showFormer();
#endif // HEAP	
			break;
		case 7:
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
	std::cout << "4) List all employees" << std::endl;
	std::cout << "5) List all current employees" << std::endl;
	std::cout << "6) List all previous employees" << std::endl;
	std::cout << "7) Edit employee record" << std::endl;
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
	unsigned char positionId;

	std::cout << "Last name: ";
	std::cin >> lastName;
	std::cout << "First name: ";
	std::cin >> firstName;
	std::cout << "Middle name: ";
	std::cin >> middleName;

	std::cout << "Employee position?\n"
		<< "1 for Librarian,\n"
		<< "2 for Librarian Assistant,\n"
		<< "3 for System Administrator,\n"
		<< "4 for Director,\n"
		<< "5 for Security Officer,\n"
		<< "6 for Secretary,\n"
		<< "7 for Cleaner\n"
		<< "Enter: ";

	std::cin >> positionId;

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
	int employeeNumber;
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;

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
	int employeeNumber;
	int raiseAmount;
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;
	std::cout << "How much of a raise: ";
	std::cin >> raiseAmount;

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
	int employeeNumber;
	int reduceAmount;
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;
	std::cout << "How much of a reduce: ";
	std::cin >> reduceAmount;

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
	int employeeNumber;
	std::cout << "Employee number: ";
	std::cin >> employeeNumber;

	try
	{
		Employee& emp = inDB.getEmployee(employeeNumber);

		int age;
		std::cout << "Employee age: ";
		std::cin >> age;
		emp.setAge(age);

		unsigned char sex;
		std::cout << "Employee sex? Enter 0 for Male, 1 for Female: ";
		std::cin >> sex;
		emp.SetSex((Employee::Sex)sex);

		int passportId;
		std::cout << "Employee passport ID: ";
		std::cin >> passportId;
		emp.setPassportId(passportId);

		std::string address;
		std::cout << "Employee address: ";
		std::cin.ignore();
		std::getline(std::cin, address);
		emp.setAddress(address);

		unsigned char positionId;
		std::cout << "Employee position?\n"
				  << "1 for Librarian,\n"
				  << "2 for Librarian Assistant,\n"
				  << "3 for System Administrator,\n"
				  << "4 for Director,\n"
				  << "5 for Security Officer,\n"
				  << "6 for Secretary,\n"
				  << "7 for Cleaner\n"
				  << "Enter: ";

		std::cin >> positionId;
		emp.setPositionId((Employee::Position)positionId);

		double salary;
		std::cout << "Employee salary: ";
		std::cin >> salary;
		emp.setSalary(salary);

		clear();
		std::cout << "Employee has been updated." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to find specified employee!" << std::endl;
	}
}

//int intInput(int min, int max)
//{
//
//}

void clear()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}