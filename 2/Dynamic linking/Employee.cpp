#include <stdexcept>
#include <iostream>
#include <string>
#include "Employee.h"

namespace DatabaseImplementation
{
	Employee::Employee()
	{
		this->age = -1;
		this->salary = 0;
		this->address = "";
		this->lastName = "";
		this->firstName = "";
		this->middleName = "";
		this->isHired = false;
		this->passportId = 0;
		this->position = Position::Undefined;
	}

	void Employee::promote(const int raiseAmount = 100)
	{
		this->setSalary(this->getSalary() + raiseAmount);
	}

	void Employee::demote(const int reduceAmount = 100)
	{
		this->setSalary(this->getSalary() - reduceAmount);
	}

	void Employee::hire(const Employee::Position position)
	{
		if (this->isHired)
		{
			std::cerr << "Employee has already been hired!" << std::endl;
			throw std::exception();
		}

		this->isHired = true;
		this->position = position;
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

	void Employee::showInfo(void) const
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

	int Employee::getId(void) const
	{
		return this->id;
	}

	void Employee::setId(const int id)
	{
		if (id > 0)
		{
			this->id = id;
		}
		else
		{
			std::cerr << "Invalid input value. ID must be greater than 0." << std::endl;
			throw std::exception();
		}
	}

	std::string Employee::getFirstName(void) const 
	{
		return this->firstName;
	}

	void Employee::setFirstName(const std::string& firstName)
	{
		if (!firstName.empty())
		{
			this->firstName = firstName;
		}
		else
		{
			std::cerr << "Invalid input value. The string must contain at least one character." << std::endl;
			throw std::exception();
		}
	}

	std::string Employee::getMiddleName(void) const
	{
		return this->middleName;
	}

	void Employee::setMiddleName(const std::string& middleName)
	{
		if (!middleName.empty())
		{
			this->middleName = middleName;
		}
		else
		{
			std::cerr << "Invalid input value. The string must contain at least one character." << std::endl;
			throw std::exception();
		}
	}

	std::string Employee::getLastName(void) const
	{
		return this->lastName;
	}

	void Employee::setLastName(const std::string& lastName)
	{
		if (!lastName.empty())
		{
			this->lastName = lastName;
		}
		else
		{
			std::cerr << "Invalid input value. The string must contain at least one character." << std::endl;
			throw std::exception();
		}
	}

	int Employee::getAge(void) const
	{
		return this->age;
	}

	void Employee::setAge(const int age)
	{
		if (age > 0)
		{
			this->age = age;
		}	
		else
		{
			std::cerr << "Invalid input value. Age must be greater than 0." << std::endl;
			throw std::exception();
		}
	}

	Employee::Sex Employee::getSex(void) const
	{
		return this->sex;
	}

	void Employee::setSex(const Employee::Sex sex)
	{
		this->sex = sex;
	}

	int Employee::getPassportId(void) const
	{
		return this->passportId;
	}

	void Employee::setPassportId(const int passportId)
	{
		this->passportId = passportId;
	}

	std::string Employee::getAddress(void) const
	{
		return this->address;
	}

	void Employee::setAddress(const std::string& address)
	{
		if (!address.empty())
		{
			this->address = address;
		}
		else
		{
			std::cerr << "Invalid input value. The string must contain at least one character." << std::endl;
			throw std::exception();
		}
	}
	
	Employee::Position Employee::getPosition(void) const
	{
		return this->position;
	}

	void Employee::setPosition(const Employee::Position position)
	{
		this->position = position;
	}

	int Employee::getSalary(void) const
	{
		return this->salary;
	}

	void Employee::setSalary(const int newSalary)
	{
		if (this->isHired)
		{
			if (newSalary > 0)
			{
				this->salary = newSalary;
			}
			else
			{
				std::cerr << "Invalid input value. Salary must be greater than or equal to 0." << std::endl;
				throw std::exception();
			}
		}
		else
		{
			std::cerr << "Employee is terminated!" << std::endl;
			throw std::exception();
		}
	}
	
	bool Employee::getIsHired(void) const
	{
		return this->isHired;
	}

	void Employee::setIsHired(bool isHired)
	{
		this->isHired = isHired;
	}
}