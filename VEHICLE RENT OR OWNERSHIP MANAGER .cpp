#include <iostream>
#include <string>
using namespace std;

int main() {
    // Car data stored in parallel arrays
    string models[3] = {"Toyota Corolla", "Honda Civic", "Ford Ranger"};
    int years[3] = {2020, 2021, 2019};
    int prices[3] = {850000, 950000, 1200000};
    bool available[3] = {true, true, true};

    // Transaction data
    string custNames[10], custTypes[10], custCars[10];
    int custAges[10];
    double custAmounts[10];
    int transactionCount = 0;

    int choice;
    string name; 
    int age, carChoice;

    cout << "Welcome to VROOM - Vehicle Rent Or Ownership Manager!\n";

    // --- DO-WHILE LOOP for menu ---
    do { 
        cout << "\n==============================\n";
        cout << "OPTIONS\n";
        cout << "==============================\n";
        cout << "[1] View Cars" << endl;
        cout << "[2] Rent a Car" << endl;
        cout << "[3] Buy a Car" << endl;
        cout << "[4] View Transactions Report" << endl;
        cout << "[5] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // --- FOR LOOP to display cars ---
            cout << "\nAvailable Cars:\n";
            for (int i = 0; i < 3; i++) {
                if (available[i]) {
                    cout << i+1 << ". " << models[i] << " (" << years[i] 
                         << ") - ₱" << prices[i] << endl;
                }
            }
        }
        else if (choice == 2 || choice == 3) {
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, name);

            cout << "Enter your age: ";
            cin >> age;

            // --- IF/ELSE + WHILE for age validation ---
            if (age < 18) {
                cout << "Sorry, you must be at least 18. System terminated.\n";
                return 0; // terminate immediately
            }
            while (age > 100) {
                cout << "Invalid age. Age must be between 18 and 100.\n";
                cout << "Enter your age again: ";
                cin >> age;
            }

            cout << "Choose a car (1-3): ";
            cin >> carChoice;

            if (carChoice < 1 || carChoice > 3 || !available[carChoice-1]) {
                cout << "Invalid choice or car not available.\n";
                continue;
            }

            string type = (choice == 2) ? "Rent" : "Buy";
            double amount = (type == "Rent") ? prices[carChoice-1] * 0.1 : prices[carChoice-1];

            // Save transaction
            custNames[transactionCount] = name;
            custAges[transactionCount] = age;
            custTypes[transactionCount] = type;
            custCars[transactionCount] = models[carChoice-1];
            custAmounts[transactionCount] = amount;
            transactionCount++;

            if (type == "Buy") available[carChoice-1] = false;

            cout << "Transaction complete: " << name << " chose to " << type 
                 << " " << models[carChoice-1] << " for ₱" << amount << endl;
        }
        else if (choice == 4) {
            cout << "\n--- Transaction Report ---\n";
            if (transactionCount == 0) {
                cout << "No transactions yet.\n";
            } else {
                double totalSales = 0, totalRentals = 0;
                int buyCount = 0, rentalCount = 0;

                // --- FOR LOOP to display transactions ---
                for (int i = 0; i < transactionCount; i++) {
                    cout << custNames[i] << " (Age " << custAges[i] << ") chose to "
                         << custTypes[i] << " " << custCars[i] << " for ₱" << custAmounts[i] << endl;

                    if (custTypes[i] == "Rent") {
                        totalRentals += custAmounts[i];
                        rentalCount++;
                    } else {
                        totalSales += custAmounts[i];
                        buyCount++;
                    }
                }

                cout << "\n--- Summary ---\n";
                cout << "Total Rentals: ₱" << totalRentals << " (" << rentalCount << " transactions)\n";
                cout << "Total Sales: ₱" << totalSales << " (" << buyCount << " transactions)\n";

                int totalTransactions = rentalCount + buyCount;
                if (totalTransactions > 0) {
                    cout << "Average Transaction Value: ₱" 
                         << (totalRentals + totalSales) / totalTransactions << endl;
                }
            }
        }
        else if (choice == 5) {
            cout << "Exiting VROOM. Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5); // (do while loop) keeps menu running

    return 0;
}
