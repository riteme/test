//
// Copyright 2015 riteme
//

#include <cassert>
#include <sstream>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;
using std::stringstream;

static unsigned AllocateCount = 0;

void *operator new(std::size_t size) {
    AllocateCount++;
    return malloc(size);
}
void operator delete(void *ptr) noexcept {
    AllocateCount--;
    free(ptr);
}

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

int main(/*int argc, char *argv[]*/) {
    Deque<int> d;

    d.PushBack(1);
    cout << d.ToString() << endl;
    assert(d.PopBack() == 1);

    d.PushBack(1);
    d.PushBack(2);
    d.PushBack(3);
    cout << d.ToString() << endl;
    assert(d.PopFront() == 1);
    assert(d.PopBack() == 3);
    assert(d.Size() == 1);
    assert(d.IsEmpty() == false);
    assert(d.PopBack() == 2);

    d.PushFront(1);
    cout << d.ToString() << endl;
    assert(d.PopFront() == 1);

    d.PushFront(1);
    d.PushFront(2);
    d.PushFront(3);
    d.PushFront(4);
    cout << d.ToString() << endl;
    assert(d.Size() == 4);
    assert(d.PopFront() == 4);
    assert(d.PopBack() == 1);
    assert(d.PopBack() == 2);
    assert(d.PopFront() == 3);
    assert(d.Size() == 0);
    try {
        d.PopBack();
    } catch (const runtime_error &) { assert(true); } catch (...) {
        assert(false);
    }

    d.PushBack(1);
    d.PushFront(2);
    d.PushBack(3);
    d.PushBack(4);
    d.PushFront(5);
    d.PushFront(6);
    d.PopBack();
    cout << d.ToString() << endl;
    assert(d.PopFront() == 6);
    assert(d.PopFront() == 5);
    assert(d.PopFront() == 2);
    assert(d.PopFront() == 1);
    assert(AllocateCount != 0);

    d.~Deque();
    assert(AllocateCount == 0);

    return 0;
}  // function main
