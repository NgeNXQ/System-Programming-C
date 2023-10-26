#include "Database.h"
#include "DatabaseIO.h"

using namespace DatabaseImplementation;

int main(void)
{
	Database* const database = new Database();

	DatabaseIO::terminalUISetup(database);

	while (1)
	{
		DatabaseIO::terminalUIUpdate();

		if (DatabaseIO::terminalUIReadInput() == -1)
			break;
	}

	delete database;

	return EXIT_SUCCESS;
}