#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Class representing a directed graph using an adjacency list
class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // BFS traversal from a given source s
    void BFS(int s) {
        vector<bool> visited(V, false);
        queue<int> q;

        // Mark the current node as visited and enqueue it
        visited[s] = true;
        q.push(s);

        cout << "Breadth First Search starting from node " << s << ": ";

        while (!q.empty()) {
            // Dequeue a vertex from queue and print it
            int curr = q.front();
            cout << curr << " ";
            q.pop();

            // Get all adjacent vertices of the dequeued vertex curr.
            // If an adjacent vertex has not been visited, mark it visited and enqueue it.
            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Create a graph with 5 vertices (0 to 4)
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    g.BFS(0);

    return 0;
}