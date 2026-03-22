#include "transport_system.h"

/*=============================================================================
 * BINARY SEARCH IMPLEMENTATION - Ticket ID Lookup (CO4)
 * 
 * Binary search requires sorted data. We first sort tickets by ID using
 * bubble sort, then perform efficient O(log n) lookup.
 *===========================================================================*/

/**
 * Bubble Sort - Sort tickets array by ticket ID in ascending order
 * Used to prepare data for binary search
 * Time Complexity: O(n²)
 */
void sortTicketsByIdBubbleSort(Ticket tickets[], int n) {
    // Input validation
    if (tickets == NULL || n <= 0) {
        printf("Error: Invalid input for sorting\n");
        return;
    }
    
    int i, j;
    Ticket temp;
    int swapped;
    
    // Bubble sort algorithm with optimization
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        
        for (j = 0; j < n - i - 1; j++) {
            // Compare adjacent ticket IDs
            if (tickets[j].ticketId > tickets[j + 1].ticketId) {
                // Swap tickets
                temp = tickets[j];
                tickets[j] = tickets[j + 1];
                tickets[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // If no swaps occurred, array is already sorted
        if (swapped == 0) {
            break;
        }
    }
    
    printf("=> Tickets sorted by ID (Total: %d tickets)\n", n);
}

/**
 * Binary Search - Find ticket by ID in sorted array
 * Returns index if found, -1 if not found
 * Time Complexity: O(log n)
 */
int binarySearchTicket(Ticket tickets[], int n, int ticketId) {
    // Input validation
    if (tickets == NULL || n <= 0) {
        printf("Error: Invalid input for search\n");
        return -1;
    }
    
    int left = 0;
    int right = n - 1;
    int comparisons = 0;  // Track number of comparisons
    
    while (left <= right) {
        comparisons++;
        
        // Calculate middle index (avoids overflow)
        int mid = left + (right - left) / 2;
        
        // Check if ticketId is at mid
        if (tickets[mid].ticketId == ticketId) {
            printf("=> Ticket found! (Comparisons made: %d)\n", comparisons);
            return mid;
        }
        
        // If ticketId is greater, ignore left half
        if (tickets[mid].ticketId < ticketId) {
            left = mid + 1;
        }
        // If ticketId is smaller, ignore right half
        else {
            right = mid - 1;
        }
    }
    
    // Ticket not found
    printf("=> Ticket ID %d not found (Comparisons made: %d)\n", 
           ticketId, comparisons);
    return -1;
}

/**
 * Display a single ticket's details
 */
void displayTicketDetails(Ticket ticket) {
    printf("\n");
    printf("==========================================================================\n");
    printf("|                         TICKET DETAILS                                 |\n");
    printf("==========================================================================\n");
    printf("  Ticket ID       : %d\n", ticket.ticketId);
    printf("  Passenger ID    : %d\n", ticket.passengerId);
    printf("  Passenger Name  : %s\n", ticket.passengerName);
    printf("  Seat Number     : %d\n", ticket.seatNumber);
    printf("  Route           : %s\n", ticket.route);
    printf("  Booking Date    : %s\n", ticket.bookingDate);
    printf("  Fare            : $%.2f\n", ticket.fare);
    printf("==========================================================================\n\n");
}

/**
 * Linear Search - Alternative search method for unsorted data
 * Returns index if found, -1 if not found
 * Time Complexity: O(n)
 */
int linearSearchTicket(Ticket tickets[], int n, int ticketId) {
    if (tickets == NULL || n <= 0) {
        printf("Error: Invalid input for search\n");
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (tickets[i].ticketId == ticketId) {
            printf("=> Ticket found using linear search at index %d\n", i);
            return i;
        }
    }
    
    printf("=> Ticket ID %d not found\n", ticketId);
    return -1;
}

/**
 * Search and display ticket information
 * Combines search with display functionality
 */
void searchAndDisplayTicket(Ticket tickets[], int n, int ticketId, int useBinarySearch) {
    int index;
    
    if (useBinarySearch) {
        printf("\n[Using Binary Search - Requires sorted data]\n");
        // Ensure tickets are sorted before binary search
        sortTicketsByIdBubbleSort(tickets, n);
        index = binarySearchTicket(tickets, n, ticketId);
    } else {
        printf("\n[Using Linear Search - Works on unsorted data]\n");
        index = linearSearchTicket(tickets, n, ticketId);
    }
    
    if (index != -1) {
        displayTicketDetails(tickets[index]);
    } else {
        printf("\nTicket with ID %d does not exist in the system.\n", ticketId);
    }
}

/**
 * Compare and demonstrate both search algorithms
 */
void compareSearchAlgorithms(Ticket tickets[], int n, int ticketId) {
    if (tickets == NULL || n <= 0) {
        printf("Error: No tickets to search\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                    SEARCH ALGORITHM COMPARISON                         |\n");
    printf("==========================================================================\n");
    printf("Searching for Ticket ID: %d in %d tickets\n\n", ticketId, n);
    
    // Linear Search
    printf("1. LINEAR SEARCH:\n");
    printf("   Time Complexity: O(n)\n");
    int linearIndex = linearSearchTicket(tickets, n, ticketId);
    if (linearIndex != -1) {
        printf("   Linear Search Result: Found at index %d\n", linearIndex);
    } else {
        printf("   Linear Search Result: Not Found\n");
    }
    
    printf("\n2. BINARY SEARCH:\n");
    printf("   Time Complexity: O(log n)\n");
    printf("   Note: Requires sorted data\n");
    sortTicketsByIdBubbleSort(tickets, n);
    binarySearchTicket(tickets, n, ticketId);
    int binaryIndex = binarySearchTicket(tickets, n, ticketId); // Variable was also unused
    if (binaryIndex != -1) {
        printf("   Binary Search Result: Found at index %d\n", binaryIndex);
    } else {
        printf("   Binary Search Result: Not Found\n");
    }
    
    printf("\n===================================================================\n");
    printf("Result: Both searches found the ticket\n");
    printf("Binary search is more efficient for large datasets!\n");
    printf("=====================================================================\n\n");
}