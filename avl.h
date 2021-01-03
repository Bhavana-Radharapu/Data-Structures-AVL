/*avl.h*/

//
// AVL tree: this code DOES NOT rebalance.  Right now the heights are updated after
// an insert, but that's it.  Instead, a public "rotate" function is provided that
// lets you call the _RightRotate and _LeftRotate functions in order to test them.
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

NODE* Root;  // pointer to root node of tree (nullptr if empty)
int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  
void deleteTree(NODE* node){  // delete tree function to free the memory

if(node == nullptr)
  return;

deleteTree(node->Left);
deleteTree(node->Right);
delete node;
}

void _inorder(NODE* cur)
{
	if (cur == nullptr)
		return;
	else
	{
		_inorder(cur->Left);
		cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
		_inorder(cur->Right);
    }
}


void _inorder_keys(NODE* cur, std::vector<TKey>& V)
{
	if (cur == nullptr)
		return;
	else
	{
		_inorder_keys(cur->Left, V);
		V.push_back(cur->Key);
		_inorder_keys(cur->Right, V);
    }
}

void _inorder_values(NODE* cur, std::vector<TValue>& V)
{
	if (cur == nullptr)
		return;
    else
    {
		_inorder_values(cur->Left, V);
		V.push_back(cur->Value);
		_inorder_values(cur->Right, V);
    }
}

void _inorder_heights(NODE* cur, std::vector<int>& V)
{
	if (cur == nullptr)
      return;
    else
    {
		_inorder_heights(cur->Left, V);
		V.push_back(cur->Height);
		_inorder_heights(cur->Right, V);
    }
  }

  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //

void _copytree(NODE* cur)
{
	if (cur == nullptr)
      return;
    else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      //
      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
    }
}

  //
  // _RightRotate
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.  You'll need to take all this into account when linking in the
  // new root after the rotation.  Don't forget to update the heights as well.
  //

void _RightRotate(NODE* Parent, NODE* N)
{
	assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    NODE* L = N-> Left;
    NODE* B = L->Right;
    
    
     N->Left = B;
	 L->Right = N;
    
    if (Parent == nullptr){
       Root = L;
    }
    else if(Parent->Key > N->Key){
       Parent->Left = L;
    }
    else {
       Parent->Right = L;
    }
	int lh = (N->Left == nullptr)? -1: N->Left->Height;
	int rh = (N->Right == nullptr)? -1: N->Right->Height;
    N->Height = std::max(lh, rh) + 1;
	int left = (L->Left == nullptr)? -1: L->Left->Height;
    L->Height = std::max(left, L->Right->Height) + 1;
  
}

void _LeftRotate(NODE* Parent, NODE* N)
{
  
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);

    NODE* R = N->Right;
    NODE* B = R->Left;
    	
    
    N->Right = B;
	R->Left = N;
    
	
		
    if (Parent == nullptr){
       Root = R;
    }

    else if( N->Key < Parent->Key ){
       Parent->Left = R;
	   
    }
    else{
	
       Parent->Right = R;
    }
	
    
    int lh = (N->Left == nullptr)? -1: N->Left->Height;
	int rh = (N->Right == nullptr)? -1: N->Right->Height;
    N->Height = std::max(rh, lh) + 1;
	int right = (R->Right == nullptr)? -1: R->Right->Height;
    R->Height = std::max(R->Left->Height, right) + 1;
	
}


public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
avltree()
{
	Root = nullptr;
    Size = 0;
}

  //
  // copy constructor:
  //

avltree(avltree& other)
{
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
}

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  
  //destructor

virtual ~avltree()
{
	deleteTree(Root);
}
  
  
int size()
{
    return Size;
}

  //
  // height
  //
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
int height()
{
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
}

  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //

TValue* search(TKey key)
{
	NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
      }

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  

    // if get here, not found
    return nullptr;
}

  //
  // insert
  //
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //

void insert(TKey key, TValue value)
{
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      nodes.push(cur);  // stack so we can return later:

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    // 
    // 4. update size:
    //
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    //

	while (!nodes.empty())
	{
		cur = nodes.top();
		nodes.pop();

		int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
		int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
		int hCur = 1 + std::max(hL, hR);

		if (cur->Height == hCur)
			break;
		else  // height changed, update and keep going:
			cur->Height = hCur;

		if(abs(hL - hR) > 1){
			if(nodes.empty())
				prev = nullptr;
			else
				prev = nodes.top();
		
			if(hL > hR)
			{
				if(newNode->Key < cur->Key && newNode->Key > cur->Left->Key){
					_LeftRotate(cur,cur->Left);
					_RightRotate(prev,cur);
				}
				else if(newNode->Key < cur->Key && newNode->Key < cur->Left->Key){
					_RightRotate(prev, cur);
				}
			}
		
			else
			{
				if(newNode->Key > cur->Key && newNode->Key < cur->Right->Key){
					_RightRotate(cur,cur->Right);
					_LeftRotate(prev,cur);
				}
				else if(newNode->Key > cur->Key && newNode->Key > cur->Right->Key){
				_LeftRotate(prev,cur);
				}
			}
		}
	  
	}//while

	return;
}

NODE* keyNode(TKey key)
{
	NODE* temp = Root;
	while(temp!=nullptr)
	{
		if(temp->Key == key)
			return temp;
		if( key < temp->Key)
			 temp = temp->Left;
		else
			temp = temp->Right;
	}
	return nullptr; // not found
}

void keySearch(TKey key,vector<TKey>& Key){  
    
	NODE* cur = Root;
	
	while (cur != nullptr)
	{
		if (key == cur->Key)  // already in tree
		{
			Key.push_back(cur->Key); 
			break;
		}
	
		Key.push_back(cur->Key);

		if (key < cur->Key)  // search left:
		{
			cur = cur->Left;
		}
	
		else
		{
			cur = cur->Right;
		}
	}//while  
}
	

int distance(TKey k1, TKey k2){ // distance function
	vector<TKey> Key1; //vector to store path to key 1
	vector<TKey> Key2; //vector to store path to key 1
	NODE* root;
	TKey K;
	int keyDistance = -1;
	
	if(keyNode(k1) == nullptr || keyNode(k2) == nullptr )
		  return -1;
		if(k1 == k2){
			  keyDistance = 0;
		}
		else{
			keySearch(k1, Key1);
			keySearch(k2, Key2);
			
		for(int i = 0; i<Key1.size();i++){
			for(int j = 0; j <Key2.size();j++){
				if(Key1[i]==Key2[j]){
				 K = Key1[i]; 
				 break;
				}
			}
			break;
		}
		cout << " K " << K << endl;

	int keyDistLeft = 0;
	int keyDistRight = 0;
		
	root = keyNode(K);
	
	while(root != nullptr){ 		
		if(root->Key == k1)
		  break;
		if(k1 < root->Key){
			root = root->Left;
		}
		else {
			root = root->Right;
		}
		
		keyDistLeft++;
	}
	
	root = keyNode(K);
	cout << "root: " << root->Key << endl;

	while(root != nullptr)
	{
		if(root->Key == k2)
		  break;
		  
		if(k2 < root->Key){
			root = root->Left;
		}
		else{
			root = root->Right;
		}
			keyDistRight++;
	}
		
			keyDistance = keyDistRight + keyDistLeft; 
	}
			return keyDistance;
}
		
		
  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }

  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }

  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }
  
  void clear()
  {
    //
    // Re-initialize root pointer and size to "empty":
    //
    deleteTree(Root);
	Root = nullptr;
    Size = 0;
	
  }

};
