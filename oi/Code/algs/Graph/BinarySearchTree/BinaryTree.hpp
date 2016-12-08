#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <stdexcept>
#include <memory>

#include "Node.hpp"

#include "../../tool.hpp"

using namespace std;

template <typename TKey,typename TValue>
class BinaryTree {
  public:
    BinaryTree()=default;
    ~BinaryTree(){
    	Clear();
    }

    typedef Node<TKey,TValue> NodeType;
    typedef shared_ptr<NodeType> NodePtr;
    typedef TKey KeyType;
    typedef TValue ValueType;
    typedef unsigned SizeType;
    
    void Clear(){
    	
    	Clear(m_pRoot);
    	m_pRoot=nullptr;

    	m_nSize=0;
    }

    void Remove(const KeyType &key){
    	Remove(m_pRoot,key);
    }

    ValueType Get(const KeyType &key) const{
    	auto result=Get(m_pRoot,key);

    	if (result==nullptr) {
    	    throw range_error("Key not found.");
    	}else{
    		return result->Value;
    	}
    }

    void Put(const KeyType &key,const ValueType &value){
    	if (m_pRoot==nullptr) {
    	    m_pRoot.reset(new NodeType(key,value,nullptr,nullptr));
    	}else{
	    	Put(m_pRoot,key,value);
	    }

	    m_nSize++;
    }

    SizeType Size() const{
    	return m_nSize;
    }
    
    bool Contain(const KeyType &key){
    	return Get(m_pRoot,key)!=nullptr;
    }

    SizeType RealSize(){
        return RealSize(m_pRoot);
    }

  private:
    SizeType RealSize(NodePtr node){
        if (node==nullptr) {
            return 0;
        }

        return 1+RealSize(node->Left)+RealSize(node->Right);
    }

  	NodePtr Get(NodePtr node,const KeyType &key) const{
  		if (node==nullptr) {
  		    return nullptr;
  		}

  		if (node->Key<key) {
  		    return Get(node->Right,key);
  		}else if(key<node->Key){
  			return Get(node->Left,key);
  		}else{
  			return node;
  		}
  	}

  	void Put(NodePtr node,const KeyType &key,const ValueType &value){
  		if (node->Key<key) {
  		    if (node->Right!=nullptr) {
  		        Put(node->Right,key,value);
  		    }else{
  		    	node->Right.reset(new NodeType(key,value,nullptr,nullptr));
  		    	return;
  		    }
  		}else if(key<node->Key){
  			if (node->Left!=nullptr) {
  			    Put(node->Left,key,value);
  			}else{
  				node->Left.reset(new NodeType(key,value,nullptr,nullptr));
  				return;
  			}
  		}else {
  		    node->Value=value;
  		    return;
  		}
  	}

  	void Clear(NodePtr current){
  		if (current==nullptr) {
  		    return;
  		}

  		Clear(current->Left);
  		Clear(current->Right);

  		current.reset();
  		m_nSize--;
  	}

  	NodePtr Remove(NodePtr node,const KeyType &key){
  		if (node==nullptr) {
  		    return nullptr;
  		}

  		if(node->Key<key){
			node->Right=Remove(node->Right,key);
  		}else if(key<node->Key){
  			node->Left=Remove(node->Left,key);
  		}else{
  			if (node->Left==nullptr&&node->Right==nullptr) {
  			    node.reset();
  			    m_nSize--;

  			    return nullptr;
  			}else if(node->Left==nullptr){
                node=node->Right;
  				m_nSize--;

  				return node;
  			}else if(node->Right==nullptr){
                node=node->Left;
                m_nSize--;

                return node;
  			}else{
  				auto min=GetMin(node->Right);
  				node->Key=min->Key;
  				node->Value=min->Value;
  				DeleteMin(node->Right);

  				m_nSize--;

  				return node;
  			}
  		}

  		return node;
  	}

  	NodePtr GetMin(NodePtr node){
  		if (node->Left==nullptr) {
  		    return node;
  		}

  		return GetMin(node->Left);
  	}

  	NodePtr DeleteMin(NodePtr node){
  		if (node->Left==nullptr) {
            node=node->Right;

  		    return node;
  		}

  		node->Left=DeleteMin(node->Left);
  	}

    NodePtr m_pRoot=nullptr;
    SizeType m_nSize=0;
};  // class BinaryTree
    
#endif  // BINARY_TREE_HPP
