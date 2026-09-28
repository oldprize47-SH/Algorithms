/*
Lecture slide chapter 22 - page 52.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX_NODES 20  // Maximum number of nodes

// Enum for vertex colors during DFS
typedef enum {
    WHITE,  // Not visited
    GRAY,   // Currently in recursion stack
    BLACK   // Finished processing
} COLOR;

// Structure for a node in the adjacency list
typedef struct AdjListNode {
    string label;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Structure for the graph
typedef struct Graph {
    string nodeLabels[MAX_NODES];  // Array to store node labels ('A', 'B', 'C' ...)
    AdjListNode* adj[MAX_NODES];   // Adjacency list head pointer array
    int numVertices;
    int dt[MAX_NODES];
    int ft[MAX_NODES];
    int distance[MAX_NODES];
    string parent[MAX_NODES];
    COLOR color[MAX_NODES];
} Graph;

// Function to create a new graph
Graph* createGraph() {
    Graph* graph = new Graph();
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adj[i] = NULL;
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
        cout << graph->nodeLabels[i] << ": ";
        AdjListNode* current = graph->adj[i];
        while (current != NULL) {
            cout << current->label << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

// Depth First Search Visit function
void DFS_VISIT(Graph* graph, int u, int* time) {
    int v = 0;
    graph->color[u] = GRAY;
    graph->dt[u] = ++(*time);  // Record discovery time
    AdjListNode* current = graph->adj[u];
    while (current != NULL) {
        v = getVertexIndex(graph, current->label);
        if (graph->color[v] == WHITE)
            DFS_VISIT(graph, v, time);
        current = current->next;
    }
    graph->color[u] = BLACK;   // Mark as finished
    graph->ft[u] = ++(*time);  // Record finishing time
}

// Depth First Search function
void DFS(Graph* graph, int* time) {
    // Initialize all nodes to unvisited
    for (int i = 0; i < graph->numVertices; i++) {
        graph->color[i] = WHITE;
    }
    *time = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->color[i] == WHITE) {
            DFS_VISIT(graph, i, time);
        }
    }
}
Graph* gPtr = nullptr;
bool compare(int a, int b) {
    return gPtr->ft[a] > gPtr->ft[b];
}

int main() {
    int size;
    Graph* graph = createGraph();
    gPtr = graph;
    cout << "Enter the number of nodes: ";
    scanf(" %d", &size);
    // Add nodes
    addVertex(graph, "A");
    addVertex(graph, "B");
    addVertex(graph, "C");
    addVertex(graph, "D");
    addVertex(graph, "E");
    addVertex(graph, "F");
    addVertex(graph, "G");
    addVertex(graph, "H");
    addVertex(graph, "I");
    // HW 6

    printGraph(graph);
    cout << endl;

    int time = 0;

    DFS(graph, &time);

    cout << endl
         << "DFS Results:"
         << endl;
    for (int i = 0; i < graph->numVertices; i++) {
        cout << "Vertex " << graph->nodeLabels[i] << ": Discovery Time = " << graph->dt[i] << ", Finishing Time = " << graph->ft[i] << ", Color = ";
        if (graph->color[i] == WHITE)
            cout << "WHITE";
        else if (graph->color[i] == GRAY)
            cout << "GRAY";
        else if (graph->color[i] == BLACK)
            cout << "BLACK";
        cout << endl;
    }

    vector<int> idx(graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
        idx[i] = i;
    }

    sort(idx.begin(), idx.end(), compare);
    cout
        << endl;
    cout << "Topological Sort Result: " << endl;
    cout << graph->nodeLabels[idx[0]];
    for (int i = 1; i < graph->numVertices; i++) {
        cout << " -> " << graph->nodeLabels[idx[i]];
    }

    freeGraph(graph);  // Free all dynamically allocated memory

    return 0;
}
