#include "stdafx.h"
#include "BinaryTree.h"


BinaryTree::BinaryTree()
{

}

BinaryTree::~BinaryTree()
{
}

TreeNode * BinaryTree::GetRoot()
{
	return root;
}

TreeNode* BinaryTree::MakeTree(int *data, int start, int end) {
	TreeNode *Tree;
	int n1, n2;
	// ограничение рекурсии 
	if (end == 0)
		return NULL;
	// выделить память под вершину 
	Tree = new  TreeNode;
	// записать данные (ключ) 
	Tree->key = data[start];
	// размеры поддеревьев 
	n1 = end / 2;
	n2 = end - n1 - 1;
	Tree->left = MakeTree(data, start + 1, n1);
	Tree->right = MakeTree(data, start + 1 + n1, n2);
	return Tree;
}

BinaryTree::BinaryTree(int *data, int start, int end)
{
	root = MakeTree(data, start, end);
}


