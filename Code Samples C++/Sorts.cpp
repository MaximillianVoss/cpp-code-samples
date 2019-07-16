#include "stdafx.h"
#include "Sorts.h"

#pragma region Конструктор/Деструктор
Sorts::Sorts()
{
}

Sorts::~Sorts()
{
}

#pragma endregion

#pragma region Methods
void Sorts::BubbleSort(int *a, size_t length) {
	for (int j = 0; j < length - 1; j++) {
		for(size_t i = 0; i < length - j - 1; i++) {
			if (a[i] > a[i + 1]) {
				//change for elements
				int b = a[i];
				a[i] = a[i + 1];
				a[i + 1] = b;
			}
		}
	}
}

int Sorts::Compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

void Sorts::QuickSort(int *a, size_t n) {
	//qsort(a, n, sizeof(int), Compare);
}

template<typename T>
void Sorts::MergerSort(T array[], size_t size)
{
	if (size > 1)
	{
		std::size_t const left_size = size / 2;
		std::size_t const right_size = size - left_size;

		MergerSort(&array[0], left_size);
		MergerSort(&array[left_size], right_size);

		std::size_t lidx = 0, ridx = left_size, idx = 0;
		T *tmp_array = new T[size];

		while (lidx < left_size || ridx < size)
		{
			if (array[lidx] < array[ridx])
			{
				tmp_array[idx++] = std::move(array[lidx]);
				lidx++;
			}
			else
			{
				tmp_array[idx++] = std::move(array[ridx]);
				ridx++;
			}

			if (lidx == left_size)
			{
				std::copy(std::make_move_iterator(&array[ridx]),
					std::make_move_iterator(&array[size]),
					&tmp_array[idx]);
				break;
			}
			if (ridx == size)
			{
				std::copy(std::make_move_iterator(&array[lidx]),
					std::make_move_iterator(&array[left_size]),
					&tmp_array[idx]);
				break;
			}
		}

		std::copy(std::make_move_iterator(tmp_array),
			std::make_move_iterator(&tmp_array[size]),
			array);

		delete[]tmp_array;
	}
}

void Sorts::InsertionSort(int *a, size_t n)
{

	for(size_t i = 1; i < n; i++)
	{
		int cur = a[i];
		int j = i;
		while (j > 0 && cur < a[j - 1])
		{
			a[j] = a[j - 1];
			j--;
		}
		a[j] = cur;
	}
}
#pragma endregion

#pragma region Sorts Test
void Sorts::Test() {
	system("pause");
}
#pragma endregion

