#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

namespace DatabaseImplementation
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

		Employee(void);

		void fire(void);
		void demote(const int);
		void promote(const int);
		void showInfo(void) const;
		void hire(const Employee::Position);

		int getId(void) const;
		void setId(const int id);

		std::string getFirstName(void) const;
		void setFirstName(const std::string&);

		std::string getMiddleName(void) const;
		void setMiddleName(const std::string&);
		
		std::string getLastName(void) const;
		void setLastName(const std::string&);
		
		int getAge(void) const;
		void setAge(const int);
		
		Sex getSex(void) const;
		void setSex(const Employee::Sex);

		int getPassportId(void) const;
		void setPassportId(const int);

		std::string getAddress(void) const;
		void setAddress(const std::string&);

		Position getPosition(void) const;
		void setPosition(const Employee::Position);

		int getSalary(void) const;
		void setSalary(const int);

		void setIsHired(bool);
		bool getIsHired(void) const;


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