#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 20; // Max size of grid

// Structure for the cockroach
struct Cockroach {
    int x, y;
};

// 8 possible directions (dx, dy)
int dx[8] = {-1, -1,  0, 1, 1, 1,  0, -1};
int dy[8] = { 0,  1,  1, 1, 0, -1, -1, -1};

// Function to initialize the grid
void initializeGrid(int visited[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visited[i][j] = 0;
}

// Function to display the grid
void displayGrid(int visited[MAX][MAX], int n, int m, int cx, int cy) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == cx && j == cy)
                cout << "C "; // Cockroach
            else if (visited[i][j] == 1)
                cout << ". ";
            else
                cout << "- ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if all tiles are visited
bool allVisited(int visited[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (visited[i][j] == 0)
                return false;
    return true;
}

// Main function
int main() {
    srand(time(0));

    int n, m;
    cout << "Enter number of rows (max 20): ";
    cin >> n;
    cout << "Enter number of columns (max 20): ";
    cin >> m;

    int visited[MAX][MAX];
    initializeGrid(visited, n, m);

    Cockroach roach;
    roach.x = n / 2;
    roach.y = m / 2;

    visited[roach.x][roach.y] = 1;
    int steps = 0;

    while (!allVisited(visited, n, m)) {
        int dir = rand() % 8;
        int nx = roach.x + dx[dir];
        int ny = roach.y + dy[dir];

        // Check bounds
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            roach.x = nx;
            roach.y = ny;
            visited[roach.x][roach.y] = 1;
            steps++;

            displayGrid(visited, n, m, roach.x, roach.y);

            // Optional delay (simulate movement)
            for (volatile int d = 0; d < 10000000; d++); // crude delay
        }
    }

    cout << "All tiles visited in " << steps << " moves.\n";

    return 0;
}