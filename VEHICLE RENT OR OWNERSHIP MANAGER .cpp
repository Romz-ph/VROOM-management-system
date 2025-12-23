#include <iostream>
#include <string>
#include <fstream>  // Required for file handling (reading and writing)
#include <iomanip>  // Required for currency formatting
using namespace std;

int main() {
    int option = 0; // sa menu options
    double totalCost = 0; // sa total cost
    string transType = ""; // transtype = BUY/RENT

    // User Input Variables
    string name, licenseNumber;
    int age, carChoice, days;
    char confirm, license, employment;

    // Vehicle Inventory Data
    // Naka arrays
    string models[3] = {"Toyota Corolla", "Honda Civic", "Ford Ranger"};
    int years[3] = {2020, 2021, 2019};
    double buyPrices[3] = {850000.00, 1100000.00, 1400000.00};
    double rentPrices[3] = {2500.00, 3000.00, 4500.00};
    bool available[3] = {true, true, true};

    // start of the program here
    cout << "===== WELCOME TO VROOM =====" << endl;

    // do while loop ng menu/options natin
    do {
        cout << "======== MAIN MENU =========" << endl;
        cout << "[1] View Vehicle Inventory" << endl;
        cout << "[2] Rent a Car" << endl;
        cout << "[3] Buy a Car" << endl;
        cout << "[4] View Transactions Report (From File)" << endl;
        cout << "[5] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            // CASE 1 - VIEW VEHICLE INVENTORY
            case 1:
            {
                cout << "--- CURRENT INVENTORY ---" << endl;
                for (int i = 0; i < 3; i++) {
                    if (available[i] == true) {
                        cout << "[" << i + 1  << "] " << models[i] << " (" << years[i] << ")" << endl;
                        cout << "    Buy: P" << fixed << setprecision(2) << buyPrices[i] << endl;
                        cout << "    Rent: P" << rentPrices[i] << "/day" << endl;
                    } else {
                        cout << "[" << i + 1 << "] " << models[i] << " - [UNAVAILABLE]" << endl;
                    }
                }
                break;
            }

            // CASE 2 & 3 - RENT AND BUY
            case 2:
            case 3:
            {
                // NAME OF THE CUSTOMER
                cin.ignore();
                cout << "--- CUSTOMER DETAILS ---" << endl;
                cout << "Enter Full Name: ";
                getline(cin, name);

                // AGE VALIDATION
                cout << "Enter your age (must be at least 18): ";
                cin >> age;
                if (age < 18) {
                    cout << "Sorry, you must be at least 18. Transaction cancelled." << endl;
                    return 1;
                } else if (age < 0 || age > 150) {
                    cout << "Invalid age. Age must be between 0 and 150." << endl;
                    cout << "Enter your age again: ";
                    cin >> age;
                }

                // LICENSE VALIDATION
                cout << "Do you have a driver's license? (y/n): ";
                cin >> license;
                if (license == 'y' || license == 'Y' ) {
                    cout << "Enter your Driver's License Number: ";
                    cin >> licenseNumber;
                } else {
                    cout << "Sorry, you must have a Driver's License." << endl;
                    return 1;
                }

                // EMPLOYMENT VALIDATION
                cout << "Are you employed? (y/n):";
                cin >> employment;
                if (employment == 'y' || employment == 'Y') {
                    cout << "Please provide proof of employment at the dealership office." << endl;
                } else {
                    cout << "Sorry, we cannot entertain you without proof of employment." << endl;
                    return 1;
                }

                // CAR SELECTION
                cout << "--- SELECT VEHICLE ---" << endl;
                for (int i = 0; i < 3; i++) {
                    if (available[i] == true) {
                        cout << "[" << i + 1 << "] " << models[i];
                        // Show Rent vs Buy price
                        if (option == 2) {
                            cout << " (Rent: P" << fixed << setprecision(2) << rentPrices[i] << "/day)" << endl;
                        } else {
                            cout << " (Buy: P" << fixed << setprecision(2) << buyPrices[i] << ")" << endl;
                        }
                    } else {
                        cout << "[" << i + 1 << "] " << models[i] << " - [UNAVAILABLE]" << endl;
                    }
                }
                cout << "Choice: ";
                cin >> carChoice;

                // Validation of Vehicle choice
                if (carChoice < 1 || carChoice > 3 || available[carChoice - 1] == false) {
                    cout << "Invalid choice or car unavailable." << endl;
                    break;
                }

                // CALCULATION COST BASE ON BUY or RENT
                if (option == 2) {
                    transType = "RENT";
                    cout << "How many days?: ";
                    cin >> days;
                    totalCost = rentPrices[carChoice - 1] * days;
                } else {
                    transType = "BUY";
                    days = 0;
                    totalCost = buyPrices[carChoice - 1];
                }

                // --- CONFIRMATION ---
                cout << "Total: P" << totalCost << ". Confirm? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    // Mark car as sold/rented
                    available[carChoice - 1] = false;
                    // --- PRINT RECEIPT ---
                    cout << fixed << setprecision(2);
                    cout << endl;
                    cout << "====== VROOM OFFICIAL RECEIPT ======" << endl;
                    cout << "Customer:     " << name << endl;
                    cout << "Transaction:  " << transType << endl;
                    cout << "Vehicle:      " << models[carChoice - 1] << endl;
                    if (option == 2) cout << "Days Rented:  " << days << endl;
                    cout << "Total Cost:   P " << totalCost << endl;
                    cout << "====================================" << endl;

                    // --- SAVE TO CSV FILE ---
                    ofstream csvFile("vroom_transactions.csv", ios::app);
                    if (csvFile.is_open()) {
                        // Saving format: "Name","Type","Car",Cost
                        csvFile << "\"" << name << "\"," << transType << ","
                                << models[carChoice - 1] << "," << totalCost << endl;
                        csvFile.close();
                        cout << "Record saved to database successfully!" << endl;
                    } else {
                            cout << "Error opening file!" << endl;
                    }
                } else {
                    cout << "Transaction Cancelled." << endl;
                    break;
                }
            }

            // CASE 4: VIEW REPORTS (READING FROM FILE)
            case 4:
            {
                cout << "\n--- TRANSACTION HISTORY FILE ---" << endl;

                // Open the file for READING (ifstream)
                ifstream inFile("vroom_transactions.csv");

                if (!inFile.is_open()) {
                    cout << "No transaction history found (File does not exist)." << endl;
                }
                else {
                    string line;
                    cout << "Raw Data (Name, Type, Car, Amount):" << endl;
                    cout << "------------------------------------" << endl;

                    // Loop through every line in the file
                    while (getline(inFile, line)) {
                        cout << line << endl;
                    }
                    inFile.close(); // Always close the file
                }
            break;
            }

            // CASE 5: EXIT
            case 5:
                cout << "Exiting system..." << endl;
                cout << "Thank you have a nice day!" << endl;
            break;

            // DEFAULT
            default:
                cout << "Invalid Input. Please enter a number between 1 and 5." << endl;
                break;
        }
    } while (option != 5);
    return 0;
}
