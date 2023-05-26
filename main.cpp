#include <iostream>
#include <list>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "graph/list/node/Node.h"
#include "collections/Array.h"
#include "collections//DoubleList.h"
#include "graph/list/ListGraph.h"
#include "graph/matrix/MatrixGraph.h"
#include "algorithms/dijkstra/Dijkstra.h"
#include "algorithms/fordBellman/FordBellman.h"
#include "algorithms/prim/Prim.h"
#include "algorithms/kruskal/Kruskal.h"
#include "collections/BinaryHeap/MinBinaryHeap.h"
#include "sorter/Sorter.h"
#include "graph/RandomDataGenerator.h"
#include "timer/Timer.h"

using namespace std;


int main(int argc, char *argv[]) {

    int number_vertices = std::stoi(argv[1]);
    float density = std::stof(argv[2]);

    RandomDataGenerator<MatrixGraph> randomDataGenerator;


//    auto *graph = new ListGraph(5);
//    graph->add_directed_edge(0, 1, 2);
//    graph->add_directed_edge(0, 3, 6);
//    graph->add_directed_edge(1, 2, 3);
//    graph->add_directed_edge(1, 3, 8);
//    graph->add_directed_edge(1, 4, 5);
//    graph->add_directed_edge(2, 4, 7);
//    graph->add_directed_edge(3, 4, 9);

    Timer timer;
    Dijkstra algorithm;
    auto whole_time = 0;

    for(int i = 0; i < 50; i++) {
        auto *graph = randomDataGenerator.create_random_directed(number_vertices, density);

        timer.timeStart();
        auto path = algorithm.process(graph, 0, 4);
        timer.timeStop();
        whole_time += timer.elapsedTime();
    }

    cout << whole_time / 50 << endl;

}
