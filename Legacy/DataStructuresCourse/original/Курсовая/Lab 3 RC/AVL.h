
#include "Node.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;
class AVL {
#pragma region Private
private:
	Node *root;
	vector<int>data;
	char ** SCREEN;
	int size;
	bool OutNodes(Node * v, int r, int c);
	void clrscr();
#pragma endregion
#pragma region Public
public:
	AVL();
	AVL(int size);
	AVL(vector<int> data);
	void OutTree();
	void OutTree(string message);
	void AddItem(int value);
	int  GetSize();
	int GetItem(int index);
	bool Find(int value);
	void Change(AVL tree, int index);
	AVL operator - (AVL&B);
	AVL operator | (const AVL&B);
	AVL operator = (const AVL&B);
#pragma endregion
};
#pragma region Sort
void QSort(int* a, int size) {
	long i = 0, j = size - 1;
	int temp, p, mIndex = size >> 1;
	p = a[mIndex];
	if (size > 1)
	{
		do {
			while (i != mIndex && p > a[i]) i++;
			while (j != mIndex && a[j] > p) j--;
			if (i <= j) {
				if (i == mIndex)mIndex = j;
				if (j == mIndex)mIndex = i;
				temp = a[i]; a[i] = a[j]; a[j] = temp;
				i++; j--;
			}
		} while (i <= j);
		if (j > 0) QSort(a, j + 1);
		if (size > i) QSort(a + i, size - i);
	}
}
#pragma endregion
#pragma region Implementation
#pragma region Constructors
///<summary>Конструктор по умолчанию</summary>
AVL::AVL() {
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
}
///<summary>Конструктор</summary>
///<param name="_size">Размер</param>
AVL::AVL(int _size) {
	size = _size;
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
	for (int i = 0;i < _size;i++)
	{
		if (i == 0)	data.push_back(rand() % 10);
		else data.push_back(data.at(i-1) + rand() % 10);
	}
	root = Build(0, _size, data);
}
AVL::AVL(vector<int> _data)
{
	size = _data.size();
	SCREEN = new char *[8];
	for (int i = 0; i < 8; i++) SCREEN[i] = new char[80];
	data = _data;
	root = Build(0, size, data);
}
#pragma endregion
#pragma region Methods
///<summary>Добавить элемент</summary>
void AVL::AddItem(int value)
{
	root = root->insert(root, value);
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
		}
		if (r < 8) {
			if (v->left) OutNodes(v->left, r + 1, c - (40 >> r)); //левый сын		
			if (v->right) OutNodes(v->right, r + 1, c + (40 >> r)); //правый сын
		}
	}
	else {
		b = 0;
		cout << "\nДерево пустое!\n";
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
///<summary>Получает размер коллекции элементо дерева</summary>
///<return>Количество элементов</return>
int AVL::GetSize()
{
	return size;
}
///<summary>Получение элемента из коллекции по индексу</summary>
///<param name="index">Индекс</param>
int AVL::GetItem(int index)
{
	if (index >= 0 && index < size)
		return data[index];
	return -1;
}
///<summary>Замена элементов последовательности</summary>
///<param name="tree">дерево-источник</param>
///<param name="index">индекс откуда будет начинаться замена</param>
void AVL::Change(AVL tree, int index)
{
	int resultSize = index + tree.GetSize();
	vector<int> result;
	for (int i = 0;i < index;i++)
		result.push_back(data[i]);
	for (int i = 0;i < resultSize;i++)
		result.push_back(tree.GetItem(i));
	QSort(&result[0], resultSize);
	root = Build(0, resultSize, result);
}
///<summary>Бинырный посик в дереве</summary>
///<param name="value">значение</param>
bool AVL::Find(int value)
{
	Node *current = root;
	while (current)
	{
		if (current->key == value)
			return true;
		else if (value > current->key)
			current = current->right;
		else
			current = current->left;
	}
	return false;
}
#pragma endregion
#pragma region Operators
///<summary>исключение</summary>
AVL AVL :: operator - (AVL &B) {
	AVL C;
	for (int i = 0;i < size;i++)
		if (!B.Find(data.at(i)))
			C.AddItem(data.at(i));
	return C;
}
///<summary>объединение</summary>
AVL AVL :: operator | (const AVL&B) {
	vector<int> resData;
	resData.insert(resData.end(), data.begin(), data.end());
	resData.insert(resData.end(), B.data.begin(), B.data.end());
	QSort(&resData[0], resData.size());
	AVL c(resData);
	return c;
}
///<summary>присваивание</summary>
AVL AVL :: operator = (const AVL &B)
{
	if (this != &B) {
		data = B.data;
		root = B.root;
	}
	return *this;
}
#pragma endregion
#pragma endregion