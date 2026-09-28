/*
(1) 강의:
    24&25 chapter-29slide (DIJKSTRA Pseudo-code)
    24&25 chapter-63slide (Floyd-Warshall code)
(2) Blog:
    https://datahub.tistory.com/15 (file read)
    https://8156217.tistory.com/20 (sstream)
    https://jungeu1509.github.io/algorithm/use-priorityqueue/#11-%ED%97%A4%EB%8D%94 (Priority Queue)
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define MAX_NODES 20  // Maximum number of nodes
#define CELL_WIDTH 8

// Structure for a node in the adjacency list
typedef struct AdjListNode {
    string label;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Structure for the graph
typedef struct Graph {
    string nodeLabels[MAX_NODES];  // Array to store node labels ("A", "B", "C" ...)
    AdjListNode* adj[MAX_NODES];   // Adjacency list head pointer array
    int numVertices;
    int distance[MAX_NODES];
    bool visited[MAX_NODES];
} Graph;

// Function to create a new graph
Graph* createGraph() {
    Graph* graph = new Graph();
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adj[i] = NULL;
        graph->distance[i] = INT_MAX;
    }
    graph->numVertices = 0;
    return graph;
}

// Function to add a vertex to the graph
void addVertex(Graph* graph, string label) {
    if (graph->numVertices < MAX_NODES) {
        // Check if the label already exists
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->nodeLabels[i] == label) {
                cout << "Vertex" << label << "already exists." << endl;
                return;
            }
        }
        // Insert vertex in alphabetical order
        int i = 0;
        for (i = graph->numVertices - 1; i >= 0 && graph->nodeLabels[i] > label; i--) {
            graph->nodeLabels[i + 1] = graph->nodeLabels[i];
        }
        graph->nodeLabels[i + 1] = label;
        graph->numVertices++;
    } else {
        cout << "Maximum number of nodes reached." << endl;
    }
}

// Function to find the index of a vertex by its label
int getVertexIndex(Graph* graph, string label) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->nodeLabels[i] == label) {
            return i;
        }
    }
    return -1;  // Not found
}

// Function to add an edge
void addEdge(Graph* graph, string srcLabel, string destLabel, int weight = 1) {
    int srcIndex = getVertexIndex(graph, srcLabel);
    int destIndex = getVertexIndex(graph, destLabel);

    if (srcIndex == -1 || destIndex == -1) {
        cout << "Invalid vertex label." << endl;
        return;
    }
    AdjListNode* newNode = new AdjListNode();
    newNode->label = destLabel;
    newNode->weight = weight;
    // Insert in order
    if (graph->adj[srcIndex] == 0 || graph->adj[srcIndex]->label > destLabel) {  // Insert at head if it's alphabetically first
        newNode->next = graph->adj[srcIndex];
        graph->adj[srcIndex] = newNode;
        return;
    }
    AdjListNode* present = graph->adj[srcIndex];
    while (1) {
        if (present->label == destLabel) {
            cout << endl
                 << "!! Error: Duplicate edge detected. (" << srcLabel << " -> " << destLabel << ") !!" << endl
                 << endl;
            return;
        } else if (present->label < destLabel && (present->next == 0 || present->next->label > destLabel)) {  // Insert in the middle in sorted order
            newNode->next = present->next;
            present->next = newNode;
            return;
        }
        present = present->next;
    }
}

// Function to free the memory allocated for the graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        AdjListNode* current = graph->adj[i];
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete graph;
}

// Function to print the graph (adjacency list representation)
void printGraph(Graph* graph) {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < graph->numVertices; i++) {
        cout << graph->nodeLabels[i] << " -> ";
        AdjListNode* current = graph->adj[i];
        while (current != NULL) {
            cout << "(" << current->weight << ") " << current->label << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
    cout << endl;
}

void print_line(int& vertex_num) {
    int totalWidth = (CELL_WIDTH + 6) + vertex_num * (CELL_WIDTH + 5);
    for (int i = 0; i < totalWidth; i++) {
        cout << "-";
    }
    cout << endl;
}

void dijkstra(Graph* graph, string source) {
    int num_v = graph->numVertices;
    for (int i = 0; i < num_v; ++i) {
        graph->distance[i] = INT_MAX;
        graph->visited[i] = false;
    }

    int src = getVertexIndex(graph, source);
    graph->distance[src] = 0;

    typedef pair<int, int> P;
    priority_queue<P, vector<P>, greater<P>> Q;  // (distance, vertex)
    Q.push(make_pair(0, src));

    while (!Q.empty()) {
        P node = Q.top();
        Q.pop();
        int dist_u = node.first;
        int u = node.second;

        if (graph->visited[u]) continue;
        graph->visited[u] = true;

        // Relaxation step
        for (AdjListNode* p = graph->adj[u]; p != NULL; p = p->next) {
            int v = getVertexIndex(graph, p->label);
            int weight = p->weight;
            if (graph->distance[v] > graph->distance[u] + weight) {
                graph->distance[v] = graph->distance[u] + weight;
                Q.push(make_pair(graph->distance[v], v));
            }
        }
    }
}

void dijkstra_table(Graph* adj_graph, int& vertex_num) {
    cout << "< Dijkstra Table >" << endl;
    print_line(vertex_num);
    cout << "|  " << setw(CELL_WIDTH) << "" << "  |";

    for (int i = 0; i < vertex_num; i++) {  // Header row
        cout << "  " << setw(CELL_WIDTH) << std::right << adj_graph->nodeLabels[i] << "  |";
    }
    cout << endl;
    print_line(vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        dijkstra(adj_graph, adj_graph->nodeLabels[i]);  // Run Dijkstra for each source
        cout << "|  " << setw(CELL_WIDTH) << std::right << adj_graph->nodeLabels[i] << "  |";
        for (int j = 0; j < vertex_num; j++) {
            if (adj_graph->distance[j] == INT_MAX)
                cout << "  " << setw(CELL_WIDTH) << std::right << "  INF  "
                     << "  |";
            else
                cout << std::right << "  " << setw(CELL_WIDTH) << adj_graph->distance[j] << "  |";
        }
        cout << endl;
        print_line(vertex_num);
    }
    cout << endl;
}

void Floyd_Warshall(vector<vector<int>>& edges, int& vertex_num) {
    for (int k = 0; k < vertex_num; k++) {
        for (int i = 0; i < vertex_num; i++) {
            for (int j = 0; j < vertex_num; j++) {
                // Update shortest path via intermediate k
                if (edges[i][k] != INT_MAX && edges[k][j] != INT_MAX && edges[i][k] + edges[k][j] < edges[i][j]) {
                    edges[i][j] = edges[i][k] + edges[k][j];
                }
            }
        }
    }
}

void Floyd_Warshall_table(vector<string> mat_vertex, vector<vector<int>>& edges, int& vertex_num) {
    cout << "< Floyd_Warshall Table >" << endl;
    print_line(vertex_num);
    cout << "|  " << setw(CELL_WIDTH) << "" << "  |";

    for (int i = 0; i < vertex_num; i++) {  // Header row
        cout << "  " << setw(CELL_WIDTH) << std::right << mat_vertex[i] << "  |";
    }
    cout << endl;
    print_line(vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        cout << "|  " << setw(CELL_WIDTH) << std::right << mat_vertex[i] << "  |";
        for (int j = 0; j < vertex_num; j++) {
            if (edges[i][j] == INT_MAX)
                cout << "  " << setw(CELL_WIDTH) << std::right << "  INF  "
                     << "  |";
            else
                cout << std::right << "  " << setw(CELL_WIDTH) << edges[i][j] << "  |";
        }
        cout << endl;
        print_line(vertex_num);
    }
    cout << endl;
}

int main() {
    string line;
    vector<string> mat_vertex;      // Vertex labels from the file
    vector<vector<int>> mat_edges;  // Adjacency matrix (weights)
    Graph* adj_graph = createGraph();

    ifstream file("homework6.data");
    int mat_vertex_num = 0;

    // === Read file & build matrix ===
    if (file.is_open()) {
        while (getline(file, line) && ++(mat_vertex_num)) {
            istringstream ss(line);
            string temp;
            ss >> temp;  // First token is the vertex label
            mat_vertex.push_back(temp);

            vector<int> row;
            while (ss >> temp) {  // Remaining tokens are edge weights
                if (temp == "INF")
                    row.push_back(INT_MAX);
                else
                    row.push_back(stoi(temp));
            }
            mat_edges.push_back(row);
        }
        file.close();
    } else {
        cout << "Unable to open file";
        return -1;
    }

    // === Build adjacency list ===
    for (int i = 0; i < mat_vertex_num; i++) addVertex(adj_graph, mat_vertex[i]);

    for (int i = 0; i < adj_graph->numVertices; i++) {
        for (int j = 0; j < adj_graph->numVertices; j++) {
            if (mat_edges[i][j] != INT_MAX && mat_edges[i][j] != 0)
                addEdge(adj_graph, mat_vertex[i], mat_vertex[j], mat_edges[i][j]);
        }
    }

    printGraph(adj_graph);

    // === HW6 output ===
    dijkstra_table(adj_graph, mat_vertex_num);

    Floyd_Warshall(mat_edges, mat_vertex_num);
    Floyd_Warshall_table(mat_vertex, mat_edges, mat_vertex_num);

    freeGraph(adj_graph);  // Clean up

    return 0;
}
