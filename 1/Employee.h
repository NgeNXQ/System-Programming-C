#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

namespace LibraryDatabase
{
	class Employee 
	{
	public:
		enum class Sex : unsigned char
		{
			Male,
			Female
		};

		enum class Position : unsigned char
		{
			Undefined,
			Librarian, 
			LibrarianAssistant, 
			SystemAdministrator, 
			Director, 
			SecurityOfficer, 
			Secretary, 
			Cleaner
		};

		Employee();

		void promote(double raiseAmount);
		void demote(double reduceAmount);
		void hire(Position position);
		void fire();
		void showInfo();

		int getId();
		void setId(int id);

		std::string getFirstName();
		void setFirstName(std::string firstName);

		std::string getMiddleName();
		void setMiddleName(std::string middleName);
		
		std::string getLastName();
		void setLastName(std::string lastName);
		
		int getAge();
		void setAge(int age);
		
		Sex getSex();
		void setSex(Sex sex);

		int getPassportId();
		void setPassportId(int passportId);

		std::string getAddress();
		void setAddress(std::string address);

		Position getPosition();
		void setPosition(Position position);

		double getSalary();
		void setSalary(double newSalary);

		bool getIsHired();

	private:
		int id;
		Sex sex;
		std::string firstName;
		std::string middleName;
		std::string lastName;
		int age;
		int passportId;
		std::string address;
		Position position;
		double salary;
		bool isHired;
	};
}

#endif // EMPLOYEE_H