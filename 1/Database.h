#include "Employee.h"

namespace LibraryDatabase 
{
	class Database
	{
	public:
		Database();
		~Database();

		Employee& addEmployee(std::string firstName, std::string middleName, std::string lastName, Employee::Position position);

		Employee& getEmployee(int id);
		Employee& getEmployee(std::string firstName, std::string middleName, std::string lastName);

		void showAll();
		void showCurrent();
		void showFormer();

	private:
		static const int CAPACITY = 100;
#ifdef STACK
		Employee employees[CAPACITY];
#endif //STACK

#ifdef HEAP
		Employee* employees[CAPACITY];
#endif //HEAP
		int index;
	};
}