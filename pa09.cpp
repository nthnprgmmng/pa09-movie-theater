
#include <iostream>
#include <iomanip>

using namespace std;

// ** Global constants *****************************************************
const int MAX_ROWS = 4;            //  Maximum number of rows.
const int MAX_SEATS = 12;          // Maximum number of seats per row.
const double SEAT_PRICE = 10.00;   // Price per seat.

/**
* @brief Structure representing a seat.
*
* Contains booking status, row number, seat number, and price.
*/
struct Seat {
    bool isBooked;   // True if booked, false if available.
    int rowNumber;   // 1-based row number.
    int seatNumber;  // 1-based seat number.
    double price;    // Price of the seat.
};

// ** Function prototypes **************************************************
void displaySeatingChart(const Seat seats[][MAX_SEATS]);
bool bookSeat(Seat seats[][MAX_SEATS], double& totalSales);
bool cancelSeat(Seat seats[][MAX_SEATS], double& totalSales);
void displaySalesSummary(const Seat seats[][MAX_SEATS], double totalSales);
int displayMenu();

int main() {
    // ** Variable Declarations ********************************************
    Seat seats[MAX_ROWS][MAX_SEATS];  // 2D array of Seat structs.
    int menuChoice;                   // User's menu selection.
    double totalSales = 0.0;          // Total ticket sales amount.
    int row;                          // Loop counter for rows.
    int col;                          // Loop counter for columns.
    bool bookResult;                    // Stores result of function bookSeat.
    bool cancelResult;                  // Stores result of function cancelSeat.

    // Initialize seating chart
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_SEATS; col++) {
            seats[row][col].isBooked = false;
            seats[row][col].rowNumber = row + 1;
            seats[row][col].seatNumber = col + 1;
            seats[row][col].price = SEAT_PRICE;
        }
    }

    cout << "Welcome to the C++ Theater Booking System!" << endl;

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                displaySeatingChart(seats);
                break;

            case 2:
                bookResult = bookSeat(seats, totalSales);

                if (!bookResult) {
                    cout << "\nCannot book an already booked seat." << endl;
                    cout << "Row and seat must be within allowed range."
                         << endl;
                }

                break;

            case 3:
                cancelResult = cancelSeat(seats, totalSales);

                if (!cancelResult) {
                    cout << "\nCannot cancel an already open seat." << endl;
                    cout << "Row and seat must be within allowed range."
                         << endl;
                }

                break;

            case 4:
                displaySalesSummary(seats, totalSales);
                break;

            case 5:
                cout << "Thank you for using the C++ Theater Booking System!"
                     << endl;
                break;

            default:
                cout << "Invalid choice. Please select from the menu." << endl;
                break;
        }
    } while (menuChoice != 5);

    return 0;
}
/**
* @brief Displays the current seating chart.
*
* Shows "O" for open seats and "X" for booked seats.
*
* @param seats The 2D array of Seat structs.
* @return None
*/
void displaySeatingChart(const Seat seats[][MAX_SEATS]) {
    cout << "\nSCREEN" << endl;

    for (int row = 0; row < MAX_ROWS; row++) {
        cout << "Row " << row + 1 << ":";

        for (int col = 0; col < MAX_SEATS; col++) {
            if (seats[row][col].isBooked) {
                cout << " X ";
            } else {
                cout << " O ";
            }
        }

        cout << endl;
    }
}
/**
* @brief Books a seat if available and updates total sales.
*
* @param seats The 2D array of Seat structs.
* @param totalSales Reference to total ticket sales amount.
* @return true if booking succeeded, false otherwise.
*/
bool bookSeat(Seat seats[][MAX_SEATS], double& totalSales) {
    int row;
    int seat;
    bool check = false;
    cout << "\nBooking a seat..." << endl;
    cout << "Enter Row (1-4): ";
    cin >> row;
    cout << "Enter Seat (1-12): ";
    cin >> seat;

    if (row - 1 < MAX_ROWS && seat - 1 < MAX_SEATS) {
        if (!seats[row - 1][seat - 1].isBooked) {
            check = true;
            seats[row - 1][seat - 1].isBooked = true;
            totalSales += SEAT_PRICE;
            cout << "\nSeat booked successfully: Row " << row << ","
                 << " Seat " <<
                 seat << " ($10.00)" << endl;
        }
    }

    return check;
}
/**
* @brief Cancels a seat booking if it exists and updates total sales.
*
* @param seats The 2D array of Seat structs.
* @param totalSales Reference to total ticket sales amount.
* @return true if cancellation succeeded, false otherwise.
*/
bool cancelSeat(Seat seats[][MAX_SEATS], double& totalSales) {
    int row;
    int seat;
    bool check = false;
    cout << "Canceling a seat..." << endl;
    cout << "Enter Row (1-4): ";
    cin >> row;
    cout << "Enter Seat (1-12): ";
    cin >> seat;

    if (row - 1 < MAX_ROWS && seat - 1 < MAX_SEATS) {
        if (seats[row - 1][seat - 1].isBooked) {
            check = true;
            seats[row - 1][seat - 1].isBooked = false;
            totalSales -= SEAT_PRICE;
            cout << "\nSeat canceled successfully: Row " << row << ","
                 << " Seat "
                 << seat << " ($10.00)" << endl;
        }
    }

    return check;
}
/**
* @brief Displays sales summary report.
*
* Shows seats sold, available, and total sales amount.
*
* @param seats The 2D array of Seat structs.
* @param totalSales The current total sales amount.
* @return None
*/
void displaySalesSummary(const Seat seats[][MAX_SEATS], double totalSales) {
    int seatsAvailable = 0;

    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_SEATS; col++) {
            if (!seats[row][col].isBooked) {
                seatsAvailable++;
            }
        }
    }

    cout << "\nSales Summary:" << endl;
    cout << "Seats Sold: " << static_cast<int>(totalSales / 10) << endl;
    cout << "Seats Available: " << seatsAvailable << endl;
    cout << fixed << setprecision(2);
    cout << "Total Sales: $" << totalSales << endl;
}
/**
* @brief Displays the main menu and reads user's choice.
*
* @return An integer representing the user's menu choice.
*/
int displayMenu() {
    int choice;  // User's menu selection
    cout << "\n1. Display Seating Chart" << endl;
    cout << "2. Book a Seat" << endl;
    cout << "3. Cancel a Booking" << endl;
    cout << "4. View Sales Summary" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}
