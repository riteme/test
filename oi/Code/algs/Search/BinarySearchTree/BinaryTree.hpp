#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <stdexcept>
#include <cassert>

#include "Node.hpp"

#include "../../tool.hpp"

template <typename TKey,typename TValue>
class BinaryTree {
  public:
    BinaryTree()=default;
    ~BinaryTree(){
    	Clear();
    }

    typedef Node<TKey,TValue> NodeType;
    typedef TKey KeyType;
    typedef TValue ValueType;
    typedef unsigned SizeType;
    
    void Clear(){
    	
    	Clear(m_pRoot);
    	m_pRoot=nullptr;

    	assert(m_nSize==0);
    	// m_nSize=0;
    }
    // void Remove(const KeyType &key){
    // 	auto target=Get(m_pRoot,key);

    // 	if (target==nullptr) {
    // 	    throw range_error("Key not found.");
    // 	}else{
    // 		if (target->Left==nullptr&&target->Right==nullptr) {
    // 		    delete target;
    // 		}else if(target->Left==nullptr){
    // 			auto t=target->Right;
    // 			*target=*target->Right;
    // 			delete t;
    // 		}else if(target->Right==nullptr){
    // 			auto t=target->Left;
    // 			*target=*target->Left;
    // 			delete t;
    // 		}else{
    // 			auto min=GetMin(target->Right);
    // 			target->Key=min->Key;
    // 			target->Value=min->Value;
    // 			DeleteMin(target->Right);
    // 		}
    // 		m_nSize--;
    // 	}
    // }
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
    	    m_pRoot=new NodeType(key,value,nullptr,nullptr);
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

  private:
  	NodeType *Get(NodeType *node,const KeyType &key) const{
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

  	void Put(NodeType *node,const KeyType &key,const ValueType &value){
  		if (node->Key<key) {
  		    if (node->Right!=nullptr) {
  		        Put(node->Right,key,value);
  		    }else{
  		    	node->Right=new NodeType(key,value,nullptr,nullptr);
  		    	return;
  		    }
  		}else if(key<node->Key){
  			if (node->Left!=nullptr) {
  			    Put(node->Left,key,value);
  			}else{
  				node->Left=new NodeType(key,value,nullptr,nullptr);
  				return;
  			}
  		}else {
  		    node->Value=value;
  		    return;
  		}
  	}

  	void Clear(NodeType *current){
  		if (current==nullptr) {
  		    return;
  		}

  		Clear(current->Left);
  		Clear(current->Right);

  		delete current;
  		m_nSize--;
  	}

  	NodeType *Remove(NodeType *node,const KeyType &key){
  		if (node==nullptr) {
  		    return nullptr;
  		}

  		if(node->Key<key){
			node->Right=Remove(node->Right,key);
  		}else if(key<node->Key){
  			node->Left=Remove(node->Left,key);
  		}else{
  			if (node->Left==nullptr&&node->Right==nullptr) {
  			    delete node;
  			    m_nSize--;

  			    return nullptr;
  			}else if(node->Left==nullptr){
  				auto t=node->Right;
  				delete node;
  				m_nSize--;

  				return t;
  			}else if(node->Right==nullptr){
  				auto t=node->Left;
  				delete node;
  				m_nSize--;

  				return t;
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

  	NodeType *GetMin(NodeType *node){
  		if (node->Left==nullptr) {
  		    return node;
  		}

  		return GetMin(node->Left);
  	}

  	NodeType *DeleteMin(NodeType *node){
  		if (node->Left==nullptr) {
  			auto right=node->Right;

  			delete node;

  		    return right;
  		}

  		node->Left=DeleteMin(node->Left);
  	}

    NodeType *m_pRoot=nullptr;
    SizeType m_nSize=0;
};  // class BinaryTree
    
#endif  // BINARY_TREE_HPP
