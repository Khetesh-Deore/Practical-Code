#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000;

class LinkState {
    int n;
    vector<vector<int>> graph;

public:
    LinkState(int nodes) : n(nodes), graph(nodes, vector<int>(nodes, INF)) {
        for (int i = 0; i < n; i++) graph[i][i] = 0;
    }

    void addEdge(int u, int v, int w) {
        graph[u][v] = w;
        graph[v][u] = w;
    }

    void dijkstra(int src) {
        vector<int> dist(n, INF);
        vector<bool> visited(n, false);
        dist[src] = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            int minDist = INF;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < n; v++) {
                if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        cout << "Distances from node " << src << ": ";
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) cout << "INF ";
            else cout << dist[i] << " ";
        }
        cout << "\n";
    }

    void run() {
        for (int i = 0; i < n; i++) {
            dijkstra(i);
        }
    }
};

int main() {
    LinkState ls(4);

    ls.addEdge(0, 1, 1);
    ls.addEdge(0, 2, 4);
    ls.addEdge(1, 2, 2);
    ls.addEdge(1, 3, 6);
    ls.addEdge(2, 3, 3);

    ls.run();

    return 0;
}