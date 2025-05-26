/*


Knight’s tour: The problem is to move the knight, beginning from any
given square on the chessboard, in such a manner that it travels
successively to all 64 squares, touching each square once and only once.
It is convenient to represent a solution by placing the numbers 1,2, ...,64 in
the squares of the chessboard indicating the order in which the squares are
reached. Note that it is not required that the knight be able to reach the
initial position by one more move; if this is possible the knight's tour is
called re-entrant. One of the more ingenious methods for solving the
problem of the knight's tour is that given by J. C. Warnsdorff in 1823. His
rule is that the knight must always be moved to one of the squares from*/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int N = 8;

// All possible moves for a knight
int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Check if position is valid and not yet visited
bool isValid(int x, int y, int board[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Count how many valid moves knight can make from position (x, y)
int countOnwardMoves(int x, int y, int board[N][N]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + moveX[i];
        int ny = y + moveY[i];
        if (isValid(nx, ny, board)) count++;
    }
    return count;
}

// Warnsdorff's Rule to find the next move
bool nextMove(int &x, int &y, int board[N][N]) {
    int minDeg = 9, nextX = -1, nextY = -1;

    for (int i = 0; i < 8; i++) {
        int nx = x + moveX[i];
        int ny = y + moveY[i];

        if (isValid(nx, ny, board)) {
            int deg = countOnwardMoves(nx, ny, board);
            if (deg < minDeg) {
                minDeg = deg;
                nextX = nx;
                nextY = ny;
            }
        }
    }

    if (nextX == -1) return false;

    x = nextX;
    y = nextY;
    return true;
}

// Solve Knight’s Tour using Warnsdorff’s Rule
bool knightTour(int startX, int startY) {
    int board[N][N];
    memset(board, -1, sizeof(board));

    int x = startX, y = startY;
    board[x][y] = 1;

    for (int step = 2; step <= N * N; step++) {
        if (!nextMove(x, y, board))
            return false;
        board[x][y] = step;
    }

    // Print the board
    cout << "\nKnight's Tour Path:\n\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(3) << board[i][j] << " ";
        cout << endl;
    }

    return true;
}

int main() {
    int startX, startY;
    cout << "Enter starting position (0 to 7 for X and Y):\n";
    cout << "X: ";
    cin >> startX;
    cout << "Y: ";
    cin >> startY;

    if (startX < 0 || startX >= N || startY < 0 || startY >= N) {
        cout << "Invalid input. Please enter values between 0 and 7.\n";
        return 1;
    }

    if (!knightTour(startX, startY))
        cout << "No solution found.\n";
    else
        cout << "\nTour completed successfully!\n";

    return 0;
}
/*Output:

Enter starting position (0 to 7 for X and Y):
X: 7 
Y: 4

Knight's Tour Path:

 30  27  10  49  40  25   8   5 
 11  48  29  26   9   6  39  24 
 28  31  50  43  52  41   4   7 
 47  12  53  60  19  44  23  38 
 32  57  46  51  42  59  18   3 
 13  54  61  58  45  20  37  22 
 64  33  56  15  62  35   2  17 
 55  14  63  34   1  16  21  36 

Tour completed successfully!*/