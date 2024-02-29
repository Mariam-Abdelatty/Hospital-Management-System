

#include <iostream>
#include<algorithm>
#include<string>
#include<string.h>
#include <assert.h>
#include "hospital.h"
int main()// Main function
{
	Hospital hospital;
	int choice = 0;
	do
	{
		cout << "1. Add patient record" << endl;
		cout << "2. Display all patient records" << endl;
		cout << "3. Search for a patient record" << endl;
		cout << "4. Delete a patient record" << endl;
		cout << "5. Display the number of patient records" << endl;
		cout << "6. Display patient's doctors" << endl;
		cout << "7. Delete a specific doctor for a patient" << endl;
		cout << "8. Add a doctor for a specific patient" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << "-------------------------" << endl;
		switch (choice)
		{
		case 1: hospital.addPatient();
			break;
		case 2: hospital.displayPatients();
			break;
		case 3: hospital.searchPatient();
			break;
		case 4: hospital.deletePatient();
			break;
		case 5: hospital.displayCount();
			break;
		case 6: hospital.displayDoctorsInPatient();
			break;
		case 7: hospital.delete_specific_Doctor();
			break;
		case 8: hospital.add_doctor_to_patient();
			break;

		case 0: cout << "Exiting program." << endl;
			break;
		default: cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 0);
	return 0;
}