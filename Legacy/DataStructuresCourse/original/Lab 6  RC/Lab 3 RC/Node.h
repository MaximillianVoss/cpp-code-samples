#include "Tree.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
using namespace std;
class Node {
#pragma region Private
private:
	int key;
	unsigned char heighth;
	//кратность узла
	int multiply;			
	vector<vector<char>>SCREEN;
	void InitScreen();
	void PrintScreen();
	void OutNodes(Node *v, int r, int c);
	void fixheight(Node*);
	int  bfactor(Node*);
	unsigned char height(Node*);
	Node* balance(Node*);
#pragma endregion
#pragma region Public
public:
#pragma region Fields
	Node *left;
	Node *right;
#pragma endregion
#pragma region Constructors
	Node();
	~Node() 
	{
	};
	Node(int k) 
	{ 
		key = k; 
		left = right = 0;
		multiply = 1;
		heighth = 1; 
	}
#pragma endregion
#pragma region Methods
	Node* Build(int a, int b, Tree tree);
	Node* Build(Tree tree);
	Node* remove(Node*, int);
	Node* findmin(Node*);
	Node* removemin(Node*);
	Node* insert(Node*, int);
	Node* rotateright(Node*);
	Node* rotateleft(Node*);
	void PrintTree(Node *node);
	void PrintTree();
#pragma endregion
#pragma endregion
};
#pragma region Implementation
const char symbol = '.';
Node::Node()
{

}
Node* Node::Build(int a, int b, Tree tree)
{
	if (b <= a)return 0;
	int c = (a + b) / 2;
	Node *s = new Node(tree.GetItemByIndex(c));
	s->left = Build(a, c, tree);
	s->right = Build(c + 1, b, tree);
	return s;
}
Node* Node::Build(Tree tree)
{
	if (tree.GetSize()==0)return 0;
	int c = tree.GetSize() / 2;
	Node *s = new Node(tree.GetItemByIndex(c));
	s->left = Build(0, c, tree);
	s->right = Build(c + 1, tree.GetSize(), tree);
	return s;
}
Node* Node::insert(Node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new Node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
	//return p;
}
Node* Node::findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}
Node*  Node::removemin(Node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
Node* Node::remove(Node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return q;
		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
	}
	return balance(p);
}
Node* Node::rotateright(Node* p) // правый поворот вокруг p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}
void Node::fixheight(Node* p) //изменение высоты дерева
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->heighth = (hl > hr ? hl : hr) + 1;
}
int Node::bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}
unsigned char Node::height(Node*p) {
	return p ? p->heighth : 0;
};
Node* Node::balance(Node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}
Node*  Node::rotateleft(Node* q) // левый поворот вокруг q
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}
void Node::InitScreen()
{
	for (int i = 0;i<8;i++)
		SCREEN.push_back(vector<char>(80));

	for (int i = 0;i<8;i++)
		for (int j = 0;j<80;j++)
		{
			SCREEN[i][j] = symbol;
		}
}
void Node::PrintScreen()
{
	for (int i = 0; i < SCREEN.size(); i++)
	{
		printf("\n");
		for (int j = 0; j < SCREEN[i].size(); j++) {
			if (SCREEN[i][j] == symbol)
				cout << SCREEN[i][j];
			else
				cout << (int)SCREEN[i][j];;
		}
	}
	printf("\n");
}
void Node::OutNodes(Node *v, int row, int cell)
{	
	if (v) 
	{
		if (row && cell) {
			if (v->key > 10) 
			{
				if (v->key > 100) {
					SCREEN[row - 1][cell - 3] = v->key / 100;
					SCREEN[row - 1][cell - 2] = v->key / 10 - v->key / 100 * 10;
					SCREEN[row - 1][cell - 1] = v->key - v->key / 100 * 100 - (v->key / 10 - v->key / 100 * 10) * 10;
				}
				else {
					SCREEN[row - 1][cell - 2] = v->key / 10;
					SCREEN[row - 1][cell - 1] = v->key % 10;
				}
			}
			else
				SCREEN[row - 1][cell - 1] = v->key;
		}
		if (v->left) OutNodes(v->left, row + 1, cell - (40 >> row)); //левый сын		
		if (v->right) OutNodes(v->right, row + 1, cell + (40 >> row)); //правый сын
	}
	else cout << "\nДерево пустое!\n";	
}
void Node::PrintTree(Node *node)
{
	this->InitScreen();
	this->OutNodes(node, 1, 40);
	this->PrintScreen();
}
void Node::PrintTree()
{
	this->PrintTree(this);
}
#pragma endregion













