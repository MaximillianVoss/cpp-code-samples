// QSortTest1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N = 0;
vector<int> Insert(int n) {
	vector<int> result;
	for (int i = 0; i < n; i++) {
		int value;
		cout << "enter a" << i << endl;
		cin >> value;
		result.push_back(value);
	}
	return result;
}
void swap(int* a, int* b) {
	int* temp = a;
	a = b;
	b = temp;
}
void Print(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
int HoarePartition(int* a, int p, int r) {
	int x = a[p], i = p - 1, j = r + 1;
	while (1) {
		do  j--; while (a[j] > x);
		do  i++; while (a[i] < x);
		if (i < j) {
			cout << "Before:" << endl;
			Print(a, N);
			cout << "change:" << endl;
			cout << "i=" << i << " a[i]=" << a[i] << endl;
			cout << "j=" << j << " a[j]=" << a[j] << endl;
			cout << "p=" << p << " a[p]=" << a[p] << endl;
			swap(a[i], a[j]);
			cout << "After:" << endl;
			Print(a, N);
		}
		else
			return j;
	}
}
void QuickSort(int* a, int start, int end) {
	if (end <= start) return;
	int q = HoarePartition(a, start, end);
	QuickSort(a, start, q);
	QuickSort(a, q + 1, end);
}


int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите число элементов" << endl;
	cin >> N;
	vector<int> a = Insert(N);
	QuickSort(&a[0], 0, N-1);

}
