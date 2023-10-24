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

		void hire(void);
		void fire(void);
		void demote(void);
		void promote(void);
		void showInfo(void);

		int getId(void);
		void setId(const int);

		std::string getFirstName(void);
		void setFirstName(const std::string&);

		std::string getMiddleName(void);
		void setMiddleName(const std::string&);
		
		std::string getLastName(void);
		void setLastName(const std::string&);
		
		int getAge(void);
		void setAge(const int);
		
		Sex getSex(void);
		void setSex(const Employee::Sex);

		int getPassportId(void);
		void setPassportId(const int);

		std::string getAddress(void);
		void setAddress(const std::string&);

		Position getPosition(void);
		void setPosition(const Employee::Position);

		int getSalary(void);
		void setSalary(const int);

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