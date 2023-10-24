//#include <iostream>
//#include <string>
//#include <limits>
//#include "Database.h"
//#include "DatabaseAPI.h"
//
//namespace LibraryDatabase
//{
//	/*void DatabaseAPI::hire(Database* const database)
//	{
//		std::string firstName;
//		std::string middleName;
//		std::string lastName;
//
//		std::cout << "Last name: ";
//		std::cin >> lastName;
//		std::cout << "First name: ";
//		std::cin >> firstName;
//		std::cout << "Middle name: ";
//		std::cin >> middleName;
//
//		const unsigned char positionId = readIntInput("Employee position: ", 1, 7);
//
//		try
//		{
//			clear();
//			database->addEmployee(firstName, middleName, lastName, (Employee::Position)positionId);
//			std::cout << "Employee has been added." << std::endl;
//		}
//		catch (std::exception ex)
//		{
//			std::cerr << "Unable to add new employee!" << std::endl;
//		}
//	}
//
//	void DatabaseAPI::fire(Database* const database)
//	{
//		const int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
//
//		try
//		{
//			clear();
//			database->getEmployee(employeeNumber).fire();
//			std::cout << "Employee " << employeeNumber << " has been terminated." << std::endl;
//		}
//		catch (std::exception ex)
//		{
//			std::cerr << "Unable to terminate employee!" << std::endl;
//		}
//	}
//
//	static void edit(Database* const database)
//	{
//		int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
//
//		try
//		{
//			Employee& employee = database->getEmployee(employeeNumber);
//
//			const int age = readIntInput("Employee age: ", 18, 100);
//			employee.setAge(age);
//
//			const unsigned char sex = readIntInput("Employee sex? Enter 0 for Male, 1 for Female: ", 0, 1);
//			employee.setSex((Employee::Sex)sex);
//
//			const int passportId = readIntInput("Employee passport ID: ", 0, std::numeric_limits<int>::max());
//			employee.setPassportId(passportId);
//
//			std::string address;
//			std::cout << "Employee address: ";
//			std::cin.ignore();
//			std::getline(std::cin, address);
//			employee.setAddress(address);
//
//			const unsigned char positionId = readIntInput("Employee position: ", 1, 7);
//			employee.setPosition((Employee::Position)positionId);
//
//			const int salary = readIntInput("Employee salary: ", 0, std::numeric_limits<int>::max());
//			employee.setSalary(salary);
//
//			clear();
//			std::cout << "Employee has been updated." << std::endl;
//		}
//		catch (std::exception ex)
//		{
//			std::cerr << "Unable to find specified employee!" << std::endl;
//		}
//	}
//
//	static void demote(Database* const database)
//	{
//		const int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
//		const int reduceAmount = readIntInput("How much of a reduce: ", 0, std::numeric_limits<int>::max());
//
//		try
//		{
//			clear();
//			database->getEmployee(employeeNumber).demote(reduceAmount);
//			std::cout << "Employee has been demoted." << std::endl;
//		}
//		catch (std::exception ex)
//		{
//			std::cerr << "Unable to demote employee!" << std::endl;
//		}
//	}
//
//	static void promote(Database* const database)
//	{
//		const int employeeNumber = readIntInput("Employee number: ", 1, std::numeric_limits<int>::max());
//		const int raiseAmount = readIntInput("How much of a raise: ", 0, std::numeric_limits<int>::max());
//
//		try
//		{
//			clear();
//			database->getEmployee(employeeNumber).promote(raiseAmount);
//			std::cout << "Employee has been promoted." << std::endl;
//		}
//		catch (std::exception ex)
//		{
//			std::cerr << "Unable to promote employee!" << std::endl;
//		}
//	}*/
//}