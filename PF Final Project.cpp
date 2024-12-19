                                                                    //Hospital Management
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  // For file handling
#include <algorithm> // For sorting
#include <limits>    // For input validation

using namespace std;

// Structure to store patient information
struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string address;
    string illness;
    string doctor;
    string admissionDate;
    bool isDischarged;
};

// Global variables
vector<Patient> patients; // Vector to hold all patients
int nextID = 1; // To generate unique IDs

// Function prototypes for CRUD operations
void admitPatient();
void dischargePatient();
void searchPatientByID();
void searchPatientByName();
void listAdmittedPatients();
void listDischargedPatients();
void listAllPatients();
void updatePatient();
void deletePatient();
void saveRecords();
void loadRecords();
void printHeader(const string& title);
void printPatientDetails(const Patient& patient);
void validateAge(int& age);
void sortPatientsByName();
void sortPatientsByID();
void generatePatientReport();
void mainMenu();

// Function to print a header (Helper Function)
void printHeader(const string& title) {
    cout << "\n====================================\n";
    cout << "==== " << title << " ====\n";
    cout << "====================================\n";
}

// Function to print patient details (Helper Function)
void printPatientDetails(const Patient& patient) {
    cout << "Patient ID: " << patient.id << endl;
    cout << "Name: " << patient.name << endl;
    cout << "Age: " << patient.age << endl;
    cout << "Gender: " << patient.gender << endl;
    cout << "Address: " << patient.address << endl;
    cout << "Illness: " << patient.illness << endl;
    cout << "Doctor: " << patient.doctor << endl;
    cout << "Admission Date: " << patient.admissionDate << endl;
    cout << "Discharged: " << (patient.isDischarged ? "Yes" : "No") << endl;
}

// Function to admit a new patient (Create)
void admitPatient() {
    Patient newPatient;
    newPatient.id = nextID++;

    printHeader("Admit New Patient");

    cout << "Enter patient name: ";
    cin.ignore(); // To clear the newline character left by previous input
    getline(cin, newPatient.name);

    cout << "Enter patient age: ";
    validateAge(newPatient.age);

    cout << "Enter gender (M/F): ";
    while (true) {
        cin >> newPatient.gender;
        if (newPatient.gender == "M" || newPatient.gender == "F") {
            break;
        } else {
            cout << "Invalid gender. Please enter M or F: ";
        }
    }

    cout << "Enter patient address: ";
    cin.ignore(); // Clear buffer
    getline(cin, newPatient.address);

    cout << "Enter illness: ";
    getline(cin, newPatient.illness);

    cout << "Enter doctor name: ";
    getline(cin, newPatient.doctor);

    cout << "Enter admission date (DD/MM/YYYY): ";
    getline(cin, newPatient.admissionDate);

    newPatient.isDischarged = false;
    patients.push_back(newPatient);

    cout << "\nPatient admitted successfully with ID: " << newPatient.id << endl;
    cout << "====================================\n";
}

// Function to discharge a patient (Update)
void dischargePatient() {
    int id;
    printHeader("Discharge Patient");

    cout << "Enter patient ID to discharge: ";
    cin >> id;

    bool found = false;
    for (auto &patient : patients) {
        if (patient.id == id && !patient.isDischarged) {
            patient.isDischarged = true;
            cout << "Patient with ID " << id << " has been discharged.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found or already discharged.\n";
    }
    cout << "====================================\n";
}

// Function to search patient by ID (Read)
void searchPatientByID() {
    int id;
    printHeader("Search Patient by ID");

    cout << "Enter patient ID to search: ";
    cin >> id;

    bool found = false;
    for (const auto &patient : patients) {
        if (patient.id == id) {
            printPatientDetails(patient);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found.\n";
    }
    cout << "====================================\n";
}

// Function to search patient by name (Read)
void searchPatientByName() {
    string name;
    printHeader("Search Patient by Name");

    cout << "Enter patient name to search: ";
    cin.ignore(); // to clear any leftover newline from previous input
    getline(cin, name);

    bool found = false;
    for (const auto &patient : patients) {
        if (patient.name == name) {
            printPatientDetails(patient);
            found = true;
        }
    }

    if (!found) {
        cout << "Patient not found.\n";
    }
    cout << "====================================\n";
}

// Function to list all admitted patients (Read)
void listAdmittedPatients() {
    printHeader("List of Admitted Patients");

    cout << "\nAdmitted Patients:\n";
    bool found = false;
    for (const auto &patient : patients) {
        if (!patient.isDischarged) {
            cout << "ID: " << patient.id << " | Name: " << patient.name << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No admitted patients found.\n";
    }
    cout << "====================================\n";
}

// Function to list all discharged patients (Read)
void listDischargedPatients() {
    printHeader("List of Discharged Patients");

    cout << "\nDischarged Patients:\n";
    bool found = false;
    for (const auto &patient : patients) {
        if (patient.isDischarged) {
            cout << "ID: " << patient.id << " | Name: " << patient.name << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No discharged patients found.\n";
    }
    cout << "====================================\n";
}

// Function to list all patients (both admitted and discharged)
void listAllPatients() {
    printHeader("List of All Patients");

    cout << "\nAll Patients:\n";
    bool found = false;
    for (const auto &patient : patients) {
        cout << "ID: " << patient.id << " | Name: " << patient.name
             << " | Discharged: " << (patient.isDischarged ? "Yes" : "No") << endl;
        found = true;
    }

    if (!found) {
        cout << "No patients found.\n";
    }
    cout << "====================================\n";
}

// Function to update patient details (Update)
void updatePatient() {
    int id;
    printHeader("Update Patient Record");

    cout << "Enter patient ID to update: ";
    cin >> id;

    bool found = false;
    for (auto &patient : patients) {
        if (patient.id == id) {
            cout << "\nUpdating record for " << patient.name << " (ID: " << id << ")\n";
            cout << "Enter new address (or press Enter to keep the same): ";
            cin.ignore(); // to clear the newline left by the previous input
            string newAddress;
            getline(cin, newAddress);
            if (!newAddress.empty()) {
                patient.address = newAddress;
            }

            cout << "Enter new illness (or press Enter to keep the same): ";
            string newIllness;
            getline(cin, newIllness);
            if (!newIllness.empty()) {
                patient.illness = newIllness;
            }

            cout << "Enter new doctor (or press Enter to keep the same): ";
            string newDoctor;
            getline(cin, newDoctor);
            if (!newDoctor.empty()) {
                patient.doctor = newDoctor;
            }

            found = true;
            cout << "Patient record updated.\n";
            break;
        }
    }

    if (!found) {
        cout << "Patient not found.\n";
    }
    cout << "====================================\n";
}

// Function to delete a patient record (Delete)
void deletePatient() {
    int id;
    printHeader("Delete Patient Record");

    cout << "Enter patient ID to delete: ";
    cin >> id;

    bool found = false;
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (it->id == id) {
            // Patient found, so delete
            cout << "Deleting patient with ID " << id << " (" << it->name << ").\n";
            patients.erase(it);  // Erase the patient from the vector
            found = true;
            break; // Exit loop after deletion
        }
    }

    if (!found) {
        cout << "Patient not found.\n";
    } else {
        cout << "Patient record deleted successfully.\n";
    }

    cout << "====================================\n";
}

// Function to save patient records to a file
void saveRecords() {
    ofstream file("patient_records.txt");
    if (!file) {
        cout << "Error saving records!\n";
        return;
    }

    for (const auto &patient : patients) {
        file << patient.id << "\n" << patient.name << "\n" << patient.age << "\n"
             << patient.gender << "\n" << patient.address << "\n" << patient.illness << "\n"
             << patient.doctor << "\n" << patient.admissionDate << "\n"
             << patient.isDischarged << "\n";
    }

    cout << "All records saved successfully.\n";
    cout << "====================================\n";
}

// Function to load patient records from a file
void loadRecords() {
    ifstream file("patient_records.txt");
    if (!file) {
        return; // If the file is not found, do nothing and return to main menu
    }

    Patient patient;
    while (file >> patient.id) {
        file.ignore();  // Ignore newline character
        getline(file, patient.name);
        file >> patient.age;
        file.ignore();
        getline(file, patient.gender);
        getline(file, patient.address);
        getline(file, patient.illness);
        getline(file, patient.doctor);
        getline(file, patient.admissionDate);
        file >> patient.isDischarged;
        file.ignore();

        patients.push_back(patient);
        if (nextID <= patient.id) nextID = patient.id + 1; // Update nextID based on loaded data
    }

    cout << "Patient records loaded successfully.\n";
    cout << "====================================\n";
}

// Function to validate age input
void validateAge(int& age) {
    while (true) {
        cin >> age;
        if (cin.fail() || age < 0 || age > 120) {
            cout << "Invalid age. Please enter a valid age (0-120): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
}

// Function to sort patients by name
void sortPatientsByName() {
    sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
        return a.name < b.name;
    });
    cout << "Patients sorted by name.\n";
}

// Function to sort patients by ID
void sortPatientsByID() {
    sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
        return a.id < b.id;
    });
    cout << "Patients sorted by ID.\n";
}

// Function to generate a detailed patient report
void generatePatientReport() {
    ofstream report("patient_report.txt");
    if (!report) {
        cout << "Error generating report.\n";
        return;
    }

    for (const auto &patient : patients) {
        report << "ID: " << patient.id << "\n"
               << "Name: " << patient.name << "\n"
               << "Age: " << patient.age << "\n"
               << "Gender: " << patient.gender << "\n"
               << "Address: " << patient.address << "\n"
               << "Illness: " << patient.illness << "\n"
               << "Doctor: " << patient.doctor << "\n"
               << "Admission Date: " << patient.admissionDate << "\n"
               << "Discharged: " << (patient.isDischarged ? "Yes" : "No") << "\n"
               << "====================================\n";
    }
    cout << "Patient report generated successfully.\n";
}

// Main menu to interact with the system
void mainMenu() {
    loadRecords();  // Load saved patient records at the beginning

    int choice;
    do {
        printHeader("Hospital Management System");
        cout << "1. Admit Patient\n";
        cout << "2. Discharge Patient\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Search Patient by Name\n";
        cout << "5. List All Admitted Patients\n";
        cout << "6. List All Discharged Patients\n";
        cout << "7. List All Patients\n";
        cout << "8. Update Patient Record\n";
        cout << "9. Delete Patient Record\n";
        cout << "10. Save Records\n";
        cout << "11. Sort Patients by Name\n";
        cout << "12. Sort Patients by ID\n";
        cout << "13. Generate Patient Report\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: admitPatient(); break;
            case 2: dischargePatient(); break;
            case 3: searchPatientByID(); break;
            case 4: searchPatientByName(); break;
            case 5: listAdmittedPatients(); break;
            case 6: listDischargedPatients(); break;
            case 7: listAllPatients(); break;
            case 8: updatePatient(); break;
            case 9: deletePatient(); break;
            case 10: saveRecords(); break;
            case 11: sortPatientsByName(); break;
            case 12: sortPatientsByID(); break;
            case 13: generatePatientReport(); break;
            case 14: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice, please try again.\n"; break;
        }
    } while (choice != 14);
}

int main() {
    mainMenu();
    return 0;
}
