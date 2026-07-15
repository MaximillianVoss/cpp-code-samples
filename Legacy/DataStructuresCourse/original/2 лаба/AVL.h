
#include "Node.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;
int treeSize = 15;
class AVL {
private:
	Node *root;
	int *data;
	char ** SCREEN;
	bool OutNodes(Node * v, int r, int c);
	void clrscr();
public:
	AVL();
	AVL(int);
	AVL(int *data);
	void OutTree();
	void OutTree(string message);
	void AddItem(int value);
	AVL operator - (const AVL&B);
	AVL operator | (const AVL&B);
	AVL operator = (const AVL&B);
};

AVL::AVL(int k) {
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
	data = new int[k];
	for (int i = 0;i < k;i++)
		data[i] = 0;
}
AVL::AVL() {
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
	data = new int[treeSize];
	for (int i = 0;i < treeSize;i++)
	{
		if (i == 0)
		{
			data[i] =  rand() % 10;
		}
		else
		{
			data[i] = data[i - 1] + rand() % 10;//генерация восх. последовательности
		}
	}
	//Node *h;
	root = Build(0, treeSize, data);
}
AVL::AVL(int *_data)
{
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
	data = _data;
	root = Build(0, treeSize, data);
}
void AVL::AddItem(int value)
{	
	root->insert(root, value);
}
bool AVL::OutNodes(Node *v, int r, int c)
{
	bool b = 1;
	if (v) {
		if (r && c && (c < 80)) {
			if (v->key > 10) {
				if (v->key > 100) {
					SCREEN[r - 1][c - 3] = v->key / 100;
					SCREEN[r - 1][c - 2] = v->key / 10 - v->key / 100 * 10;
					SCREEN[r - 1][c - 1] = v->key - v->key / 100 * 100 - (v->key / 10 - v->key / 100 * 10) * 10;
				}
				else {
					SCREEN[r - 1][c - 2] = v->key / 10;
					SCREEN[r - 1][c - 1] = v->key % 10;
				}
			}
			else
				SCREEN[r - 1][c - 1] = v->key;
			//SCREEN[r-1][c-2]=v->heighth;
			//SCREEN[r-1][c-1]=v->multiply;
		}
		if (r < 8) {
			if (v->left) OutNodes(v->left, r + 1, c - (40 >> r)); //левый сын		
			if (v->right) OutNodes(v->right, r + 1, c + (40 >> r)); //правый сын
		}
	}
	else {
		b = 0;
		cout << "\nV dereve net elementov!";
	}
	return b;
}
void AVL::OutTree()
{
	clrscr();
	bool b = OutNodes(root, 1, 40);
	if (b)
	{
		for (int i = 0; i < 8; i++)
		{
			cout << "\n";
			for (int j = 0; j < 80; j++) {
				if (SCREEN[i][j] == '.')
					cout << SCREEN[i][j];
				//else if (SCREEN[i][j] == '-') {
				//	cout << "-" << (int)SCREEN[i][++j];
				//}
				else	cout << (int)SCREEN[i][j];;
			}
		}
		cout << '\n';
	}
}
void AVL::OutTree(string message)
{
	printf("%s\n", message.c_str());
	OutTree();
}
void AVL::clrscr()
{
	for (int i = 0; i < 8; i++)
		memset(SCREEN[i], '.', 80);
}
AVL AVL :: operator - (const AVL&B) {
	int q = 0;
	AVL C(treeSize);
	for (int i = 0;i < treeSize;i++) {
		int f = 1;
		for (int j = 0; j < treeSize;j++)
		{
			if (B.data[j] == data[i]) f = 0;
		}
		if (f) C.data[q++] = data[i];
	}
	C.root = Build(0, q, C.data);
	return C;
}
AVL AVL :: operator | (const AVL&B) { //объединение
	int q = 0;
	AVL C(2 * treeSize);
	for (int i = 0;i < treeSize;i++) {
		C.data[q++] = data[i];
	}
	for (int i = 0;i < treeSize;i++) {
		C.data[q++] = B.data[i];
	}
	for (int i = 0; i < q; i++)
		for (int j = i + 1; j < q; j++)
			if (C.data[i] > C.data[j])
			{
				int buf = C.data[i];
				C.data[i] = C.data[j];
				C.data[j] = buf;
			}
	C.root = Build(0, q, C.data);
	return C;
}
AVL AVL :: operator = (const AVL &B)
{
	if (this != &B) {
		data = B.data;
		root = B.root;
	}
	return *this;
}



