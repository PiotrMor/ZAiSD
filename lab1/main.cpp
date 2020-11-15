#include <iostream>
#include <list>
#include <bits/stdc++.h>

using namespace std;

class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

void BellmanFord(const list<struct Edge> &edges, int numberOfNodes, int destination);

void initializeArrayWithIntMax(int numberOfNodes, int *distance);

void runList();

void runMatrix();


int main() {
    runList();
    runMatrix();
    return 0;
}

void runMatrix() {
    cout << "-----Matrix-----" << endl;
    const int NONE = INT_MIN;
    const int numberOfNodes = 6;
    const int destinationNode = 3;
    int distance[numberOfNodes];
    int path[numberOfNodes];
    initializeArrayWithIntMax(numberOfNodes, distance);
    distance[destinationNode] = 0;

    int matrixArray[numberOfNodes][numberOfNodes] = {
            {NONE, 2,    NONE, NONE, NONE, 5},
            {NONE, NONE, 3,    NONE, NONE, 2},
            {NONE, 2,    NONE, 2,    NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, 1,    1,    NONE, NONE},
            {NONE, NONE, -4,   NONE, 2,    NONE}
    };

    /*int matrixArray[numberOfNodes][numberOfNodes] = {
            {NONE, 3, NONE, 4, NONE, NONE},
            {NONE, NONE, 1, NONE, NONE, 2},
            {NONE, NONE, NONE, -3, NONE, NONE},
            {NONE, NONE, NONE, NONE, 2, NONE},
            {NONE, NONE, NONE, NONE, NONE, 1},
            {NONE, NONE, NONE, NONE, NONE, NONE}
    };*/

/*    int matrixArray[numberOfNodes][numberOfNodes] = {
            {NONE, 2,    NONE, NONE, NONE, 5},
            {NONE, NONE, 3,    NONE, NONE, 2},
            {NONE, 2,    NONE, 2,    NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, 1,    1,    NONE, NONE},
            {NONE, NONE, -10,  NONE, 2,    NONE}
    };*/

    int numberOfEdges = 0;
    for (auto &i : matrixArray) {
        for (int j : i) {
            if (j != NONE) {
                numberOfEdges++;
            }
        }
    }

    for (int i = 0; i < numberOfEdges; i++) {
        for (int u = 0; u < numberOfNodes; u++) {
            for (int v = 0; v < numberOfNodes; v++) {
                int matrixValue = matrixArray[u][v];
                if (matrixValue != NONE && distance[v] != INT_MAX && distance[u] > distance[v] + matrixValue) {
                    distance[u] = distance[v] + matrixValue;
                    path[u] = v;
                }
            }
        }
    }

    for (int u = 0; u < numberOfNodes; u++) {
        for (int v = 0; v < numberOfNodes; v++) {
            int matrixValue = matrixArray[u][v];
            if (matrixValue != NONE && distance[v] != INT_MAX && distance[u] > distance[v] + matrixValue) {
                cout << "Negative cycle!" << endl;
            }
        }
    }

    cout << "Destination node: " << destinationNode << endl;
    for (int i = 0; i < numberOfNodes; i++) {
        cout << "Node: " << i << " d: " << distance[i] << " pi: " << path[i] << endl;
    }
}

void runList() {
    cout << "-----List-----" << endl;
    int numberOfNodes = 6;
    int destinationNode = 3;

    list<Edge> edgeList;
    edgeList.push_front(Edge(0, 1, 2));
    edgeList.push_front(Edge(1, 2, 3));
    edgeList.push_front(Edge(2, 1, 2));
    edgeList.push_front(Edge(2, 3, 2));
    edgeList.push_front(Edge(0, 5, 5));
    edgeList.push_front(Edge(5, 4, 2));
    edgeList.push_front(Edge(4, 3, 1));
    edgeList.push_front(Edge(1, 5, 2));
    edgeList.push_front(Edge(5, 2, -4));
    edgeList.push_front(Edge(4, 2, 1));

/*    edgeList.push_front(Edge(0, 1, 3));
    edgeList.push_front(Edge(1, 2, 1));
    edgeList.push_front(Edge(2, 5, 2));
    edgeList.push_front(Edge(2, 3, -3));
    edgeList.push_front(Edge(0, 3, 4));
    edgeList.push_front(Edge(3, 4, 2));
    edgeList.push_front(Edge(4, 5, 1));*/

/*    edgeList.push_front(Edge(0, 1, 2));
    edgeList.push_front(Edge(1, 2, 3));
    edgeList.push_front(Edge(2, 1, 2));
    edgeList.push_front(Edge(2, 3, 2));
    edgeList.push_front(Edge(0, 5, 5));
    edgeList.push_front(Edge(5, 4, 2));
    edgeList.push_front(Edge(4, 3, 1));
    edgeList.push_front(Edge(1, 5, 2));
    edgeList.push_front(Edge(5, 2, -10));
    edgeList.push_front(Edge(4, 2, 1));*/

    BellmanFord(edgeList, numberOfNodes, destinationNode);
}

void BellmanFord(const list<Edge> &edges, int numberOfNodes, int destination) {
    int numberOfEdges = edges.size();
    int distance[numberOfNodes];
    int path[numberOfNodes];

    initializeArrayWithIntMax(numberOfNodes, distance);
    distance[destination] = 0;

    for (int i = 0; i < numberOfNodes; i++) {
        for (Edge edge : edges) {
            if (distance[edge.dest] != INT_MAX && distance[edge.src] > distance[edge.dest] + edge.weight) {
                distance[edge.src] = distance[edge.dest] + edge.weight;
                path[edge.src] = edge.dest;
            }
        }
    }

    for (Edge edge : edges) {
        if (distance[edge.dest] != INT_MAX && distance[edge.src] > distance[edge.dest] + edge.weight) {
            cout << "Negative cycle!" << endl;
        }
    }

    cout << "Destination node: " << destination << endl;
    for (int i = 0; i < numberOfNodes; i++) {
        cout << "Node: " << i << " d: " << distance[i] << " pi: " << path[i] << endl;
    }

}

void initializeArrayWithIntMax(int numberOfNodes, int *distance) {
    for (int i = 0; i < numberOfNodes; i++) {
        distance[i] = INT_MAX;
    }
}
