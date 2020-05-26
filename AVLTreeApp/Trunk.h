#pragma once
#include "pch.h"
#include "AVLTree.h"
#include <string>
using namespace std;

struct Trunk
{
	Trunk *prev;
	string str;

	Trunk(Trunk *prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};


// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
	if (p == nullptr)
		return;

	showTrunks(p->prev);

	std::cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
template <class ItemType>
void printTree(TreeNode<ItemType> *root, Trunk *prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk *trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << root->info << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}
