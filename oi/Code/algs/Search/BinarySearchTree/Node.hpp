#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

using namespace std;

template <typename TKey,typename TValue>
struct Node {
	Node(TKey key,TValue value,Node *left,Node *right):Key(key),Value(value),Left(left),Right(right) {}
	Node(const Node &other){
		Key=other.Key;
		Value=other.Value;
		Left=other.Left;
		Right=other.Right;
	}

	Node &operator=(const Node &other){
		Key=other.Key;
		Value=other.Value;
		Left=other.Left;
		Right=other.Right;
		
		return *this;
	}

    TKey Key;
    TValue Value;
    shared_ptr<Node> Left;
    shared_ptr<Node> Right;
};  // struct Node

#endif  // NODE_HPP
