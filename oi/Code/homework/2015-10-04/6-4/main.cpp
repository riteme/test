#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
class List {
 public:
    typedef unsigned long SizeType;

    List() = default;
    ~List() {
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

    void Delete(unsigned index) {
        auto ptr = m_pFirst;

        for (SizeType i = 0;
             i<index && ptr != nullptr;
             i++) {
            ptr = ptr->Next;
        }  // for

        DeleteNode(ptr);
        m_size--;
    }

    void Insert(unsigned index, const T &value) {
        auto ptr = m_pFirst;

        for (SizeType i = 0;
             i<index && ptr != nullptr;
             i++) {
            ptr = ptr->Next;
        }  // for

        InsertNode(ptr, value);
        m_size++;
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

    void DeleteNode(Node *node) {
        auto x = node;

        if (x == m_pFirst) {
            PopFront();
        } else if (x == m_pLast) {
            PopBack();
        } else {
            if (x->Prev != nullptr) {            
                x->Prev->Next = x->Next;
            }

            if (x->Next != nullptr) {
                x->Next->Prev = x->Prev;
            }

            delete node;
        }
    }

    void InsertNode(Node *node, const T &value) {
        if (node == nullptr) {
            throw range_error("Insert error!");
        }

        auto x = node;

        if (x == m_pLast) {
            PushBack(value);
        } else {
            Node *newNode = new Node();
            newNode->Item = value;
            newNode->Prev = x;
            newNode->Next = x->Next;

            if (x->Next != nullptr) {
                x->Next = newNode;
                x->Next->Prev = newNode;
            }
        }
    }
};  // class List

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);

    List<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    l.PushBack(5);

    cout<<l.ToString()<<endl;

    l.Delete(0);
    l.Delete(3);

    cout<<l.ToString()<<endl;

    l.Insert(0,999);
    l.Insert(3,233);
    cout<<l.ToString()<<endl;

    return 0;
}