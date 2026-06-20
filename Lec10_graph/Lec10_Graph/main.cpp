#include <iostream>
#include "WGraphMST.h"

using namespace std;

int main() {
    WGraphMST g;

    g.load("graph.txt");

    cout << "입력 그래프: graph.txt" << endl;
    g.display();

    cout << "MST By Kruskal's Algorithm" << endl;
    g.Kruskal();

    WGraphDijkstra d;
    d.load("graph_sp.txt");
        // printf("Dijkstra의 최단경로 탐색을 위한 그래프: graph_sp.txt\n");
        // g.display();
        printf("Shortest Path By Dijkstra Algorithm\n");
    d.ShortestPath(0);
    
}