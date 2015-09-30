#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

using namespace std;

constexpr bool RED=true;
constexpr bool BLACK=false;

template <typename TKey,typename TValue>
struct Node {
	Node(TKey key,TValue value,Node *left,Node *right,bool color):Key(key),Value(value),Left(left),Right(right),Color(color) {}
	Node(const Node &other){
		Key=other.Key;
		Value=other.Value;
		Left=other.Left;
		Right=other.Right;
        Color=other.Color;
	}

	Node &operator=(const Node &other){
        Key=other.Key;
        Value=other.Value;
        Left=other.Left;
        Right=other.Right;
        Color=other.Color;
		
		return *this;
	}

    TKey Key;
    TValue Value;
    shared_ptr<Node> Left;
    shared_ptr<Node> Right;
    bool Color;
};  // struct Node

#endif  // NODE_HPP
