// AVLTreeApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "AVLTree.h"
#include "Trunk.h"
#include <iostream>

using namespace std;

AVLTree<string> tree;

void displayTree();
void displayMenu();
void search(string item);
void deleteItem(string item);

int main()
{
	int option;
	string item;
	do
	{
		system("cls");
		displayTree();
		displayMenu();
		cin >> option;
		switch (option)
		{
		case 3:
			cout << "\nEnter item: ";
			cin >> item;
			deleteItem(item);
			break;
		case 2:
			cout << "\nEnter item: ";
			cin >> item;
			search(item);
			break;
		case 1: 
			cout << "Enter an item to be inserted: ";
			cin >> item;
			tree.InsertItem(item);
			break;
		case 0:
			exit;
			break;

		default:
			cout << "Inavlid selection\n";
			break;
		}
	} while (option != 0);
	
}

void displayMenu() {
	cout << "\n\n1.Insert an item: ";
	cout << "\n2.Search for an item: ";
	cout << "\n3.Delete an item: ";
	cout << "\n0.Exit: \n";
}

void displayTree() {
	system("cls");
	tree.Print();
}

void search(string item) {
	if (tree.Search(item)) {
		cout << "\nItem Found\n";
		system("pause");
	}
	else {
		cout << "\nItem not found\n";
		system("pause");
	}
}

void deleteItem(string item) {
	if(!tree.Search(item)){
		cout << "\nCannot delete an item that is not in the tree\n";
		system("pause");
	}
	else
		tree.DeleteItem(item);
	
}
