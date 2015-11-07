#ifndef WEIGHTED_GRAPH_HPP_
#define WEIGHTED_GRAPH_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>

struct WeightedEdge {
    // WeightedEdge(int _v, int _w, double _dist) : v(_v), w(_w), dist(_dist) {}

    int v;
    int w;
    double dist;

    int &from() { return v; }
    int from() const { return v; }
    int &to() { return w; }
    int to() const { return w; }
};  // struct Edge

class WeightedGraph {
 public:
    WeightedGraph() { m_nVertexCount = m_nEdgeCount = 0; }
    WeightedGraph(int n) {
        m_data.resize(n);
        m_nVertexCount = n;
        m_nEdgeCount = 0;
    }

    int VertexCount() const { return m_nVertexCount; }
    int EdgeCount() const { return m_nEdgeCount; }

    std::list<WeightedEdge> &GetRelative(int v) { return m_data[v]; }
    std::list<WeightedEdge> GetRelative(int v) const { return m_data[v]; }

    void Connect(int v, int w, double dist) {
        if (v == w) { m_data[v].push_back({ v, v, dist }); } else {
            m_data[v].push_back({ v, w, dist });
            m_data[w].push_back({ w, v, dist });
        }
        m_nEdgeCount++;
    }
    void DirectedConnect(int v, int w, double dist) {
        m_data[v].push_back({ v, w, dist });
        m_nEdgeCount++;
    }

    std::string ToString() const {
        std::ostringstream s;

        s << "====Graph REPORT=====" << std::endl;
        s << "Vertex Count: " << VertexCount() << std::endl;
        s << "Edge Count: " << EdgeCount() << std::endl;
        s << "====DATA BEGIN=======" << std::endl;

        for (int v = 0; v < VertexCount(); v++) {
            if (m_data[v].empty()) { continue; }

            s << v << ": ";

            for (auto &w : m_data[v]) {
                s << "(" << w.from() << " -> " << w.to() << ", " << w.dist
                  << ")"
                  << " ";
            }  // foreach in m_data[v]

            s << std::endl;
        }  // for

        s << "====DATA END=========" << std::endl;

        return s.str();
    }

 private:
    std::vector<std::list<WeightedEdge>> m_data;
    int m_nVertexCount;
    int m_nEdgeCount;
};  // class WeightedGraph

template <typename TStream, typename TGraph>
void ReadIntoWeightedGraph(TStream &in, TGraph &G) {
    int n;
    in >> n;

    G = TGraph(n);

    int v, w;
    double d;
    while (in >> v >> w >> d) { G.DirectedConnect(v, w, d); }  // while

    std::cout << "Data read." << std::endl;
}

// int main(/*int argc, char *argv[]*/) {
//     std::ios::sync_with_stdio(false);

//     WeightedGraph G;
//     ReadIntoWeightedGraph(std::cin, G);

//     std::cout << G.ToString() << std::endl;

//     return 0;
// }  // function main

#endif  // WEIGHTED_GRAPH_HPP_
