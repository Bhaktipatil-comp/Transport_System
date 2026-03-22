#include "transport_system.h"

/*=============================================================================
 * MAIN PROGRAM
 * 
 * Main driver program that integrates all modules and provides
 * interactive menu-driven interface for the transport system.
 *===========================================================================*/
int main() {
    // Initialize all data structures
    SeatQueue seatQueue;
    CancelledQueue cancelledQueue;
    PassengerNode* passengerList = NULL;
    RouteGraph routeGraph;
    
    // Array to store all tickets for searching
    Ticket allTickets[MAX_QUEUE_SIZE * 2];
    int totalTickets = 0;
    
    int choice;
    int running = 1;
    
    // Initialize system
    printf("Initializing Smart Transport Reservation System...\n\n");
    initSeatQueue(&seatQueue);
    initCancelledQueue(&cancelledQueue);
    initRouteGraph(&routeGraph);
    
    // Display welcome banner
    displayWelcomeBanner();
    pauseScreen();
    
    // Add some sample routes for demonstration
    printf("\nLoading sample routes...\n");
    int route1 = addRoute(&routeGraph, "Express Line 1");
    addStopToRoute(&routeGraph, route1, "Central Station", 0);
    addStopToRoute(&routeGraph, route1, "Park Avenue", 5);
    addStopToRoute(&routeGraph, route1, "Airport Terminal", 15);
    
    int route2 = addRoute(&routeGraph, "City Circle");
    addStopToRoute(&routeGraph, route2, "Downtown Plaza", 0);
    addStopToRoute(&routeGraph, route2, "Shopping Mall", 3);
    addStopToRoute(&routeGraph, route2, "University Campus", 8);
    
    connectRoutes(&routeGraph, route1, route2, 10);
    printf("\nSample data loaded successfully!\n");
    pauseScreen();
    
    // Main program loop
    while (running) {
        #ifdef _WIN32
            system("cls");  // Clear screen on Windows
        #else
            system("clear");  // Clear screen on Unix/Linux
        #endif
        
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            pauseScreen();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Book Ticket
                printf("\n=============== BOOK NEW TICKET ===============\n");
                
                int passengerId;
                char passengerName[MAX_NAME_LENGTH];
                char route[MAX_NAME_LENGTH];
                int seatNumber;
                float fare;
                
                printf("Enter Passenger ID: ");
                scanf("%d", &passengerId);
                clearInputBuffer();
                // Check if passenger exists
                PassengerNode* passenger = searchPassenger(passengerList, passengerId);
                if (passenger == NULL) {
                    printf("Warning: Passenger ID not found in system.\n");
                    printf("Enter Passenger Name: ");
                    // Now, fgets correctly waits for the name because the buffer is clean.
                    fgets(passengerName, MAX_NAME_LENGTH, stdin);
                    passengerName[strcspn(passengerName, "\n")] = 0;
                } else {
                    strcpy(passengerName, passenger->name);
                    printf("Passenger found: %s\n", passengerName);
                    updatePassengerBookings(passenger);
                }
                printf("Enter Route Name: ");
                fgets(route, MAX_NAME_LENGTH, stdin);
                route[strcspn(route, "\n")] = 0;
                
                printf("Enter Seat Number: ");
                scanf("%d", &seatNumber);
                clearInputBuffer();
                
                if (isSeatTaken(allTickets, totalTickets, route, seatNumber)) {
                    printf("\n--- ERROR: Seat %d on Route '%s' is already booked! Please choose a different seat. ---\n", 
                        seatNumber, route);
                    pauseScreen();
                    break; // ABORT the booking and return to the main menu
                }

                printf("Enter Fare ($): ");
                scanf("%f", &fare);
                clearInputBuffer();
                // Create ticket
                Ticket newTicket;
                newTicket.ticketId = generateTicketId();
                newTicket.passengerId = passengerId;             // store ID
                strcpy(newTicket.passengerName, passengerName);
                newTicket.seatNumber = seatNumber;
                strcpy(newTicket.route, route);
                getCurrentDate(newTicket.bookingDate);
                newTicket.fare = fare;
                
                // Add to queue and ticket array
                if (enqueueSeat(&seatQueue, newTicket)) {
                    if (totalTickets < MAX_QUEUE_SIZE * 2) {
                        allTickets[totalTickets++] = newTicket;
                    }
                }
                
                pauseScreen();
                break;
            }
            
            case 2: {
                // Process Next Booking
                printf("\n===============PROCESS BOOKING===============\n");
                Ticket processedTicket;
                
                if (dequeueSeat(&seatQueue, &processedTicket)) {
                    printf("\nBoarding Details:\n");
                    displayTicketDetails(processedTicket);
                }
                
                pauseScreen();
                break;
            }
            
            case 3: {
                // View Current Bookings
                displaySeatQueue(&seatQueue);
                pauseScreen();
                break;
            }
            
            case 4: {
                // Cancel Ticket
                printf("\n===============CANCEL TICKET===============\n");
                
                if (isSeatQueueEmpty(&seatQueue)) {
                    printf("No active bookings to cancel.\n");
                } else {
                    Ticket cancelledTicket;
                    if (dequeueSeat(&seatQueue, &cancelledTicket)) {
                        enqueueCancelled(&cancelledQueue, cancelledTicket);
                        printf("\nCancelled Ticket Details:\n");
                        displayTicketDetails(cancelledTicket);
                    }
                }
                
                pauseScreen();
                break;
            }
            
            case 5: {
                // View Cancelled Tickets
                displayCancelledLogs(&cancelledQueue);
                pauseScreen();
                break;
            }
            
            case 6: {
                // Register New Passenger
                printf("\n===============REGISTER PASSENGER===============\n");
                
                int id = generatePassengerId();
                char name[MAX_NAME_LENGTH];
                char phone[15];
                char email[MAX_NAME_LENGTH];
                
                printf("Generated Passenger ID: %d\n", id);
                
                printf("Enter Name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = 0;
                
                do {
                    printf("Enter Phone: ");
                    fgets(phone, 15, stdin);
                    phone[strcspn(phone, "\n")] = 0;
                    
                    if (!validatePhone(phone)) {
                        printf("Invalid phone format! Try again.\n");
                    }
                } while (!validatePhone(phone));
                
                do {
                    printf("Enter Email: ");
                    fgets(email, MAX_NAME_LENGTH, stdin);
                    email[strcspn(email, "\n")] = 0;
                    
                    if (!validateEmail(email)) {
                        printf("Invalid email format! Try again.\n");
                    }
                } while (!validateEmail(email));
                
                passengerList = addPassenger(passengerList, id, name, phone, email);
                
                pauseScreen();
                break;
            }
            
            case 7: {
                // Search Passenger
                printf("\n===============SEARCH PASSENGER===============\n");
                
                int searchId;
                printf("Enter Passenger ID to search: ");
                scanf("%d", &searchId);
                clearInputBuffer();
                
                PassengerNode* found = searchPassenger(passengerList, searchId);
                if (found != NULL) {
                    displayPassengerDetails(found);
                } else {
                    printf("\n✗ Passenger with ID %d not found.\n", searchId);
                }
                
                pauseScreen();
                break;
            }
            
            case 8: {
                // Delete Passenger
                printf("\n===============DELETE PASSENGER===============\n");
                
                int deleteId;
                printf("Enter Passenger ID to delete: ");
                scanf("%d", &deleteId);
                clearInputBuffer();
                
                printf("Are you sure you want to delete this passenger? (y/n): ");
                char confirm;
                scanf("%c", &confirm);
                clearInputBuffer();
                
                if (confirm == 'y' || confirm == 'Y') {
                    passengerList = deletePassenger(passengerList, deleteId);
                } else {
                    printf("Deletion cancelled.\n");
                }
                
                pauseScreen();
                break;
            }
            
            case 9: {
                // Display All Passengers
                displayAllPassengers(passengerList);
                pauseScreen();
                break;
            }
            
            case 10: {
                // Add New Route
                printf("\n===============ADD NEW ROUTE===============\n");
                
                char routeName[MAX_NAME_LENGTH];
                printf("Enter Route Name: ");
                fgets(routeName, MAX_NAME_LENGTH, stdin);
                routeName[strcspn(routeName, "\n")] = 0;
                
                addRoute(&routeGraph, routeName);
                
                pauseScreen();
                break;
            }
            
            case 11: {
                // Add Stop to Route
                printf("\n===============ADD STOP TO ROUTE===============\n");
                
                displayAllRoutes(&routeGraph);
                
                int routeIndex;
                char stopName[MAX_NAME_LENGTH];
                int distance;
                
                printf("Enter Route Index (0-%d): ", routeGraph.routeCount - 1);
                scanf("%d", &routeIndex);
                clearInputBuffer();
                
                printf("Enter Stop Name: ");
                fgets(stopName, MAX_NAME_LENGTH, stdin);
                stopName[strcspn(stopName, "\n")] = 0;
                
                printf("Enter Distance from previous stop (km): ");
                scanf("%d", &distance);
                clearInputBuffer();
                
                addStopToRoute(&routeGraph, routeIndex, stopName, distance);
                
                pauseScreen();
                break;
            }
            
            case 12: {
                // Connect Routes
                printf("\n===============CONNECT ROUTES===============\n");
                
                displayAllRoutes(&routeGraph);
                
                int route1, route2, distance;
                
                printf("Enter first route index: ");
                scanf("%d", &route1);
                
                printf("Enter second route index: ");
                scanf("%d", &route2);
                
                printf("Enter connection distance (km): ");
                scanf("%d", &distance);
                clearInputBuffer();
                
                connectRoutes(&routeGraph, route1, route2, distance);
                
                pauseScreen();
                break;
            }
            
            case 13: {
                // Display All Routes
                displayAllRoutes(&routeGraph);
                pauseScreen();
                break;
            }
            
            case 14: {
                // Display Route Details
                printf("\n===============ROUTE DETAILS===============\n");
                
                displayAllRoutes(&routeGraph);
                
                int routeIndex;
                printf("Enter Route Index to view details: ");
                scanf("%d", &routeIndex);
                clearInputBuffer();
                
                displayRouteDetails(&routeGraph, routeIndex);
                
                pauseScreen();
                break;
            }
            
            case 15: {
                // Search Ticket by ID
                printf("\n===============SEARCH TICKET===============\n");
                
                if (totalTickets == 0) {
                    printf("No tickets in system yet.\n");
                } else {
                    int searchId;
                    printf("Enter Ticket ID to search: ");
                    scanf("%d", &searchId);
                    clearInputBuffer();
                    
                    searchAndDisplayTicket(allTickets, totalTickets, searchId, 1);
                }
                
                pauseScreen();
                break;
            }
            
            case 16: {
                // Compare Search Algorithms
                printf("\n===============COMPARE ALGORITHMS===============\n");
                
                if (totalTickets == 0) {
                    printf("No tickets in system yet.\n");
                } else {
                    int searchId;
                    printf("Enter Ticket ID to search: ");
                    scanf("%d", &searchId);
                    clearInputBuffer();
                    
                    compareSearchAlgorithms(allTickets, totalTickets, searchId);
                }
                
                pauseScreen();
                break;
            }
            
            case 0: {
                // Exit System
                printf("\n===============EXIT SYSTEM===============\n");
                
                printf("Saving data and cleaning up...\n");
                
                // Display final statistics
                displaySystemStats(&seatQueue, &cancelledQueue, passengerList, &routeGraph);
                
                // Free allocated memory
                freePassengerList(passengerList);
                freeRouteGraph(&routeGraph);
                
                displayExitMessage();
                running = 0;
                break;
            }
            
            default: {
                printf("\n✗ Invalid choice! Please select a valid option (0-16).\n");
                pauseScreen();
                break;
            }
        }
    }
    
    return 0;
}