#include "Employee.h"
#include <stdexcept>
#include <iostream>
#include <string>

namespace LibraryDatabase 
{
	Employee::Employee(void)
	{
		this->firstName = "";
		this->middleName = "";
		this->lastName = "";
		this->age = -1;
		this->passportId = -1;
		this->address = "";
		this->position = Position::Undefined;
		this->salary = 0;
		this->isHired = false;
	}

	//void hire(void);
	//void fire(void);
	//void demote(void);
	//void promote(void);
	//void showInfo(void);

	void Employee::hire(void)
	{
		if (this->isHired)
		{
			std::cerr << "Employee has already been hired!" << std::endl;
			throw std::exception();
		}

		this->isHired = true;
		this->position = position;
	}

	void Employee::promote(void)
	{
		int raiseAmount = 05;
		this->setSalary(this->getSalary() + raiseAmount);
	}

	void Employee::demote(void)
	{
		int reduceAmount = 05;
		this->setSalary(this->getSalary() - reduceAmount);
	}

	void Employee::fire(void)
	{
		if (!this->isHired)
		{
			std::cerr << "Employee has already been terminated!" << std::endl;
			throw std::exception();
		}

		this->salary = 0;
		this->isHired = false;
		this->position = Employee::Position::Undefined;
	}

	void Employee::showInfo(void)
	{
		std::cout << "Employee: " << this->getLastName() << ' ' << this->getFirstName() << ' ' << this->getMiddleName() << std::endl
				  << "Age: " << this->getAge() << std::endl
				  << "ID: " << this->getId() << std::endl
				  << (this->isHired ? "Current employee" : "Former employee") << std::endl
				  << "Salary: $" << this->getSalary() << std::endl
				  << "Position ID: " << (int)this->getPosition() << std::endl
				  << "Passport ID: " << this->getPassportId() << std::endl
				  << "Address: " << this->getAddress() << std::endl << std::endl;
	}

	int Employee::getId(void)
	{
		return this->id;
	}

	void Employee::setId(const int id)
	{
		if (id > 0)
			this->id = id;
		else
			std::cout << "Invalid input value. Age must be greater than 0." << std::endl;
	}

	std::string Employee::getFirstName(void) 
	{
		return this->firstName;
	}

	void Employee::setFirstName(const std::string& firstName)
	{
		if (!firstName.empty())
			this->firstName = firstName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	std::string Employee::getMiddleName(void)
	{
		return this->middleName;
	}

	void Employee::setMiddleName(const std::string& middleName)
	{
		if (!middleName.empty())
			this->middleName = middleName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	std::string Employee::getLastName(void)
	{
		return this->lastName;
	}

	void Employee::setLastName(const std::string& lastName)
	{
		if (!lastName.empty())
			this->lastName = lastName;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}

	int Employee::getAge(void)
	{
		return this->age;
	}

	void Employee::setAge(const int age)
	{
		if (age > 0)
			this->age = age;
		else
			std::cout << "Invalid input value. Age must be greater than 0." << std::endl;
	}

	Employee::Sex Employee::getSex(void)
	{
		return this->sex;
	}

	void Employee::setSex(const Employee::Sex sex)
	{
		this->sex = sex;
	}

	int Employee::getPassportId(void)
	{
		return this->passportId;
	}

	void Employee::setPassportId(const int passportId)
	{
		this->passportId = passportId;
	}

	std::string Employee::getAddress(void)
	{
		return this->address;
	}

	void Employee::setAddress(const std::string& address)
	{
		if (!address.empty())
			this->address = address;
		else
			std::cout << "Invalid input value. The string must contain at least one character." << std::endl;
	}
	
	Employee::Position Employee::getPosition(void)
	{
		return this->position;
	}

	void Employee::setPosition(const Employee::Position position)
	{
		this->position = position;
	}

	int Employee::getSalary(void)
	{
		return this->salary;
	}

	void Employee::setSalary(const int newSalary)
	{
		if (newSalary > 0)
			this->salary = newSalary;
		else
			std::cout << "Invalid input value. Salary must be greater than or equal to 0." << std::endl;
	}
	
	bool Employee::getIsHired(void)
	{
		return this->isHired;
	}
}