#include "Flags.h"
#include "Database.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace LibraryDatabase;

void clear(void);
int displayMenu(void);
void hire(Database&);
void fire(Database&);
void edit(Database&);
void demote(Database&);
void promote(Database&);
int readIntInput(const std::string&, const int, const int);

int main(void)
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

void hire(Database& const database)
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

	const unsigned char positionId = readIntInput("Employee position: ", 1, 7);

	try 
	{
		clear();
		database.addEmployee(firstName, middleName, lastName, (Employee::Position)positionId);
		std::cout << "Employee has been added." << std::endl;
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to add new employee!" << std::endl;
	}
}

void fire(Database& database)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

	try 
	{
		clear();
		database.getEmployee(employeeNumber).fire();
		std::cout << "Employee " << employeeNumber << " has been terminated." << std::endl;
	}
	catch (std::exception ex) 
	{
		std::cerr << "Unable to terminate employee!" << std::endl;
	}
}

void promote(Database& database)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
	int raiseAmount = readIntInput("How much of a raise: ", 0, std::numeric_limits<int>::max());

	try 
	{
		clear();
		database.getEmployee(employeeNumber).promote(raiseAmount);
		std::cout << "Employee has been promoted." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to promote employee!" << std::endl;
	}
}

void demote(Database& database)
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
	int reduceAmount = readIntInput("How much of a reduce: ", 0, std::numeric_limits<int>::max());

	try
	{
		clear();
		database.getEmployee(employeeNumber).demote(reduceAmount);
		std::cout << "Employee has been demoted." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to demote employee!" << std::endl;
	}
}

void edit(Database& database) 
{
	int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

	try
	{
		Employee& employee = database.getEmployee(employeeNumber);

		const int age = readIntInput("Employee age: ", 18, 100);
		employee.setAge(age);

		const unsigned char sex = readIntInput("Employee sex? Enter 0 for Male, 1 for Female: ", 0, 1);
		employee.setSex((Employee::Sex)sex);

		const int passportId = readIntInput("Employee passport ID: ", 0, std::numeric_limits<int>::max());
		employee.setPassportId(passportId);

		std::string address;
		std::cout << "Employee address: ";
		std::cin.ignore();
		std::getline(std::cin, address);
		employee.setAddress(address);

		const unsigned char positionId = readIntInput("Employee position: ", 1, 7);
		employee.setPosition((Employee::Position)positionId);

		const int salary = readIntInput("Employee salary: ", 0, std::numeric_limits<int>::max());
		employee.setSalary(salary);

		clear();
		std::cout << "Employee has been updated." << std::endl;
	}
	catch (std::exception ex)
	{
		std::cerr << "Unable to find specified employee!" << std::endl;
	}
}

int readIntInput(const std::string& const inputInvitation, const int min, const int max)
{
	int result;
	std::string userInput;

	while (true) 
	{
		std::cout << inputInvitation;
		std::cin >> userInput;

		if (!userInput.empty() &&
			(userInput[0] == '-' || (userInput[0] >= '0' && userInput[0] <= '9')) &&
			(userInput.find_first_not_of("0123456789", 1) == std::string::npos))
		{
			result = std::stoi(userInput);

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

void clear(void)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}