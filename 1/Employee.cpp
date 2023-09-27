#include "Employee.h"
#include <stdexcept>
#include <iostream>
#include <string>

namespace LibraryDatabase 
{
	Employee::Employee()
	{
		this->firstName = "";
		this->middleName = "";
		this->lastName = "";
		this->age = -1;
		this->passportId = -1;
		this->address = "";
		this->positionId = Position::Undefined;
		this->salary = 0.0;
		this->isHired = false;
	}

	void Employee::promote(double raiseAmount = 100.0)
	{
		this->setSalary(this->getSalary() + raiseAmount);
	}

	void Employee::demote(double reduceAmount = 100.0)
	{
		this->setSalary(this->getSalary() - reduceAmount);
	}

	void Employee::hire(Position position)
	{
		if (this->isHired)
		{
			std::cerr << "Employee has already been hired!" << std::endl;
			throw std::exception();
		}

		this->isHired = true;
		this->positionId = position;
	}

	void Employee::fire()
	{
		if (!this->isHired)
		{
			std::cerr << "Employee has already been terminated!" << std::endl;
			throw std::exception();
		}

		this->salary = 0.0;
		this->isHired = false;
		this->positionId = Employee::Position::Undefined;
	}

	void Employee::showInfo()
	{
		std::cout << "Employee: " << this->getLastName() << ' ' << this->getFirstName() << ' ' << this->getMiddleName() << std::endl
				  << "Age: " << this->getAge() << std::endl
				  << "ID: " << this->getId() << std::endl
				  << (this->isHired ? "Current employee" : "Former employee") << std::endl
				  << "Salary: $" << this->getSalary() << std::endl
				  << "Position ID: " << this->getId() << std::endl
				  << "Passport ID: " << this->getPassportId() << std::endl
				  << "Address: " << this->getAddress() << std::endl << std::endl;
	}

	int Employee::getId()
	{
		return this->id;
	}

	void Employee::setId(int id)
	{
		if (id > 0)
			this->id = id;
		else
			std::cout << "Invalid input value. Age must be greater than 0." << std::endl;
	}

	std::string Employee::getFirstName() 
	{
		return this->firstName;
	}

	void Employee::setFirstName(std::string firstName)
	{
		if (!firstName.empty())
			this->firstName = firstName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	std::string Employee::getMiddleName()
	{
		return this->middleName;
	}

	void Employee::setMiddleName(std::string middleName)
	{
		if (!middleName.empty())
			this->middleName = middleName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	std::string Employee::getLastName()
	{
		return this->lastName;
	}

	void Employee::setLastName(std::string lastName)
	{
		if (!lastName.empty())
			this->lastName = lastName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	int Employee::getAge()
	{
		return this->age;
	}

	void Employee::setAge(int age)
	{
		if (age > 0)
			this->age = age;
		else
			std::cout << "Invalid input value. Age must be greater than 0." << std::endl;
	}

	Employee::Sex Employee::getSex()
	{
		return this->sex;
	}

	void Employee::SetSex(Sex sex)
	{
		this->sex = sex;
	}

	int Employee::getPassportId()
	{
		return this->passportId;
	}

	void Employee::setPassportId(int passportId)
	{
		this->passportId = passportId;
	}

	std::string Employee::getAddress()
	{
		return this->address;
	}

	void Employee::setAddress(std::string address)
	{
		if (!address.empty())
			this->address = address;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}
	
	Employee::Position Employee::getPositionId()
	{
		return this->positionId;
	}

	void Employee::setPositionId(Employee::Position positionId)
	{
		this->positionId = positionId;
	}

	double Employee::getSalary()
	{
		return this->salary;
	}

	void Employee::setSalary(double newSalary)
	{
		if (newSalary > 0)
			this->salary = newSalary;
		else
			std::cout << "Invalid input value. Salary must be greater than or equal to 0." << std::endl;
	}
	
	bool Employee::getIsHired()
	{
		return this->isHired;
	}
}