#include "graphUtils.hpp"
#include "weightedGraph.hpp"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

using DataStructure::WeightedGraph;
using DataStructure::IDType;

void DFS(WeightedGraph const& graph, IDType const start, std::function<void(IDType const)> const& callback, std::function<bool(IDType const)> const& should_explore_neighbors) {
    std::set<IDType> visited {};
    std::stack<IDType> to_visit {};
    to_visit.push(start);
    while (!to_visit.empty()) {
        auto const current { to_visit.top() };
        to_visit.pop();

        if (visited.contains(current)) {
            continue;
        }

        visited.insert(current);
        callback(current);

        if (should_explore_neighbors(current)) {
            for (auto const& edge : graph.get_neighbors(current)) {
                to_visit.push(edge.to);
            }
        }
    }
}

void print_DFS(WeightedGraph const& graph, IDType const start) {
    DFS(graph, start, [](IDType const id) {
    }, [](IDType const) { 
        return true; 
    });
}

template<class T>
using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

// map of node id to pair of cost and parent node id (for path reconstruction)
std::unordered_map<IDType, std::pair<float, IDType>> Dijkstra(WeightedGraph const& graph, IDType const start, IDType const end) {
    std::unordered_map<IDType, std::pair<float, IDType>> distances {};
    // priority queue of pair of current cost from starting node and current node id
    // this will sort node base on the cost (as pair are ordered with lexicographical order)
    min_priority_queue<std::pair<float, IDType>> to_visit {};

    distances[start] = {0.0f, start};
    to_visit.push({0.0f, start});

    while (!to_visit.empty()) {
        float current_dist = to_visit.top().first;
        IDType u = to_visit.top().second;
        to_visit.pop();

        if (u == end) break;

        if (distances.contains(u) && current_dist > distances[u].first) {
            continue;
        }

        for (auto const& edge : graph.get_neighbors(u)) {
            IDType v = edge.to;
            float weight = edge.weight;
            float new_dist = current_dist + weight;

            if (distances.find(v) == distances.end() || new_dist < distances[v].first) {
                distances[v] = {new_dist, u};
                to_visit.push({new_dist, v});
            }
        }
    }
    
    return distances;
}

std::vector<IDType> reconstruct_path(std::unordered_map<IDType, std::pair<float, IDType>> const& distances, IDType const start, IDType const end) {
    std::vector<IDType> path { };
    IDType current_node { end };
    while (current_node != start) {
        path.push_back(current_node);

        auto const find_current_node { distances.find(current_node) };
        if(find_current_node == distances.end()) {
            // if we reach a node that is not in the distances map, it means that there is no path from start to end
            return {};
        }
        else {
            // we update the current node to its parent node
            current_node = find_current_node->second.second;
        }
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<IDType> dijkstra_path(WeightedGraph const& graph, IDType const start, IDType const end) {
    return reconstruct_path(Dijkstra(graph, start, end), start, end);
}