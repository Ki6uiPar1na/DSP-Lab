#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int to;
    double cost;
};

// Structure to represent a node during the A* evaluation process
struct Node {
    int id;
    double g; // Cost from start node to current node
    double f; // Total estimated cost (f = g + h)

    // Overload the operator to create a min-priority queue based on f-value
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class AStarGraph {
    int V;
    vector<vector<Edge>> adj;
    vector<double> heuristics; // h(n) values for each node

public:
    AStarGraph(int V) {
        this->V = V;
        adj.resize(V);
        heuristics.resize(V, 0.0);
    }

    void addEdge(int u, int v, double cost) {
        adj[u].push_back({v, cost});
    }

    void setHeuristic(int node, double h_val) {
        heuristics[node] = h_val;
    }

    void search(int start, int goal) {
        // Priority queue containing elements ordered by lowest f value
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        vector<double> gCost(V, 1e9); // Initialize path costs to infinity
        vector<int> parent(V, -1);
        vector<bool> closedSet(V, false);

        gCost[start] = 0.0;
        pq.push({start, 0.0, heuristics[start]});

        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();

            int u = curr.id;

            // If we reached the destination
            if (u == goal) {
                cout << "A* Path found with total cost: " << gCost[goal] << endl;
                printPath(parent, goal);
                return;
            }

            if (closedSet[u]) continue;
            closedSet[u] = true;

            // Evaluate neighbors
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                double weight = edge.cost;

                if (closedSet[v]) continue;

                double tentative_g = gCost[u] + weight;

                // Found a better path to node v
                if (tentative_g < gCost[v]) {
                    gCost[v] = tentative_g;
                    parent[v] = u;
                    double fCost = tentative_g + heuristics[v];
                    pq.push({v, tentative_g, fCost});
                }
            }
        }
        cout << "No path could be discovered to the goal node." << endl;
    }

private:
    void printPath(const vector<int>& parent, int goal) {
        if (parent[goal] == -1) {
            cout << goal;
            return;
        }
        printPath(parent, parent[goal]);
        cout << " -> " << goal;
    }
};

int main() {
    // Implementing a sample graph configuration
    AStarGraph g(4);
    
    // Set heuristics for nodes 0, 1, 2, 3
    g.setHeuristic(0, 5.5); // Start node
    g.setHeuristic(1, 3.0);
    g.setHeuristic(2, 2.0);
    g.setHeuristic(3, 0.0); // Goal node

    // Add weighted edges
    g.addEdge(0, 1, 2.0);
    g.addEdge(0, 2, 4.0);
    g.addEdge(1, 3, 5.0);
    g.addEdge(2, 3, 1.5);

    // Search for shortest path from node 0 to node 3
    g.search(0, 3);
    cout << endl;

    return 0;
}