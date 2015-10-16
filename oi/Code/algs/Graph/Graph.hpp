#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>

struct Edge {
    int v;
    int w;
};  // struct Edge

class Graph {
 public:
    Graph() { m_nVertexCount = m_nEdgeCount = 0; }
    Graph(int n) {
        m_data.resize(n);
        m_nVertexCount = n;
        m_nEdgeCount = 0;
    }

    int VertexCount() const { return m_nVertexCount; }
    int EdgeCount() const { return m_nEdgeCount; }

    std::list<int> &GetRelative(int v) { return m_data[v]; }
    std::list<int> GetRelative(int v) const { return m_data[v]; }

    void Connect(int v, int w) {
        if (v == w) { m_data[v].push_back(v); } else {
            m_data[v].push_back(w);
            m_data[w].push_back(v);
        }
        m_nEdgeCount++;
    }

    std::string ToString() const {
        std::ostringstream s;

        s << "====GRAPH REPORT=====" << std::endl;
        s << "Vertex Count: " << VertexCount() << std::endl;
        s << "Edge Count: " << EdgeCount() << std::endl;
        s << "====DATA BEGIN=======" << std::endl;

        for (int v = 0; v < VertexCount(); v++) {
            if (m_data[v].empty()) { continue; }

            s << v << ": ";

            for (auto w : m_data[v]) { s << w << " "; }  // foreach in m_data[v]

            s << std::endl;
        }  // for

        s << "====DATA END=========" << std::endl;

        return s.str();
    }

 private:
    std::vector<std::list<int>> m_data;
    int m_nVertexCount;
    int m_nEdgeCount;
};  // class Graph

template <typename TStream, typename TGraph>
void ReadIntoGraph(TStream &in, TGraph &G) {
    int n;
    in >> n;

    G = TGraph(n);

    int v, w;
    while (in >> v >> w) { G.Connect(v, w); }  // while
}

// int main(/*int argc, char *argv[]*/) {
//     ios::sync_with_stdio(false);

//     int n;
//     std::cin >> n;

//     Graph G(n);

//     int v, w;
//     while (cin >> v >> w) { G.Connect(v, w); }  // while

//     std::cout << G.ToString() << std::endl;

//     return 0;
// }  // function main

#endif  // GRAPH_HPP_
