#include "transport_system.h"

/* Windows compatibility - disable format warnings for custom format specifiers */
#ifdef _WIN32
#pragma GCC diagnostic ignored "-Wformat"
#endif

/*=============================================================================
 * LINEAR QUEUE IMPLEMENTATION - Seat Booking Queue (CO1)
 * 
 * This queue manages seat bookings in a First-Come-First-Serve manner.
 * When seats are booked, they are added to the rear of the queue.
 * When passengers board, tickets are removed from the front.
 *===========================================================================*/

/**
 * Initialize the seat booking queue
 * Sets front and rear to -1 indicating empty queue
 */
void initSeatQueue(SeatQueue* q) {
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return;
    }
    q->front = -1;
    q->rear = -1;
    q->count = 0;
    printf("Seat booking queue initialized successfully.\n");
}

/**
 * Check if seat queue is full
 * Returns 1 if full, 0 otherwise
 */
int isSeatQueueFull(SeatQueue* q) {
    if (q == NULL) return 1;
    return (q->rear == MAX_QUEUE_SIZE - 1);
}

/**
 * Check if seat queue is empty
 * Returns 1 if empty, 0 otherwise
 */
int isSeatQueueEmpty(SeatQueue* q) {
    if (q == NULL) return 1;
    return (q->front == -1 || q->front > q->rear);
}

/**
 * Add a ticket to the seat booking queue
 * Returns 1 on success, 0 on failure
 */
int enqueueSeat(SeatQueue* q, Ticket ticket) {
    // Input validation
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return 0;
    }
    
    // Check if queue is full
    if (isSeatQueueFull(q)) {
        printf("Error: Seat queue is full! Cannot book more seats.\n");
        return 0;
    }
    
    // If queue is empty, set front to 0
    if (q->front == -1) {
        q->front = 0;
    }
    
    // Add ticket to rear and increment
    q->rear++;
    q->tickets[q->rear] = ticket;
    q->count++;
    
    printf("=> Ticket booked successfully! Ticket ID: %d, Seat: %d\n", 
           ticket.ticketId, ticket.seatNumber);
    
    return 1;
}

/**
 * Remove a ticket from the front of the seat queue
 * Returns 1 on success, 0 on failure
 */
int dequeueSeat(SeatQueue* q, Ticket* ticket) {
    // Input validation
    if (q == NULL || ticket == NULL) {
        printf("Error: NULL pointer provided\n");
        return 0;
    }
    
    // Check if queue is empty
    if (isSeatQueueEmpty(q)) {
        printf("Error: No bookings in queue!\n");
        return 0;
    }
    
    // Remove ticket from front
    *ticket = q->tickets[q->front];
    q->front++;
    q->count--;
    
    // Reset queue if empty
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    
    printf("=> Ticket processed: ID %d, Passenger: %s\n", 
           ticket->ticketId, ticket->passengerName);
    
    return 1;
}

/**
 * Display all bookings in the seat queue
 */
void displaySeatQueue(SeatQueue* q) {
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return;
    }

    if (isSeatQueueEmpty(q)) {
        printf("\n-- No bookings in queue. --\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                  CURRENT SEAT BOOKINGS QUEUE                           |\n");
    printf("==========================================================================\n");
    printf("Total Bookings: %d\n\n", q->count);

    printf("%-12s %-12s %-25s %-8s %-20s %-10s\n", 
           "Ticket ID", "PassengerID", "Passenger", "Seat", "Route", "Fare");
    printf("--------------------------------------------------------------------------------------------\n");

    for (int i = q->front; i <= q->rear; i++) {
        Ticket t = q->tickets[i];
        printf("%-12d %-12d %-25s %-8d %-20s $%-9.2f\n", 
               t.ticketId, t.passengerId, t.passengerName, t.seatNumber, t.route, t.fare);
    }
    printf("\n");
}


/*=============================================================================
 * CIRCULAR QUEUE IMPLEMENTATION - Cancelled Ticket Logs (CO1)
 * 
 * This circular queue maintains a log of cancelled tickets.
 * It overwrites the oldest entry when full, maintaining recent history.
 *===========================================================================*/

/**
 * Initialize the cancelled ticket circular queue
 */
void initCancelledQueue(CancelledQueue* q) {
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return;
    }
    q->front = -1;
    q->rear = -1;
    q->count = 0;
    printf("Cancelled ticket log initialized successfully.\n");
}

/**
 * Check if cancelled queue is full
 * In circular queue, full when (rear+1)%MAX == front
 */
int isCancelledQueueFull(CancelledQueue* q) {
    if (q == NULL) return 1;
    return ((q->rear + 1) % MAX_CANCELLED_LOGS == q->front);
}

/**
 * Check if cancelled queue is empty
 */
int isCancelledQueueEmpty(CancelledQueue* q) {
    if (q == NULL) return 1;
    return (q->front == -1);
}

/**
 * Add a cancelled ticket to the circular queue log
 * Overwrites oldest entry if full
 */
int enqueueCancelled(CancelledQueue* q, Ticket ticket) {
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return 0;
    }
    
    // If queue is full, automatically advance front (overwrite oldest)
    if (isCancelledQueueFull(q)) {
        printf("Warning: Cancelled log full. Overwriting oldest entry.\n");
        q->front = (q->front + 1) % MAX_CANCELLED_LOGS;
        q->count--;
    }
    
    // If queue is empty, set front to 0
    if (q->front == -1) {
        q->front = 0;
    }
    
    // Add ticket to rear position using circular indexing
    q->rear = (q->rear + 1) % MAX_CANCELLED_LOGS;
    q->logs[q->rear] = ticket;
    q->count++;
    
    printf("=> Cancellation logged: Ticket ID %d\n", ticket.ticketId);
    
    return 1;
}

/**
 * Display all cancelled ticket logs
 */
void displayCancelledLogs(CancelledQueue* q) {
    if (q == NULL) {
        printf("Error: NULL queue pointer\n");
        return;
    }

    if (isCancelledQueueEmpty(q)) {
        printf("\n-- No cancelled tickets logged. --\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                     CANCELLED TICKETS LOG                              |\n");
    printf("==========================================================================\n");
    printf("Total Cancellations: %d\n\n", q->count);

    printf("%-12s %-12s %-25s %-8s %-20s %-12s\n", 
           "Ticket ID", "PassengerID", "Passenger", "Seat", "Route", "Date");
    printf("--------------------------------------------------------------------------------------------------\n");

    int i = q->front;
    int count = 0;
    while (count < q->count) {
        Ticket t = q->logs[i];
        printf("%-12d %-12d %-25s %-8d %-20s %-12s\n", 
               t.ticketId, t.passengerId, t.passengerName, t.seatNumber, t.route, t.bookingDate);

        i = (i + 1) % MAX_CANCELLED_LOGS;
        count++;
    }
    printf("\n");
}