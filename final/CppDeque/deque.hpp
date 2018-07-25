//
// Copyright 2015 riteme
//

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::runtime_error;
using std::stringstream;

template <typename T>
class Deque {
 public:
    typedef unsigned long SizeType;

    Deque() = default;
    ~Deque() {
        auto iter = m_pFirst;
        while (iter != nullptr) {
            auto oldIter = iter;
            iter = iter->Next;
            delete oldIter;
        }  // while

        // Reset them to nullptr.
        m_pFirst = m_pLast = nullptr;
        m_size = 0;
    }

    SizeType Size() { return m_size; }
    bool IsEmpty() { return m_size == 0; }

    void PushBack(const T &value) {
        Node *newNode = new Node();
        newNode->Item = value;

        if (m_pLast == nullptr) { m_pLast = m_pFirst = newNode; } else {
            m_pLast->Next = newNode;
            newNode->Prev = m_pLast;
            m_pLast = newNode;
        }

        m_size++;
    }
    T PopBack() {
        if (m_size == 0) { throw runtime_error("PopBack failed! Nothing in the list."); }

        auto oldValue = m_pLast->Item;
        m_pLast = m_pLast->Prev;

        if (m_pLast == nullptr) {
            delete m_pFirst;  // If m_pLast is nullptr, m_pFirst is m_pLast->Next.
            m_pFirst = nullptr;
        } else {
            delete m_pLast->Next;
            m_pLast->Next = nullptr;
        }

        m_size--;

        return oldValue;
    }

    void PushFront(const T &value) {
        Node *newNode = new Node();
        newNode->Item = value;
        newNode->Next = m_pFirst;

        if (m_pFirst == nullptr) { m_pFirst = m_pLast = newNode; } else {
            m_pFirst = newNode;
            m_pFirst->Next->Prev = m_pFirst;
        }

        m_size++;
    }
    T PopFront() {
        if (m_size == 0) { throw runtime_error("PopFront failed! Nothing in the list."); }

        auto oldValue = m_pFirst->Item;
        m_pFirst = m_pFirst->Next;

        if (m_pFirst == nullptr) {
            delete m_pLast;  // The same as PopBack().
            m_pLast = nullptr;
        } else {
            delete m_pFirst->Prev;
            m_pFirst->Prev = nullptr;
        }

        m_size--;

        return oldValue;
    }

    string ToString() {
        stringstream ss;
        ss << '{';
        for (auto iter = m_pFirst; iter != nullptr; iter = iter->Next) { ss << iter->Item << (iter->Next == nullptr ? "" : ", "); }  // for
        ss << '}';

        return ss.str();
    }

 private:
    struct Node {
        T Item = T();
        Node *Prev = nullptr;
        Node *Next = nullptr;
    };  // struct Node

    Node *m_pFirst = nullptr;
    Node *m_pLast = nullptr;
    unsigned long m_size = 0;
};  // class Deque

#endif
