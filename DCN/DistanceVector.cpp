#include <iostream>
using namespace std;

#define INF 999
#define N 4 // Number of routers (nodes)

void distanceVectorRouting(int graph[N][N]) {
    int dist[N][N]; // distance table
    bool updated;

    // Initialize distance table
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Repeat until no update (convergence)
    do {
        updated = false;
        for (int i = 0; i < N; i++) {           // For each router i
            for (int j = 0; j < N; j++) {       // For each destination j
                for (int k = 0; k < N; k++) {   // Check via neighbor k
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        updated = true;
                    }
                }
            }
        }
    } while (updated);

    // Print final routing tables
    for (int i = 0; i < N; i++) {
        cout << "\nRouting Table for Router " << i << ":\n";
        cout << "Destination\tCost\n";
        for (int j = 0; j < N; j++) {
            if (dist[i][j] == INF)
                cout << j << "\t\t" << "INF" << endl;
            else
                cout << j << "\t\t" << dist[i][j] << endl;
        }
    }
}

int main() {
    // Adjacency matrix representing direct distances (INF = no direct path)
    int graph[N][N] = {
        {0,   2,   INF, 1},
        {2,   0,   3,   INF},
        {INF, 3,   0,   4},
        {1,   INF, 4,   0}
    };

    distanceVectorRouting(graph);

    return 0;
}
