#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int u;
    int v;
    double weight;

    Edge(int u, int v, double weight) : u(u), v(v), weight(weight) {}
};

// Structure to represent a node in the priority queue
struct Node {
    int vertex;
    double key;

    Node(int v, double k) : vertex(v), key(k) {}

    // Comparison operator for priority queue
    bool operator<(const Node& other) const {
        return key < other.key;
    }
};

// Binary heap implementation of the priority queue
class PriorityQueue {
private:
    vector<Node> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) { // Modified comparison operator
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index; // Modified variable name

            if (left < size && heap[left] < heap[smallest]) { // Modified comparison operator
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) { // Modified comparison operator
                smallest = right;
            }

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    bool empty() const {
        return heap.empty();
    }

    void push(const Node& node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    Node top() const {
        return heap[0];
    }

    void pop() {
        if (!empty()) {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
        }
    }
};

// Function to write the MST to the output file
void writeMSTToFile(const vector<Edge>& mst) {
    ofstream file("mst.txt");
    if (!file) {
        cerr << "Failed to create the output file." << endl;
        return;
    }

    double totalWeight = 0.0;
    for (int i = 0; i < mst.size(); ++i) {
        const Edge& edge = mst[i];
        totalWeight += edge.weight;
    }

    file << totalWeight << endl;

    for (int i = 0; i < mst.size(); ++i) {
        const Edge& edge = mst[i];
        file << edge.u << " " << edge.v << " " << edge.weight << endl;
    }

    file.close();
}

// Prim's algorithm to find the Minimum Spanning Tree
void primMST(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) {
        cerr << "Failed to open the input file." << endl;
        return;
    }

    int numVertices;
    file >> numVertices;

    vector<bool> inMST(numVertices, false); // Keeps track of vertices included in MST

    PriorityQueue pq;

    int startVertex = 0; // Start with vertex 0 as the initial vertex
    pq.push(Node(startVertex, 0.0));

    vector<vector<pair<int, double> > > graph(numVertices); // Adjacency list representation of the graph

    int u, v;
    double weight;
    while (file >> u >> v >> weight) {
        graph[u].push_back(make_pair(v, weight));
        graph[v].push_back(make_pair(u, weight));
    }

    file.close();

    vector<Edge> mst; // Stores the edges of the MST
    vector<double> key(numVertices, numeric_limits<double>::max()); // Stores the key values
    vector<int> parent(numVertices, -1); // Stores the parent vertices

    while (!pq.empty()) {
        int u = pq.top().vertex;
        double keyU = pq.top().key;
        pq.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;

        if (parent[u] != -1) {
            mst.push_back(Edge(parent[u], u, keyU));
        }

        for (int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i].first;
            double weight = graph[u][i].second;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push(Node(v, weight));
            }
        }
    }

    writeMSTToFile(mst);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Please provide the input filename." << endl;
        return 1;
    }

    string filename = argv[1];

    // Measure the time taken to construct MST
    clock_t startTime = clock();
    primMST(filename);
    double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;

    cout << "Time: " << elapsedTime << endl;

    return 0;
}