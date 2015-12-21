//
// Copyright 2015 riteme
//

#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <vector>
#include <algorithm>

typedef int IdType;
typedef unsigned SizeType;

class UnionFind {
 public:
    UnionFind(SizeType n) {
        m_data.resize(n);
        m_rank.resize(n);

        IdType cnt = 0;
        generate_n(m_data.begin(), n, [&cnt]() { return cnt++; });
        fill_n(m_rank.begin(), n, 0);
    }
    ~UnionFind() = default;

    IdType Find(IdType x) {
        if (x != m_data[x]) m_data[x] = Find(m_data[x]);

        return m_data[x];
    }

    void Union(IdType a, IdType b) {
        a = Find(a);
        b = Find(b);

        if (m_rank[a] == m_rank[b]) {
            m_data[a] = b;
            m_rank[b]++;
        } else if (m_rank[a] < m_rank[b])
            m_data[a] = b;
        else
            m_data[b] = a;
    }

 private:
    std::vector<IdType> m_data;
    std::vector<SizeType> m_rank;
};  // class UnionFind

#endif  // UNION_FIND_HPP_
