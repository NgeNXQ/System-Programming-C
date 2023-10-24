#ifndef DATABASE_H
#define DATABASE_H

#include "Flags.h"

namespace LibraryDatabase 
{
	template <typename T>
	class Database
	{
	public:
		//Database(void);
		//~Database(void);

		enum class Operation: unsigned char
		{
			HIRE,
			FIRE,
			EDIT,
			DEMOTE,
			PROMOTE
		};

		//T& getRecord(const int);
		//void addRecord(T* const);
		//void printRecords(bool(*condition)(const T&));
		//void performOperation(const int, const Database::Operation);

	private:
		static const int CAPACITY = 50;
		int index;

#ifdef STACK
		T records[CAPACITY];
#endif //STACK

#ifdef HEAP
		T** records;
#endif //HEAP
	};
}

#endif // DATABASE_H