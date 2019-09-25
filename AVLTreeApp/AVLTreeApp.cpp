// AVLTreeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "AVLTree.h"
#include <iostream>

using namespace std;

AVLTree<int> tree;

void insertItem();
void displayTree();

int main()
{
	int option;

	do{
		displayTree();
		cout << "\n\n1.Insert an item: ";
		cin >> option;
		switch (option)
		{
		case 1: insertItem();
			break;

		}

	} while (option != 0);
	
}

void insertItem() {
	int item;
	system("cls");
	cout << "Enter an item to be inserted: ";
	cin >> item;
	tree.InsertItem(item);
}

void displayTree() {
	system("cls");
	tree.Print();
}
