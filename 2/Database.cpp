#include "Flags.h"
#include "Database.h"
#include "Employee.h"
#include <iostream>
#include <stdexcept>
#include <string>

namespace LibraryDatabase
{
	Database::Database(void)
	{
		this->index = 0;

#ifdef HEAP
		employees = new Employee*[CAPACITY];
#endif
	}

	Database::~Database(void)
	{
#ifdef HEAP
		for (int i = 0; i < index; ++i)
			delete employees[i];

		delete[] employees;
#endif
	}

	Employee& Database::addEmployee(const std::string& firstName, const std::string& middleName, const std::string& lastName, const Employee::Position position)
	{
		if (this->index < this->CAPACITY)
		{
#ifdef STACK
			Employee& newEmployee = this->employees[this->index++];
			newEmployee.setFirstName(firstName);
			newEmployee.setMiddleName(middleName);
			newEmployee.setLastName(lastName);
			newEmployee.setId(this->index);
			newEmployee.hire(position);
			return newEmployee;
#endif // STACK

#ifdef HEAP
			this->employees[this->index] = new Employee();
			this->employees[this->index]->setFirstName(firstName);
			this->employees[this->index]->setMiddleName(middleName);
			this->employees[this->index]->setLastName(lastName);
			this->employees[this->index]->setId(this->index + 1);
			this->employees[this->index]->hire(position);
			++this->index;
			return *(this->employees[this->index - 1]);
#endif // HEAP
		}

		std::cerr << "There is no more room to add the new employee!" << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(const int employeeId)
	{
		for (int i = 0; i < index; ++i) 
		{
#ifdef STACK
			if (this->employees[i].getId() == employeeId)
				return this->employees[i];
#endif // STACK

#ifdef HEAP
			if (this->employees[i]->getId() == employeeId)
				return *(this->employees[i]);
#endif // STACK
			
		}

		std::cerr << "No employee with employee number " << employeeId << std::endl;
		throw std::exception();
	}

	Employee& Database::getEmployee(const std::string& firstName, const std::string& middleName, const std::string& lastName)
	{
		for (int i = 0; i < index; ++i) 
		{
#ifdef STACK
			if (this->employees[i].getFirstName() == firstName && this->employees[i].getMiddleName() == middleName && this->employees[i].getLastName() == lastName)
				return this->employees[i];
#endif // STACK

#ifdef HEAP
			if (this->employees[i]->getFirstName() == firstName && this->employees[i]->getMiddleName() == middleName && this->employees[i]->getLastName() == lastName)
				return *(this->employees[i]);
#endif // STACK
			
		}

		std::cerr << "No match with name " << lastName << " " << firstName << middleName << std::endl;
		throw std::exception();
	}

	void Database::showAll(void)
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			this->employees[i]->showInfo();
#endif // STACK
		}		
	}

	void Database::showCurrent(void)
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			if (this->employees[i].getIsHired())
				this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			if (this->employees[i]->getIsHired())
				this->employees[i]->showInfo();
#endif // STACK
			
		}
	}

	void Database::showFormer(void)
	{
		for (int i = 0; i < this->index; ++i)
		{
#ifdef STACK
			if (!this->employees[i].getIsHired())
				this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			if (!this->employees[i]->getIsHired())
				this->employees[i]->showInfo();
#endif // STACK

		}
	}
}