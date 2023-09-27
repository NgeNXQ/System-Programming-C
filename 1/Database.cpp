#include "Database.h"
#include "Employee.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace LibraryDatabase
{
	Database::Database()
	{
		this->index = 0;
	}

	Database::~Database()
	{
#ifdef HEAP
		for (int i = 0; i < index; ++i)
			delete employees[i];
#endif
	}

	Employee& Database::addEmployee(std::string firstName, std::string middleName, std::string lastName, Employee::Position position)
	{
		if (this->index + 1 < this->CAPACITY)
		{
#ifdef STACK
			Employee& newEmployee = this->employees[this->index++];
			newEmployee.setFirstName(firstName);
			newEmployee.setMiddleName(middleName);
			newEmployee.setLastName(lastName);
			newEmployee.SetId(this->index);
			newEmployee.hire(position);
			return newEmployee;
#endif // STACK

#ifdef HEAP
			employees[index] = new Employee();
			*(employees[index - 1]).setFirstName(firstName);
			*(employees[index - 1]).setMiddleName(middleName);
			*(employees[index - 1]).setLastName(lastName);
			*(employees[index - 1]).SetId(this->index);
			*(employees[index - 1]).hire(position);
			return *(employees[index - 1]);
#endif // HEAP
		}

		std::cerr << "There is no more room to add the new employee!" << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(int employeeId)
	{
		for (int i = 0; i < index; ++i) 
		{
#ifdef STACK
			if (this->employees[i].getId() == employeeId)
				return this->employees[i];
#endif // STACK

#ifdef HEAP
			if (this->*(employees[index]).getId() == employeeId)
				return this->*(employees[index]);
#endif // STACK
			
		}

		std::cerr << "No employee with employee number " << employeeId << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(std::string firstName, std::string middleName, std::string lastName)
	{
		for (int i = 0; i < index; ++i) 
		{
#ifdef STACK
			if (this->employees[i].getFirstName() == firstName && this->employees[i].getMiddleName() == middleName && this->employees[i].getLastName() == lastName)
				return this->employees[i];
#endif // STACK

#ifdef HEAP
			if (this->*(employees[index]).getFirstName() == firstName && this->*(employees[index]).getMiddleName() == middleName && this->*(employees[index]).getLastName() == lastName)
				return this->*(employees[index]);
#endif // STACK
			
		}

		std::cerr << "No match with name " << lastName << " " << firstName << middleName << std::endl;
		throw std::exception();
	}

	void Database::showAll()
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			this->*(employees[index]).showInfo();
#endif // STACK
		}		
	}

	void Database::showCurrent()
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			if (this->employees[i].getIsHired())
				this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			if (this->*(employees[index]).getIsHired())
				this->*(employees[index]).showInfo();
#endif // STACK
			
		}
	}

	void Database::showFormer()
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			if (!this->employees[i].getIsHired())
				this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			if (!this->*(employees[index]).getIsHired())
				this->*(employees[index]).showInfo();
#endif // STACK

		}
	}
}