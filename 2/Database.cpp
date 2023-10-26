#include <iostream>
#include <stdexcept>
#include <string>
//#include "Flags.h"
#include "Database.h"
#include "Employee.h"

namespace DatabaseImplementation
{
	Database::Database()
	{
		this->index = 0;

#ifdef HEAP
		employees = new Employee*[CAPACITY];
#endif
	}

#ifdef HEAP

	Database::~Database()
	{
		for (int i = 0; i < index; ++i)
			delete employees[i];

		delete[] employees;
	}

#endif

#ifdef STACK

	void Database::add(Employee& newEmployee)
	{
		if (this->index + 1 < this->CAPACITY)
		{
			++this->index;
			newEmployee.setIsHired(1);
			newEmployee.setId(this->index);
			this->employees[this->index] = newEmployee;
		}
		else
		{
			std::cerr << "There is no more room to add the new employee!" << std::endl;
			throw std::exception();
		}
	}

#endif // STACK

#ifdef HEAP

	void Database::add(Employee* const newEmployee)
	{
		if (this->index + 1 < this->CAPACITY)
		{
			++this->index;
			newEmployee->setIsHired(1);
			newEmployee->setId(this->index);
			this->employees[this->index] = newEmployee;
		}
		else
		{
			std::cerr << "There is no more room to add the new employee!" << std::endl;
			throw std::exception();
		}
	}

#endif // HEAP

	Employee& Database::get(const int id)
	{
		if (this->index == 0 || id > this->index)
		{
			std::cerr << "Wrong employee ID!" << std::endl;
			throw std::exception();
		}

		for (int i = 1; i <= this->index; ++i)
		{
#ifdef STACK
			if (this->employees[i].getId() == id)
				return this->employees[i];
#endif // STACK

#ifdef HEAP
			if (this->employees[i]->getId() == id)
				return *(this->employees[i]);
#endif // HEAP	
		}
	}

	void Database::showAll(void) const
	{
		for (int i = 1; i <= this->index; ++i)
		{
#ifdef STACK
			this->employees[i].showInfo();
#endif // STACK

#ifdef HEAP
			this->employees[i]->showInfo();
#endif // STACK
		}
	}

	void Database::showCurrent(void) const
	{
		for (int i = 1; i <= this->index; ++i)
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

	void Database::showFormer(void) const
	{
		for (int i = 1; i <= this->index; ++i)
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
