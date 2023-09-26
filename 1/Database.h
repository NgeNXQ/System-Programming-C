#include "Employee.h"

namespace LibraryDatabase 
{
	class Database
	{
	public:
		Database();

		Employee& addEmployee(std::string firstName, std::string middleName, std::string lastName);

		Employee& getEmployee(int id);
		Employee& getEmployee(std::string firstName, std::string middleName, std::string lastName);

		void showAll();
		void showCurrent();
		void showFormer();

	private:
		static const int CAPACITY = 100;
		Employee employees[CAPACITY];
		int index;
	};
}