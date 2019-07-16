#include "stdafx.h"
#include "Matrix.h"

#pragma region Контсруктор
Matrix::Matrix(int n, int m, Matrix::MatrixType type)
{
	CreateMatrix(n, m, type);
}
Matrix::Matrix()
{

}
Matrix::~Matrix()
{
}
#pragma endregion

#pragma region Методы
void Matrix::CreateMatrix(int rowsCount, int columnCount, Matrix::MatrixType type)
{
	srand(time(NULL));
	for(size_t i = 0; i < rowsCount; i++)
	{
		matrix.push_back(vector<int>());
		for (int j = 0; j < columnCount; j++)
		{
			switch (type)
			{
			case Matrix::zeroDiagonal:
				if (i == j)
					matrix[i].push_back(0);
				else
					matrix[i].push_back(1);
				break;
			case Matrix::oneDiagonal:
				if (i == j)
					matrix[i].push_back(1);
				else
					matrix[i].push_back(0);
				break;
			case Matrix::one:
				matrix[i].push_back(1);
				break;
			case Matrix::zero:
				matrix[i].push_back(0);
				break;
			case Matrix::randomAll:
				matrix[i].push_back((rand() % 100)*(pow(-1, rand() % 2)));
				break;
			case Matrix::randomPositive:
				matrix[i].push_back(rand() % 100);
				break;
			default:
				break;
			}

		}
	}
}
void Matrix::Add(Matrix m) {
	for(size_t i = 0; i < matrix.size(); i++)
		matrix[i].insert(matrix[i].end(), m.matrix[i].begin(), m.matrix[i].end());
}
void Matrix::Rotate(Matrix &m)
{
	if (matrix.size() > 0)
	{
		int rows = m.matrix.size(), columns = m.matrix[0].size();
		int n = max(rows, columns);
		Matrix temp = Matrix(n, n, Matrix::MatrixType::zero);
		for(size_t i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				temp.matrix[j][i] = m.matrix[i][j];
		m.matrix.clear();
		m = temp;
	}
}
#pragma endregion