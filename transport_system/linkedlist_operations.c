#include "transport_system.h"

/*=============================================================================
 * LINKED LIST IMPLEMENTATION - Passenger Information Management (CO2)
 * 
 * This singly linked list maintains passenger profiles with their details.
 * Allows dynamic addition, deletion, and searching of passenger records.
 *===========================================================================*/

/**
 * Create a new passenger node
 * Allocates memory and initializes passenger data
 */
PassengerNode* createPassengerNode(int id, const char* name, const char* phone, const char* email) {
    // Input validation
    if (name == NULL || phone == NULL || email == NULL) {
        printf("Error: NULL string provided\n");
        return NULL;
    }
    
    // Allocate memory for new node
    PassengerNode* newNode = (PassengerNode*)malloc(sizeof(PassengerNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    
    // Initialize passenger data
    newNode->passengerId = id;
    strncpy(newNode->name, name, MAX_NAME_LENGTH - 1);
    newNode->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null termination
    
    strncpy(newNode->phone, phone, 14);
    newNode->phone[14] = '\0';
    
    strncpy(newNode->email, email, MAX_NAME_LENGTH - 1);
    newNode->email[MAX_NAME_LENGTH - 1] = '\0';
    
    newNode->totalBookings = 0;
    newNode->next = NULL;
    
    return newNode;
}

/**
 * Add a new passenger to the linked list
 * Inserts at the beginning for O(1) complexity
 */
PassengerNode* addPassenger(PassengerNode* head, int id, const char* name, 
                           const char* phone, const char* email) {
    // Check for duplicate passenger ID
    if (searchPassenger(head, id) != NULL) {
        printf("Error: Passenger with ID %d already exists!\n", id);
        return head;
    }
    
    // Create new node
    PassengerNode* newNode = createPassengerNode(id, name, phone, email);
    if (newNode == NULL) {
        return head;
    }
    
    // Insert at beginning
    newNode->next = head;
    head = newNode;
    
    printf("=> Passenger added successfully! ID: %d, Name: %s\n", id, name);
    
    return head;
}

/**
 * Search for a passenger by ID
 * Returns pointer to node if found, NULL otherwise
 */
PassengerNode* searchPassenger(PassengerNode* head, int id) {
    PassengerNode* current = head;
    
    // Traverse the list
    while (current != NULL) {
        if (current->passengerId == id) {
            return current;  // Passenger found
        }
        current = current->next;
    }
    
    return NULL;  // Passenger not found
}

/**
 * Delete a passenger from the linked list
 * Returns updated head pointer
 */
PassengerNode* deletePassenger(PassengerNode* head, int id) {
    if (head == NULL) {
        printf("Error: Passenger list is empty\n");
        return NULL;
    }
    
    PassengerNode* current = head;
    PassengerNode* previous = NULL;
    
    // Search for the node to delete
    while (current != NULL && current->passengerId != id) {
        previous = current;
        current = current->next;
    }
    
    // Passenger not found
    if (current == NULL) {
        printf("Error: Passenger with ID %d not found\n", id);
        return head;
    }
    
    // Delete the node
    if (previous == NULL) {
        // Deleting the first node
        head = current->next;
    } else {
        // Deleting a middle or last node
        previous->next = current->next;
    }
    
    printf("=> Passenger deleted: ID %d, Name: %s\n", current->passengerId, current->name);
    free(current);
    
    return head;
}

/**
 * Display all passengers in the linked list
 */
void displayAllPassengers(PassengerNode* head) {
    if (head == NULL) {
        printf("\n No passengers registered.\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                      REGISTERED PASSENGERS                             |\n");
    printf("==========================================================================\n");
    
    printf("%-8s %-25s %-15s %-30s %-10s\n", 
           "ID", "Name", "Phone", "Email", "Bookings");
    printf("--------------------------------------------------------------------------------\n");
    
    PassengerNode* current = head;
    int count = 0;
    
    while (current != NULL) {
        printf("%-8d %-25s %-15s %-30s %-10d\n", 
               current->passengerId, 
               current->name, 
               current->phone, 
               current->email, 
               current->totalBookings);
        
        current = current->next;
        count++;
    }
    
    printf("\nTotal Passengers: %d\n\n", count);
}

/**
 * Display details of a specific passenger
 */
void displayPassengerDetails(PassengerNode* passenger) {
    if (passenger == NULL) {
        printf("Error: Passenger not found\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                          PASSENGER DETAILS                             |\n");
    printf("==========================================================================\n");
    printf("  Passenger ID    : %d\n", passenger->passengerId);
    printf("  Name            : %s\n", passenger->name);
    printf("  Phone           : %s\n", passenger->phone);
    printf("  Email           : %s\n", passenger->email);
    printf("  Total Bookings  : %d\n", passenger->totalBookings);
    printf("═══════════════════════════════════════════════════════════════════\n\n");
}

/**
 * Free all memory allocated for the passenger linked list
 * Important for preventing memory leaks
 */
void freePassengerList(PassengerNode* head) {
    PassengerNode* current = head;
    PassengerNode* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    printf("=> Passenger list memory freed.\n");
}

/**
 * Update passenger booking count
 */
void updatePassengerBookings(PassengerNode* passenger) {
    if (passenger != NULL) {
        passenger->totalBookings++;
        printf("=> Booking count updated for %s: %d bookings\n", 
               passenger->name, passenger->totalBookings);
    }
}