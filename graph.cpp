#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <queue>
#include <limits>
#include <algorithm>
#include <set>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        bool operator==(const Edge& other) const {
            return from == other.from && to == other.to && distance == other.distance;
        }
    };

private:
    std::unordered_map<Vertex, std::vector<std::shared_ptr<Edge>>> adjacency_list;

public:
    bool has_vertex(const Vertex& v) const {
        return adjacency_list.find(v) != adjacency_list.end();
    }

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v)) return false;
        adjacency_list[v] = {};
        return true;
    }

    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) return false;

        adjacency_list.erase(v);
        for (auto& pair : adjacency_list) {
            auto& edges = pair.second;
            edges.erase(
                std::remove_if(edges.begin(), edges.end(), [&](const std::shared_ptr<Edge>& e) {
                    return e->to == v;
                    }),
                edges.end()
            );
        }
        return true;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> verts;
        for (const auto& pair : adjacency_list) {
            verts.push_back(pair.first);
        }
        return verts;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        add_vertex(from);
        add_vertex(to);
        adjacency_list[from].push_back(std::make_shared<Edge>(Edge{ from, to, d }));
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_vertex(from)) return false;
        auto& edges = adjacency_list[from];
        auto old_size = edges.size();
        edges.erase(
            std::remove_if(edges.begin(), edges.end(), [&](const std::shared_ptr<Edge>& e) {
                return e->to == to;
                }),
            edges.end()
        );
        return edges.size() != old_size;
    }

    bool remove_edge(const Edge& e) {
        if (!has_vertex(e.from)) return false;
        auto& edges = adjacency_list[e.from];
        auto old_size = edges.size();
        edges.erase(
            std::remove_if(edges.begin(), edges.end(), [&](const std::shared_ptr<Edge>& edge) {
                return *edge == e;
                }),
            edges.end()
        );
        return edges.size() != old_size;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from)) return false;
        const auto& edges = adjacency_list.at(from);
        return std::any_of(edges.begin(), edges.end(), [&](const std::shared_ptr<Edge>& e) {
            return e->to == to;
            });
    }

    bool has_edge(const Edge& e) const {
        if (!has_vertex(e.from)) return false;
        const auto& edges = adjacency_list.at(e.from);
        return std::any_of(edges.begin(), edges.end(), [&](const std::shared_ptr<Edge>& edge) {
            return *edge == e;
            });
    }

    std::vector<Edge> edges(const Vertex& vertex) const {
        std::vector<Edge> result;
        if (!has_vertex(vertex)) return result;
        for (const auto& edge_ptr : adjacency_list.at(vertex)) {
            result.push_back(*edge_ptr);
        }
        return result;
    }

    size_t order() const {
        return adjacency_list.size();
    }

    size_t degree(const Vertex& v) const {
        if (!has_vertex(v)) return 0;
        return adjacency_list.at(v).size();
    }

    bool is_connected() const {
        if (adjacency_list.empty()) return true;

        auto it = adjacency_list.begin();
        Vertex start = it->first;
        std::set<Vertex> visited;

        dfs(start, visited);

        return visited.size() == adjacency_list.size();
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> previous;
        auto comp = [&](const Vertex& a, const Vertex& b) {
            return distances[a] > distances[b];
            };
        std::priority_queue<Vertex, std::vector<Vertex>, decltype(comp)> pq(comp);

        for (const auto& pair : adjacency_list) {
            distances[pair.first] = std::numeric_limits<Distance>::max();
        }

        distances[from] = 0;
        pq.push(from);

        while (!pq.empty()) {
            Vertex current = pq.top();
            pq.pop();

            if (current == to) break;

            for (const auto& edge_ptr : adjacency_list.at(current)) {
                Vertex neighbor = edge_ptr->to;
                Distance weight = edge_ptr->distance;
                if (distances[current] + weight < distances[neighbor]) {
                    distances[neighbor] = distances[current] + weight;
                    previous[neighbor] = current;
                    pq.push(neighbor);
                }
            }
        }

        std::vector<Edge> path;
        if (previous.find(to) == previous.end()) return path;

        for (Vertex at = to; at != from; at = previous[at]) {
            Vertex prev = previous[at];
            auto it = std::find_if(adjacency_list.at(prev).begin(), adjacency_list.at(prev).end(),
                [&](const std::shared_ptr<Edge>& e) {
                    return e->to == at;
                });
            if (it != adjacency_list.at(prev).end()) {
                path.push_back(*(*it));
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        std::vector<Vertex> result;
        std::set<Vertex> visited;
        dfs_walk(start_vertex, visited, result);
        return result;
    }

private:
    void dfs(const Vertex& v, std::set<Vertex>& visited) const {
        visited.insert(v);
        for (const auto& edge_ptr : adjacency_list.at(v)) {
            if (visited.find(edge_ptr->to) == visited.end()) {
                dfs(edge_ptr->to, visited);
            }
        }
    }

    void dfs_walk(const Vertex& v, std::set<Vertex>& visited, std::vector<Vertex>& result) const {
        visited.insert(v);
        result.push_back(v);
        for (const auto& edge_ptr : adjacency_list.at(v)) {
            if (visited.find(edge_ptr->to) == visited.end()) {
                dfs_walk(edge_ptr->to, visited, result);
            }
        }
    }
};

template<typename Vertex, typename Distance = double>
Vertex find_best_warehouse(const Graph<Vertex, Distance>& g) {
    auto verts = g.vertices();
    Distance min_max_distance = std::numeric_limits<Distance>::max();
    Vertex best_vertex = verts.front();

    for (const auto& candidate : verts) {
        Distance current_max = 0;
        for (const auto& other : verts) {
            if (candidate == other) continue;
            auto path = g.shortest_path(candidate, other);
            Distance dist = 0;
            for (const auto& edge : path) {
                dist += edge.distance;
            }
            if (dist > current_max) {
                current_max = dist;
            }
        }
        if (current_max < min_max_distance) {
            min_max_distance = current_max;
            best_vertex = candidate;
        }
    }
    return best_vertex;
}

template<typename Vertex, typename Distance = double>
void print_graph(const Graph<Vertex, Distance>& g) {
    for (const auto& v : g.vertices()) {
        const auto& edges = g.edges(v);
        if (edges.empty()) {
            std::cout << v << " (no outgoing edges)\n";
        }
        else {
            for (const auto& e : edges) {
                std::cout << e.from << " -> " << e.to << " (" << e.distance << ")\n";
            }
        }
    }
}


int main() {
    Graph<std::string> g;

    std::cout << "=== Adding vertices ===\n";
    g.add_vertex("Shop1");
    g.add_vertex("Shop2");
    g.add_vertex("Shop3");
    g.add_vertex("Shop4");
    g.add_vertex("Shop5");

    std::cout << "Does Shop1 exist? " << (g.has_vertex("Shop1") ? "Yes" : "No") << "\n";
    std::cout << "Does Shop6 exist? " << (g.has_vertex("Shop6") ? "Yes" : "No") << "\n";

    std::cout << "\n=== Adding edges ===\n";
    g.add_edge("Shop1", "Shop2", 4.0);
    g.add_edge("Shop2", "Shop3", 3.0);
    g.add_edge("Shop3", "Shop1", 2.0);
    g.add_edge("Shop1", "Shop4", 7.0);
    g.add_edge("Shop4", "Shop2", 1.0);
    g.add_edge("Shop2", "Shop5", 5.0);

    print_graph(g); // выводим структуру после добавления рёбер

    std::cout << "\n=== Checking existence of edges Shop2->Shop3 and Shop4->Shop5 ===\n";
    std::cout << "Shop2->Shop3: " << (g.has_edge("Shop2", "Shop3") ? "Yes" : "No") << "\n";
    std::cout << "Shop4->Shop5: " << (g.has_edge("Shop4", "Shop5") ? "Yes" : "No") << "\n";

    std::cout << "\n=== Graph order ===\n";
    std::cout << "Order (number of vertices): " << g.order() << "\n";

    std::cout << "\n=== Degree of vertex Shop2 ===\n";
    std::cout << "Degree of Shop2: " << g.degree("Shop2") << "\n";

    std::cout << "\n=== Depth-first traversal from Shop1 ===\n";
    for (const auto& v : g.walk("Shop1")) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Checking if the graph is strongly connected ===\n";
    std::cout << (g.is_connected() ? "Graph is strongly connected" : "Graph is not strongly connected") << "\n";

    std::cout << "\n=== Shortest path from Shop1 to Shop5 ===\n";
    auto path = g.shortest_path("Shop1", "Shop5");
    for (const auto& e : path) {
        std::cout << e.from << " -> " << e.to << " (" << e.distance << ")\n";
    }

    std::cout << "\n=== Removing vertex Shop5 and checking ===\n";
    g.remove_vertex("Shop5");
    std::cout << "Does Shop5 exist? " << (g.has_vertex("Shop5") ? "Yes" : "No") << "\n";

    std::cout << "\n=== Removing edge Shop1->Shop4 and checking ===\n";
    g.remove_edge("Shop1", "Shop4");
    std::cout << "Does edge Shop1->Shop4 exist? " << (g.has_edge("Shop1", "Shop4") ? "Yes" : "No") << "\n";

    print_graph(g); // выводим актуальную структуру после удалений

    std::cout << "\n=== Solving the warehouse optimization task ===\n";
    std::string warehouse = find_best_warehouse(g);
    std::cout << "The best location for the warehouse: " << warehouse << "\n";

    return 0;
}

