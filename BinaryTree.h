#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

struct Node {					// a node of the tree
	int code = 0;					// element value
	int pop = 0;
	int height = 1;
	string countyState;
	Node*   left;					// left child
	Node*   right;					// right child
	Node() : pop(0), code(0), left(NULL), right(NULL) { } // constructor
};

class BinaryTree {
public:

	BinaryTree()
	{
		root = NULL;
	}

	Node* getRoot()
	{
		return root;
	}

	void setRoot(Node *n)
	{
		root = n;
	}
	
	void addRoot()
	{
		root = new Node();
	}

	Node *search(int key, Node *leaf)
	{
		if (leaf != NULL) {
			if (key == leaf->code) {
				
				return leaf;
			}
			if (key < leaf->code) {
				return search(key, leaf->left);
			}
			else {
				return search(key, leaf->right);
			}
		}
		else {
			return NULL;
		}
	}

	Node* search(int key) {
		return search(key, root);
	}

	void inorder_print(Node *leaf) {

		if (leaf == NULL)
		{
			return;
		}
		if (leaf != NULL) {
			//cout << "root: " << root->code << endl;
			inorder_print(leaf->left);
			cout << leaf->code << " " << leaf->pop << " " << leaf->countyState << endl;
			inorder_print(leaf->right);
		}
	}

private:
	Node *root;


};

#endif