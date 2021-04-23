/**
 * @file main.cpp
 * @brief This is Final Project for CPTR 227.
 * @details This is implementation of Dijkstra's Algorithm to find the shortest path.
 * @author Nathan Quick & Brandon Yi
 * @date 5/5/2021
 * 
 */

#include <iostream>
#include <vector>
using namespace std;

class Graph{
private:
    int n;
    int **matrix;
public:
    //http://www.cplusplus.com/forum/articles/7459/ was used to understand how to make a variable matrix
    Graph(int x){
        n = x;
        matrix = new int*[n];
        for (int i=0; i<n; i++)
            matrix[i] = new int[n];

    }

    void addEdge(int i, int j, int dist) {
        matrix[i][j] = dist;
        matrix[j][i] = dist;
    }
    void removeEdge(int i, int j) {
        matrix[i][j] = 0;
        matrix[i][j] = 0;
    }
    int distance(int i, int j) {
        return matrix[i][j];
    }


    vector<int> outEdges(int i) {
        vector<int> edges;
        for (int j=0; j<n; j++) {
            if (matrix[i][j]) {
                edges.push_back(j);
            }
        }
        return edges;
    }

    int length(){
        return n;
    }

    int **matrixOut(){
        return matrix;
    }
};


// TODO make the distance print nice
void Dijkstra(Graph g, int source, int* dist, int* parent) {
    int index = 0;
    bool used[g.length()];

    for (int i=0; i<g.length(); i++){
        dist[i] = -1;
        used[i] = false;
    }

    dist[source] = 0;
    used[source] = true;
    parent[source] = 0;

    for (int i=0; i<g.length(); i++){
        vector<int> edge = g.outEdges(index);
        for (int ii=0; ii<edge.size(); ii++){
            int u = dist[index] + g.distance(index, edge[ii]);
            if (u < dist[edge[ii]] || dist[edge[ii]] == -1){
                parent[edge[ii]] = index;
                dist[edge[ii]] = dist[index] + g.distance(index, edge[ii]);
            }
        }
        int min = -1;
        for (int ii=0; ii<g.length(); ii++){
            if (!used[ii] && dist[ii] != -1){
                if (dist[ii] < min || min == -1){
                    min = dist[ii];
                    index = ii;
                }
            }
        }
        used[index] = true;
    }
}

void printShortPath(int* parent) {
    int index = 0;
    for (int i=0; i<9; i++){
        cout << i;
        index = i;
        do
        {
                cout << " ← " << parent[index];
                index = parent[index];
        } while (index > 0);
        cout << endl;
    }
}


int main(int, char**) {
    Graph g(9);

    int dist[g.length()];
    int parent[g.length()];

    g.addEdge(0,1,4);
    g.addEdge(1,2,8);
    g.addEdge(2,3,7);
    g.addEdge(3,4,9);
    g.addEdge(4,5,10);
    g.addEdge(5,6,2);
    g.addEdge(6,7,1);
    g.addEdge(7,8,7);
    g.addEdge(7,0,8);
    g.addEdge(1,7,11);
    g.addEdge(2,5,4);
    g.addEdge(3,5,14);
    g.addEdge(2,8,2);
    g.addEdge(6,8,6);
    g.addEdge(0,7,8);

    Dijkstra(g, 0, dist, parent);
    printShortPath(parent);
}
