#include <stdio.h>
#include <string.h>

// Structure to hold booking information
struct Booking {
    int table;        // Table number
    int pax;          // Number of people
    char name[20];    // Name of the person booking
    char time[6];     // Time of booking (e.g., "18:30")
    char req[100];    // Special requests
};

// Define the table capacities
#define MAX_BOOKINGS 60
struct Table {
    int number;
    int capacity;
    int isAvailable;
} tables[] = {
    {3, 2, 1}, {4, 4, 1}, {5, 2, 1}, {6, 2, 1}, {7, 2, 1}, {8, 2, 1}, {9, 2, 1}, {10, 2, 1},
    {12, 6, 1}, {20, 4, 1}, {21, 4, 1}, {22, 10, 1}, {41, 6, 1}, {42, 3, 1}, {43, 2, 1}, 
    {44, 4, 1}, {45, 4, 1}, {46, 4, 1}, {47, 2, 1}, {48, 4, 1}, {49, 2, 1}, {50, 2, 1}, 
    {51, 2, 1}, {53, 4, 1}, {54, 4, 1}, {55, 2, 1}, {555, 4, 1}, {56, 3, 1}, {57, 4, 1}, 
    {58, 2, 1}, {59, 8, 1}, {60, 2, 1}, {61, 2, 1}, {62, 8, 1}
};

struct Booking bookings[MAX_BOOKINGS] = {0}; // Array to store bookings
int bookingCount = 0;                       // Number of active bookings

// Function prototypes
void view(void);
void add(void);
void deleteBooking(void);
int findTable(int pax);

int main() {
    int choice;

    while (1) {
        printf("\nWelcome to the Restaurant Booking System\n");
        printf("1. View Bookings\n");
        printf("2. Add Booking\n");
        printf("3. Delete Booking\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view();
                break;
            case 2:
                add();
                break;
            case 3:
                deleteBooking();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to view all bookings
void view(void) {
    if (bookingCount == 0) {
        printf("\nNo bookings available.\n");
        return;
    }

    printf("\nCurrent Bookings:\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("Table: %d | Name: %s | People: %d | Time: %s | Requests: %s\n",
               bookings[i].table,
               bookings[i].name,
               bookings[i].pax,
               bookings[i].time,
               bookings[i].req[0] ? bookings[i].req : "None");
    }
}

// Function to find an available table for the specified number of people
int findTable(int pax) {
    for (int i = 0; i < sizeof(tables) / sizeof(tables[0]); i++) {
        if (tables[i].isAvailable && tables[i].capacity >= pax) {
            return i; // Return the index of the available table
        }
    }
    return -1; // No suitable table found
}

// Function to add a new booking
void add(void) {
    if (bookingCount >= MAX_BOOKINGS) {
        printf("\nAll tables are booked. Cannot add new booking.\n");
        return;
    }

    struct Booking newBooking;
    printf("\nEnter booking details:\n");

    // Input number of people
    printf("Number of people: ");
    scanf("%d", &newBooking.pax);

    // Find a suitable table
    int tableIndex = findTable(newBooking.pax);
    if (tableIndex == -1) {
        printf("\nNo available table can accommodate %d people.\n", newBooking.pax);
        return;
    }

    newBooking.table = tables[tableIndex].number;
    tables[tableIndex].isAvailable = 0; // Mark the table as booked

    // Input other booking details
    printf("Name: ");
    scanf("%s", newBooking.name);

    printf("Time (HH:MM): ");
    scanf("%s", newBooking.time);

    printf("Special requests (leave empty if none): ");
    getchar(); // Clear newline character from the buffer
    fgets(newBooking.req, sizeof(newBooking.req), stdin);
    newBooking.req[strcspn(newBooking.req, "\n")] = 0; // Remove newline character

    // Add the booking
    bookings[bookingCount++] = newBooking;
    printf("\nBooking added successfully at Table %d!\n", newBooking.table);
}

// Function to delete a booking
void deleteBooking(void) {
    if (bookingCount == 0) {
        printf("\nNo bookings available to delete.\n");
        return;
    }

    int tableNumber;
    printf("\nEnter the table number to delete booking: ");
    scanf("%d", &tableNumber);

    // Search for the booking
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].table == tableNumber) {
            // Mark the table as available again
            for (int j = 0; j < sizeof(tables) / sizeof(tables[0]); j++) {
                if (tables[j].number == tableNumber) {
                    tables[j].isAvailable = 1;
                    break;
                }
            }

            // Shift the remaining bookings to fill the gap
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            printf("Booking for table %d deleted successfully.\n", tableNumber);
            return;
        }
    }

    printf("No booking found for table %d.\n", tableNumber);
}
