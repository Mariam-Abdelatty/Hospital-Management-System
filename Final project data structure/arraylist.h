#include <iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include<fstream>
#include<istream>
#include <assert.h>
using namespace std;

template <class elemType>
class arrayListType
{
public:
	const arrayListType<elemType>& operator=(const arrayListType<elemType>&);//Overloads the assignment operator
	bool isEmpty() const; //Function to determine whether the list is empty
	bool isFull() const; //Function to determine whether the list is full.
	int listSize() const; //Function to determine the number of elements in the list
	int maxListSize() const; //Function to determine the size of the list.
	void display() const; //Function to output the elements of the list
	bool isItemAtEqual(int location, const elemType& item) const; //Function to determine whether the item is the same as the item in the list at position specified by location
	void insertAt(int location, const elemType& insertItem); //Function to insert an item in the list at the position specified by location
	void insertEnd(const elemType& insertItem); //Function to insert an item at the end of the list.
	void removeAt(int location); //Function to remove the item from the list at the position specified by location
	void retrieveAt(int location, elemType& retItem) const;//Function to retrieve the element from the list at the position specified by location.
	void replaceAt(int location, const elemType& repItem); //Function to replace the elements in the list at the position specified by location. The item to be replaced is specified by the parameter repItem.
	void clearList(); //Function to remove all the elements from the list.
	int seqSearch(const elemType& item) const; //Function to search the list for a given item.
	void insert(const elemType& insertItem);//Function to insert the item specified by the parameter
	void remove(const elemType& removeItem);//Function to remove an item from the list.
	arrayListType(int size = 100);//constructor
	arrayListType(const arrayListType<elemType>& otherList);//copy constructor
	~arrayListType();//destructor
	elemType& operator[](int index)
	{
		return list[index];
	}

protected:
	elemType* list; //array to hold the list elements
	int length; //to store the length of the list
	int maxSize = 10; //to store the maximum size of the list
};

template <class elemType>
bool arrayListType<elemType>::isEmpty() const
{
	return (length == 0);
}

template <class elemType>
bool arrayListType<elemType>::isFull() const
{
	return (length == maxSize);
}

template <class elemType>
int arrayListType<elemType>::listSize() const
{
	return length;
}

template <class elemType>
int arrayListType<elemType>::maxListSize() const
{
	return maxSize;
}

template <class elemType>
void arrayListType<elemType>::display() const
{
	for (int i = 0; i < length; i++)
		cout << list[i] << " " << endl;
}

template <class elemType>
bool arrayListType<elemType>::isItemAtEqual(int location, const elemType& item) const
{
	return(list[location] == item);
}

template <class elemType>
void arrayListType<elemType>::insertAt(int location, const elemType& insertItem)
{
	if (location < 0 || location >= maxSize)
		cerr << "The position of the item to be inserted " << "is out of range" << endl;
	else
		if (length >= maxSize) //list is full
			cerr << "Cannot insert in a full list" << endl;
		else
		{
			for (int i = length; i > location; i--)
				list[i] = list[i - 1]; //move the elements down
			list[location] = insertItem; //insert the item at the specified position
			length++; //increment the length
		}
}

template <class elemType>
void arrayListType<elemType>::insertEnd(const elemType& insertItem)
{
	if (length >= maxSize) //the list is full
		cerr << "Cannot insert in a full list" << endl;
	else
	{
		list[length] = insertItem; //insert the item at the end
		length++; //increment the length
	}
}

template <class elemType>
void arrayListType<elemType>::removeAt(int location)
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be removed "
		<< "is out of range" << endl;
	else
	{
		for (int i = location; i < length - 1; i++)
			list[i] = list[i + 1];
		length--;
	}
}

template <class elemType>
void arrayListType<elemType>::retrieveAt(int location, elemType& retItem) const
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be retrieved is "
		<< "out of range." << endl;
	else
		retItem = list[location];
}

template <class elemType>
void arrayListType<elemType>::replaceAt(int location, const elemType& repItem)
{
	if (location < 0 || location >= length)
		cerr << "The location of the item to be replaced is "
		<< "out of range." << endl;
	else
		list[location] = repItem;
}

template <class elemType>
void arrayListType<elemType>::clearList()
{
	length = 0;
}

template <class elemType>
arrayListType<elemType>::arrayListType(int size)
{
	if (size < 0)
	{
		cerr << "The array size must be positive. Creating "
			<< "an array of size 100. " << endl;
		maxSize = 100;
	}
	else
		maxSize = size;
	length = 0;
	list = new elemType[maxSize];
	assert(list != NULL);
}

template <class elemType>
arrayListType<elemType>::~arrayListType()
{
	delete[] list;
}

template <class elemType>
arrayListType<elemType>::arrayListType(const arrayListType<elemType>& otherList)
{
	maxSize = otherList.maxSize;
	length = otherList.length;
	list = new elemType[maxSize]; //create the array
	assert(list != NULL); //terminate if unable to allocate memory space
	for (int j = 0; j < length; j++) //copy otherList
		list[j] = otherList.list[j];
}

template <class elemType>
const arrayListType<elemType>& arrayListType<elemType>::operator=(const arrayListType<elemType>& otherList)
{
	if (this != &otherList) //avoid self-assignment
	{
		delete[] list;
		maxSize = otherList.maxSize;
		length = otherList.length;
		list = new elemType[maxSize]; //create the array
		assert(list != NULL); //if unable to allocate memory space, terminate the program
		for (int i = 0; i < length; i++)
			list[i] = otherList.list[i];
	}
	return *this;
}

template <class elemType>
int arrayListType<elemType>::seqSearch(const elemType& item) const
{
	int loc;
	bool found = false;
	for (loc = 0; loc < length; loc++)
		if (list[loc] == item)
		{
			found = true;
			break;
		}
	if (found)
		return loc;
	else
		return -1;
}

template <class elemType>
void arrayListType<elemType>::insert(const elemType& insertItem)
{
	int loc;
	if (length == 0) //list is empty
		list[length++] = insertItem; //insert the item and increment the length
	else if (length == maxSize)
		cerr << "Cannot insert in a full list." << endl;
	else
	{
		loc = seqSearch(insertItem);
		if (loc == -1) //the item to be inserted does not exist in the list
			list[length++] = insertItem;
		else
			cerr << "the item to be inserted is already in the list. No duplicates are allowed." << endl;
	}
}

template<class elemType>
void arrayListType<elemType>::remove(const elemType& removeItem)
{
	int loc;
	if (length == 0)
		cerr << "Cannot delete from an empty list." << endl;
	else
	{
		loc = seqSearch(removeItem);
		if (loc != -1)
			removeAt(loc);
		else
			cout << "The item to be deleted is not in the list."
			<< endl;
	}
}