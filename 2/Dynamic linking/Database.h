#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "Flags.h"
#include "Employee.h"

namespace DatabaseImplementation
{
	class Database
	{
	public:
		Database();

#ifdef HEAP
		~Database();
#endif // HEAP

#ifdef STACK
		void add(Employee&);
#endif // STACK

#ifdef HEAP
		void add(Employee* const);
#endif // HEAP

		Employee& get(const int);

		void showAll(void) const;
		void showFormer(void) const;
		void showCurrent(void) const;

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