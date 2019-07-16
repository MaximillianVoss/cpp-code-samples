#include "TreeNode.h"
#pragma once
/// <summary>
/// описывает бинарное дерево
/// </summary>
class BinaryTree
{
public:
	/// <summary>
	/// Создает дерево 
	/// по указанному массиву
	/// массив следует отсартировать по возрастанию
	/// </summary>
	/// <param name="data">массив</param>
	/// <param name="start">начальный индекс</param>
	/// <param name="end">конечный индекс</param>
	BinaryTree(int *data, int from, int n);
	BinaryTree();
	~BinaryTree();
	/// <summary>
	/// Получает корень дерева
	/// </summary>
	/// <returns>указатель на корень дерева</returns>
	TreeNode* GetRoot();
private:
	TreeNode *root;
	/// <summary>
	/// Создает дерево 
	/// по указанному массиву
	/// массив следует отсартировать по возрастанию
	/// </summary>
	/// <param name="data">массив</param>
	/// <param name="start">начальный индекс</param>
	/// <param name="end">конечный индекс</param>
	/// <returns>указатель на корень дерева</returns>
	TreeNode * MakeTree(int *data, int start, int end);
};

