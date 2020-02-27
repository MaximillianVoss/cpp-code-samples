#include "stdafx.h"
#include "Hamming.h"

#pragma region Constructors
Hamming::Hamming()
{
}

Hamming::~Hamming()
{
}
#pragma endregion

#pragma region Methods

vector<int> Hamming::Code(char c) {
	return Code(converter.Convert(c));
}

vector<int> Hamming::Code(int a) {
	return Code(converter.Convert(converter.Convert(a, 2)));
}

vector<int> Hamming::Code(string str) {
	vector<int> res;
	for (char c : str) {
		vector<int> temp = Code(c);
		res.insert(res.end(), temp.begin(), temp.end());
	}
	return res;
}

vector<int> Hamming::Code(vector<string> strs) {
	vector<int> res;
	for (string str : strs) {
		vector<int> temp = Code(str);
		res.insert(res.end(), temp.begin(), temp.end());
	}
	return res;
}

vector<int> Hamming::Code(vector<int>bits)
{
	int a, b, d = 0, r = 0, d1 = 1;
	a = bits.size();
	while (a + r + 1 > pow(2, r))
		r++;

	//cout << "No of data bits to be added " << r << " : Total Bits :" << a + r << endl;

	vector<int> data = vector<int>(a + r);
	for (int i = 1; i < a + r; ++i)
	{
		if ((i) == pow(2, d))
		{
			data[i] = 0;
			++d;
		}
		else
		{
			data[i] = bits[d1];
			++d1;
		}
	}

	//cout << " Data Bits are Encoded with Piraty bits(0): ";
	//for (int i = 1; i <= a + r; ++i)
	//	cout << data[i] << " ";

	d1 = 0;
	int min, max = 0, piraty, s, j;

#pragma region Parity Bit Calculation
	for (int i = 1; i < a + r; i = pow(2, d1))
	{
		++d1; piraty = 0; j = i;
		s = i;
		min = 1;
		max = i;

		for (j; j <= a + r;) {
			for (s = j; max >= min && s < a + r; ++min, ++s)
				if (data[s] == 1)
					piraty++;
			j = s + i;
			min = 1;
		}
		// Even Parity
		if (piraty % 2 == 0)
			data[i] = 0;
		else { data[i] = 1; }
	}

	//cout << endl << " Hamming codeword bits for even piraty are : ";
	//for (int i = 1; i <= a + r; ++i)
	//	cout << data[i] << " ";
	//cout << endl << endl;

	return data;
#pragma endregion
}

void Hamming::Decode() {

}

//TODO:интегрировать эти методы и посмотреть
//#include <stdio.h>
////Кодер Хемминга
//int at(unsigned char c, int i)
//{
//	return (c & (1 << i)) >> i;
//}
//
//unsigned char code(unsigned char c)
//{
//	int d;
//	unsigned char s;
//	s = 0;
//	for (d = 0; d < 8; d++)
//		s ^= at(c, d) * (d + 1);
//	return ~s;
//}
//
//void code_all(FILE *fin, FILE *fout, int n)
//{
//	int i;
//	unsigned char c;
//	for (i = 0; i < n; i++)
//	{
//		c = fgetc(fin);
//		fprintf(fout, "%c%c", c, code(c));
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	int n;
//	sscanf(argv[1], "%d", &n);
//
//	FILE *fin, *fout;
//	//for (i = 0; i < n; i++)
//	//	fprintf(fin, "%c", i + 30);
//
//	fin = fopen("in.txt", "r");
//	fout = fopen("out.txt", "w");
//	code_all(fin, fout, n);
//
//	fclose(fin);
//	fclose(fout);
//
//	return 0;
//}
////Декодер Хемминга
//#include <stdio.h>
//
//int at(unsigned char c, int i)
//{
//	return (c & (1 << i)) >> i;
//}
//
//unsigned char change(unsigned char c, int i)
//{
//	return c ^ (1 << i);
//}
//
//unsigned char code(unsigned char c)
//{
//	int d;
//	unsigned char s;
//	s = 0;
//	for (d = 0; d < 8; d++)
//		s ^= at(c, d) * (d + 1);
//	return ~s;
//}
//
//void decode_all(FILE *fin, FILE *fout, int n)
//{
//	int i;
//	unsigned char c, s, ds, c1;
//	for (i = 0; i < n; i++)
//	{
//		c = fgetc(fin);
//		s = fgetc(fin);
//		ds = s ^ code(c);
//		c1 = c;
//		if (ds)
//		{
//			c1 = change(c, ds - 1);
//			printf("Symnol %d bit %d\n", i, ds);
//		}
//		fprintf(fout, "%c", c1);
//	}
//}
//
//void main(int argc, char *argv[])
//{
//	int n;
//	sscanf(argv[1], "%d", &n);
//
//	FILE *fin, *fout;
//	//for (i = 0; i < n; i++)
//	//	fprintf(fin, "%c", i + 30);
//
//	fin = fopen("out.txt", "r");
//	fout = fopen("out2.txt", "w");
//	decode_all(fin, fout, n);
//}

#pragma endregion
