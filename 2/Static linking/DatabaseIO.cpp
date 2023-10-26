#include <iostream>
#include <string>
#include <limits>
#include "Employee.h"
#include "Database.h"
#include "DatabaseIO.h"

namespace DatabaseImplementation
{
	Database* DatabaseIO::database = nullptr;

	void DatabaseIO::terminalUISetup(Database* const database)
	{
		if (database == nullptr)
		{
			std::cerr << "database is NULL" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			DatabaseIO::database = database;
		}
	}

	int DatabaseIO::terminalUIReadInput(void)
	{
		int choice = readIntInput("---> ", 0, 8);

		switch ((DatabaseIO::Operation)choice)
		{
		case DatabaseIO::Operation::HIRE:
			hire(DatabaseIO::database);
			break;
		case DatabaseIO::Operation::FIRE:
			fire(DatabaseIO::database);
			break;
		case DatabaseIO::Operation::PROMOTE:
			promote(DatabaseIO::database);
			break;
		case DatabaseIO::Operation::DEMOTE:
			demote(DatabaseIO::database);
			break;
		case DatabaseIO::Operation::ALL:
			clear();
			database->showAll();
			break;
		case DatabaseIO::Operation::CURRENT:
			clear();
			database->showCurrent();
			break;
		case DatabaseIO::Operation::FORMER:
			clear();
			database->showFormer();
			break;
		case DatabaseIO::Operation::EDIT:
			edit(DatabaseIO::database);
			break;
		case DatabaseIO::Operation::EXIT:
			return -1;
			break;
		default:
			std::cerr << "Unknown command." << std::endl;
			break;
		}

		return choice;
	}

	void DatabaseIO::terminalUIUpdate(void)
	{
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
	}

	void DatabaseIO::hire(Database* const database)
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

#ifdef STACK
		Employee newEmployee;
		newEmployee.setLastName(lastName);
		newEmployee.setFirstName(firstName);
		newEmployee.setMiddleName(middleName);
		newEmployee.setPosition((Employee::Position)positionId);
#endif // STACK

#ifdef HEAP
		Employee* newEmployee = new Employee();
		newEmployee->setLastName(lastName);
		newEmployee->setFirstName(firstName);
		newEmployee->setMiddleName(middleName);
		newEmployee->setPosition((Employee::Position)positionId);
#endif // HEAP

		try
		{
			clear();
			database->add(newEmployee);
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	void DatabaseIO::fire(Database* const database)
	{
		const int employeeId = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

		try
		{
			clear();
			database->get(employeeId).fire();
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	void DatabaseIO::edit(Database* const database)
	{
		int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());

		try
		{
			Employee& employee = database->get(employeeNumber);

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
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	void DatabaseIO::demote(Database* const database)
	{
		const int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
		const int reduceAmount = readIntInput("How much of a reduce: ", 0, std::numeric_limits<int>::max());

		try
		{
			clear();
			database->get(employeeNumber).demote(reduceAmount);
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	void DatabaseIO::promote(Database* const database)
	{
		const int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
		const int raiseAmount = readIntInput("How much of a raise: ", 0, std::numeric_limits<int>::max());

		try
		{
			clear();
			database->get(employeeNumber).promote(raiseAmount);
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}

	int DatabaseIO::readIntInput(const std::string& inputInvitation, const int min, const int max)
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

	void DatabaseIO::clear(void)
	{
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}
}