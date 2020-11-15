#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <limits.h>

using namespace std;


class Edge {
public:
    int src, dest, flow;

    Edge(int src, int dest, int flow) : src(src), dest(dest), flow(flow) {}
};

list<Edge> edgeList;
int **matrix;
int numberOfEdges, numberOfNodes, maxFlow = 0;
int source = 0, sink = 3;
const int NONE = INT_MAX;

void readListFromFile(string filename);
void readMatrixFromFile(string filename);
bool findPath(int **graph, int path[]);
void runList(string filename);
void runMatrix(string filename);

template <typename Out>
void split(const string &s, char delimiter, Out result) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, delimiter)) {
        *result++ = item;
    }
}

vector<string> split(const string &s, char delimiter) {
    vector<string> elements;
    split(s, delimiter, back_inserter(elements));
    return elements;
}

int main() {
    string filename = "/home/piotr/CLionProjects/ZAISD/lab2/data.txt";
    runList(filename);
    runMatrix(filename);
    return 0;
}

void runList(string filename) {
    cout<<"---------------MATRIX---------------"<<endl;
    readListFromFile(filename);
    int **residualGraph = new int*[numberOfNodes];
    int path[numberOfNodes];
    maxFlow = 0;

    for (int src = 0; src < numberOfNodes; src++) {
        residualGraph[src] = new int[numberOfNodes];
        for (int dest = 0; dest < numberOfNodes; dest++) {
            residualGraph[src][dest] = NONE;
        }
    }

    for (Edge edge: edgeList) {
        residualGraph[edge.src][edge.dest] = edge.flow;
    }

    while (findPath(residualGraph, path)) {
        int pathFlow = INT_MAX;
        for (int src = source; src != sink; src=path[src]) {
            pathFlow = min(pathFlow, residualGraph[src][path[src]]);
        }
        cout<<"Path flow: "<<pathFlow<<endl<<endl;
        for (int src = source; src != sink; src=path[src]) {
            int dest = path[src];
            residualGraph[src][dest] -= pathFlow;
            if (residualGraph[dest][src] == NONE) {
                residualGraph[dest][src] = 0;
            }
            //residualGraph[dest][src] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    cout<<"Max flow: "<< +maxFlow<<endl;
    for (int i = 0; i < numberOfNodes; ++i) {
        delete [] residualGraph[i];
    }
    delete [] residualGraph;
}

void runMatrix(string filename) {
    cout<<"---------------LIST---------------"<<endl;
    readMatrixFromFile(filename);

    int **residualGraph = new int*[numberOfNodes];
    int path[numberOfNodes];
    maxFlow = 0;

    for (int src = 0; src < numberOfNodes; src++) {
        residualGraph[src] = new int[numberOfNodes];
        for (int dest = 0; dest < numberOfNodes; dest++) {
            residualGraph[src][dest] = matrix[src][dest];
        }
    }

    while (findPath(residualGraph, path)) {
        int pathFlow = INT_MAX;
        for (int src = source; src != sink; src=path[src]) {
            pathFlow = min(pathFlow, residualGraph[src][path[src]]);
        }
        cout<<"Path flow: "<<pathFlow<<endl<<endl;
        for (int src = source; src != sink; src=path[src]) {
            int dest = path[src];
            residualGraph[src][dest] -= pathFlow;
            if (residualGraph[dest][src] == NONE) {
                residualGraph[dest][src] = 0;
            }
            residualGraph[dest][src] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    cout<<"Max flow: "<< +maxFlow<<endl;
    for (int i = 0; i < numberOfNodes; ++i) {
        delete [] residualGraph[i];
        delete [] matrix[i];
    }
    delete [] residualGraph;
    delete [] matrix;

}

void readListFromFile(string filename) {
    ifstream file(filename);
    int lineNumber = 1;
    string line;
    while (getline(file, line)) {
        vector<string> vector = split(line, ' ');
        if (lineNumber == 1) {
            if (vector.size() == 2) {
                numberOfNodes = stoi(vector[0]);
                numberOfEdges = stoi(vector[1]);
            }
        } else {
            Edge newEdge = Edge(stoi(vector[0]), stoi(vector[1]), stoi(vector[2]));
            edgeList.push_front(newEdge);
        }
        lineNumber++;
    }
}

void readMatrixFromFile(string filename) {
    fstream file(filename);
    int lineNumber = 1;
    string line;
    while (getline(file, line)) {
        vector<string> vector = split(line, ' ');
        if (lineNumber == 1) {
            if (vector.size() == 2) {
                numberOfNodes = stoi(vector[0]);
                numberOfEdges = stoi(vector[1]);
                matrix = new int*[numberOfNodes];
                for (int i = 0; i < numberOfNodes; i++) {
                    matrix[i] = new int[numberOfNodes];
                    for (int j = 0; j < numberOfNodes; j++) {
                        matrix[i][j] = NONE;
                    }
                }
            }
        } else {
            matrix[stoi(vector[0])][stoi(vector[1])] = stoi(vector[2]);
        }
        lineNumber++;
    }

}

bool findPath(int **graph, int path[]) {
    int distance[numberOfNodes];
    for (int i = 0; i <numberOfNodes; i++) {
        path[i] = INT_MAX;
        distance[i] = INT_MAX;
    }
    distance[sink] = 0;

    for (int i = 0; i < numberOfEdges; i++) {
        for (int u = 0; u < numberOfNodes; u++) {
            for (int v = 0; v < numberOfNodes; v++) {
                int matrixValue = graph[u][v];
                if (matrixValue != NONE && matrixValue > 0 && distance[v] != INT_MAX && distance[u] > distance[v] + matrixValue) {
                    distance[u] = distance[v] + matrixValue;
                    path[u] = v;
                }
            }
        }
    }

    for (int src = source; src != sink; src = path[src]) {
        cout<<src<<"->";
        if (src == INT_MAX) {
            cout<<endl;
            return false;
        }
    }
    cout<<endl;
    return true;
}
