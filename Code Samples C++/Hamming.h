#include "InfoIO.h"
#include "Converter.h"
#pragma once
class Hamming
{
private:
	Converter converter;
public:
	Hamming();
	~Hamming();
	/// <summary>
	/// 
	/// </summary>
	vector<int> Code(char c);
	/// <summary>
	/// 
	/// </summary>
	vector<int> Code(int a);
	/// <summary>
	/// https://teckphile.wordpress.com/2017/10/27/hamming-code-c-implementation-for-n-bits/
	/// Кодирует информацию кодо Хэмминга
	/// </summary>
	vector<int> Code(vector<int>bits);
	/// <summary>
	/// кодирует строку
	/// </summary>
	/// <param name="str">строка</param>
	/// <returns></returns>
	vector<int>Code(string str);
	/// <summary>
	/// кодирует список строк
	/// </summary>
	/// <param name="strs">список строк</param>
	/// <returns></returns>
	vector<int> Code(vector<string> strs);
	/// <summary>
	/// Декодирует информацию
	/// </summary>
	void Decode();
};

