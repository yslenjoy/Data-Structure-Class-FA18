#include <iostream>
#include <string>
#include "adjacency_list.h"

using namespace std;

bool containsEdge(Graph const * const g, int src, int dest) {
    // Your code here
    AdjacencyList adjList = g->adjLists[src];
    // if (adjList.edges == NULL) {
    //     return false;
    // }
    LinkedListNode* node = adjList.edges;
    while (node != NULL) {
        if (node->v == dest) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void addEdge(Graph* g, int src, int dest) {
    // Your code here
    AdjacencyList & srcList = g->adjLists[src];
    // this should be a reference variable since changes will be made to this variable, make a copy is not helpful
    
    // AdjacencyList destList = g->adjLists[dest];
    if (containsEdge(g, src, dest)) {// necessary to earn full credit
        return;
    }

    // src vertex manipulation
    LinkedListNode* srcEdge = new LinkedListNode();
    // insert front (null case is also considered)
    srcEdge->next = srcList.edges;
    srcEdge->v = dest;
    srcList.edges = srcEdge;

    // Since in this adj list the direction matters, these steps should be eliminated
    // // dest vertex manipulation
    // LinkedListNode* destEdge = new LinkedListNode();
    // destEdge->next = destList.edges->next;
    // destList.edges->next = destEdge;
    // destEdge->v = src;    
}

int numOutgoingEdges(Graph const * const g, int v) {
    // Your code here
    AdjacencyList adjList = g->adjLists[v];

    LinkedListNode* node = adjList.edges;
    // cout << 
    int count = 0;
    while (node != NULL) {
        cout << "outgoing" << endl;
        count++;
        node = node->next;
    }
    return count;
    
}


int numIncomingEdges(Graph const * const g, int v) {
    // Your code here
    int vNum = g->n;
    int count = 0;
    for (int i = 0; i < vNum; i++) {
        AdjacencyList adjList = g->adjLists[i];
        LinkedListNode* node = adjList.edges;
        while (node != NULL) {
            if (node->v == v) {
                count++;
            }
            node = node->next;
        }
    }
    return count;
}

// No need to modify the functions below

Graph* createVertices(int numV) {
        Graph* g = new Graph();
        g->adjLists = new AdjacencyList[numV];
        g->n = numV;

        // Initialize the vertices
        for (int i = 0; i < numV; i += 1) {
                g->adjLists[i].vertex = i;
                g->adjLists[i].edges = NULL;
        }

        return g;
}

void printGraph(Graph const * const g) {
    for (int i = 0; i < g->n; i += 1) {
        AdjacencyList adjList = g->adjLists[i];

        int v = adjList.vertex;
        // Vertex
        cout << "Vertex: " << v << endl;

        // Print number of incoming and outgoing edges
        int inc = numIncomingEdges(g, v);
        int out = numOutgoingEdges(g, v);
        cout << "Number of incoming edges: " << inc << endl;
        cout << "Number of outgoing edges: " << out << endl;

        cout << "\n" << endl;
    }
}
