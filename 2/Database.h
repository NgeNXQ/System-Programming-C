#ifndef DATABASE_H
#define DATABASE_H

#include "Flags.h"
#include "Employee.h"

namespace LibraryDatabase 
{
	class Database
	{
	public:
		Database(void);
		~Database(void);

		Employee& addEmployee(const std::string& firstName, const std::string& middleName, const std::string& lastName, const Employee::Position position);

		Employee& getEmployee(const int id);
		Employee& getEmployee(const std::string& firstName, const std::string& middleName, const std::string& lastName);

		void showAll(void);
		void showCurrent(void);
		void showFormer(void);

	private:
		static const int CAPACITY = 50;
		int index;

#ifdef STACK
		Employee employees[CAPACITY];
#endif //STACK

#ifdef HEAP
		Employee** employees;
#endif //HEAP
	};
}

#endif // DATABASE_H