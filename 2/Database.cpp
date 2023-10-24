#include <iostream>
#include <stdexcept>
#include "Flags.h"
#include "Database.h"

namespace LibraryDatabase
{
	//template <typename T>
	//Database<T>::Database(void)
	//{
//		this->index = 0;
//
//#ifdef HEAP
//		records = new T*[CAPACITY];
//#endif // HEAP
//
//		for (int i = 0; i < CAPACITY; ++i)
//			records[i] = nullptr;

		/*static_assert(std::is_member_function_pointer<decltype(&T::hire)>::value, "T does not have a hire member function");
		static_assert(std::is_member_function_pointer<decltype(&T::fire)>::value, "T does not have a fire member function");
		static_assert(std::is_member_function_pointer<decltype(&T::edit)>::value, "T does not have a edit member function");
		static_assert(std::is_member_function_pointer<decltype(&T::getId)>::value, "T does not have a getId member function");
		static_assert(std::is_member_function_pointer<decltype(&T::setId)>::value, "T does not have a setId member function");
		static_assert(std::is_member_function_pointer<decltype(&T::demote)>::value, "T does not have a demote member function");
		static_assert(std::is_member_function_pointer<decltype(&T::promote)>::value, "T does not have a promote member function");
		static_assert(std::is_member_function_pointer<decltype(&T::showInfo)>::value, "T does not have a showInfo member function");*/
	//}

	//template <typename T>
	//Database<T>::~Database(void)
	//{
//#ifdef HEAP
//		for (int i = 0; i < index; ++i)
//			delete records[i];
//
//		delete[] records;
//#endif // HEAP
	//}

	//template <typename T>
	//T& Database<T>::getRecord(const int id)
//	{
//		for (int i = 0; i < index; ++i)
//		{
//#ifdef STACK
//			if (this->records[i].getId() == id)
//				return this->records[i];
//#endif // STACK
//
//#ifdef HEAP
//			if (this->records[i]->getId() == id)
//				return *(this->records[i]);
//#endif // STACK
//
//		}
//
//		std::cerr << "No record with specified id." << id << std::endl;
//		throw std::exception();
//	}

	//template <typename T>
	//void Database<T>::addRecord(T* const newRecord)
//	{
//		if (newRecord == nullptr)
//		{
//			std::cerr << "newRecord is NULL." << std::endl;
//			throw std::exception();
//		}
//
//		if (this->index < CAPACITY)
//		{
//#ifdef STACK
//			this->records[this->index] = *newRecord;
//#endif // STACK
//
//#ifdef HEAP
//			this->records[this->index] = newRecord;
//#endif // HEAP
//
//			newRecord->setId(this->index++);
//		}
//		else
//		{
//			std::cerr << "There is no more room to add the new record!" << std::endl;
//			throw std::exception();
//		}
//	}

//	template <typename T>
//	void Database<T>::printRecords(bool(*condition)(const T&))
//	{
		//for (int i = 0; i < index; ++i)
		//{
		//	if (condition(this->records[i]))
		//		this->records[i].showInfo();
		//}
//	}

//	template <typename T>
//	void Database<T>::performOperation(const int id, const Database<T>::Operation operation)
//	{
		/*if (id < -1 || id > this->index)
		{
			std::cerr << "No record with specified id." << id << std::endl;
			throw std::exception();
		}

		switch(operation)
		{
			case Database<T>::Operation.HIRE:
				this->records[id].hire();
				break;
			case Database<T>::Operation.FIRE:
				this->records[id].fire();
				break;
			case Database<T>::Operation.EDIT:
				this->records[id].edit();
				break;
			case Database<T>::Operation.DEMOTE:
				this->records[id].demote();
				break;
			case Database<T>::Operation.PROMOTE:
				this->records[id].promote();
				break;
		}*/
//	}
}
