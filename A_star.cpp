#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>

using namespace std;

// Define the puzzle size
const int N = 3;

// Class to represent a puzzle state
class PuzzleState
{
    private:
    int puzzle[N][N];
    int zeroRow, zeroCol; //cordinates of a any empty cell
    int g, h; //g = cost so far, h = manhattan distance
    
    public:
    PuzzleState()
    {
        this->g = 0;
        this->h = 0;
        this->zeroRow = 0;
        this->zeroCol = 0;

        //set position of empty tile initially to top left corner
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                this->puzzle[i][j] = 0;
            }
        }
    }

    //Overload the < operator to compare puzzle states
    bool operator<(const PuzzleState &other) const
    {
        return (g + h) > (other.g + other.h);
    }

    void printPuzzle() const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << puzzle[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-----\n";
    }


    //Function to check whether the goat state is reached, i.e initial == final
    bool isEqual(const PuzzleState &other) const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (puzzle[i][j] != other.puzzle[i][j])
                    return false;
            }
        }
        return true;
    }

    //Heuristic Function which calculated heuristic cost
    int calculateManhattanDistance() const
    {
        int distance = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int value = puzzle[i][j];
                if (value != 0)
                {
                    //Target row and column for each cel value i.e. target cell for a value   
                    int targetRow = (value - 1) / N;
                    int targetCol = (value - 1) % N;
                    distance += abs(i - targetRow) + abs(j - targetCol);
                }
            }
        }
        return distance;
    }

    vector<PuzzleState> generateNextStates() const
    {
        vector<PuzzleState> nextStates;
        const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Left, Right, Up, Down

        for (int k = 0; k < 4; k++)
        {
            //add move dir to the empty tile to all possible directions
            int nextZeroRow = zeroRow + moves[k][0];
            int nextZeroCol = zeroCol + moves[k][1];

            //Remain in bounds i.e between 0 to N
            if (nextZeroRow >= 0 && nextZeroRow < N && nextZeroCol >= 0 && nextZeroCol < N)
            {
                PuzzleState nextState = *this; //Create a new object nextState that is an exact copy of the current puzzle state.
                swap(nextState.puzzle[zeroRow][zeroCol], nextState.puzzle[nextZeroRow][nextZeroCol]); //swap current state particular position with new position
                nextState.zeroRow = nextZeroRow;  //update the blank tile position 
                nextState.zeroCol = nextZeroCol;
                nextState.g = g + 1;
                nextState.h = nextState.calculateManhattanDistance();
                nextStates.push_back(nextState);
            }
        }

        return nextStates;
    }

    // A* search algorithm
    void aStarSearch(const PuzzleState &finalState)
    {
        priority_queue<PuzzleState> pq;
        unordered_set<int> visited;

        pq.push(*this);

        while (!pq.empty())
        {
            PuzzleState current = pq.top();
            pq.pop();

            cout << "Current State:\n";
            current.printPuzzle();
            cout << "Number of moves: " << current.g << endl;
            cout << "Heuristic cost: " << current.h << endl;
            cout << "-------------------\n";

            if (current.isEqual(finalState))
            {
                cout << "Goal State Reached!\n";
                cout << "Number of moves: " << current.g << endl;
                cout << "Heuristic cost: " << current.h << endl;
                break;
            }

            vector<PuzzleState> nextStates = current.generateNextStates();

            for (const PuzzleState &nextState : nextStates)
            {
                int hash = 0;
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++)
                        hash = hash * 10 + nextState.puzzle[i][j];

                if (visited.find(hash) == visited.end())
                {
                    pq.push(nextState);
                    visited.insert(hash);
                }
            }
        }
    }

    // Static function to get user input for the puzzle state
    static PuzzleState getPuzzleState(const string &prompt)
    {
        PuzzleState state;

        cout << prompt << " (0 represents the empty tile):\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << "Enter value at position (" << i << ", " << j << "): ";
                cin >> state.puzzle[i][j];

                if (state.puzzle[i][j] == 0)
                {
                    state.zeroRow = i;
                    state.zeroCol = j;
                }
            }
        }

        state.h = state.calculateManhattanDistance();
        return state;
    }
};

int main()
{
    PuzzleState initialState = PuzzleState::getPuzzleState("Enter the initial state of the puzzle");
    PuzzleState finalState = PuzzleState::getPuzzleState("Enter the final state of the puzzle");

    cout << "Initial State:\n";
    initialState.printPuzzle();

    initialState.aStarSearch(finalState);

    return 0;
}
