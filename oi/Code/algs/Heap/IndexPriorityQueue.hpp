//
// Copyright 2015 riteme
//

#ifndef RITEME_INEDX_PRIORITY_QUEUE_HPP_
#define RITEME_INEDX_PRIORITY_QUEUE_HPP_

#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)

template <typename TValue>
struct Node {
    Node() : Value(), Index(0), IsExist(false) {}
    Node(const TValue &value) : Value(value), Index(0), IsExist(false) {}

    TValue Value;
    std::size_t Index;
    bool IsExist;
};  // struct Node

template <typename TValue, typename TCompare = std::less<TValue>>
class IndexPriorityQueue {
 public:
    typedef std::size_t SizeType;
    typedef TValue ValueType;
    typedef Node<ValueType> NodeType;
    typedef std::vector<NodeType> NodeContainerType;
    typedef std::vector<NodeType *> ContainerType;

    IndexPriorityQueue(const size_t size)
            : m_array({ 0 }), m_node(size), m_cmp(TCompare()) {}
    ~IndexPriorityQueue() = default;

    void Push(const size_t index, const TValue &v) {
        m_node[index].Value = v;
        m_array.push_back(&m_node[index]);
        m_array.back()->Index = Size();
        m_array.back()->IsExist = true;

        Swim(Size());
    }

    void Pop() {
        if (Size() == 0)
            throw std::range_error("Nothing in the priority when pop element.");

        m_array[1]->IsExist = false;
        m_array[1] = m_array.back();
        m_array[1]->Index = 1;
        m_array.pop_back();
        Sink(1);
    }

    auto Top() const -> TValue {
        if (Size() == 0)
            throw std::range_error(
                "Nothing in the priority queue when get the top element.");

        return m_array[1]->Value;
    }

    void Decrease(const size_t index, const ValueType &value) {
        m_node[index].Value = value;

        Swim(m_node[index].Index);
    }

    void Increase(const size_t index, const ValueType &value) {
        m_node[index].Value = value;

        Sink(m_node[index].Index);
    }

    auto IsExist(const size_t index) const -> bool {
        return m_node[index].IsExist;
    }

    auto Size() const -> SizeType { return m_array.size() - 1; }

 private:
    void Sink(SizeType x) {
        while (true) {
            auto next = x;

            if (LEFT(x) <= Size() and
                m_cmp(m_array[LEFT(x)]->Value, m_array[next]->Value))
                next = LEFT(x);

            if (RIGHT(x) <= Size() and
                m_cmp(m_array[RIGHT(x)]->Value, m_array[next]->Value))
                next = RIGHT(x);

            if (next == x)
                break;
            else {
                std::swap(m_array[x]->Index, m_array[next]->Index);
                std::swap(m_array[x], m_array[next]);
            }
        }  // while
    }

    void Swim(SizeType x) {
        while (PARENT(x) > 0 and
               m_cmp(m_array[x]->Value, m_array[PARENT(x)]->Value)) {
            std::swap(m_array[x]->Index, m_array[PARENT(x)]->Index);
            std::swap(m_array[x], m_array[PARENT(x)]);

            x = PARENT(x);
        }  // while
    }

    ContainerType m_array;
    NodeContainerType m_node;
    TCompare m_cmp;
};  // class IndexPriorityQueue

#undef PARENT
#undef LEFT
#undef RIGHT

#endif  // RITEME_INEDX_PRIORITY_QUEUE_HPP_
