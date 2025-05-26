#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unistd.h> // For usleep()

using namespace std;

const int N = 8; // Chessboard size
int board[N][N];

// All 8 possible knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2,  2,  1, -1, -2, -2, -1};

// Check if the next move is within bounds and not visited
bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Count onward moves from (x, y)
int countOnwardMoves(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny))
            count++;
    }
    return count;
}

// Pick the next move using Warnsdorff’s rule
bool nextMove(int &x, int &y, int moveNum) {
    vector<pair<int, pair<int, int>>> candidates;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny)) {
            int onward = countOnwardMoves(nx, ny);
            candidates.push_back({onward, {nx, ny}});
        }
    }

    if (candidates.empty()) return false;

    // Sort by least onward moves
    sort(candidates.begin(), candidates.end());

    x = candidates[0].second.first;
    y = candidates[0].second.second;
    board[x][y] = moveNum;

    return true;
}

// Show the board in the terminal
void displayBoard() {
    system("clear"); // Clear terminal for animation
    cout << "\nKnight's Tour Progress:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == -1)
                cout << setw(3) << ".";
            else
                cout << setw(3) << board[i][j];
        }
        cout << endl;
    }
    usleep(200000); // 0.2 second delay for animation
}

int main() {
    // Initialize board with -1
    for (int i = 0; i < N; i++)
        fill(board[i], board[i] + N, -1);

    int x, y;
    cout << "Enter starting position (row and column from 0 to 7): ";
    cin >> x >> y;

    if (x < 0 || x >= N || y < 0 || y >= N) {
        cout << "Invalid starting position!\n";
        return 1;
    }

    board[x][y] = 1;
    displayBoard();

    for (int move = 2; move <= N * N; move++) {
        if (!nextMove(x, y, move)) {
            cout << "\nTour failed at move " << move << endl;
            return 0;
        }
        displayBoard();
    }

    cout << "\n🎉 Knight's Tour completed successfully! Final Board:\n";
    displayBoard();
    return 0;
}
