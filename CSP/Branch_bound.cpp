#include <iostream>
#include <vector>
using namespace std;

class NQueensSolver
{
private:
    int n;
    vector<int> board;
    vector<bool> rowLookup;
    vector<bool> d1; // main diagonal
    vector<bool> d2; // anti-diagonal

public:
    NQueensSolver(int size)
    {
        n = size;
        board = vector<int>(size, -1);
        rowLookup = vector<bool>(size, false);
        d1 = vector<bool>(2 * size - 1, false);
        d2 = vector<bool>(2 * size - 1, false);
    }

    // Public method to start solving
    void solveNQueens()
    {
        if (solve(0))
        {
            cout << "\nSolution exists for " << n << "-Queens:\n";
            printBoard();
        }
        else
        {
            cout << "\nNo solution exists for " << n << "-Queens.\n";
        }
    }

    // Print current board
    void printBoard()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << (board[j] == i ? "Q " : "- ");
            }
            cout << endl;
        }
    }

    // Recursive solver with Branch and Bound
    bool solve(int col)
    {
        if (col == n)
        {
            return true;
        }

        for (int row = 0; row < n; ++row)
        {
            if (!rowLookup[row] && !d1[row + col] && !d2[row - col + n - 1])
            {
                board[col] = row;
                rowLookup[row] = d1[row + col] = d2[row - col + n - 1] = true;

                if (solve(col + 1))
                    return true;

                // Backtrack
                rowLookup[row] = d1[row + col] = d2[row - col + n - 1] = false;
            }
        }
        return false;
    }
};

int main()
{
    int n;
    cout << "Enter the board size (n): ";
    cin >> n;

    NQueensSolver solver(n);
    solver.solveNQueens();

    return 0;
}
