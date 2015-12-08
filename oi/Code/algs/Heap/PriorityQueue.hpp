//
// Copyright 2015 riteme
//

#ifndef RITEME_PRIORITY_QUEUE
#define RITEME_PRIORITY_QUEUE

#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

template <typename TValue, typename TCompare = std::less<TValue>,
          typename TContainer = std::vector<TValue>>
class PriorityQueue {
 public:
    typedef std::size_t SizeType;
    typedef TValue ValueType;

    PriorityQueue() : m_array({ 0 }), m_cmp(TCompare()) {}
    ~PriorityQueue() = default;

    void Push(const TValue &v) {
        m_array.push_back(v);
        Swim(Size());
    }

    void Pop() {
        if (Size() == 0)
            throw std::range_error("Nothing in the priority when pop element.");

        m_array[1] = m_array.back();
        m_array.pop_back();
        Sink(1);
    }

    auto Top() const -> TValue {
        if (Size() == 0)
            throw std::range_error(
                "Nothing in the priority queue when get the top element.");

        return m_array[1];
    }

    auto Size() const -> SizeType { return m_array.size() - 1; }

 private:
    void Sink(SizeType x) {
        auto v = m_array[x];

        while (true) {
            auto next = x;

            if (LEFT(x) <= Size() and m_cmp(m_array[LEFT(x)], m_array[next]))
                next = LEFT(x);

            if (RIGHT(x) <= Size() and m_cmp(m_array[RIGHT(x)], m_array[next]))
                next = RIGHT(x);

            if (next == x)
                break;
            else {
                // std::swap(m_array[x], m_array[next]);

                m_array[x] = m_array[next];
                m_array[next] = v;
                x = next;
            }
        }  // while
    }

    void Swim(SizeType x) {
        auto v = m_array[x];

        while (PARENT(x) > 0 and m_cmp(m_array[x], m_array[PARENT(x)])) {
            // std::swap(m_array[x], m_array[PARENT(x)]);

            m_array[x] = m_array[PARENT(x)];
            m_array[PARENT(x)] = v;

            x = PARENT(x);
        }  // while
    }

    TContainer m_array;
    TCompare m_cmp;
};  // class PriorityQueue

#undef PARENT
#undef LEFT
#undef RIGHT

#endif  // RITEME_PRIORITY_QUEUE
