#include "transport_system.h"

/*=============================================================================
 * GRAPH IMPLEMENTATION - Bus Route Planner (CO3)
 * 
 * This graph represents bus routes as vertices and connections between routes.
 * Each route contains a linked list of stops with distances.
 * Adjacency matrix tracks connections between different routes.
 *===========================================================================*/

/**
 * Initialize the route graph
 * Sets all routes to empty and adjacency matrix to 0
 */
void initRouteGraph(RouteGraph* graph) {
    if (graph == NULL) {
        printf("Error: NULL graph pointer\n");
        return;
    }
    
    graph->routeCount = 0;
    
    // Initialize adjacency matrix to 0 (no connections)
    for (int i = 0; i < MAX_ROUTES; i++) {
        for (int j = 0; j < MAX_ROUTES; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
        graph->routes[i].stops = NULL;
        graph->routes[i].stopCount = 0;
        strcpy(graph->routes[i].routeName, "");
    }
    
    printf("Route graph initialized successfully.\n");
}

/**
 * Add a new route to the graph
 * Returns the index of the new route, or -1 on failure
 */
int addRoute(RouteGraph* graph, const char* routeName) {
    // Input validation
    if (graph == NULL || routeName == NULL) {
        printf("Error: NULL pointer provided\n");
        return -1;
    }
    
    // Check if graph is full
    if (graph->routeCount >= MAX_ROUTES) {
        printf("Error: Maximum routes limit reached\n");
        return -1;
    }
    
    // Check for duplicate route name
    for (int i = 0; i < graph->routeCount; i++) {
        if (strcmp(graph->routes[i].routeName, routeName) == 0) {
            printf("Error: Route '%s' already exists\n", routeName);
            return -1;
        }
    }
    
    // Add new route
    int index = graph->routeCount;
    strncpy(graph->routes[index].routeName, routeName, MAX_NAME_LENGTH - 1);
    graph->routes[index].routeName[MAX_NAME_LENGTH - 1] = '\0';
    graph->routes[index].stops = NULL;
    graph->routes[index].stopCount = 0;
    graph->routeCount++;
    
    printf("====Route added: %s (Index: %d)====\n", routeName, index);
    
    return index;
}

/**
 * Add a stop to a specific route
 * Creates a linked list of stops for each route
 */
int addStopToRoute(RouteGraph* graph, int routeIndex, const char* stopName, int distance) {
    // Input validation
    if (graph == NULL || stopName == NULL) {
        printf("Error: NULL pointer provided\n");
        return 0;
    }
    
    if (routeIndex < 0 || routeIndex >= graph->routeCount) {
        printf("Error: Invalid route index\n");
        return 0;
    }
    
    if (graph->routes[routeIndex].stopCount >= MAX_STOPS) {
        printf("Error: Maximum stops limit reached for this route\n");
        return 0;
    }
    
    // Create new stop node
    RouteNode* newStop = (RouteNode*)malloc(sizeof(RouteNode));
    if (newStop == NULL) {
        printf("Error: Memory allocation failed\n");
        return 0;
    }
    
    // Initialize stop data
    strncpy(newStop->stopName, stopName, MAX_NAME_LENGTH - 1);
    newStop->stopName[MAX_NAME_LENGTH - 1] = '\0';
    newStop->distance = distance;
    newStop->next = NULL;
    
    // Add to the end of the linked list
    BusRoute* route = &graph->routes[routeIndex];
    
    if (route->stops == NULL) {
        // First stop in the route
        route->stops = newStop;
    } else {
        // Traverse to the end and add
        RouteNode* current = route->stops;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStop;
    }
    
    route->stopCount++;
    
    printf("-> Stop added to %s: %s (%d km)\n", 
           route->routeName, stopName, distance);
    
    return 1;
}

/**
 * Connect two routes in the adjacency matrix
 * Creates bidirectional connection with given distance
 */
void connectRoutes(RouteGraph* graph, int route1, int route2, int distance) {
    // Input validation
    if (graph == NULL) {
        printf("Error: NULL graph pointer\n");
        return;
    }
    
    if (route1 < 0 || route1 >= graph->routeCount || 
        route2 < 0 || route2 >= graph->routeCount) {
        printf("Error: Invalid route indices\n");
        return;
    }
    
    // Create bidirectional connection
    graph->adjacencyMatrix[route1][route2] = distance;
    graph->adjacencyMatrix[route2][route1] = distance;
    
    printf("=> Routes connected: %s <-> %s (Distance: %d km)\n", 
           graph->routes[route1].routeName, 
           graph->routes[route2].routeName, 
           distance);
}

/**
 * Display all routes with their stops
 */
void displayAllRoutes(RouteGraph* graph) {
    if (graph == NULL) {
        printf("Error: NULL graph pointer\n");
        return;
    }
    
    if (graph->routeCount == 0) {
        printf("\n No routes available.\n");
        return;
    }
    printf("\n");
    printf("==========================================================================\n");
    printf("|                          BUS ROUTE NETWORK                             |\n");
    printf("==========================================================================\n");
    
    for (int i = 0; i < graph->routeCount; i++) {
        printf("Route %d: %s\n", i + 1, graph->routes[i].routeName);
        printf("  Stops: %d\n", graph->routes[i].stopCount);
        
        if (graph->routes[i].stops != NULL) {
            printf("  Route path: ");
            RouteNode* current = graph->routes[i].stops;
            while (current != NULL) {
                printf("%s", current->stopName);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
        printf("\n");
    }
}

/**
 * Display detailed information about a specific route
 */
void displayRouteDetails(RouteGraph* graph, int routeIndex) {
    if (graph == NULL) {
        printf("Error: NULL graph pointer\n");
        return;
    }
    
    if (routeIndex < 0 || routeIndex >= graph->routeCount) {
        printf("Error: Invalid route index\n");
        return;
    }
    
    BusRoute* route = &graph->routes[routeIndex];
    printf("\n");
    printf("==========================================================================\n");
    printf("|                           ROUTE DETAILS                                |\n");
    printf("==========================================================================\n");
    printf("  Route Name      : %s\n", route->routeName);
    printf("  Total Stops     : %d\n", route->stopCount);
    printf("==================================================================================\n");
    
    if (route->stops == NULL) {
        printf("  No stops defined for this route.\n");
    } else {
        printf("\n  %-5s %-30s %-15s\n", "Stop", "Name", "Distance (km)");
        printf(" =============================================================================\n");
        
        RouteNode* current = route->stops;
        int stopNum = 1;
        int totalDistance = 0;
        
        while (current != NULL) {
            printf("  %-5d %-30s %-15d\n", 
                   stopNum, current->stopName, current->distance);
            totalDistance += current->distance;
            current = current->next;
            stopNum++;
        }
        
        printf(" ==================================================================================\n");
        printf("  Total Route Distance: %d km\n", totalDistance);
    }
    
    // Display connections with other routes
    printf("\n  Connected Routes:\n");
    int hasConnections = 0;
    for (int i = 0; i < graph->routeCount; i++) {
        if (i != routeIndex && graph->adjacencyMatrix[routeIndex][i] > 0) {
            printf("    - %s (Distance: %d km)\n", 
                   graph->routes[i].routeName, 
                   graph->adjacencyMatrix[routeIndex][i]);
            hasConnections = 1;
        }
    }
    
    if (!hasConnections) {
        printf("    No connections to other routes.\n");
    }
    
    printf("==============================================================================\n\n");
}

/**
 * Free all memory allocated for route stops
 */
void freeRouteGraph(RouteGraph* graph) {
    if (graph == NULL) return;
    
    for (int i = 0; i < graph->routeCount; i++) {
        RouteNode* current = graph->routes[i].stops;
        RouteNode* next;
        
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
    }
    
    printf("=> Route graph memory freed.\n");
}