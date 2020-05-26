#pragma once
#include <string>
#include "pch.h"
using namespace std;

const int LH = -1;
const int EH = 0;
const int RH = 1;

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
	bool Search(ItemType key);
	bool FindItem(TreeNode<ItemType>* root, ItemType key);
	void DeleteItem(ItemType item);
	void Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter);
	void DeleteNode(TreeNode <ItemType>*& tree, bool& shorter);
	void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);
	void DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter);
	void DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter);


private:
	TreeNode<ItemType>* root;
};


template<class ItemType>
AVLTree<ItemType>::AVLTree()
{
	root = nullptr;
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
		tree->bf = EH;
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
			case LH:
				LeftBalance(tree, taller);
				break;

			case EH:
				tree->bf = LH;
				break;

			case RH:
				tree->bf = EH;
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
			case RH:
				RightBalance(tree, taller);
				break;

			case EH:
				tree->bf = RH;
				break;

			case LH:
				tree->bf = EH;
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
	case RH:	
		tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH:	
		cerr << "Tree already balanced " << endl;
		break;
	case LH:	
		ls = rs->left;
		switch (ls->bf)
		{
		case RH:	
			tree->bf = LH;
			rs->bf = EH;
			break;
		case EH:	
			tree->bf = rs->bf = EH;
			break;
		case LH:	
			tree->bf = EH;
			rs->bf = RH;
			break;
		}
		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template <class ItemType>
void AVLTree<ItemType> ::LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;

	switch (ls->bf)
	{
	case LH:
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:
		cerr << "Tree already balanced " << endl;
		break;
	case RH:
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:
			tree->bf = RH;
			ls->bf = EH;
			break;
		case EH:
			tree->bf = ls->bf = EH;
			break;
		case RH:
			tree->bf = EH;
			ls->bf = LH;
			break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

template<class ItemType>
void AVLTree<ItemType>::Print()
{
	
	printTree(root, nullptr, false);
	cout << "\n\n\n";
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
		cout << "Right: " << tree->right->info << ": ";
	}
	else {
		cout << "Right: empty: ";
	}
	if (tree->bf == LH) {
		cout << " Balance Factor: Left High" << endl;
	}
	else if (tree->bf == EH) {
		cout << " Balance Factor: Equal Height" << endl;
	}
	else if (tree->bf == RH) {
		cout << " Balance Factor: Right High" << endl;
	}

	/* now recur on right child */
	PrintInorder(tree->right);
}

template<class ItemType>
bool AVLTree<ItemType>::Search(ItemType key)
{
	return FindItem(root, key);
}

template<class ItemType>
bool AVLTree<ItemType>::FindItem(TreeNode<ItemType>* root, ItemType key)
{
	// Traverse untill root reaches to dead end 
	while (root != NULL) {
		// pass right subtree as new tree 
		if (key > root->info)
			root = root->right;

		// pass left subtree as new tree 
		else if (key < root->info)
			root = root->left;
		else
			return true; // if the key is found return 1 
	}
	return false;
}

template <class ItemType>
void AVLTree<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool shorter;
	Delete(root, item, shorter);
}

template <class ItemType>
void AVLTree<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: 
					tree->bf = EH; 
					break;
				case EH: 
					tree->bf = RH; shorter = false;
					break;
				case RH: 
					DelRightBalance(tree, shorter);
					break;
				} // END SWITCH	
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: 
					DelLeftBalance(tree, shorter);
				break;				
				case EH: tree->bf = LH; shorter = false; 							
					break;
				case RH: 
					tree->bf = EH; 
					break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item << " not in the tree so cannot be deleted.";
	}
}

template <class ItemType>
void AVLTree<ItemType>::DeleteNode(TreeNode <ItemType>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node 
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	ItemType data;	TreeNode <ItemType>* tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
			switch (tree->bf)
			{
			case LH: 
				tree->bf = EH; 
				break;
			case EH: 
				tree->bf = RH; shorter = false;
				break;
			case RH: 
				DelRightBalance(tree, shorter);
				break;
			}
	}
}

template <class ItemType>
void AVLTree<ItemType>::GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}

template <class ItemType>
void AVLTree<ItemType>::DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;
	switch (rs->bf)
	{
	case RH:	
		tree->bf = rs->bf = EH;
		RotateLeft(tree);
		shorter = true; 
		break;
	case EH:	
		tree->bf = RH;
		rs->bf = LH;
		RotateLeft(tree);
		shorter = false; 
		break;
	case LH:	
		ls = rs->left;
		switch (ls->bf)
		{
		case RH:	
			tree->bf = LH;
			rs->bf = EH; 
			break;
		case EH:	
			tree->bf = rs->bf = EH;
			break;
		case LH:	
			tree->bf = EH;
			rs->bf = RH; 
			break;
		} // END SWITCH

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class ItemType>
void AVLTree<ItemType>::DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;
	switch (ls->bf)
	{
	case LH:	
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		shorter = true; 
		break;
	case EH:	
		tree->bf = LH;
		ls->bf = RH;
		RotateRight(tree);
		shorter = false; 
		break;
	case RH:	
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:	
			tree->bf = RH;
			ls->bf = EH; 
			break;
		case EH:	
			tree->bf = ls->bf = EH;
			break;
		case RH:	
			tree->bf = EH;
			ls->bf = LH; 
			break;
		} // END SWITCH
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}

 




