// hostel.c
// Simple Hostel Management System
// Made for a freshman small project - kept very simple
// Compile with: gcc hostel.c -o hostel
// Run with: ./hostel

#include <stdio.h>
#include <string.h> // for strcpy and strcmp

#define MAX 100 // maximum number of rooms we can store

// 0 = VACANT, 1 = RESERVED, 2 = ALLOCATED
// We use numbers to keep it simple

struct Room {
    char hostelName[30];  // name of hostel, e.g MaleHostel
    int roomNo;           // room number, e.g 101
    int status;           // 0 vacant, 1 reserved, 2 allocated
    char studentName[30]; // name of student staying / reserving
    char studentId[20];   // student ID / matric number
};

// Global variables (freshman style - easy to access everywhere)
struct Room rooms[MAX];
int totalRooms = 0; // how many rooms we have now

// Function to add a new hostel room (Admin work)
void addRoom() {
    // check if array is full
    if (totalRooms >= MAX) {
        printf("Sorry, no more space to add rooms.\n");
        return;
    }

    printf("\n--- Add Hostel Room ---\n");
    printf("Enter hostel name (no space, use MaleHostel): ");
    scanf("%s", rooms[totalRooms].hostelName);

    printf("Enter room number (e.g 101): ");
    scanf("%d", &rooms[totalRooms].roomNo);

    // new room is always vacant at first
    rooms[totalRooms].status = 0;
    strcpy(rooms[totalRooms].studentName, "None");
    strcpy(rooms[totalRooms].studentId, "None");

    printf("Room added! %s Room %d is now VACANT.\n", rooms[totalRooms].hostelName, rooms[totalRooms].roomNo);

    totalRooms++; // increase count
}

// Function to show one room in a fine line
void printRoom(int i) {
    char statusWord[20];
    // change number status to word for display
    if (rooms[i].status == 0)
        strcpy(statusWord, "VACANT");
    else if (rooms[i].status == 1)
        strcpy(statusWord, "RESERVED");
    else
        strcpy(statusWord, "ALLOCATED");

    printf("%s Room %d | %s | Student: %s (%s)\n",
           rooms[i].hostelName, rooms[i].roomNo,
           statusWord,
           rooms[i].studentName, rooms[i].studentId);
}

// Show all rooms
void showAllRooms() {
    int i;
    printf("\n--- All Rooms ---\n");
    if (totalRooms == 0) {
        printf("No rooms yet. Admin should add rooms first.\n");
        return;
    }
    for (i = 0; i < totalRooms; i++) {
        printf("%d. ", i + 1);
        printRoom(i);
    }
}

// Student books a vacant room (it becomes RESERVED)
void bookRoom() {
    int i, found = 0;
    int rno;
    char hname[30];

    printf("\n--- Student Book Room ---\n");
    printf("Vacant rooms are:\n");
    // first show only vacant rooms
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 0) {
            printRoom(i);
            found = 1;
        }
    }
    if (found == 0) {
        printf("No vacant rooms to book.\n");
        return;
    }

    // ask which room they want
    printf("Enter hostel name to book: ");
    scanf("%s", hname);
    printf("Enter room number to book: ");
    scanf("%d", &rno);

    // search for the room
    for (i = 0; i < totalRooms; i++) {
        // strcmp == 0 means strings are equal
        if (strcmp(rooms[i].hostelName, hname) == 0 && rooms[i].roomNo == rno) {
            // check if vacant
            if (rooms[i].status != 0) {
                printf("Sorry, that room is not vacant.\n");
                return;
            }
            // take student details
            printf("Enter your name (no space): ");
            scanf("%s", rooms[i].studentName);
            printf("Enter your student ID: ");
            scanf("%s", rooms[i].studentId);

            rooms[i].status = 1; // 1 = reserved
            printf("Booked! You have RESERVED %s Room %d.\n", hname, rno);
            printf("Wait for Admin to ALLOCATE you.\n");
            return;
        }
    }
    printf("Room not found.\n");
}

// Admin allocates a reserved room (RESERVED -> ALLOCATED)
void allocateRoom() {
    int i;
    int rno;
    char hname[30];

    printf("\n--- Admin Allocate Room ---\n");
    printf("Reserved rooms are:\n");
    int found = 0;
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 1) {
            printRoom(i);
            found = 1;
        }
    }
    if (found == 0) {
        printf("No reserved rooms to allocate.\n");
        return;
    }

    printf("Enter hostel name to allocate: ");
    scanf("%s", hname);
    printf("Enter room number to allocate: ");
    scanf("%d", &rno);

    for (i = 0; i < totalRooms; i++) {
        if (strcmp(rooms[i].hostelName, hname) == 0 && rooms[i].roomNo == rno) {
            if (rooms[i].status != 1) {
                printf("That room is not reserved. Cannot allocate.\n");
                return;
            }
            rooms[i].status = 2; // 2 = allocated
            printf("Done! %s Room %d ALLOCATED to %s.\n", hname, rno, rooms[i].studentName);
            return;
        }
    }
    printf("Room not found.\n");
}

// Admin clears a room (makes it vacant again)
void clearRoom() {
    int i;
    int rno;
    char hname[30];

    printf("\n--- Admin Clear Room ---\n");
    showAllRooms();
    if (totalRooms == 0) return;

    printf("Enter hostel name to clear: ");
    scanf("%s", hname);
    printf("Enter room number to clear: ");
    scanf("%d", &rno);

    for (i = 0; i < totalRooms; i++) {
        if (strcmp(rooms[i].hostelName, hname) == 0 && rooms[i].roomNo == rno) {
            if (rooms[i].status == 0) {
                printf("Room is already vacant.\n");
                return;
            }
            // clear student info and make vacant
            rooms[i].status = 0;
            strcpy(rooms[i].studentName, "None");
            strcpy(rooms[i].studentId, "None");
            printf("Room cleared. It is now VACANT.\n");
            return;
        }
    }
    printf("Room not found.\n");
}

// REPORTS - just loops and prints rooms with wanted status

void reportStudents() {
    int i, found = 0;
    printf("\n--- Report: Current Students in Hostel Rooms ---\n");
    printf("(These are ALLOCATED rooms)\n");
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 2) {
            printRoom(i);
            found = 1;
        }
    }
    if (!found) printf("No students allocated yet.\n");
}

void reportReserved() {
    int i, found = 0;
    printf("\n--- Report: Reserved Rooms ---\n");
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 1) {
            printRoom(i);
            found = 1;
        }
    }
    if (!found) printf("No reserved rooms.\n");
}

void reportAllocated() {
    int i, found = 0;
    printf("\n--- Report: Allocated Rooms ---\n");
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 2) {
            printRoom(i);
            found = 1;
        }
    }
    if (!found) printf("No allocated rooms.\n");
}

void reportVacant() {
    int i, found = 0;
    printf("\n--- Report: Vacant Rooms ---\n");
    for (i = 0; i < totalRooms; i++) {
        if (rooms[i].status == 0) {
            printRoom(i);
            found = 1;
        }
    }
    if (!found) printf("No vacant rooms.\n");
}

// Small menu for Admin
void adminMenu() {
    int choice;
    while (1) {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Hostel Room\n");
        printf("2. Show All Rooms\n");
        printf("3. Allocate Reserved Room to Student\n");
        printf("4. Clear Student from Room\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) addRoom();
        else if (choice == 2) showAllRooms();
        else if (choice == 3) allocateRoom();
        else if (choice == 4) clearRoom();
        else if (choice == 5) break; // go back
        else printf("Wrong choice, try again.\n");
    }
}

// Small menu for Student
void studentMenu() {
    int choice;
    while (1) {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. View Vacant Rooms\n");
        printf("2. Book a Vacant Room\n");
        printf("3. Show All Rooms\n");
        printf("4. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) reportVacant();
        else if (choice == 2) bookRoom();
        else if (choice == 3) showAllRooms();
        else if (choice == 4) break;
        else printf("Wrong choice, try again.\n");
    }
}

// Small menu for Reports
void reportMenu() {
    int choice;
    while (1) {
        printf("\n===== REPORTS MENU =====\n");
        printf("1. List of current students in hostel rooms\n");
        printf("2. List of reserved rooms\n");
        printf("3. List of allocated rooms\n");
        printf("4. List of vacant rooms\n");
        printf("5. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) reportStudents();
        else if (choice == 2) reportReserved();
        else if (choice == 3) reportAllocated();
        else if (choice == 4) reportVacant();
        else if (choice == 5) break;
        else printf("Wrong choice, try again.\n");
    }
}

// This function adds some rooms at start so demo is easy
void addSampleData() {
    // Room 1
    strcpy(rooms[0].hostelName, "MaleHostel");
    rooms[0].roomNo = 101;
    rooms[0].status = 0;
    strcpy(rooms[0].studentName, "None");
    strcpy(rooms[0].studentId, "None");
    // Room 2
    strcpy(rooms[1].hostelName, "MaleHostel");
    rooms[1].roomNo = 102;
    rooms[1].status = 0;
    strcpy(rooms[1].studentName, "None");
    strcpy(rooms[1].studentId, "None");
    // Room 3
    strcpy(rooms[2].hostelName, "FemaleHostel");
    rooms[2].roomNo = 201;
    rooms[2].status = 0;
    strcpy(rooms[2].studentName, "None");
    strcpy(rooms[2].studentId, "None");

    totalRooms = 3;
}

// Main program - shows main menu again and again
int main() {
    int choice;

    addSampleData(); // load 3 sample rooms for quick testing

    printf("===================================\n");
    printf("  HOSTEL MANAGEMENT SYSTEM\n");
    printf("===================================\n");

    while (1) {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Admin\n");
        printf("2. Student\n");
        printf("3. Reports\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) adminMenu();
        else if (choice == 2) studentMenu();
        else if (choice == 3) reportMenu();
        else if (choice == 4) {
            printf("Bye! Thanks for using Hostel System.\n");
            break;
        } else {
            printf("Wrong choice, try again.\n");
        }
    }

    return 0; // end program
}
