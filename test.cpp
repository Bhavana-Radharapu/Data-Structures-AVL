/*test.cpp*/

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;


TEST_CASE("(1) AVL tree with 4 nodes") 
{
	  avltree<int, int>  avl;

	  //
	  // build a simple BST tree with 4 nodes:
	  //
	  avl.insert(100, -100);
	  avl.insert(50, -50);
	  avl.insert(150, -150);
	  avl.insert(125, -125);

	  // 
	  // Tests:
	  //
	  vector<int>  keys, values, heights;

	  keys = avl.inorder_keys();
	  values = avl.inorder_values();
	  heights = avl.inorder_heights();

	  REQUIRE(avl.size() == 4);
	  REQUIRE(avl.height() == 2);

	  REQUIRE(keys[0] == 50);
	  REQUIRE(values[0] == -50);
	  REQUIRE(heights[0] == 0);

	  REQUIRE(keys[1] == 100);
	  REQUIRE(values[1] == -100);
	  REQUIRE(heights[1] == 2);

	  REQUIRE(keys[2] == 125);
	  REQUIRE(values[2] == -125);
	  REQUIRE(heights[2] == 0);

	  REQUIRE(keys[3] == 150);
	  REQUIRE(values[3] == -150);
	  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) empty tree") 
{
    avltree<int, int>  avl;

    REQUIRE(avl.size() == 0);
    REQUIRE(avl.height() == -1);
}

TEST_CASE("(3) just one node") 
{
    avltree<int, int>  avl;
	
	avl.insert(123, 88);

    REQUIRE(avl.size() == 1);
    REQUIRE(avl.height() == 0);
	
	vector<int>  keys, values, heights;

    keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();

	REQUIRE(keys[0] == 123);
	REQUIRE(values[0] == 88);
    REQUIRE(heights[0] == 0);
}

TEST_CASE("(4) Right Rotation") 
{
	avltree<int, int>  avl;
	
	avl.insert(12,56);
	avl.insert(78,89);
	avl.insert(80,30);
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 1);
	REQUIRE(avl.size() == 3);
	
	REQUIRE(keys[0]==12);
	REQUIRE(keys[1] ==78 );
	REQUIRE(keys[2] == 80);
	
	REQUIRE(values[0]== 56);
	REQUIRE(values[1]==89);
	REQUIRE(values[2]==30);
	
	REQUIRE(heights[0]==0);
	REQUIRE(heights[1]==1);
	REQUIRE(heights[2]==0);
			
}

TEST_CASE("(5) Left Rotation") 
{
	avltree<int, int>  avl;
	
	avl.insert(92,56);
	avl.insert(78,89);
	avl.insert(70,30);
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 1);
	REQUIRE(avl.size()== 3);
	
	REQUIRE(keys[0]== 70);
	REQUIRE(keys[1] == 78 );
	REQUIRE(keys[2] == 92);
	
	REQUIRE(values[0]== 30);
	REQUIRE(values[1]==89);
	REQUIRE(values[2]==56);
	
	REQUIRE(heights[0]==0);
	REQUIRE(heights[1]==1);
	REQUIRE(heights[2]==0);
}

TEST_CASE("(6) Right rotation on subtree") 
{
	avltree<int, int>  avl;
	
	avl.insert(120,56);
	avl.insert(780,89);
	avl.insert(12,34);
	avl.insert(29,30);
	avl.insert(47,98);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()== 5);
	
	REQUIRE(keys[0]== 12);
	REQUIRE(keys[1] == 29 );
	REQUIRE(keys[2] == 47);
	REQUIRE(keys[3] == 120);
	REQUIRE(keys[4] == 780);
	
	
	REQUIRE(values[0]== 34);
	REQUIRE(values[1]== 30);
	REQUIRE(values[2]== 98);
	REQUIRE(values[3] == 56);
	REQUIRE(values[4] == 89);
	
	
	REQUIRE(heights[0]==0);
	REQUIRE(heights[1]==1);
	REQUIRE(heights[2]==0);
	REQUIRE(heights[3] == 2);
	REQUIRE(heights[4] == 0);
	
	
}

TEST_CASE("(7) Left rotation on subtree") 
{
	avltree<int, int>  avl;
	
	avl.insert(56,56);
	avl.insert(35,89);
	avl.insert(62,34);
	avl.insert(74,30);
	avl.insert(87,98);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()==5);
	
	REQUIRE(keys[0]== 35);
	REQUIRE(keys[1] == 56 );
	REQUIRE(keys[2] == 62);
	REQUIRE(keys[3] == 74);
	REQUIRE(keys[4] == 87);
	
	
	REQUIRE(values[0]== 89);
	REQUIRE(values[1]== 56);
	REQUIRE(values[2]== 34);
	REQUIRE(values[3] == 30);
	REQUIRE(values[4] == 98);
	
	
	REQUIRE(heights[0]==0);
	REQUIRE(heights[1]==2);
	REQUIRE(heights[2]==0);
	REQUIRE(heights[3] == 1);
	REQUIRE(heights[4] == 0);
	
	
}

TEST_CASE("(8) Left rotation and then right rotation") 
{
	avltree<int, int>  avl;
	
	avl.insert(56,56);
	avl.insert(35,89);
	avl.insert(62,34);
	avl.insert(74,30);
	avl.insert(87,98);
	avl.insert(58,23);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()== 6);
	
	REQUIRE(keys[0]== 35);
	REQUIRE(keys[1] == 56 );
	REQUIRE(keys[2] == 58 );
	REQUIRE(keys[3] == 62);
	REQUIRE(keys[4] == 74);
	REQUIRE(keys[5] == 87);
	
	
	REQUIRE(values[0]== 89);
	REQUIRE(values[1]== 56);
	REQUIRE(values[2] == 23 );
	REQUIRE(values[3]== 34);
	REQUIRE(values[4] == 30);
	REQUIRE(values[5] == 98);
	
	
	REQUIRE(heights[0] == 0);
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 0);
	REQUIRE(heights[3] == 2);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);
		
}

TEST_CASE("(9) Right rotation and then Left rotation") 
{
	avltree<int, int>  avl;
	
	avl.insert(120,56);
	avl.insert(780,89);
	avl.insert(12,34);
	avl.insert(29,30);
	avl.insert(47,98);
	avl.insert(50,27);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()== 6);
	
	REQUIRE(keys[0] == 12);
	REQUIRE(keys[1] == 29 );
	REQUIRE(keys[2] == 47);
	REQUIRE(keys[3] == 50);
	REQUIRE(keys[4] == 120);
	REQUIRE(keys[5] == 780);
	
	
	REQUIRE(values[0] == 34);
	REQUIRE(values[1] == 30);
	REQUIRE(values[2] == 98);
	REQUIRE(values[3] == 27);
	REQUIRE(values[4] == 56);
	REQUIRE(values[5] == 89);
	
	
	REQUIRE(heights[0] == 0); 
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 2);
	REQUIRE(heights[3] == 0);
	REQUIRE(heights[4] == 1);
	REQUIRE(heights[5] == 0);
		
}

TEST_CASE("(10) tilting tree to right") 
{
	avltree<int, int>  avl;
	
	avl.insert(1,5);
	avl.insert(10,8);
	avl.insert(12,34);
	avl.insert(15,3);
	avl.insert(17,9);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()== 5);
	
	REQUIRE(keys[0] == 1);
	REQUIRE(keys[1] == 10);
	REQUIRE(keys[2] == 12);
	REQUIRE(keys[3] == 15);
	REQUIRE(keys[4] == 17);
	
	REQUIRE(values[0] == 5);
	REQUIRE(values[1] == 8);
	REQUIRE(values[2] == 34);
	REQUIRE(values[3] == 3);
	REQUIRE(values[4] == 9);
	
	REQUIRE(heights[0] == 0); 
	REQUIRE(heights[1] == 2);
	REQUIRE(heights[2] == 0);
	REQUIRE(heights[3] == 1);
	REQUIRE(heights[4] == 0);

}
	TEST_CASE("(11) tilting tree to left") 
{
	avltree<int, int>  avl;
        
		avl.insert(17,9);
		avl.insert(15,3);
		avl.insert(12,34);
		avl.insert(10,8);
		avl.insert(1,5);
	
	vector<int>  keys, values, heights;
	
	keys = avl.inorder_keys();
    values = avl.inorder_values();
    heights = avl.inorder_heights();
	
	REQUIRE(avl.height() == 2);
	REQUIRE(avl.size()== 5);
	
	REQUIRE(keys[0] == 1);
	REQUIRE(keys[1] == 10);
	REQUIRE(keys[2] == 12);
	REQUIRE(keys[3] == 15);
	REQUIRE(keys[4] == 17);
	
	REQUIRE(values[0] == 5);
	REQUIRE(values[1] == 8);
	REQUIRE(values[2] == 34);
	REQUIRE(values[3] == 3);
	REQUIRE(values[4] == 9);
	
	REQUIRE(heights[0] == 0); 
	REQUIRE(heights[1] == 1);
	REQUIRE(heights[2] == 0);
	REQUIRE(heights[3] == 2);
	REQUIRE(heights[4] == 0);

}
	

	
	
	
	
	