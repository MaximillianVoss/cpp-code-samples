#include "stdafx.h"
#pragma once

/// <summary>
/// Стандартная матрица
/// создает матрицу указанного размера
/// и указанного типа
/// </summary>
class Matrix
{
private:

public:
	/// <summary>
	/// Тип матрицы
	/// </summary>
	enum MatrixType {
		/// <summary>
		/// по главной диагонли стоят 0
		/// в остальных местах 1
		/// </summary>
		zeroDiagonal,
		/// <summary>
		/// по главной диагонли стоят 1
		/// в остальных местах 0
		/// </summary>
		oneDiagonal,
		/// <summary>
		/// заполнена 1
		/// </summary>
		one,
		/// <summary>
		/// заполнена 0
		/// </summary>
		zero,
		/// <summary>
		/// содержит случайные числа:
		/// положительные и отрицательные
		/// </summary>
		randomAll,
		/// <summary>
		/// содержит только положительные числа
		/// </summary>
		randomPositive,
		/// <summary>
		/// Проверочная матрица 
		/// для кода Хэмминга
		/// </summary>
		check
	};
	/// <summary>
	/// Создает матрицу, заполненную случайными числами
	/// </summary>
	/// <param name="n">число строк</param>
	/// <param name="m">число столбцов</param>
	Matrix(int n, int m, Matrix::MatrixType type);
	/// <summary>
	/// конструктор по умлочанию
	/// </summary>
	Matrix();
	/// <summary>
	/// дектруктор
	/// </summary>
	~Matrix();
	/// <summary>
	/// содежримое матрицы
	/// </summary>
	vector<vector<int>> matrix;
	/// <summary>
	/// Создает матрицу, заполненную случайными числами
	/// </summary>
	/// <param name="rowsCount">число строк</param>
	/// <param name="columnCount">число столбцов</param>
	/// <returns></returns>
	void CreateMatrix(int rowsCount, int columnCount, Matrix::MatrixType type);
	/// <summary>
	/// Склеивает два матрицы по горизонтали
	/// матрицы должн быть одного размера по строкам
	/// </summary>
	/// <param name="m">матрица для склейки</param>
	/// <returns></returns>
	void Add(Matrix m);
	/// <summary>
	/// Переставляет строки и столбцы в матрице
	/// </summary>
	/// <param name="m">матрица</param>
	void Rotate(Matrix& m);
};