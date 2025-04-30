#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>

using namespace std;

// Graph class
class graph
{
private:
    int ver;
    int edg;
    vector<vector<string>> adj_list;
    vector<string> vertices;  // This will store the vertex names

public:
    graph()
    {
        this->ver = 0;
        this->edg = 0;
        this->adj_list.resize(0);
    }

    graph(int val1, int val2)
    {
        this->ver = val1;
        this->edg = val2;
        this->adj_list.resize(val1); // resize the adj list to accommodate vertices = val1
    }

    // Getter functions to access private variables
    int getVer() const { return ver; }
    const vector<string>& getVertices() const { return vertices; }

    // Create a graph
    void createGraph()
    {
        cout << "Enter the number of vertices in this graph: ";
        cin >> ver;
        adj_list.resize(ver); // Resize to accommodate the number of vertices
        vertices.resize(ver);

        cout << "Enter the names of vertices (strings): " << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Enter vertex " << i + 1 << ": ";
            cin >> vertices[i];  // Input vertex name as string
        }

        cout << "Enter the number of edges in this graph: ";
        cin >> edg;
        cout << "Enter the edges (start end):" << endl;

        for (int i = 0; i < edg; ++i)
        {
            string strt, end;
            cin >> strt >> end;

            int startIndex = -1, endIndex = -1;

            // Find the indices of the start and end vertices
            for (int i = 0; i < ver; ++i)
            {
                if (vertices[i] == strt)
                    startIndex = i;
                if (vertices[i] == end)
                    endIndex = i;
            }

            if (startIndex == -1 || endIndex == -1) {
                cout << "Invalid edge: " << strt << " " << end << endl;
                continue;
            }

            adj_list[startIndex].push_back(end);
            adj_list[endIndex].push_back(strt); // Add reverse edge too
        }
    }

    // Display the graph
    void displayGraph()
    {
        cout << "Adjacency List Representation of the Graph:" << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Vertex " << vertices[i] << ": ";
            for (const string& neighbor : adj_list[i])
            {
                cout << neighbor << "->";
            }
            cout << endl;
        }
    }

    // Calculate the degree of each node
    void calculateDegree()
    {
        cout << "Degree of Each Node:" << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Vertex " << vertices[i] << ": " << adj_list[i].size() << endl;
        }
    }

    // BFS Traversal (recursive)
    void recursiveBfsTraversalHelper(int vtx, vector<bool>& visited, queue<int>& q)
    {
        if (q.empty()) return;

        // Process the front of the queue
        int front = q.front();
        q.pop();
        cout << vertices[front] << " ";

        // Visit all adjacent vertices of the current vertex
        for (const string& u : adj_list[front])
        {
            int uIndex = -1;
            for (int i = 0; i < ver; ++i)
            {
                if (vertices[i] == u)
                {
                    uIndex = i;
                    break;
                }
            }

            if (uIndex != -1 && !visited[uIndex]) 
            {
                visited[uIndex] = true;
                q.push(uIndex);
            }
        }

        // Continue processing the next vertex
        recursiveBfsTraversalHelper(vtx, visited, q);
    }

    // Wrapper for recursive BFS
    void recursiveBfsTraversal(int startIndex)
    {
        vector<bool> visited(ver, false);
        queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;

        cout << "Recursive Breadth-First Search Traversal: ";
        recursiveBfsTraversalHelper(startIndex, visited, q);
        cout << endl;
        cout << "BFS completed" << endl;
    }

    // DFS Traversal of the graph (recursive)
    void recursiveDfsTraversal(int vtx, vector<bool>& visited)
    {
        visited[vtx] = true;
        cout << vertices[vtx] << " ";

        for (const string& u : adj_list[vtx])
        {
            int uIndex = -1;
            for (int i = 0; i < ver; ++i)
            {
                if (vertices[i] == u)
                {
                    uIndex = i;
                    break;
                }
            }

            if (uIndex != -1 && !visited[uIndex])
            {
                recursiveDfsTraversal(uIndex, visited);
            }
        }
    }

    // Wrapper for recursive DFS
    void startRecursiveDfs(int startIndex)
    {
        vector<bool> visited(ver, false);
        cout << "Recursive Depth-First Search Traversal: ";
        recursiveDfsTraversal(startIndex, visited);
        cout << endl;
        cout << "DFS completed" << endl;
    }
};

// Main function
int main()
{
    graph obj;
    string startVertex;
    int startIndex = -1, choice;
    const vector<string>& vertices = obj.getVertices();  // Declare outside the switch

    while (true)
    {
        cout << "-----------CHOICE----------" << endl;
        cout << "1. Create a graph" << endl;
        cout << "2. Display adjacency list/graph" << endl;
        cout << "3. Print degree of each node" << endl;
        cout << "4. Perform DFS and BFS traversal" << endl;
        cout << "5. Perform recursive DFS traversal" << endl;
        cout << "6. Perform recursive BFS traversal" << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.createGraph();
            break;
        case 2:
            obj.displayGraph();
            break;
        case 3:
            obj.calculateDegree();
            break;
        case 4:
            cout << "Enter the starting vertex: ";
            cin >> startVertex;

            // Find the index of the start vertex
            startIndex = -1;
            for (int i = 0; i < obj.getVer(); ++i)
            {
                if (vertices[i] == startVertex)
                {
                    startIndex = i;
                    break;
                }
            }

            if (startIndex != -1)
            {
                obj.recursiveBfsTraversal(startIndex);
                obj.startRecursiveDfs(startIndex);
            }
            else
            {
                cout << "Invalid starting vertex!" << endl;
            }
            break;
        case 5:
            cout << "Enter the starting vertex: ";
            cin >> startVertex;

            // Find the index of the start vertex
            startIndex = -1;
            for (int i = 0; i < obj.getVer(); ++i)
            {
                if (vertices[i] == startVertex)
                {
                    startIndex = i;
                    break;
                }
            }

            if (startIndex != -1)
            {
                obj.startRecursiveDfs(startIndex);
            }
            else
            {
                cout << "Invalid starting vertex!" << endl;
            }
            break;
        case 6:
            cout << "Enter the starting vertex: ";
            cin >> startVertex;

            // Find the index of the start vertex
            startIndex = -1;
            for (int i = 0; i < obj.getVer(); ++i)
            {
                if (vertices[i] == startVertex)
                {
                    startIndex = i;
                    break;
                }
            }

            if (startIndex != -1)
            {
                obj.recursiveBfsTraversal(startIndex);
            }
            else
            {
                cout << "Invalid starting vertex!" << endl;
            }
            break;
        case 7:
            return 0;
        default:
            break;
        }
    }

    return 0;
}
