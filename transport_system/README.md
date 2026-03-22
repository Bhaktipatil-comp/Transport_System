# Smart Public Transport Reservation System

## Project Overview
A comprehensive C-based public transport reservation system demonstrating various data structures and algorithms taught in Data Structures course.

## Course Outcomes Implemented

### CO1 - Queue Data Structures
- **Linear Queue**: Manages seat bookings in First-Come-First-Serve manner
- **Circular Queue**: Maintains a rolling log of cancelled tickets

### CO2 - Linked List
- **Singly Linked List**: Dynamic passenger information management with insertion, deletion, and search operations

### CO3 - Graph
- **Graph with Adjacency Matrix**: Bus route planner with stops represented as nodes and connections between routes

### CO4 - Searching Algorithms
- **Binary Search**: Efficient O(log n) ticket lookup by ID
- **Comparison with Linear Search**: Demonstrates algorithm efficiency

## File Structure

```
transport_system/
│
├── transport_system.h          # Main header file with all declarations
├── queue_operations.c          # Linear & circular queue implementations
├── linkedlist_operations.c     # Passenger management using linked list
├── graph_operations.c          # Route planning using graph
├── search_operations.c         # Binary search implementation
├── utility_functions.c         # Helper functions
├── main_program.c              # Main driver program
├── Makefile                    # Compilation script
└── README.md                   # This file
```

## Features

### 1. Booking Operations
- Book new tickets (added to queue)
- Process bookings (dequeue operation)
- View all active bookings
- Cancel tickets (moved to cancelled log)
- View cancellation history

### 2. Passenger Management
- Register new passengers with validation
- Search passengers by ID
- Delete passenger records
- Display all registered passengers
- Track booking history per passenger

### 3. Route Management
- Add new bus routes
- Add stops to routes with distances
- Connect different routes
- Display route network
- View detailed route information

### 4. Search Operations
- Binary search for ticket lookup
- Algorithm comparison (Binary vs Linear)
- Sorted data handling

## Compilation Instructions

### Using Makefile (Recommended)
```bash
make
```

### Manual Compilation
```bash
gcc -c queue_operations.c -o queue_operations.o
gcc -c linkedlist_operations.c -o linkedlist_operations.o
gcc -c graph_operations.c -o graph_operations.o
gcc -c search_operations.c -o search_operations.o
gcc -c utility_functions.c -o utility_functions.o
gcc -c main_program.c -o main_program.o

gcc queue_operations.o linkedlist_operations.o graph_operations.o \
    search_operations.o utility_functions.o main_program.o \
    -o transport_system
```

### Clean Build Files
```bash
make clean
```

## Running the Program

```bash
./transport_system
```

## Usage Guide

### Quick Start
1. Run the program
2. Sample routes are pre-loaded for demonstration
3. Start by registering passengers (Option 6)
4. Book tickets (Option 1)
5. Explore other features from the menu

### Important Notes
- Passenger IDs are auto-generated
- Ticket IDs are generated using timestamp + counter
- Phone and email validation is implemented
- Binary search requires sorted data (automatic sorting)

## Data Structure Details

### Linear Queue (Seat Booking)
```c
- Operations: Enqueue, Dequeue, Display
- Complexity: O(1) for enqueue/dequeue
- Max Size: 50 seats
- Properties: FIFO (First In First Out)
```

### Circular Queue (Cancelled Logs)
```c
- Operations: Enqueue (with overwrite), Display
- Complexity: O(1) for all operations
- Max Size: 100 logs
- Properties: Overwrites oldest when full
```

### Linked List (Passengers)
```c
- Operations: Insert, Delete, Search, Display
- Complexity: O(1) insert, O(n) search/delete
- Structure: Singly linked list
- Dynamic: Grows/shrinks as needed
```

### Graph (Route Network)
```c
- Representation: Adjacency Matrix + Linked List
- Operations: Add route, Add stop, Connect routes
- Structure: Each route has linked list of stops
- Matrix: Tracks connections between routes
```

### Binary Search (Tickets)
```c
- Preprocessing: Bubble sort O(n²)
- Search: Binary search O(log n)
- Comparison: Linear search O(n) provided
- Demonstrates efficiency gain
```

## Error Handling

The system includes comprehensive error handling:
- NULL pointer checks
- Boundary validations
- Input format validation
- Queue overflow/underflow detection
- Memory allocation failure handling
- Invalid index/ID error messages

## Code Quality Features

### Modularity
- Separate files for each data structure
- Clear function segregation
- Reusable utility functions

### Documentation
- Detailed comments throughout
- Function header descriptions
- Algorithm explanations
- Parameter documentation

### User Experience
- Clear menu interface
- Visual separators and boxes
- Informative success/error messages
- Input validation and feedback

## Sample Test Cases

### Test Case 1: Basic Booking Flow
```
1. Register passenger (ID: 1)
2. Book ticket (Passenger ID: 1)
3. View booking queue
4. Process booking
```

### Test Case 2: Cancellation
```
1. Book multiple tickets
2. Cancel a ticket
3. View cancelled logs
4. Verify circular queue behavior
```

### Test Case 3: Route Planning
```
1. Add new route
2. Add multiple stops
3. Connect with existing route
4. Display route details
```

### Test Case 4: Search Efficiency
```
1. Book 20+ tickets
2. Search specific ticket ID
3. Compare algorithms
4. Observe time difference
```

## Memory Management

- Dynamic allocation for passengers (linked list)
- Dynamic allocation for route stops (linked list)
- Proper deallocation on exit
- Memory leak prevention

## Limitations & Edge Cases

1. **Maximum Limits**
   - 50 seat bookings in queue
   - 100 cancelled ticket logs
   - 10 routes maximum
   - 20 stops per route

2. **Edge Cases Handled**
   - Empty queue operations
   - Full queue scenarios
   - Duplicate passenger IDs
   - Invalid route indices
   - Search on empty dataset

## Future Enhancements

- File I/O for data persistence
- Priority queue for VIP passengers
- Shortest path algorithm for routes
- Multi-route ticket booking
- Payment integration
- Real-time seat availability

## Author Information

This project demonstrates:
- Data structure implementation
- Algorithm analysis
- Modular programming
- Error handling
- User interface design

## Academic Integrity

This code is for educational purposes. Students should:
- Understand each implementation
- Be able to explain algorithms
- Modify for their specific requirements
- Add proper attribution if used

## Compilation Tested On

- GCC 9.4.0+
- Linux/Unix systems
- Windows (MinGW)
- macOS

## Support

For issues or questions:
1. Review the code comments
2. Check function documentation
3. Test with provided examples
4. Verify input formats

---

**Course**: Data Structures and Algorithms  
**Language**: C Programming  
**Concepts**: Queues, Linked Lists, Graphs, Binary Search  
**Complexity**: Intermediate to Advanced