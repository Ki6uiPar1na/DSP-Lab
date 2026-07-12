#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

    // Helper function used by DFS
    void DFSUtil(int v, vector<bool>& visited) {
        // Mark the current node as visited and print it
        visited[v] = true;
        cout << v << " ";

        // Recur for all the vertices adjacent to this vertex
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // DFS traversal of the vertices reachable from v
    void DFS(int v) {
        vector<bool> visited(V, false);
        cout << "Depth First Search starting from node " << v << ": ";
        DFSUtil(v, visited);
        cout << endl;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    g.DFS(0);

    return 0;
}