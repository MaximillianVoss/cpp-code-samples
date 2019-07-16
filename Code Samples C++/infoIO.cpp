#include "stdafx.h"
#include "InfoIO.h"

#pragma region Конструктор/Деструктор
IO::IO()
{
}
IO::~IO()
{
}
#pragma endregion

#pragma region Методы

#pragma region Out
void IO::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void IO::SetColor(int color) {
	SetColor(color, color);
}
void IO::Print(string message)
{
	Print(message.c_str());
}
void IO::Print(const char* message)
{
	if (strlen(message) > 0)
		printf("%s\n", message);
}
void IO::Print(vector<vector<int>> matrix)
{
	for (size_t i = 0; i < matrix.size(); i++)
		Print(matrix[i]);
}
void IO::Print(vector<vector<int>> matrix, string message)
{
	printf("%s\n", message.c_str());
	for (size_t i = 0; i < matrix.size(); i++)
		Print(matrix[i]);
}
//void InfoIO::Print(Field field, map<CellTypes, ConsoleColors> colorsMap) {
//	//system("cls");
//	map<CellTypes, ConsoleColors>::iterator it;
//	ConsoleColors headerText = ConsoleColors::Black;
//	ConsoleColors headerBackground = ConsoleColors::White;
//	SetColor(headerBackground, headerBackground);
//	printf("%.2i", 0);
//	SetColor(headerText, headerBackground);
//	for (int i = 0; i < field.size; i++)
//		cout << setw(2) << i + 1;
//	//printf("%.2i", i+1);
//	printf("\n");
//
//	for (int i = 0; i < field.size; i++) {
//		SetColor(headerText, headerBackground);
//		cout << setw(2) << i + 1;
//		//printf("%.2i", i + 1);
//		for (int j = 0; j < field.size; j++) {
//			it = colorsMap.find(field.a[i][j].type);
//			if (it != colorsMap.end())
//			{
//				SetColor(it->second);
//				printf("%.2i", field.a[i][j].value);
//			}
//		}
//		printf("\n");
//	}
//	//возвращаем цвет по умолчанию
//	it = colorsMap.find(CellTypes::default);
//	if (it != colorsMap.end())
//		SetColor(ConsoleColors::White, it->second);
//	else
//		SetColor(ConsoleColors::White, ConsoleColors::Black);
//}

void IO::PrintSeparator(int count)
{
	for (int i = 0; i < count; i++)
		cout << '_';
	cout << endl;
}

#pragma endregion

#pragma region  In
bool IO::isInt(string s) {
	string nums = "1234567890";
	for (int i = 0; i < s.length(); i++)
		if (nums.find(s[i]) == -1)
			return false;
	return true;
}
bool IO::isInt(char* s) {
	return isInt(string(s));
}
bool IO::Get(int& value, string message)
{
	Print(message);
	if (cin >> value)
		return true;
	else if (cin.bad()) {
		Print("Ошибка ввода, повторите ввод");
		Get(value, message);
		return false;
	}
	else {
		Print("Ошибка форматирования, проверьте формат данных  повторите ввод");
		Get(value, message);
		return false;
	}
}
bool IO::Get(double& value, string message)
{
	Print(message);
	if (cin >> value)
		return true;
	else if (cin.bad()) {
		Print("Ошибка ввода, повторите ввод");
		Get(value, message);
		return false;
	}
	else {
		Print("Ошибка форматирования, проверьте формат данных  повторите ввод");
		Get(value, message);
		return false;
	}
}
void IO::Get(int* a, int n) {
	a = new int[n];
	for (size_t i = 0; i < n; i++)
		Get(a[i], "Введите " + to_string(i + 1) + "элемент массива");
}
void IO::Get(double* a, int n) {
	a = new double[n];
	for (size_t i = 0; i < n; i++)
		Get(a[i], "Введите " + to_string(i + 1) + "элемент массива");
}
void IO::Get(string * str, string message) {
	Print(message);
	Get(str);
}
void IO::Get(string * str) {
	cin >> *str;
}
void IO::Get(bool* b)
{
	string str;
	Get(&str, "Введите значение да/нет:");
	if (str == "да")
		* b = true;
	else
		*b = false;
}
int IO::GetInt()
{
	int result = 0;
	this->Get(result, "");
	return  result;
}
int IO::GetInt(string message)
{
	this->Print(message);
	this->GetInt();
}
double IO::GetDouble()
{
	double result = 0;
	this->Get(result, "");
	return  result;
}
double IO::GetDouble(string message)
{
	this->Print(message);
	return this->GetDouble();
}
string IO::GetStr()
{
	string str = "";
	this->Get(&str, "");
	return str;
}
string IO::GetStr(string message)
{
	this->Print(message);
	return this->GetStr();
}
#pragma endregion

#pragma region Other
void IO::SetRusIO() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}
void IO::Pause() {
	system("pause");
}
void IO::Clear()
{
	system("cls");
}
void IO::Wait(int milliSeconds) {
	Sleep(milliSeconds);
}
#pragma endregion

#pragma endregion