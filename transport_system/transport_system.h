#ifndef TRANSPORT_SYSTEM_H
#define TRANSPORT_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Windows compatibility */
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

/*=============================================================================
 * CONSTANTS AND CONFIGURATION
 *===========================================================================*/
#define MAX_QUEUE_SIZE 10          // Maximum seats in linear queue
#define MAX_CANCELLED_LOGS 10     // Circular queue size for cancelled tickets
#define MAX_NAME_LENGTH 50         // Maximum length for passenger names
#define MAX_ROUTES 10              // Maximum number of bus routes
#define MAX_STOPS 20               // Maximum stops per route

/*=============================================================================
 * DATA STRUCTURES
 *===========================================================================*/

/* Structure for Ticket Information */
typedef struct {
    int ticketId;
    int passengerId;
    char passengerName[MAX_NAME_LENGTH];
    int seatNumber;
    char route[MAX_NAME_LENGTH];
    char bookingDate[20];
    float fare;
} Ticket;

/* LINEAR QUEUE - For Seat Booking (CO1) */
typedef struct {
    Ticket tickets[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} SeatQueue;

/* CIRCULAR QUEUE - For Cancelled Ticket Logs (CO1) */
typedef struct {
    Ticket logs[MAX_CANCELLED_LOGS];
    int front;
    int rear;
    int count;
} CancelledQueue;

/* LINKED LIST NODE - For Passenger Information (CO2) */
typedef struct PassengerNode {
    int passengerId;
    char name[MAX_NAME_LENGTH];
    char phone[15];
    char email[MAX_NAME_LENGTH];
    int totalBookings;
    struct PassengerNode* next;
} PassengerNode;

/* GRAPH STRUCTURES - For Bus Route Planner (CO3) */
typedef struct RouteNode {
    char stopName[MAX_NAME_LENGTH];
    struct RouteNode* next;
    int distance;  // Distance to this stop in km
} RouteNode;

typedef struct {
    char routeName[MAX_NAME_LENGTH];
    RouteNode* stops;
    int stopCount;
} BusRoute;

typedef struct {
    BusRoute routes[MAX_ROUTES];
    int routeCount;
    int adjacencyMatrix[MAX_ROUTES][MAX_ROUTES];  // For route connections
} RouteGraph;

/*=============================================================================
 * FUNCTION PROTOTYPES
 *===========================================================================*/

/* Linear Queue Operations (CO1) */
void initSeatQueue(SeatQueue* q);
int isSeatQueueFull(SeatQueue* q);
int isSeatQueueEmpty(SeatQueue* q);
int isSeatTaken(Ticket allTickets[], int totalTickets, const char* route, int seatNumber);
int enqueueSeat(SeatQueue* q, Ticket ticket);
int dequeueSeat(SeatQueue* q, Ticket* ticket);
void displaySeatQueue(SeatQueue* q);

/* Circular Queue Operations (CO1) */
void initCancelledQueue(CancelledQueue* q);
int isCancelledQueueFull(CancelledQueue* q);
int isCancelledQueueEmpty(CancelledQueue* q);
int enqueueCancelled(CancelledQueue* q, Ticket ticket);
void displayCancelledLogs(CancelledQueue* q);

/* Linked List Operations (CO2) */
PassengerNode* createPassengerNode(int id, const char* name, const char* phone, const char* email);
PassengerNode* addPassenger(PassengerNode* head, int id, const char* name, const char* phone, const char* email);
PassengerNode* searchPassenger(PassengerNode* head, int id);
PassengerNode* deletePassenger(PassengerNode* head, int id);
void displayAllPassengers(PassengerNode* head);
void freePassengerList(PassengerNode* head);

/* Graph Operations (CO3) */
void initRouteGraph(RouteGraph* graph);
int addRoute(RouteGraph* graph, const char* routeName);
int addStopToRoute(RouteGraph* graph, int routeIndex, const char* stopName, int distance);
void connectRoutes(RouteGraph* graph, int route1, int route2, int distance);
void displayAllRoutes(RouteGraph* graph);
void displayRouteDetails(RouteGraph* graph, int routeIndex);

/* Binary Search Operations (CO4) */
void sortTicketsByIdBubbleSort(Ticket tickets[], int n);
int binarySearchTicket(Ticket tickets[], int n, int ticketId);

/* Utility Functions */
void getCurrentDate(char* buffer);
int generateTicketId(void);
int generatePassengerId(void);
void displayMenu(void);
void clearInputBuffer(void);
int validatePhone(const char* phone);
int validateEmail(const char* email);
void displaySystemStats(SeatQueue* sq, CancelledQueue* cq, PassengerNode* passengers, RouteGraph* graph);
void pauseScreen(void);
void displayWelcomeBanner(void);
void displayExitMessage(void);

/* Additional Display Functions */
void displayTicketDetails(Ticket ticket);
void displayPassengerDetails(PassengerNode* passenger);
void updatePassengerBookings(PassengerNode* passenger);

/* Additional Search Functions */
void searchAndDisplayTicket(Ticket tickets[], int n, int ticketId, int useBinarySearch);
void compareSearchAlgorithms(Ticket tickets[], int n, int ticketId);

/* Graph Memory Management */
void freeRouteGraph(RouteGraph* graph);

#endif /* TRANSPORT_SYSTEM_H */