#ifndef DATABASEIO_H
#define DATABASEIO_H

#include "Database.h"

namespace DatabaseImplementation
{
	class DatabaseIO
	{
	public:
		enum class Operation : unsigned char
		{
			EXIT,
			HIRE,
			FIRE,
			PROMOTE,
			DEMOTE,
			ALL,
			CURRENT,
			FORMER,
			EDIT
		};

		static void clear(void);
		static void terminalUIUpdate(void);
		static int terminalUIReadInput(void);
		static void terminalUISetup(Database* const database);
		static void hire(Database* const database);
		static void fire(Database* const database);
		static void edit(Database* const database);
		static void demote(Database* const database);
		static void promote(Database* const database);
		static int readIntInput(const std::string&, const int, const int);

	private:
		static Database* database;
	};
}

#endif // DATABASEIO_H
