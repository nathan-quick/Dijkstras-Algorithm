/**
 * @file main.cpp
 * @brief This is Final Project for CPTR 227.
 * @details This is implementation of Dijkstra's Algorithm to find the shortest path.
 * @author Nathan Quick & Brandon Yi
 * @date 5/5/2021
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/**
 * This class creates an integer matrix graph.
 * 
 */
class Graph{
private:
    int n; // Dimension of graph
    int **matrix;
public:

    /**
     * Graph constructor
     * 
     * @param x The dimensions of the graph
     */
    //http://www.cplusplus.com/forum/articles/7459/ was used to understand how to make a variable matrix
    Graph(int x){
        n = x;
        matrix = new int*[n];
        for (int i=0; i<n; i++)
            matrix[i] = new int[n];

    }

    /**
     * Adds an edge to the graph by setting [i][j] to the distance from the nodes
     * 
     * @param i Initial node
     * @param j Node to connect
     */
    void addEdge(int i, int j, int dist) {
        matrix[i][j] = dist;
        matrix[j][i] = dist;
    }

    /**
     * Removes an edge from the graph by setting [i][j] to 0
     * 
     * @param i Initial node
     * @param j Connected node
     */
    void removeEdge(int i, int j) {
        matrix[i][j] = 0;
        matrix[i][j] = 0;
    }

    /** Finds distance by checking the number stored in [i][j]
     * 
     * @param i Initial node
     * @param j A connected node
     */
    int distance(int i, int j) {
        return matrix[i][j];
    }

    /** Finds all nodes connected to i by checking all of it's rows
     * 
     * @param i Initial node
     * 
     * @return A vector of all connected nodes
     */
    vector<int> outEdges(int i) {
        vector<int> edges;
        for (int j=0; j<n; j++) {
            if (matrix[i][j]) {
                edges.push_back(j);
            }
        }
        return edges;
    }

    /**
     * Returns the length by returning n
     * 
     * @return lenght of graph
     */
    int length(){
        return n;
    }

    /**
     * Retruns the matrix
     * 
     * @return the matrix
     */
    int **matrixOut(){
        return matrix;
    }
};


/**
 * Finds the shortest path in a graph using Dijkstras algorithm
 * 
 * @param g The graph
 * @param source Initial node
 * @param dist An empty array with the same size as g to store distance values
 * @param parent An empty array with the same size as g to store path values
 */
void Dijkstra(Graph g, int source, int* dist, int* parent) {
    int index = 0;
    bool used[g.length()]; // An array that stors if the node's shortest path has already be found

    for (int i=0; i<g.length(); i++){
        dist[i] = -1;
        used[i] = false;
    }

    dist[source] = 0; // The distance from source to source is 0
    used[source] = true; // Mark source as used
    parent[source] = 0; // Source has no path to source

    for (int i=0; i<g.length(); i++){

        vector<int> edge = g.outEdges(index); // Stores all of index's connected nodes

        // Updates the distances from source to the edge
        for (int ii=0; ii<edge.size(); ii++){
            int u = dist[index] + g.distance(index, edge[ii]);
            if (u < dist[edge[ii]] || dist[edge[ii]] == -1){
                parent[edge[ii]] = index;
                dist[edge[ii]] = dist[index] + g.distance(index, edge[ii]);
            }
        }
        // Reset min
        int min = -1; // Stores the smalles distance value

        // Finds the shortest path of the discovered distances
        for (int ii=0; ii<g.length(); ii++){
            if (!used[ii] && dist[ii] != -1){
                if (dist[ii] < min || min == -1){
                    min = dist[ii];
                    index = ii;
                }
            }
        }
        // Marks shortest node path as used
        used[index] = true;
    }
}

/**
 * Prints the distances and shortest path of each node from source
 * 
 * @param g The graph
 * @param dist The list of smallest distances
 * @param parent A list that hold path info
 */
void printShortPath(Graph g, int* dist, int* parent) {
    cout << "Distance  Shortest" << endl;
    cout << " from 0     path" << endl;
    cout << "--------------" << endl;
    int index = 0;
    vector<int> items;
    for (int i=1; i<g.length(); i++){
        cout << i << ": " << dist[i] << string(5, ' ');
        items.clear();
        index = i;
        do
        {       
                items.push_back(parent[index]);
                index = parent[index];
        } while (index > 0);
        reverse(items.begin(),items.end());
        for (int ii=0; ii<=items.size()-1; ii++){
            if (ii==0 && dist[i] < 10){
                cout << ' ';
            }
            cout << items[ii] << "->";
        }
        cout << i <<endl;
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
    printShortPath(g, dist, parent);
}
