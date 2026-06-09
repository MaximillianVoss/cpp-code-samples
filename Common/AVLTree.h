#pragma once
#include "TreeNode.h"
#define NIL &sentinel           /* all leafs are sentinels */
/* root of Red-Black tree */
template<typename T>
class AVLTree {
private:
	/// <summary>
	/// Шаблон для листа
	/// </summary>
	TreeNode<T> sentinel = TreeNode<T>();// { NIL, NIL, 0, BLACK, 0 };
	/// <summary>
	/// Балансировка после удаления
	/// </summary>
	/// <param name="x"></param>
	void DeleteFixup(TreeNode<T>* x) {
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				TreeNode<T>* w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					RotateLeft(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						RotateRight(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					RotateLeft(x->parent);
					x = root;
				}
			}
			else {
				TreeNode<T>* w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					RotateRight(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						RotateLeft(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					RotateRight(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
	/// <summary>
	/// Балансировка после вставки
	/// </summary>
	/// <param name="x"></param>
	void InsertFixup(TreeNode<T>* x) {
		/* check Red-Black properties */
		while (x != root && x->parent->color == RED) {
			/* we have a violation */
			if (x->parent == x->parent->parent->left) {
				TreeNode<T>* y = x->parent->parent->right;
				if (y->color == RED) {

					/* uncle is RED */
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else {

					/* uncle is BLACK */
					if (x == x->parent->right) {
						/* make x a left child */
						x = x->parent;
						RotateLeft(x);
					}

					/* recolor and rotate */
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RotateRight(x->parent->parent);
				}
			}
			else {

				/* mirror image of above code */
				TreeNode<T>* y = x->parent->parent->left;
				if (y->color == RED) {

					/* uncle is RED */
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else {

					/* uncle is BLACK */
					if (x == x->parent->left) {
						x = x->parent;
						RotateRight(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RotateLeft(x->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	/// <summary>
	/// Левый поворот
	/// </summary>
	/// <param name="x"></param>
	void RotateLeft(TreeNode<T>* x) {
		TreeNode<T>* y = x->right;

		/* establish x->right link */
		x->right = y->left;
		if (y->left != NIL) y->left->parent = x;

		/* establish y->parent link */
		if (y != NIL) y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		else {
			root = y;
		}

		/* link x and y */
		y->left = x;
		if (x != NIL) x->parent = y;
	}
	/// <summary>
	/// Правы поворот
	/// </summary>
	/// <param name="x"></param>
	void RotateRight(TreeNode<T>* x) {
		TreeNode<T>* y = x->left;

		/* establish x->left link */
		x->left = y->right;
		if (y->right != NIL) y->right->parent = x;

		/* establish y->parent link */
		if (y != NIL) y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
		else {
			root = y;
		}

		/* link x and y */
		y->right = x;
		if (x != NIL) x->parent = y;
	}
public:
	/// <summary>
	/// Корень дерева
	/// </summary>
	TreeNode<T>* root;
	AVLTree() {
		this->root = NULL;
	}
	/// <summary>
	/// Добавляет вершину
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	TreeNode<T>* Add(T data) {
		TreeNode<T>* current, * parent, * x;
		/* find where node belongs */
		current = root;
		parent = 0;
		while (current != NIL) {
			if (compEQ(data, current->data)) return (current);
			parent = current;
			current = compLT(data, current->data) ?
				current->left : current->right;
		}

		/* setup new node */
		/*if ((x = malloc(sizeof(*x))) == 0) {
			printf("insufficient memory (insertNode)\n");
			exit(1);
		}*/
		x->data = data;
		x->parent = parent;
		x->left = NIL;
		x->right = NIL;
		x->color = RED;

		/* insert node in tree */
		if (parent) {
			if (compLT(data, parent->data))
				parent->left = x;
			else
				parent->right = x;
		}
		else {
			root = x;
		}

		InsertFixup(x);
		return(x);
	}
	/// <summary>
	/// Удаляет вершину
	/// </summary>
	/// <param name="z"></param>
	void Delete(TreeNode<T>* z) {
		TreeNode<T>* x, * y;
		if (!z || z == NIL) return;


		if (z->left == NIL || z->right == NIL) {
			/* y has a NIL node as a child */
			y = z;
		}
		else {
			/* find tree successor with a NIL node as a child */
			y = z->right;
			while (y->left != NIL) y = y->left;
		}

		/* x is y's only child */
		if (y->left != NIL)
			x = y->left;
		else
			x = y->right;

		/* remove y from the parent chain */
		x->parent = y->parent;
		if (y->parent)
			if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
		else
			root = x;

		if (y != z) z->data = y->data;


		if (y->color == BLACK)
			DeleteFixup(x);
		free(y);
	}
	/// <summary>
	/// Возвращает указатель на вершину, если такая есть в дереве
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	TreeNode<T>* Find(T data) {
		TreeNode<T>* current = root;
		while (current != NIL)
			if (compEQ(data, current->data))
				return (current);
			else
				current = compLT(data, current->data) ?
				current->left : current->right;
		return(0);
	}
};