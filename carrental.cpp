#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Car {
    int id;
    string make;
    string model;
    int year;
    double rentalPricePerDay;  // Price is now directly in INR
    bool isAvailable;
    int rentDays;
    int dueDate;
};

// List of valid car brands (you can expand this list)
vector<string> validBrands = {"Toyota", "Honda", "Ford", "BMW", "Mercedes", "Audi", "Tesla", "Hyundai", "Kia", "Chevrolet","Tata"};

// List of valid car models (generic, can be expanded or linked to brands)
vector<string> validModels = {"Camry", "Civic", "Mustang", "Model S", "Model 3", "Corolla", "Elantra", "Sonata", "Accord", "A4", "C-Class", "X5", "Explorer","Altroz"};

// Function to display a car's details in INR
void displayCar(const Car &car) {
    cout << "Car ID: " << car.id << endl;
    cout << "Make: " << car.make << endl;
    cout << "Model: " << car.model << endl;
    cout << "Year: " << car.year << endl;
    cout << "Rental Price per Day: ₹" << car.rentalPricePerDay << " INR" << endl;
    cout << "Availability: " << (car.isAvailable ? "Available" : "Rented") << endl;
}

// Function to validate car make (against the list of valid brands)
bool isValidCarBrand(const string &brand) {
    for (const string &validBrand : validBrands) {
        if (brand == validBrand) {
            return true;
        }
    }
    return false;
}

// Function to validate car model (against the list of valid models)
bool isValidCarModel(const string &model) {
    for (const string &validModel : validModels) {
        if (model == validModel) {
            return true;
        }
    }
    return false;
}

// Function to rent a car
void rentCar(Car &car) {
    if (car.isAvailable) {
        cout << "Renting Car ID " << car.id << " - " << car.make << " " << car.model << endl;
        cout << "Enter the number of days you want to rent the car: ";
        cin >> car.rentDays;

        if (car.rentDays <= 0) {
            cout << "Invalid number of days. Please enter a positive number of days." << endl;
            return;
        }

        car.dueDate = car.rentDays;
        car.isAvailable = false;

        double totalCost = car.rentDays * car.rentalPricePerDay;

        cout << "Total cost for renting this car for " << car.rentDays << " days is ₹" 
             << totalCost << " INR" << endl;
    } else {
        cout << "Car ID " << car.id << " is already rented." << endl;
    }
}

// Function to return a car and generate an invoice
void returnCar(Car &car) {
    if (!car.isAvailable) {
        int returnDate;
        cout << "Returning Car ID " << car.id << " - " << car.make << " " << car.model << endl;
        cout << "Enter the number of days the car was actually rented: ";
        cin >> returnDate;

        if (returnDate <= 0) {
            cout << "Invalid number of days. Please enter a positive number of days." << endl;
            return;
        }

        double rentalCost = car.rentDays * car.rentalPricePerDay;
        double lateFine = 0.0;
        if (returnDate > car.dueDate) {
            lateFine = (returnDate - car.dueDate) * car.rentalPricePerDay * 0.5; // 50% of rental price per day as fine
        }
        double totalCost = rentalCost + lateFine;

        // Display invoice
        cout << "\n----- Invoice -----\n";
        cout << "Car ID: " << car.id << endl;
        cout << "Make: " << car.make << endl;
        cout << "Model: " << car.model << endl;
        cout << "Rental days: " << car.rentDays << endl;
        cout << "Due days: " << car.dueDate << endl;
        cout << "Return days: " << returnDate << endl;
        cout << "Rental cost: ₹" << rentalCost << " INR" << endl;
        if (lateFine > 0) {
            cout << "Late fine: ₹" << lateFine << " INR" << endl;
        }
        cout << "Total cost: ₹" << totalCost << " INR" << endl;
        cout << "--------------------\n";

        // Make the car available again
        car.isAvailable = true;
    } else {
        cout << "Car ID " << car.id << " is already available." << endl;
    }
}

// Function to validate car ID (positive integer)
bool isValidCarID(int carId, int numCars) {
    return carId > 0 && carId <= numCars;
}

// Function to remove a car
void removeCar(Car cars[], int &numCars, int carId) {
    if (isValidCarID(carId, numCars)) {
        if (cars[carId - 1].isAvailable) {
            // Shift cars to remove the car
            for (int i = carId - 1; i < numCars - 1; ++i) {
                cars[i] = cars[i + 1];
            }
            --numCars; // Decrease the total number of cars
            cout << "Car ID " << carId << " has been removed successfully." << endl;
        } else {
            cout << "Car ID " << carId << " is currently rented and cannot be removed." << endl;
        }
    } else {
        cout << "Invalid Car ID." << endl;
    }
}

int main() {
    // Array of cars in the rental system with prices in INR
    const int maxCars = 10;  // Maximum number of cars
    Car cars[maxCars] = {
        {1, "Toyota", "Camry", 2020, 4000.0, true, 0, 0},  // Price in INR
        {2, "Honda", "Civic", 2019, 3500.0, true, 0, 0},   // Price in INR
        {3, "Ford", "Mustang", 2021, 5000.0, true, 0, 0}   // Price in INR
    };
    int numCars = 3;  // Current number of cars

    int choice, carId;

    do {
        // Display menu
        cout << "\nCar Rental System Menu" << endl;
        cout << "1. Display Available Cars" << endl;
        cout << "2. Rent a Car" << endl;
        cout << "3. Return a Car" << endl;
        cout << "4. Add New Car" << endl;
        cout << "5. Remove a Car" << endl;  // New option to remove a car
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display available cars
                cout << "\nAvailable Cars:\n";
                for (int i = 0; i < numCars; ++i) {
                    if (cars[i].isAvailable) {
                        displayCar(cars[i]);
                        cout << "--------------------" << endl;
                    }
                }
                break;

            case 2:
                // Rent a car
                cout << "Enter the Car ID to rent: ";
                cin >> carId;
                if (isValidCarID(carId, numCars)) {
                    rentCar(cars[carId - 1]);
                } else {
                    cout << "Invalid Car ID." << endl;
                }
                break;

            case 3:
                // Return a car
                cout << "Enter the Car ID to return: ";
                cin >> carId;
                if (isValidCarID(carId, numCars)) {
                    returnCar(cars[carId - 1]);
                } else {
                    cout << "Invalid Car ID." << endl;
                }
                break;

            case 4: {
                // Add a new car with validation
                string make, model;
                int year;
                double rentalPricePerDay;

                cout << "Enter car make: ";
                cin.ignore();  // Clear input buffer
                getline(cin, make);

                if (!isValidCarBrand(make)) {
                    cout << "Invalid car make. Please enter a globally recognized car brand." << endl;
                    break;
                }

                cout << "Enter car model: ";
                getline(cin, model);

                if (!isValidCarModel(model)) {
                    cout << "Invalid car model. Please enter a recognized model." << endl;
                    break;
                }

                cout << "Enter manufacturing year: ";
                cin >> year;

                if (year < 1886 || year > 2024) {
                    cout << "Invalid year. Please enter a year between 1886 and 2024." << endl;
                    break;
                }

                cout << "Enter rental price per day (in INR): ";
                cin >> rentalPricePerDay;

                if (rentalPricePerDay <= 0) {
                    cout << "Invalid rental price. Please enter a positive price." << endl;
                    break;
                }

                if (numCars < maxCars) {
                    // Add new car to the system
                    cars[numCars] = {numCars + 1, make, model, year, rentalPricePerDay, true, 0, 0};
                    ++numCars;
                    cout << "New car added successfully!" << endl;
                } else {
                    cout << "Car inventory is full. Cannot add more cars." << endl;
                }
                break;
            }

            case 5:
                // Remove a car
                cout << "Enter the Car ID to remove: ";
                cin >> carId;
                removeCar(cars, numCars, carId);
                break;

            case 6:
                // Exit the program
                cout << "Exiting the system..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
