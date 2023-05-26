#include "FordBellman.h"
#include "../../graph/list/ListGraph.h"
#include "../../graph/matrix/MatrixGraph.h"

template<class G>
int FordBellman::process(G *graph, int start_vertex, int stop_vertex) {
    for (int i = 0; i < graph->get_vertices(); i++) {
        distances.push_back(INT_MAX);
        predecessors.push_back(-1);
    }
    distances[start_vertex] = 0;
    for (int i = 0; i < graph->get_vertices() - 1; i++) {
        for (int j = 0; j < graph->get_vertices(); j++) {
            if constexpr (std::is_same_v<G, MatrixGraph>) {
                for (int v = 0; v < graph->get_vertices(); v++) {
                    int weight = graph->find_edge(j, v);
                    if (weight != 0) {
                        if (distances[j] + weight < distances[v] &&
                            distances[j] != INT_MAX) {
                            distances[v] = distances[j] + weight;
                            predecessors[v] = j;
                        }
                    }
                }
            } else if constexpr (std::is_same_v<G, ListGraph>) {
                for (auto item: graph->get_adjacent_vertices(j)) {
                    if (distances[j] + item.weight < distances[item.vertex] &&
                        distances[j] != INT_MAX) {
                        distances[item.vertex] = distances[j] + item.weight;
                        predecessors[item.vertex] = j;
                    }
                }
            }
        }
    }
    return distances[stop_vertex];
}

void FordBellman::get_path(int start_vertex, int stop_vertex) {
    if (distances.get_size() == 0) {
        return;
    }
    Array<int> shortest_path;
    int current_vertex = stop_vertex;
    while (current_vertex != start_vertex) {
        if (current_vertex == -1) {
            cout << "Path has not been found!" << endl;
            return;
        }
        shortest_path.push_front(current_vertex);

        current_vertex = predecessors[current_vertex];
    }
    shortest_path.push_front(start_vertex);

    for (const auto vertex: shortest_path) {
        cout << vertex << " ";
    }
    cout << endl;
}

template int FordBellman::process<ListGraph>(ListGraph *graph, int start_vertex, int stop_vertex);

template int FordBellman::process<MatrixGraph>(MatrixGraph *graph, int start_vertex, int stop_vertex);
