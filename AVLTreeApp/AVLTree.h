#pragma once
#include <string>
#include "pch.h"
using namespace std;

template <class ItemType>
struct TreeNode;

template <class ItemType>
struct TreeNode {
	ItemType info;
	TreeNode *left;
	TreeNode *right;
	int bf;
};


template <class ItemType>
class AVLTree
{

public:
	AVLTree();
	~AVLTree();

	
	void RotateLeft(TreeNode<ItemType> * & tree);
	void RotateRight(TreeNode<ItemType> * & tree);
	void InsertItem(ItemType item);
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller);
	void RightBalance(TreeNode<ItemType> *& tree, bool & taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool & taller);
	void Print();
	void PrintInorder(TreeNode<ItemType> *& tree);

private:
	TreeNode<ItemType>* root;
};


template<class ItemType>
AVLTree<ItemType>::AVLTree()
{
}

template<class ItemType>
AVLTree<ItemType>::~AVLTree()
{
}

template<class ItemType>
void AVLTree<ItemType>::RotateLeft(TreeNode<ItemType> * & tree)
{
	TreeNode<ItemType> * rs;
	if (tree == NULL)
		std::cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	else if (tree->right == NULL)
		std::cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

template<class ItemType>
void AVLTree<ItemType>::RotateRight(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType> * ls;
	if (tree == NULL)
		std::cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	else if (tree->left == NULL)
		std::cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}


template <class ItemType>
void AVLTree<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller = false;
	Insert(root, item, taller);
}

template<class ItemType>
void AVLTree<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller)
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = 0;
		taller = true;
	}
	else if (item == tree->info)
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		// Insert into left subtree	
		if (taller)
		{
			switch (tree->bf)
			{
			case -1:
				LeftBalance(tree, taller);
				break;

			case 0:
				tree->bf = -1;
				break;

			case 1:
				tree->bf = -1;
				taller = false;
				break;
			}
		}
	}
	else
	{
		Insert(tree->right, item, taller);
		// Insert into right subtree				
		if (taller)
		{
			switch (tree->bf)
			{
			case 1:
				RightBalance(tree, taller);
				break;

			case 0:
				tree->bf = 1;
				break;

			case -1:
				tree->bf = 0;
				taller = false;
				break;
			}
		}

	}
}


template <class ItemType>
void AVLTree<ItemType>::RightBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;

	switch (rs->bf)
	{
	case 1:	
		tree->bf = rs->bf = 0;
		RotateLeft(tree);
		taller = false;
		break;
	case 0:	
		cerr << "Tree already balanced " << endl;
		break;
	case -1:	
		ls = rs->left;
		switch (ls->bf)
		{
		case 1:	
			tree->bf = -1;
			rs->bf = 0;
			break;
		case 0:	
			tree->bf = rs->bf = 0;
			break;
		case -1:	
			tree->bf = 0;
			rs->bf = 1;
			break;
		}
		ls->bf = 0;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template <class ItemType>
void AVLTree<ItemType>::LeftBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;

	switch (ls->bf)
	{
	case 1:
		tree->bf = ls->bf = 0;
		RotateRight(tree);
		taller = false;
		break;
	case 0:
		cerr << "Tree already balanced " << endl;
		break;
	case -1:
		rs = ls->right;
		switch (rs->bf)
		{
		case 1:
			tree->bf = -1;
			ls->bf = 0;
			break;
		case 0:
			tree->bf = ls->bf = 0;
			break;
		case -1:
			tree->bf = 0;
			ls->bf = 1;
			break;
		}
		rs->bf = 0;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

template<class ItemType>
void AVLTree<ItemType>::Print()
{
	PrintInorder(root);
}

template<class ItemType>
void AVLTree<ItemType>::PrintInorder(TreeNode<ItemType> *& tree)
{
	if (tree == NULL)
		return;

	/* first recur on left child */
	PrintInorder(tree->left);

	/* then print the data of node */
	cout << tree->info << " ";
	if (tree->left != NULL) {
		cout << "Left: " << tree->left->info << " ";
	}
	else {
		cout << "Left: empty" << " ";
	}

	if (tree->right != NULL) {
		cout << "Right: " << tree->right->info << " " << endl;
	}
	else {
		cout << "Right: empty" << endl;
	}

	/* now recur on right child */
	PrintInorder(tree->right);

	
}

 




