#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    string name;
    Node *next;
    Node *down;

public:
    Node(string n = "", Node *node1 = nullptr, Node *node2 = nullptr)
    {
        this->name = n;
        this->next = nullptr;
        this->down = nullptr;
    }
    friend class Graph;
};

class Graph
{
private:
    Node *head = nullptr;

public:
    Graph()
    {
        head = nullptr;
    }

public:
    // Function to add an edge to the graph
    void add(string NodeA, string NodeB)
    {
        // Check if NodeA exists in the graph, if not create it
        if (head == nullptr)
        {
            Node *node1 = new Node(NodeA);
            Node *node2 = new Node(NodeB);
            head = node1;
            node1->next = node2;
        }
        else
        {
            Node *currentNode = head;
            bool foundA = false;
            bool foundB = false;

            // Traverse the graph to check if NodeA and NodeB exist
            while (currentNode != nullptr)
            {
                if (currentNode->name == NodeA)
                {
                    foundA = true;
                }
                if (currentNode->name == NodeB)
                {
                    foundB = true;
                }
                currentNode = currentNode->down;
            }

            // If NodeA doesn't exist, create it
            if (!foundA)
            {
                Node *newNodeA = new Node(NodeA);
                newNodeA->down = head;
                head = newNodeA;
            }

            // If NodeB doesn't exist, create it
            if (!foundB)
            {
                Node *newNodeB = new Node(NodeB);
                newNodeB->down = head;
                head = newNodeB;
            }

            // Now that we know both nodes exist, add the edge
            currentNode = head;
            while (currentNode != nullptr)
            {
                if (currentNode->name == NodeA)
                {
                    Node *currentListNode = currentNode;
                    while (currentListNode->next != nullptr)
                        currentListNode = currentListNode->next;
                    Node *newNode = new Node(NodeB);
                    currentListNode->next = newNode;
                    break;
                }
                currentNode = currentNode->down;
            }
        }
    }

    void print()
    {
        Node *currentArrayNode = head;
        while (currentArrayNode != nullptr)
        {
            Node *currentListNode = currentArrayNode;
            while (currentListNode != nullptr)
            {
                cout << currentListNode->name << " -> ";
                currentListNode = currentListNode->next;
            }
            cout << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void printOutDegrees()
    {
        Node *currentArrayNode = head;
        while (currentArrayNode != nullptr)
        {
            Node *currentListNode = currentArrayNode->next;
            int degree = 0;
            while (currentListNode != nullptr)
            {
                degree++;
                currentListNode = currentListNode->next;
            }
            cout << currentArrayNode->name << " : " << degree << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void printInDegrees()
    {
        Node *currentNode = head;
        while (currentNode != nullptr)
        {
            int count = 0;
            Node *temp = head;
            while (temp != nullptr)
            {
                Node *neighbour = temp->next;

                // Check if the current node is a neighbor of any other node
                while (neighbour != nullptr)
                {
                    if (neighbour->name == currentNode->name) // Incoming edge to current node
                        count++;                              // Increment count for each incoming edge
                    neighbour = neighbour->next;
                }
                temp = temp->down; // Move to the next node's adjacency list
            }

            cout << currentNode->name << "\t : \t" << count << endl;
            currentNode = currentNode->down; // Move to the next node
        }
    }

    // Iterative BFS
    void BFS(string node)
    {
        queue<string> Queue;
        vector<string> visited;
        Queue.push(node);
        visited.push_back(node);
        while (!Queue.empty())
        {
            node = Queue.front();
            Queue.pop();
            cout << node << " ";

            Node *currentNode = head;
            bool found = false;
            while (currentNode != nullptr)
            {
                if (currentNode->name == node)
                {
                    found = true;
                    Node *currentListNode = currentNode->next;
                    while (currentListNode != nullptr)
                    {
                        if (find(visited.begin(), visited.end(), currentListNode->name) == visited.end())
                        {
                            visited.push_back(currentListNode->name);
                            Queue.push(currentListNode->name);
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if (!found)
            {
                cout << "Given node not in the graph" << endl;
                return;
            }
        }
        cout << endl;
    }

    // Iterative DFS
    void DFS(string node)
    {
        stack<string> Stack;
        vector<string> visited;
        Stack.push(node);
        visited.push_back(node);
        while (!Stack.empty())
        {
            node = Stack.top();
            Stack.pop();
            cout << node << " ";

            Node *currentNode = head;
            bool found = false;
            while (currentNode != nullptr)
            {
                if (currentNode->name == node)
                {
                    found = true;
                    Node *currentListNode = currentNode->next;
                    while (currentListNode != nullptr)
                    {
                        if (find(visited.begin(), visited.end(), currentListNode->name) == visited.end())
                        {
                            Stack.push(currentListNode->name);
                            visited.push_back(currentListNode->name);
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if (!found)
            {
                cout << "Given node doesn't exist in the graph" << endl;
                return;
            }
        }
        cout << endl;
    }

    // Correct Recursive BFS Helper
    void bfs_recursive_helper(queue<string> &q, set<string> &visited)
    {
        if (q.empty())
            return;

        string node = q.front();
        q.pop();
        cout << node << " ";

        Node *currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->name == node)
            {
                Node *currentListNode = currentNode->next;
                while (currentListNode != nullptr)
                {
                    if (visited.find(currentListNode->name) == visited.end())
                    {
                        visited.insert(currentListNode->name);
                        q.push(currentListNode->name);
                    }
                    currentListNode = currentListNode->next;
                }
                break;
            }
            currentNode = currentNode->down;
        }

        bfs_recursive_helper(q, visited);
    }

    // Public function to start Recursive BFS
    void BFS_recursive(string node)
    {
        set<string> visited;
        queue<string> q;
        visited.insert(node);
        q.push(node);
        bfs_recursive_helper(q, visited);
        cout << endl;
    }

    // Correct Recursive DFS Helper
    void dfs_recursive_helper(string node, set<string> &visited)
    {
        cout << node << " ";
        visited.insert(node);

        Node *currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->name == node)
            {
                Node *currentListNode = currentNode->next;
                while (currentListNode != nullptr)
                {
                    if (visited.find(currentListNode->name) == visited.end())
                    {
                        dfs_recursive_helper(currentListNode->name, visited);
                    }
                    currentListNode = currentListNode->next;
                }
                break;
            }
            currentNode = currentNode->down;
        }
    }

    // Public function to start Recursive DFS
    void DFS_recursive(string node)
    {
        set<string> visited;
        dfs_recursive_helper(node, visited);
        cout << endl;
    }
};

// Main function to test the graph implementation
int main()
{
    Graph g;

    int choice;
    do
    {
        cout << "\nMenu: \n";
        cout << "1. Add edge\n";
        cout << "2. Print graph\n";
        cout << "3. Print in-degrees\n";
        cout << "4. Print out-degrees\n";
        cout << "5. Perform BFS (Iterative)\n";
        cout << "6. Perform DFS (Iterative)\n";
        cout << "7. Perform BFS (Recursive)\n";
        cout << "8. Perform DFS (Recursive)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int numEdges;
            cout << "Enter the number of edges to add: ";
            cin >> numEdges;
            cout << "Enter the edges in the format NodeA NodeB: \n";
            for (int i = 0; i < numEdges; i++)
            {
                string NodeA, NodeB;
                cin >> NodeA >> NodeB;
                g.add(NodeA, NodeB); // Adding the edge to the graph
            }
            break;
        }
        case 2:
            cout << "Graph: \n";
            g.print();
            break;
        case 3:
            cout << "In-degrees: \n";
            g.printInDegrees();
            break;
        case 4:
            cout << "Out-degrees: \n";
            g.printOutDegrees();
            break;
        case 5:
        {
            string node;
            cout << "Enter the node to start BFS: ";
            cin >> node;
            cout << "BFS Traversal: ";
            g.BFS(node);
            break;
        }
        case 6:
        {
            string node;
            cout << "Enter the node to start DFS: ";
            cin >> node;
            cout << "DFS Traversal: ";
            g.DFS(node);
            break;
        }
        case 7:
        {
            string node;
            cout << "Enter the node to start Recursive BFS: ";
            cin >> node;
            cout << "Recursive BFS Traversal: ";
            g.BFS_recursive(node);
            break;
        }
        case 8:
        {
            string node;
            cout << "Enter the node to start Recursive DFS: ";
            cin >> node;
            cout << "Recursive DFS Traversal: ";
            g.DFS_recursive(node);
            break;
        }
        case 9:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
