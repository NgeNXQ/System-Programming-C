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

	Employee& Database::addEmployee(std::string firstName, std::string middleName, std::string lastName)
	{
		if (this->index + 1 < this->CAPACITY)
		{
			Employee& newEmployee = this->employees[this->index++];
			newEmployee.setFirstName(firstName);
			newEmployee.setMiddleName(middleName);
			newEmployee.setLastName(lastName);
			newEmployee.SetId(this->index++);
			newEmployee.hire();
			return newEmployee;
		}

		std::cerr << "There is no more room to add the new employee!" << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(int employeeId)
	{
		for (int i = 0; i < index; ++i) 
		{
			if (this->employees[i].getId() == employeeId)
				return this->employees[i];
		}

		std::cerr << "No employee with employee number " << employeeId << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(std::string firstName, std::string middleName, std::string lastName)
	{
		for (int i = 0; i < index; ++i) 
		{
			if (this->employees[i].getFirstName() == firstName && this->employees[i].getMiddleName() == middleName && this->employees[i].getLastName() == lastName) 
				return this->employees[i];
		}

		std::cerr << "No match with name " << lastName << " " << firstName << middleName << std::endl;
		throw std::exception();
	}

	void Database::showAll()
	{
		for (int i = 0; i < this->index; ++i) 
			this->employees[i].showInfo();
	}

	void Database::showCurrent()
	{
		for (int i = 0; i < this->index; ++i) 
		{
			if (this->employees[i].getIsHired()) 
				this->employees[i].showInfo();
		}
	}

	void Database::showFormer()
	{
		for (int i = 0; i < this->index; ++i) 
		{
			if (!this>employees[i].getIsHired()) 
				this->employees[i].showInfo();
		}
	}
}