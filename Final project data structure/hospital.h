#include <iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include <assert.h>
#include "arraylist.h"
#include "doublylinkedlist.h"
#include <algorithm>
using namespace std;
const int MIN_AGE = 1;
const int MAX_AGE = 300;
const float MIN_TEMP = 34;
const float MAX_TEMP = 45;
const int MIN_HEIGHT = 1;
const int MAX_HEIGHT = 200;
const int MIN_WEIGHT = 1;
const int MAX_WEIGHT = 500;


struct Doctor //Define the structure for doctor record
{
	string name;
	string gender;
	string department;
	string phone_number;
	string office_hours;
	int office_number;
	int experience_year;
};

struct Patient // Define the structure for the patient record 
{
	string name;
	int age;
	string gender;
	string illness;
	string blood_type;
	string blood_pressure;
	float temperature;
	float weight;
	float height;
	arrayListType<Doctor> doctors; // Add an array list for doctors
	Patient* next;
	doublyLinkedList<Patient> patient;


};

bool operator>=(const Patient& l, const Patient& r)
{
	return ((l.name) >= (r.name));
}
bool operator==(const Patient& p1, const Patient& p2)
{
	return p1.name == p2.name;
}
ostream& operator<< (ostream& os, const Patient& p)
{
	os << "Name: " << p.name << endl;
	os << "Age: " << p.age << endl;
	os << "Gender: " << p.gender << endl;
	os << "Illness: " << p.illness << endl;
	os << "Blood Type: " << p.blood_type << endl;
	os << "Blood Pressure: " << p.blood_pressure << endl;
	os << "Temperature: " << p.temperature << endl;
	os << "Weight: " << p.weight << endl;
	os << "Height: " << p.height << endl;
	return os;
}
ostream& operator<< (ostream& os, const Doctor& d)
{
	os << "Name: " << d.name << endl;
	os << "Gender: " << d.gender << endl;
	os << "Department: " << d.department << endl;
	os << "Phone Number: " << d.phone_number << endl;
	os << "Office Hours: " << d.office_hours << endl;
	os << "Office Number: " << d.office_number << endl;
	os << "Experience Year: " << d.experience_year << endl;
	return os;
}

class Hospital :public doublyLinkedList<Patient>, arrayListType<Doctor>// Define the class for the hospital management system
{
private:
	Patient* head;
	Patient* tail;
	Patient* current;
	Patient* previous;
	Patient* temp;
	int count;
public:
	Hospital();
	void add_doctor(Patient* patient);
	void addPatient();
	void displayPatients();
	void sortPatientsByAge();
	void sortDoctorsByName();
	void deleteDoctor(string& patientname);
	void displayCount();
	void delete_specific_Doctor();
	void displayDoctorsInPatient();
	void searchPatient();
	void deletePatient();
	void add_doctor_to_patient();
	friend ostream& operator<< (ostream& os, const Patient& p);
	friend ostream& operator<< (ostream& os, const Doctor& d);
	friend bool operator>=(const Patient& l, const Patient& r);
	friend bool operator==(const Patient& p1, const Patient& p2);
};

Hospital::Hospital()// Constructor
{
	head = NULL;
	tail = NULL;
	current = NULL;
	previous = NULL;
	temp = NULL;
	count = 0;
}
void Hospital::add_doctor(Patient* patient)
{
	Doctor newDoctor;
	cin.ignore();
	cout << "Enter doctor name: ";
	getline(cin, newDoctor.name);
	cout << "Enter doctor gender {F/M}: ";
	cin >> newDoctor.gender;
	while (newDoctor.gender != "Male" && newDoctor.gender != "male" && newDoctor.gender != "M" && newDoctor.gender != "m" &&
		newDoctor.gender != "Female" && newDoctor.gender != "female" && newDoctor.gender != "F" && newDoctor.gender != "f")
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newDoctor.gender;

	}
	cout << "Enter the doctor's department (Pediatrics, Cardiology, Neurology): ";
	cin >> newDoctor.department;
	while (newDoctor.department != "Pediatrics" && newDoctor.department != "pediatrics" && newDoctor.department != "Cardiology" && newDoctor.department != "cardiology" &&
		newDoctor.department != "Neurology" && newDoctor.department != "neurology")
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newDoctor.department;
	}
	cout << "Enter the doctor's phone number (10 digits): ";
	cin >> newDoctor.phone_number;
	while (newDoctor.phone_number.length() != 10)
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newDoctor.phone_number;
	}
	for (int i = 0; i < 10; i++)
	{
		if (!isdigit(newDoctor.phone_number[i]))
		{
			cout << "Invalid data entered please try again" << endl;
			cin >> newDoctor.phone_number;
			i = -1;//reset the loop counter to check the new input again
		}
	}
	cout << "Enter doctor office hours: ";
	cin >> newDoctor.office_hours;
	cout << "Enter doctor office number: ";
	cin >> newDoctor.office_number;
	cout << "Enter doctor experience year: ";
	cin >> newDoctor.experience_year;
	while (newDoctor.experience_year < 0 || newDoctor.experience_year > 80)
	{
		cout << "Error: Invalid experience year. Please enter again: ";
		cin >> newDoctor.experience_year;
	}
	patient->doctors.insertEnd(newDoctor);
}
void Hospital::addPatient() // Function to add a new patient record to the linked list
{
	Patient* newPatient = new Patient;

	cout << "Enter patient name: ";
	cin.ignore();
	getline(cin, newPatient->name);
	cout << "Enter patient age: ";
	cin >> newPatient->age;
	while (newPatient->age < MIN_AGE || newPatient->age > MAX_AGE)
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->age;
	}
	cout << "Enter patient gender {F/M}: ";
	cin >> newPatient->gender;
	while (newPatient->gender != "Male" && newPatient->gender != "male" && newPatient->gender != "M" && newPatient->gender != "m" &&
		newPatient->gender != "Female" && newPatient->gender != "female" && newPatient->gender != "F" && newPatient->gender != "f") {
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->gender;
	}
	cout << "Enter patient illness: ";
	cin >> newPatient->illness;
	cout << "Enter patient blood_type {A+,A-,B+,B-,AB+,AB-,O+,O-}: ";
	cin >> newPatient->blood_type;
	while (newPatient->blood_type != "A+" && newPatient->blood_type != "A-" && newPatient->blood_type != "B+" && newPatient->blood_type != "B-" &&
		newPatient->blood_type != "AB+" && newPatient->blood_type != "AB-" && newPatient->blood_type != "O+" && newPatient->blood_type != "O-") {
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->blood_type;
	}
	cout << "Enter patient blood_pressure: ";
	cin >> newPatient->blood_pressure;
	cout << "Enter patient temperature: ";
	cin >> newPatient->temperature;
	while (newPatient->temperature < MIN_TEMP || newPatient->temperature > MAX_TEMP)
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->temperature;
	}
	cout << "Enter patient weight: ";
	cin >> newPatient->weight;
	while (newPatient->weight < MIN_WEIGHT || newPatient->weight > MAX_WEIGHT)
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->weight;
	}
	cout << "Enter patient height: ";
	cin >> newPatient->height;
	while (newPatient->height < MIN_HEIGHT || newPatient->height > MAX_HEIGHT)
	{
		cout << "Invalid data entered please try again" << endl;
		cin >> newPatient->height;
	}
	cout << "-------------------------" << endl;
	// Add doctors to the patient's array list
	int numDoctors;
	cout << "Enter number of doctors for this patient: ";
	cin >> numDoctors;

	for (int i = 0; i < numDoctors; i++)
	{
		add_doctor(newPatient);
		cout << "-------------------------" << endl;
	}
	newPatient->next = NULL;
	if (head == NULL)
	{
		head = newPatient;
		tail = newPatient;
	}
	else
	{
		tail->next = newPatient;
		tail = newPatient;
	}
	count++;
	newPatient->patient.insert(*newPatient);

}
void Hospital::displayPatients() //display patients record
{
	sortDoctorsByName();
	sortPatientsByAge();
	current = head;
	while (current != NULL)
	{
		if (!(current->patient.isEmptyList()))
		{
			cout << "Patient" << endl;
			current->patient.print();
			cout << "-------------------------" << endl;
		}
		if (!(current->doctors.isEmpty()))
		{
			cout << "Doctors" << endl;
			current->doctors.display();
			cout << "-------------------------" << endl;
			cout << "-----------------------------------------------------" << endl;
		}

		current = current->next;
	}
}
void Hospital::sortDoctorsByName()
{
	current = head;
	while (current != NULL)
	{
		arrayListType<Doctor>& doctors = current->doctors;
		for (int i = 0; i < doctors.listSize(); i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < doctors.listSize(); j++)
			{
				if (doctors[j].name < doctors[minIndex].name)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				Doctor temp = doctors[i];
				doctors[i] = doctors[minIndex];
				doctors[minIndex] = temp;
			}
		}
		current = current->next;
	}

}
void Hospital::sortPatientsByAge()
{
	if (head == nullptr || head->next == nullptr)
	{
		// If the list is empty or has only one element, no sorting is necessary
		return;
	}

	bool swapped = true;
	while (swapped) {
		swapped = false;
		Patient* current = head;
		Patient* previous = nullptr;

		while (current->next != nullptr)
		{
			Patient* next = current->next;
			if (current->age > next->age)
			{
				// Swap the two nodes
				if (previous != nullptr)
				{
					previous->next = next;
				}
				else
				{
					head = next;
				}

				current->next = next->next;
				next->next = current;
				previous = next;
				swapped = true;
			}
			else
			{
				previous = current;
				current = next;
			}
		}
	}
}
void Hospital::displayCount()// Function to display the number of patient records in the linked list 
{
	cout << "Number of patient records: " << count << endl;
	cout << "-------------------------" << endl;
}
void Hospital::displayDoctorsInPatient() // Function to display the doctors of a specific patient
{
	Patient p;
	string patientName;
	cout << "Enter the patient name: ";
	cin.ignore();
	getline(cin, patientName);
	p.name = patientName;
	sortDoctorsByName();
	// Traverse the linked list to find the patient
	current = head;
	bool found = false;
	while (current != NULL)
	{
		if (current->patient.search(p))
		{
			// Found the patient, display their doctors
			current->doctors.display();
			cout << "-------------------------" << endl;
			found = true;
			break;
		}

		current = current->next;
	}
	if (!found)// Patient not found
	{
		cout << "Patient not found." << endl;
	}

}
void Hospital::searchPatient() // Function to search for a patient record by name
{
	Patient p;
	string name;
	cout << "Enter patient name to search: ";
	cin.ignore();
	getline(cin, name);
	p.name = name;
	sortDoctorsByName();
	current = head;
	while (current != NULL)
	{
		if (current->patient.search(p))
		{

			current->patient.print();
			cout << "-------------------------" << endl;


			Doctor* currentDoctor = &current->doctors[0];
			for (int i = 0; i < current->doctors.listSize() - 1; i++)
			{
				Doctor* currentDoctor = &current->doctors[i];
				current->doctors.display();
				cout << "-------------------------" << endl;
			}


		}
		current = current->next;
	}
}
void Hospital::delete_specific_Doctor()
{
	string patientName, doctorName;
	cout << "Enter patient name: ";
	cin.ignore();
	getline(cin, patientName);
	current = head;
	while (current != NULL && current->name != patientName)
	{

		current = current->next;
	}
	if (current == NULL)
	{
		cout << "Patient not found" << endl;
		return;
	}
	cout << "Enter doctor name: ";
	getline(cin, doctorName);
	bool found = false;
	for (int i = 0; i < current->doctors.listSize(); i++)
	{
		if (current->doctors[i].name == doctorName)
		{
			current->doctors.removeAt(i);
			found = true;
		}
	}
	if (found)
	{
		cout << "Doctor successfully removed from patient record" << endl;
	}
	else
	{
		cout << "Doctor " << doctorName << " not found in patient record" << endl;
	}
}
void Hospital::deletePatient() // Function to search for a patient record by name
{
	Patient p;
	string name;
	cout << "Enter patient name to delete: ";
	cin.ignore();
	getline(cin, name);
	p.name = name;
	sortDoctorsByName();
	current = head;
	while (current != NULL)
	{
		if (current->patient.search(p))
		{
			deleteDoctor(name);
			current->patient.deleteNode(p);
			cout << "patient deleted successfully" << endl;
			cout << "-------------------------" << endl;
			count--;
		}
		current = current->next;
	}
}
void Hospital::deleteDoctor(string& patientname)
{
	Patient p;
	p.name = patientname;
	bool found = false;
	current = head;
	while (current != NULL)
	{
		if (current->patient.search(p))
		{
			for (int i = current->doctors.listSize() - 1; i >= 0; i--)
			{
				current->doctors.removeAt(i);
			}
			return;
		}

		current = current->next;
	}
}
void Hospital::add_doctor_to_patient()
{
	Patient p;
	string patientName;
	cin.ignore();
	cout << "Enter the patient name: " << endl;
	getline(cin, patientName);
	p.name = patientName;
	current = head;
	bool found = false;
	while (current != NULL)
	{
		if (current->patient.search(p))
		{
			add_doctor(current);
			return;
		}
		current = current->next;
	}
	if (!found)
	{
		cout << "Patient not found." << endl;
	}
}