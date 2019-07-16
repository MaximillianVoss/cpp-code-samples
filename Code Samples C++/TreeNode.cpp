#include "stdafx.h"
#include "TreeNode.h"


TreeNode::TreeNode()
{
}


TreeNode::TreeNode(int _key, TreeNode * _left, TreeNode * _right)
{
	key = _key;
	left = _left;
	right = _right;
}

TreeNode::~TreeNode()
{
}
