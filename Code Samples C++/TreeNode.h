#pragma once
/// <summary>
/// ќписание вершины дерева
/// </summary>
class TreeNode
{
public:
	/// <summary>
	/// полезные данные (ключ) 
	/// </summary>
	int  key;
	/// <summary>
	/// указатели на сыновей   
	/// </summary>
	struct TreeNode *left, *right;
	TreeNode();
	/// <summary>
	/// конструктор с параметрами
	/// </summary>
	/// <param name="_key">ключ вершины</param>
	/// <param name="left">левый потомок</param>
	/// <param name="right">правый потомок</param>
	TreeNode(int _key, TreeNode *_left, TreeNode *_right);
	~TreeNode();
};

