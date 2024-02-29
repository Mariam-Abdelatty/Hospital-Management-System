#include <iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include<fstream>
#include<istream>
#include <assert.h>
#include<iterator>
using namespace std;


template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* next;
	nodeType<Type>* back;

};


template <class Type>
class doublyLinkedList
{
public:
	void initializeList(); //Function to initialize the list to an empty state.
	bool isEmptyList() const; //Function to determine whether the list is empty.
	void destroy(); //Function to delete all the nodes from the list.
	void print() const; //Function to output the info contained in each node.
	void reversePrint() const; //Function to output the info contained in each node in reverse order.
	int length() const; //Function to return the number of nodes in the list.
	Type front() const; //Function to return the first element of the list.
	Type back() const; //Function to return the last element of the list.
	void insert(const Type& insertItem); //Function to insert insertItem in the list.
	doublyLinkedList(); //default constructor
	doublyLinkedList(const doublyLinkedList<Type>& otherList); //copy constructor
	~doublyLinkedList(); //destructor
	const doublyLinkedList<Type>& operator=(const doublyLinkedList<Type>&); //Overload the assignment operator.
	bool search(const Type& searchItem) const; //Function to determine whether searchItem is in the list.
	void deleteNode(const Type& deleteItem); //Function to delete deleteItem from the list.
protected:
	int count;
	nodeType<Type>* first; //pointer to the first node
	nodeType<Type>* last; //pointer to the last node
	string name;
private:
	void copyList(const doublyLinkedList<Type>& otherList); //Function to make a copy of otherList.
};


template <class Type>
const doublyLinkedList<Type>& doublyLinkedList<Type>::operator=(const doublyLinkedList<Type>& otherList)
{
	if (this != &otherList) //avoid self-copy
	{
		copyList(otherList);
	}
	return *this;
}

template <class Type>
doublyLinkedList<Type>::doublyLinkedList()
{
	first = NULL;
	last = NULL;
	count = 0;
}

template <class Type>
bool doublyLinkedList<Type>::isEmptyList() const
{
	return (first == NULL);
}

template <class Type>
void doublyLinkedList<Type>::destroy()
{
	nodeType<Type>* temp; //pointer to delete the node
	while (first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <class Type>
void doublyLinkedList<Type>::initializeList()
{
	destroy();
}

template <class Type>
int doublyLinkedList<Type>::length() const
{
	return count;
}

template <class Type>
void doublyLinkedList<Type>::print() const
{
	nodeType<Type>* current; //pointer to traverse the list
	current = first; //set current to point to the first node
	while (current != NULL)
	{
		cout << current->info << " " << endl;//output info
		current = current->next;
	}
}

template <class Type>
void doublyLinkedList<Type>::reversePrint() const
{
	nodeType<Type>* current; //pointer to traverse the list
	current = last; //set current to point to the last node
	while (current != NULL)
	{
		cout << current->info << " ";
		current = current->back;
	}
}

template <class Type>
Type doublyLinkedList<Type>::front() const
{
	assert(first != NULL);
	return first->info;
}

template <class Type>
Type doublyLinkedList<Type>::back() const
{
	assert(last != NULL);
	return last->info;
}

template <class Type>
void doublyLinkedList<Type>::insert(const Type& insertItem)
{
	nodeType<Type>* current; //pointer to traverse the list
	nodeType<Type>* trailCurrent = NULL; //pointer just before current
	nodeType<Type>* newNode; //pointer to create a node
	bool found;
	newNode = new nodeType<Type>; //create the node
	newNode->info = insertItem; //store the new item in the node
	newNode->next = NULL;
	newNode->back = NULL;
	if (first == NULL) //if list is empty, newNode is the only node
	{
		first = newNode;
		last = newNode;
		count++;
	}
	else
	{
		found = false;
		current = first;
		while (current != NULL && !found) //search the list
			if (current->info >= insertItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->next;
			}
		if (current == first) //insert newNode before first
		{
			first->back = newNode;
			newNode->next = first;
			first = newNode;
			count++;
		}
		else
		{
			//insert newNode between trailCurrent and current
			if (current != NULL)
			{
				trailCurrent->next = newNode;
				newNode->back = trailCurrent;
				newNode->next = current;
				current->back = newNode;
			}
			else
			{
				trailCurrent->next = newNode;
				newNode->back = trailCurrent;
				last = newNode;
			}
			count++;
		}
	}
}

template <class Type>
void doublyLinkedList<Type>::copyList(const doublyLinkedList<Type>& otherList)
{
	nodeType<Type>* newNode; //pointer to create a node
	nodeType<Type>* current; //pointer to traverse the list

	if (first != NULL) //if the list is nonempty, make it empty
		destroy();

	if (otherList.first == NULL) //otherList is empty
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	else
	{
		current = otherList.first; //current points to the list to be copied
		count = otherList.count;

		//copy the first node
		first = new nodeType<Type>;  //create the node

		first->info = current->info; //copy the info
		first->next = NULL;        //set the link field of the node to NULL
		last = first;              //make last point to the first node
		current = current->next;     //make current point to the next node

		//copy the remaining list
		while (current != NULL)
		{
			newNode = new nodeType<Type>;  //create a node
			newNode->info = current->info; //copy the info
			newNode->next = NULL;       //set the link of newNode to NULL
			last->next = newNode;  //attach newNode after last
			last = newNode;        //make last point to the actual last node
			current = current->next;   //make current point to the next node
		}
	}
}

template <class Type>
doublyLinkedList<Type>::doublyLinkedList(const doublyLinkedList<Type>& otherList)

{
	first = NULL;
	copyList(otherList);
}

template <class Type>
doublyLinkedList<Type>::~doublyLinkedList()

{
	destroy();
}

template <class Type>
bool doublyLinkedList<Type>::search(const Type& searchItem) const
{
	bool found = false;
	nodeType<Type>* current; //pointer to traverse the list
	current = first;
	while (current != NULL && !found)
		if (current->info >= searchItem)
			found = true;
		else
			current = current->next;
	if (found)

		found = (current->info == searchItem); //test for equality
	return found;
}

template <class Type>
void doublyLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type>* current; //pointer to traverse the list
	nodeType<Type>* trailCurrent; //pointer just before current
	bool found;
	if (first == NULL)
		cout << "Cannot delete from an empty list." << endl;
	else if (first->info == deleteItem) //node to be deleted is the first node
	{
		current = first;
		first = first->next;
		if (first != NULL)
			first->back = NULL;
		else
			last = NULL;
		count--;
		delete current;
	}
	else
	{
		found = false;
		current = first;
		while (current != NULL && !found) //search the list
			if (current->info >= deleteItem)
				found = true;
			else
				current = current->next;
		if (current == NULL)
			cout << "The item to be deleted is not in the list." << endl;
		else if (current->info == deleteItem) //check for equality
		{
			trailCurrent = current->back;
			trailCurrent->next = current->next;
			if (current->next != NULL)
				current->next->back = trailCurrent;
			if (current == last)
				last = trailCurrent;
			count--;
			delete current;
		}
		else
			cout << "The item to be deleted is not in list." << endl;
	}
}