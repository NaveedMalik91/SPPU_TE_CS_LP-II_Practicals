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
    vector<string> vertices;

public:
    graph() : ver(0), edg(0) {}

    graph(int val1, int val2)
    {
        this->ver = val1;
        this->edg = val2;
        this->adj_list.resize(val1);
    }

    int getVer() const { return ver; }
    const vector<string>& getVertices() const { return vertices; }

    void createGraph()
    {
        cout << "Enter the number of vertices in this graph: ";
        cin >> ver;
        adj_list.resize(ver);
        vertices.resize(ver);

        cout << "Enter the names of vertices (strings): " << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Enter vertex " << i + 1 << ": ";
            cin >> vertices[i];
        }

        cout << "Enter the number of edges in this graph: ";
        cin >> edg;
        cout << "Enter the edges (start end):" << endl;

        for (int i = 0; i < edg; ++i)
        {
            string strt, end;
            cin >> strt >> end;

            int startIndex = -1, endIndex = -1;

            for (int j = 0; j < ver; ++j)
            {
                if (vertices[j] == strt)
                    startIndex = j;
                if (vertices[j] == end)
                    endIndex = j;
            }

            if (startIndex == -1 || endIndex == -1)
            {
                cout << "Invalid edge: " << strt << " " << end << endl;
                continue;
            }

            adj_list[startIndex].push_back(end);
            adj_list[endIndex].push_back(strt);
        }
    }

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
            cout << "NULL" << endl;
        }
    }

    void calculateDegree()
    {
        cout << "Degree of Each Node:" << endl;
        for (int i = 0; i < ver; ++i)
        {
            cout << "Vertex " << vertices[i] << ": " << adj_list[i].size() << endl;
        }
    }

    void bfsTraversal(int startIndex, string target)
    {
        vector<bool> visited(ver, false);
        cout << "Breadth-First Search Traversal: ";

        queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;

        while (!q.empty())
        {
            int vtx = q.front();
            q.pop();
            cout << vertices[vtx] << " ";

            if (vertices[vtx] == target)
            {
                cout << "\nTarget " << target << " found in BFS.\n";
                return;
            }

            for (const string &u : adj_list[vtx])
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
                    q.push(uIndex);
                    visited[uIndex] = true;
                }
            }
        }

        cout << "\nTarget " << target << " not found in BFS.\n";
    }

    void dfsTraversal(int startIndex, string target)
    {
        vector<bool> visited(ver, false);
        cout << "Depth-First Search Traversal: ";

        stack<int> s;
        s.push(startIndex);
        visited[startIndex] = true;

        while (!s.empty())
        {
            int v = s.top();
            s.pop();
            cout << vertices[v] << " ";

            if (vertices[v] == target)
            {
                cout << "\nTarget " << target << " found in DFS.\n";
                return;
            }

            for (const string &u : adj_list[v])
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
                    s.push(uIndex);
                    visited[uIndex] = true;
                }
            }
        }

        cout << "\nTarget " << target << " not found in DFS.\n";
    }

    // Recursive DFS helper
    void recursiveDFSUtil(int index, const string &target, vector<bool> &visited, bool &found)
    {
        if (found || visited[index])
            return;

        visited[index] = true;
        cout << vertices[index] << " ";

        if (vertices[index] == target)
        {
            cout << "\nTarget " << target << " found in Recursive DFS.\n";
            found = true;
            return;
        }

        for (const string &neighbor : adj_list[index])
        {
            int neighborIndex = -1;
            for (int i = 0; i < ver; ++i)
            {
                if (vertices[i] == neighbor)
                {
                    neighborIndex = i;
                    break;
                }
            }
            if (neighborIndex != -1 && !visited[neighborIndex])
                recursiveDFSUtil(neighborIndex, target, visited, found);
        }
    }

    void recursiveDFS(int startIndex, const string &target)
    {
        vector<bool> visited(ver, false);
        bool found = false;
        cout << "Recursive DFS Traversal: ";
        recursiveDFSUtil(startIndex, target, visited, found);
        if (!found)
            cout << "\nTarget " << target << " not found in Recursive DFS.\n";
    }

    // Recursive BFS helper
    void recursiveBFSUtil(queue<int> &q, const string &target, vector<bool> &visited, bool &found)
    {
        if (q.empty() || found)
            return;

        int index = q.front();
        q.pop();
        cout << vertices[index] << " ";

        if (vertices[index] == target)
        {
            cout << "\nTarget " << target << " found in Recursive BFS.\n";
            found = true;
            return;
        }

        for (const string &neighbor : adj_list[index])
        {
            int neighborIndex = -1;
            for (int i = 0; i < ver; ++i)
            {
                if (vertices[i] == neighbor)
                {
                    neighborIndex = i;
                    break;
                }
            }

            if (neighborIndex != -1 && !visited[neighborIndex])
            {
                visited[neighborIndex] = true;
                q.push(neighborIndex);
            }
        }

        recursiveBFSUtil(q, target, visited, found);
    }

    void recursiveBFS(int startIndex, const string &target)
    {
        vector<bool> visited(ver, false);
        bool found = false;
        queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;
        cout << "Recursive BFS Traversal: ";
        recursiveBFSUtil(q, target, visited, found);
        if (!found)
            cout << "\nTarget " << target << " not found in Recursive BFS.\n";
    }
};

int main()
{
    graph obj;
    string startVertex, targetVertex;
    int startIndex = -1, choice;

    while (true)
    {
        cout << "\n-----------CHOICE----------" << endl;
        cout << "1. Create a graph" << endl;
        cout << "2. Display adjacency list/graph" << endl;
        cout << "3. Print degree of each node" << endl;
        cout << "4. Perform DFS and BFS traversal with search" << endl;
        cout << "5. Exit" << endl;
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
        {
            cout << "Enter the starting vertex: ";
            cin >> startVertex;
            cout << "Enter the target/search vertex: ";
            cin >> targetVertex;

            startIndex = -1;
            const vector<string>& vertices = obj.getVertices();
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
                obj.bfsTraversal(startIndex, targetVertex);
                obj.dfsTraversal(startIndex, targetVertex);
                obj.recursiveBFS(startIndex, targetVertex);
                obj.recursiveDFS(startIndex, targetVertex);
            }
            else
            {
                cout << "Invalid starting vertex!" << endl;
            }
            break;
        }
        case 5:
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
