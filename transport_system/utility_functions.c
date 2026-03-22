#include "transport_system.h"

/*=============================================================================
 * UTILITY FUNCTIONS
 * 
 * Helper functions for the transport reservation system including
 * date handling, ID generation, and user interface.
 *===========================================================================*/

/**
 * Get current date in formatted string
 * Format: YYYY-MM-DD
 */
void getCurrentDate(char* buffer) {
    if (buffer == NULL) {
        printf("Error: NULL buffer provided\n");
        return;
    }
    
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    // Format: YYYY-MM-DD
    strftime(buffer, 20, "%Y-%m-%d", tm_info);
}

/**
 * Generate a unique ticket ID
 * Uses time-based generation for uniqueness
 */
int generateTicketId(void) {
    static int counter = 1000;  // Static counter for sequential IDs
    counter++;
    
    // Combine timestamp with counter for better uniqueness
    time_t t = time(NULL);
    int id = (int)(t % 100000) + counter;
    
    return id;
}

/**
 * Generate a unique passenger ID
 */
int generatePassengerId(void) {
    static int counter = 0;
    if (counter == 0) {
        FILE *f = fopen("id_store.txt", "r");
        if (f) { fscanf(f, "%d", &counter); fclose(f); }
    }
    counter++;
    FILE *f = fopen("id_store.txt", "w");
    fprintf(f, "%d", counter);
    fclose(f);
    return counter;
}


/**
 * Display main menu
 */
void displayMenu(void) {
    printf("\n");
    printf("====================================================================\n");
    printf("          SMART PUBLIC TRANSPORT RESERVATION SYSTEM                \n");
    printf("====================================================================\n");
    printf("\n");
    printf("------------------- BOOKING OPERATIONS ----------------------------\n");
    printf("  1. Book Ticket (Add to Queue)                               \n");
    printf("  2. Process Next Booking (Dequeue)                           \n");
    printf("  3. View Current Bookings Queue                              \n");
    printf("  4. Cancel Ticket (Add to Cancelled Log)                     \n");
    printf("  5. View Cancelled Tickets Log                               \n");
    printf("-------------------------------------------------------------------\n");
    printf("\n");
    printf("------------------- PASSENGER MANAGEMENT --------------------------\n");
    printf("  6. Register New Passenger                                   \n");
    printf("  7. Search Passenger by ID                                   \n");
    printf("  8. Delete Passenger Record                                  \n");
    printf("  9. Display All Passengers                                   \n");
    printf("-------------------------------------------------------------------\n");
    printf("\n");
    printf("------------------- ROUTE MANAGEMENT ------------------------------\n");
    printf("  10. Add New Bus Route                                       \n");
    printf("  11. Add Stop to Route                                       \n");
    printf("  12. Connect Routes                                          \n");
    printf("  13. Display All Routes                                      \n");
    printf("  14. Display Route Details                                   \n");
    printf("-------------------------------------------------------------------\n");
    printf("\n");
    printf("------------------- SEARCH OPERATIONS -----------------------------\n");
    printf("  15. Search Ticket by ID (Binary Search)                     \n");
    printf("  16. Compare Search Algorithms                               \n");
    printf("-------------------------------------------------------------------\n");
    printf("\n");
    printf("------------------- SYSTEM ----------------------------------------\n");
    printf("  0. Exit System                                              \n");
    printf("-------------------------------------------------------------------\n");
    printf("\nEnter your choice: ");
}

/**
 * Clear input buffer
 * Useful after scanf to remove newline characters
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Function to check if the specific seat on the route is already booked.
// It assumes a ticket in allTickets is active/booked.

int isSeatTaken(Ticket allTickets[], int totalTickets, const char* route, int seatNumber) {
    for (int i = 0; i < totalTickets; i++) {
        // 1. Check if the Route names match (case-sensitive comparison)
        // 2. Check if the Seat Numbers match
        if (strcmp(allTickets[i].route, route) == 0 &&
            allTickets[i].seatNumber == seatNumber) {
            
            return 1; // Seat is TAKEN!
        }
    }
    return 0; // Seat is AVAILABLE.
}
/**
 * Validate phone number format
 * Returns 1 if valid, 0 otherwise
 */
int validatePhone(const char* phone) {
    if (phone == NULL) return 0;
    
    int len = strlen(phone);
    if (len < 10 || len > 14) return 0;
    
    // Check if all characters are digits, spaces, or hyphens
    for (int i = 0; i < len; i++) {
        if (!((phone[i] >= '0' && phone[i] <= '9') || 
              phone[i] == ' ' || 
              phone[i] == '-' || 
              phone[i] == '+')) {
            return 0;
        }
    }
    
    return 1;
}

/**
 * Validate email format (basic validation)
 * Returns 1 if valid, 0 otherwise
 */
int validateEmail(const char* email) {
    if (email == NULL) return 0;
    
    int len = strlen(email);
    if (len < 5) return 0;  // Minimum: a@b.c
    
    // Check for @ and . in email
    int hasAt = 0, hasDot = 0;
    
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') hasAt = 1;
        if (email[i] == '.' && hasAt) hasDot = 1;
    }
    
    return (hasAt && hasDot);
}

/**
 * Display system statistics
 */
void displaySystemStats(SeatQueue* sq, CancelledQueue* cq, PassengerNode* passengers, RouteGraph* graph) {
    printf("\n");
    printf("====================================================================\n");
    printf("|                     SYSTEM STATISTICS                             \n");
    printf("====================================================================\n");
    
    // Count passengers
    int passengerCount = 0;
    PassengerNode* current = passengers;
    while (current != NULL) {
        passengerCount++;
        current = current->next;
    }
    
    printf("  Active Bookings        : %d\n", sq->count);
    printf("  Cancelled Tickets      : %d\n", cq->count);
    printf("  Registered Passengers  : %d\n", passengerCount);
    printf("  Available Routes       : %d\n", graph->routeCount);
    printf("====================================================================\n\n");
}

/**
 * Pause and wait for user input
 */
/**
 * Pause and wait for user input, clearing all characters until Enter.
 */
void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    
    // 1. Clears any junk left from a previous scanf (like the newline)
    clearInputBuffer(); 
    
    // 2. We now need a way to wait for the next keypress. 
    // The previous getchar() in clearInputBuffer may have consumed the previous ENTER.
    // Let's use a robust wait-for-newline loop here instead of the two-function call.
    
    // REPLACE the two lines above with this robust implementation:
    int c;
    // This loop effectively clears the buffer AND waits for the user's ENTER.
    // We are essentially waiting for the current keystrokes to end with a newline.
    while ((c = getchar()) != '\n' && c != EOF) {
        // This loop body discards characters and is a foolproof pause.
    }
}
/**
 * Display welcome banner
 */
void displayWelcomeBanner(void) {
    printf("\n");
    printf("====================================================================\n");
    printf("|                                                                  |\n");
    printf("|         SMART PUBLIC TRANSPORT RESERVATION SYSTEM                |\n");
    printf("|                                                                  |\n");
    printf("|                   Data Structures Project                        |\n");
    printf("|                                                                  |\n");
    printf("====================================================================\n");
    printf("\n");
    printf("  Implementing:\n");
    printf("    * Linear Queue - Seat Booking Management\n");
    printf("    * Circular Queue - Cancelled Ticket Logs\n");
    printf("    * Linked List - Passenger Information\n");
    printf("    * Graph - Bus Route Network\n");
    printf("    * Binary Search - Efficient Ticket Lookup\n");
    printf("\n");
    printf("====================================================================\n");
}

/**
 * Display exit message
 */
void displayExitMessage(void) {
    printf("\n");
    printf("====================================================================\n");
    printf("                    THANK YOU FOR USING                             \n");
    printf("          SMART PUBLIC TRANSPORT RESERVATION SYSTEM                \n");
    printf("                                                                    \n");
    printf("                      Have a safe journey!                         \n");
    printf("====================================================================\n");
    printf("\n");
}