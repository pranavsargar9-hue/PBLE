#include <stdio.h>

#define MAX 10
#define INF 999

int graph[MAX][MAX], n = 0;
char location[MAX][30];
int dist[MAX], visited[MAX], parent[MAX];
int graphEntered = 0, source = -1, calculated = 0;

void enterGraph()
{
    int i, j, d;

    printf("Enter number of locations (max 10): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of locations!\n");
        n = 0;
        return;
    }

    for (i = 0; i < n; i++) {
        printf("Enter location %d name: ", i + 1);
        scanf(" %29[^\n]", location[i]);
    }

    // Initialize adjacency matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = (i == j) ? 0 : INF;

    printf("\nEnter road distances between locations.\n");
    printf("Enter -1 if there is no direct road.\n");

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            do {
                printf("Distance between %s and %s: ",
                       location[i], location[j]);
                scanf("%d", &d);

                if (d == -1)
                    break;

                if (d <= 0) {
                    printf("Enter a positive distance or -1.\n");
                }
            } while (d <= 0);

            if (d != -1) {
                graph[i][j] = d;
                graph[j][i] = d;
            }
        }
    }

    graphEntered = 1;
    calculated = 0;
    source = -1;
    printf("\nCampus graph created successfully!\n");
}

void displayMatrix()
{
    int i, j;

    printf("\nAdjacency Matrix:\n\n");
    printf("%-22s", "Location");

    for (i = 0; i < n; i++)
        printf("%-12d", i + 1);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%-22s", location[i]);

        for (j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf("%-12s", "INF");
            else
                printf("%-12d", graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int src)
{
    int i, j, u, min;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (i = 0; i < n; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] != INF &&
                dist[u] + graph[u][j] < dist[j]) {
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }

    source = src;
    calculated = 1;
    printf("Shortest distances calculated successfully.\n");
}

void printPath(int v)
{
    if (parent[v] == -1) {
        printf("%s", location[v]);
        return;
    }

    printPath(parent[v]);
    printf(" -> %s", location[v]);
}

void selectSource()
{
    int i, s;

    if (!graphEntered) {
        printf("Please enter the campus graph first!\n");
        return;
    }

    printf("\nSelect source location:\n");
    for (i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, location[i]);

    printf("Enter source number: ");
    scanf("%d", &s);

    if (s < 1 || s > n) {
        printf("Invalid source location!\n");
        return;
    }

    dijkstra(s - 1);
    printf("Selected source: %s\n", location[source]);
}

void displayDistances()
{
    int i;

    if (!calculated) {
        printf("Please select a source first!\n");
        return;
    }

    printf("\nSource: %s\n", location[source]);
    printf("\nDestination\t\tShortest Distance\n");

    for (i = 0; i < n; i++) {
        if (i == source)
            continue;

        printf("%-24s", location[i]);

        if (dist[i] == INF)
            printf("Unreachable\n");
        else
            printf("%d\n", dist[i]);
    }
}

void displayPaths()
{
    int i;

    if (!calculated) {
        printf("Please select a source first!\n");
        return;
    }

    printf("\nShortest Paths from %s:\n", location[source]);

    for (i = 0; i < n; i++) {
        if (i == source)
            continue;

        printf("%s: ", location[i]);

        if (dist[i] == INF) {
            printf("No path available\n");
        } else {
            printPath(i);
            printf(" (Distance: %d)\n", dist[i]);
        }
    }
}

int main()
{
    int choice;

    do {
        printf("\n--- CAMPUS SHORTEST ROUTE FINDER ---\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance to All Locations\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enterGraph();
            break;

        case 2:
            if (graphEntered)
                displayMatrix();
            else
                printf("Enter campus graph first!\n");
            break;

        case 3:
            selectSource();
            break;

        case 4:
            if (graphEntered && source != -1) {
                dijkstra(source);
                displayDistances();
            } else {
                printf("Please enter graph and select source first!\n");
            }
            break;

        case 5:
            displayPaths();
            break;

        case 6:
            displayDistances();
            break;

        case 7:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}
