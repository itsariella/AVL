#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class AVLTree : public BinaryTree {

public:
	BinaryTree ST; //Binary Tree with some search tree functions
	int numNodes; //Total number of nodes in tree

public:

	// constructor accepts file name and construct AVL tree
	AVLTree(string filename) : ST()
	{
		ST.addRoot();

		//Declare local variables
		int myCode, myPop = 0;
		string myCounty, myState, myLocation, oneLine;
		string temp;
		ifstream countyFile;

		//open file
		countyFile.open(filename);

		//If file is not found
		if (!countyFile)
		{
			cout << "Error: Unable to open file" << endl;
			exit(EXIT_FAILURE);
		}

		istringstream countyStream;
		getline(countyFile, oneLine);
		countyStream.str(oneLine);

		//Input file data
		while (!countyFile.eof())
		{
			istringstream ss(oneLine);
			ss >> myCode;
			int count = 0;
			while (getline(ss, temp, ',')) {
				
				if (count == 0)
				{
					ss >> myPop;
					count++;
				}
				else if (count == 1)
				{
					getline(ss,myLocation);
					insert(myCode, myPop, myLocation);
					count++;
				}
				else if (count == 2)
				{
					myLocation = "";
					count++;
				}
				else if (count == 3)
				{
					ss >> myCode;
					count = 0;
				}
			}
			countyStream.clear();
			getline(countyFile, oneLine);
			countyStream.str(oneLine);
		}
	}

	//Find record and print if found
	//Return node where record is found
	bool find(int code, int &numNodes)
	{
		//Call binary search for key code
		Node *found = new Node;
		found = ST.search(code);

		//if key is not found, print not found msg
		if (found == NULL)
		{
			cout << endl << "Record not found!" << endl;
			numNodes = ST.getRoot()->height;
			return false; //returns null node;
		}

		// number of nodes examined
		numNodes = ST.getRoot()->height - found->height;

		//print record
		cout << endl << found->code << " " << found->pop << " " << found->countyState << endl;

		//Returns node where record is found
		return true;
	}

	//insert function that takes node data as parameters
	void insert(int code, int pop, string countyState)
	{

		Node *myData = new Node;
		myData->code = code;
		myData->pop = pop;
		myData->countyState = countyState;
		myData->height = 1;

		insert(code, ST.getRoot(), myData,numNodes); 

	}

	//Overloaded function that displays nodes examined
	void insert2(int code, int pop, string countyState)
	{
		int numNodes = 0;
		Node *myData = new Node;
		myData->code = code;
		myData->pop = pop;
		myData->countyState = countyState;
		myData->height = 1;

		insert(code, ST.getRoot(), myData, numNodes);
		numNodes++;

		cout << "Nodes examined: " << numNodes << endl;

	}

	//insert function that takes nodes as paramter
	Node* insert(int key, Node *r, Node *n, int &numNodes)
	{

		//Check if any of the nodes are null
		if (n == NULL || r == NULL) {
			if (n == NULL)
			{
				cout << "n is null!" << endl;
			}
			else
			{
				cout << "r is null!" << endl;
			}
		}

		//Check if the root has no values stored
		else if (r->code == 0 )
		{
			r->code = n->code;
			r->countyState = n->countyState;
			r->height = n->height;
			r->left = NULL;
			r->right = NULL;
			r->pop = n->pop;
		}
		//Perform BST insert
		else {
			//CASE 1
			if (key < r->code) {

				if (r->left != NULL) {
					r->left = insert(key, r->left, n, numNodes);
					r = restructure(r);
				}
				else {
					r->left = new Node(*n);
					r->left->code = key;
					r->left->left = NULL;
					r->left->right = NULL;

					/*////////Code for debugging purposes/////////
					//cout << "insert " << n->code << " external left of " << r->code << endl;
					//print();
					//cout << endl;
					*/
					r = restructure(r);
					
				}
			}
			//CASE 2
			else if (key > r->code) {
				if (r->right != NULL) {
					r->right = insert(key, r->right, n, numNodes);
					r = restructure(r);
				}
				else {
					r->right = new Node(*n);
					r->right->code = key;
					r->right->right = NULL;
					r->right->left = NULL;

					/*////////Code for debugging purposes/////////
					cout << "insert " << n->code << " external right of " << r->code << endl;
					print();
					cout << endl;
					*/

					r = restructure(r);
				}
			}
			//CASE 3
			else {
				r->code = n->code;
				r->pop = n->pop;
				r->countyState = n->countyState;
				r = restructure(r);
			}
		}

		//update height
		r->height = 1 + max(height(r->left), height(r->right));

		//nodes examined = times the function was called
		numNodes++;

		return r;
	}

// print appropriate message and erase node if found
// print number of nodes examined
	void erase(const int& k) {
		int num = 0;
		deleteNode(ST.getRoot(),k, num);
	}

	Node* deleteNode(Node* root, int key, int &numNodes)
	{

		if (root == NULL) {
			return root;
		}
		numNodes++;
		if (key < root->code) //recursively check left subtree
		{
			root->left = deleteNode(root->left, key, numNodes);
		}
		else if (key > root->code) //recursively check right subtree
		{
			root->right = deleteNode(root->right, key, numNodes);
		}
		else if (key == root->code)//if key is found, delete node 
		{
			// node with only one child or no child  
			if ((root->left == NULL) || (root->right == NULL))
			{
				Node *temp = root->left ? root->left : root->right;

				// No child case  
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // one child
				{
					*root = *temp;
				}
				free(temp);
			}
			else
			{
				//Get the in-order successor for a node with two children 
				Node* temp = root->right;

				while (temp->left != NULL)
				{
					temp = temp->left;
				}
				//replace root with successor
				root->code = temp->code;
				// Delete the original inorder successor
				root->right = deleteNode(root->right, temp->code, numNodes);
			}
		}

		if (root == NULL)
		{
			return root;
		}

		//update height
		root->height = 1 + max(height(root->left), height(root->right));

		//Check if the tree needs to be restructured to keep AVL property
		int balance = balanceFactor(root);

		restructure(root);

		return root;
	}


	Node* restructure(Node *temp)
	{
		int bal_factor = balanceFactor(temp);
		if (bal_factor > 1)
		{
			if (balanceFactor(temp->left) > 0) //ll rotate
			{
				temp = rightRotate(temp);
			}
			else
			{
				temp->left = leftRotate(temp->left); //lr rotate
				temp = rightRotate(temp);
			}

		}
		else if (bal_factor < -1)
		{
			if (balanceFactor(temp->right) > 0)
			{
				temp->right = rightRotate(temp->right); //rl rotate
				temp = leftRotate(temp); 
			}
			else
			{
				temp = leftRotate(temp); // right rotate
			}
				
		}
		return temp;
	}

	Node *leftRotate(Node *x)
	{

		/*////////Code for debugging purposes/////////
		cout << "left rotate node " << x->code << endl;
		*/

		//rotate
		Node *y = x->right;
		x->right = y->left;
		y->left = x;

		// Update heights  
		x->height = max(height(x->left),
			height(x->right)) + 1;
		y->height = max(height(y->left),
			height(y->right)) + 1;

		//if the node of rotation is the root, change the root
		if (x == ST.getRoot())
		{
			ST.setRoot(y);
		}

		// Return new root  
		return y;
	}

	Node *rightRotate(Node *y)
	{
		/*/////////Code for debugging purposes/////////
		cout << "right rotate node " << y->code << endl;
		*/

		//Rotate nodes
		Node *x = y->left;
		y->left = x->right;
		x->right = y;

		// Update height
		y->height = max(height(y->left),
			height(y->right)) + 1;
		x->height = max(height(x->left),
			height(x->right)) + 1;

		//If rotating the root node, change the root node
		if (y == ST.getRoot())
		{
			ST.setRoot(x);
		}

		// Return new root  
		return x;
	}

	//For AVL height property
	int balanceFactor(Node *N)
	{
		if (N == NULL)
		{
			return 0;
		}

		return height(N->left) - height(N->right);
	}


	// print one record per line using an in-order traversal
	void print()
	{
		ST.inorder_print(ST.getRoot());
	}

	// draw a reasonable tree with just code
	void draw()
	{
		display(ST.getRoot(),2);
	}

	void display(Node *ptr, int level)
	{
		if (ptr != NULL)
		{
			display(ptr->right, level + 1);
			cout << endl;
			if (ptr == ST.getRoot())
			{
				cout << "Root:  ";
			}
			for (int i = 0; i < level && ptr != ST.getRoot(); i++)
			{
				cout << "	";
			}
			cout << ptr->code;
			display(ptr->left, level + 1);
		}

	}

	int height(Node *n) const
	{
		if (n == NULL)
		{
			return 0;
		}
		return n->height;
	}

};