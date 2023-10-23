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

		void promote(const int raiseAmount);
		void demote(const int reduceAmount);
		void hire(const Employee::Position position);
		void fire(void);
		void showInfo(void);

		int getId(void);
		void setId(const int id);

		std::string getFirstName(void);
		void setFirstName(const std::string& firstName);

		std::string getMiddleName(void);
		void setMiddleName(const std::string& middleName);
		
		std::string getLastName(void);
		void setLastName(const std::string& lastName);
		
		int getAge(void);
		void setAge(const int age);
		
		Sex getSex(void);
		void setSex(const Employee::Sex sex);

		int getPassportId(void);
		void setPassportId(const int passportId);

		std::string getAddress(void);
		void setAddress(const std::string& address);

		Position getPosition(void);
		void setPosition(const Employee::Position position);

		int getSalary(void);
		void setSalary(const int newSalary);

		bool getIsHired(void);

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
		int salary;
		bool isHired;
	};
}

#endif // EMPLOYEE_H