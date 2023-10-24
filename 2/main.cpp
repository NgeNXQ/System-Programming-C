#include "Flags.h"
#include "Database.h"
#include "Employee.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

using namespace LibraryDatabase;

//void clear(void);
//int readIntInput(const std::string&, const int, const int);

int main(void)
{
#ifdef STACK
	Database<Employee> employeeDB;
#endif // STACK

#ifdef HEAP
	Database<Employee>* employeeDB = new Database<Employee>();
#endif // HEAP



#ifdef HEAP
	delete employeeDB;
#endif // HEAP

	return EXIT_SUCCESS;
}

//int displayMenu()
//{
//	int choice;
//
//	std::cout << std::endl;
//	std::cout << "Employee Database" << std::endl;
//	std::cout << "-----------------" << std::endl;
//	std::cout << "1) Hire a new employee" << std::endl;
//	std::cout << "2) Fire an employee" << std::endl;
//	std::cout << "3) Promote an employee" << std::endl;
//	std::cout << "4) Demote an employee" << std::endl;
//	std::cout << "5) List all employees" << std::endl;
//	std::cout << "6) List all current employees" << std::endl;
//	std::cout << "7) List all previous employees" << std::endl;
//	std::cout << "8) Edit employee record" << std::endl;
//	std::cout << "0) Quit" << std::endl;
//	std::cout << std::endl;
//
//	std::cout << "---> ";
//	std::cin >> choice;
//
//	return choice;
//}
//
//int readIntInput(const std::string& inputInvitation, const int min, const int max)
//{
//	int result;
//	std::string userInput;
//
//	while (true) 
//	{
//		std::cout << inputInvitation;
//		std::cin >> userInput;
//
//		if (!userInput.empty() &&
//			(userInput[0] == '-' || (userInput[0] >= '0' && userInput[0] <= '9')) &&
//			(userInput.find_first_not_of("0123456789", 1) == std::string::npos))
//		{
//			result = std::stoi(userInput);
//
//			if (result >= min && result <= max)
//				return result;
//			else 
//				std::cout << "Input is not within the specified range. [" << min << ";" << max << "]." << std::endl;
//		}
//		else 
//			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
//
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	}
//}
//
//void clear(void)
//{
//#ifdef _WIN32
//	system("cls");
//#else
//	system("clear");
//#endif
//}