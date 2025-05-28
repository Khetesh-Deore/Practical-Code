#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unistd.h> // For sleep (use Windows.h for Windows users)

using namespace std;

const int N = 8; // Chessboard size
int board[N][N];

// Possible knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2,  2,  1, -1, -2, -2, -1};

// Function to check if position is valid and unvisited
bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Count available onward moves from (x, y)
int countOnwardMoves(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny))
            count++;
    }
    return count;
}

// Warnsdorff's rule: choose the next move with minimum onward moves
bool nextMove(int &x, int &y, int moveNum) {
    vector<pair<int, pair<int, int>>> candidates;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (isValid(nx, ny)) {
            int c = countOnwardMoves(nx, ny);
            candidates.push_back({c, {nx, ny}});
        }
    }

    if (candidates.empty())
        return false;

    // Sort by least onward moves
    sort(candidates.begin(), candidates.end());

    x = candidates[0].second.first;
    y = candidates[0].second.second;
    board[x][y] = moveNum;

    return true;
}

// Display board
void displayBoard() {
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
    cout << endl;

    usleep(200000); // 0.2 sec delay for animation (Linux/macOS)
    // Sleep(200); // Uncomment for Windows users
}

int main() {
    // Initialize board
    for (int i = 0; i < N; i++)
        fill(board[i], board[i] + N, -1);

    int x, y;
    cout << "Enter starting position (0 to 7) for knight (x y): ";
    cin >> x >> y;

    board[x][y] = 1; // Starting move
    displayBoard();

    for (int move = 2; move <= N * N; move++) {
        if (!nextMove(x, y, move)) {
            cout << "Tour failed at move " << move << endl;
            break;
        }
        displayBoard();
    }

    cout << "Final Knight's Tour:\n";
    displayBoard();

    return 0;
}