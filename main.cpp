
// 
// Interactive program for calling AVL insert.  Let's you insert nodes and 
// watch tree rotate...
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "avl.h"

using namespace std;

int main()
{
  avltree<int, int>  avl;
  int  x;

  cout << "Enter a key to insert into tree (0 to stop)> ";
  cin >> x;

  while (x > 0)
  {
    avl.insert(x, x);
    cout << "Size: " << avl.size() << endl;
    cout << "Height: " << avl.height() << endl;
    avl.inorder();

    cout << endl;
    cout << "Enter a key to insert into tree (0 to stop)> ";
    cin >> x;
  }
	
	cout<<"Enter two keys to check the distance: ";
	int key1,key2;
	cin>>key1>>key2;
	
	cout << "Distance : " << avl.distance(key1,key2) <<endl;
	
	avl.clear();

  //
  // done:
  //
  return 0;
}


