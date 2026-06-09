#pragma once
#include "pch.h"
#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)
/// <summary>
/// Цвета дерева
/// </summary>
enum TreeNodeColor {
	BLACK,
	RED
};

template<typename T>
class TreeNode {
public:
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNodeColor color;
	T data;
	TreeNode(TreeNode* parent, TreeNode* right, TreeNode* left, T data, TreeNodeColor color = TreeNodeColor::BLACK) {
		this->parent = parent;
		this->left = left;
		this->right = right;
		this->data = data;
		this->color = color;
	}
	TreeNode() :TreeNode(NULL, NULL, NULL, 0) {

	}
};