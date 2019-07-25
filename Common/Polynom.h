#pragma once
#include "pch.h"
#include "StrHelper.h"
template <class T>
/// <summary>
/// Полином
/// </summary>
class Polynom {
	/// <summary>
	/// Элемент полинома - коэфффициент, степень
	/// </summary>
	typedef pair< double, int > Item;
private:
#pragma region Fields
	/// <summary>
	/// коэффициенты
	/// </summary>
	vector<T> items;
	/// <summary>
	/// значение независимой переменной
	/// </summary>
	T x;
#pragma endregion
#pragma region Methods
	vector<T> Reverse(vector<T> items) {
		vector<T> copy = items;
		reverse(copy.begin(), copy.end());
		return copy;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="power"></param>
	/// <returns></returns>
	T Power(T value, size_t power) {
		T result = 1;
		while (power > 0) {
			result = result * value;
			power--;
		}
		return result;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="i1"></param>
	/// <param name="i2"></param>
	/// <returns></returns>
	bool compareItems(Item i1, Item i2)
	{
		return (i1.second < i2.second);
	}
#pragma endregion
public:
#pragma region Constructors
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="items"></param>
	Polynom(T x, vector<T> items) {
		this->x = x;
		this->items = Reverse(items);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="length"></param>
	Polynom(T x, size_t length) :Polynom(x, vector<T>(length)) {
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="length"></param>
	Polynom(size_t length) :Polynom(0, length) {

	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="items"></param>
	Polynom(vector<T> items) :Polynom(0, items) {

	}
	/// <summary>
	/// 
	/// </summary>
	Polynom() :Polynom(0, 0) {
	}
	/// <summary>
	/// Создает полином из строки
	/// </summary>
	/// <param name="str"> строка вида: x^3+2*x^2 + x^1 +x^0 , x^0 указывать обязательно</param>
	Polynom(string str) {
		this->x = 0;
		StrHelper strHelper = StrHelper();
		str = strHelper.Remove(str, ' ');
		vector<string> items = strHelper.Split(str, "-+", "");
		vector<Item> pitems;
		for (int i = 0; i < items.size(); i++)
		{
			vector<string> subtems = strHelper.Split(items[i], "*^", "");
			if (subtems.size() == 2) {
				//если имеет вид x^6
				if (!strHelper.IsNumber(subtems[0]) && strHelper.IsNumber(subtems[1]))
					pitems.push_back(Item(1.0, atoi(subtems[1].c_str())));
			}
			else if (subtems.size() == 3) {
				//если имеет вид 7*x^6
				if (strHelper.IsNumber(subtems[0]) && !strHelper.IsNumber(subtems[1]) && strHelper.IsNumber(subtems[2]))
					pitems.push_back(Item(atof(subtems[0].c_str()), atoi(subtems[2].c_str())));
			}
			else
				throw exception("Некорректная запись полинома!");
		}
		sort(pitems.begin(), pitems.end());
		this->items = vector<double>(pitems[pitems.size() - 1].second + 1);
		for (int i = 0; i < pitems.size(); i++)
			this->items[pitems[i].second] = pitems[i].first;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <summary>
	/// 
	/// </summary>
	~Polynom() {

	}
#pragma endregion
#pragma region GET
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	vector<T> GetItems() {
		return this->items;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	T Get(int i) {
		if (Check(-1, this->items.size(), i))
			return this->items[i];
		return NULL;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	T GetValue(T value) {
		T result = 0;
		for (int i = 0; i < this->GetLength(); i++)
			result = result + (this->Get(i) * Power(value, i));
		return result;
	}
	vector<Pair<double, double>> GetValues(double from, double to, double step) {
		if (from > to)
			throw exception("неправильно указан промежуток!");
		vector<Pair<double, double>> result;
		for (double i = from; i < to; i += step) {
			Pair<double, double> pair = Pair<double, double>(i, (double)this->GetValue(i));
			result.push_back(pair);
		}
		return result;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Polynom<T> GetDerivative() {
		vector<T> copy = this->items;
		for (int i = 0; i < copy.size(); i++)
			copy[i] = copy[i] * i;
		copy.erase(copy.begin());
		return Polynom<T>(Reverse(copy));
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetLength() {
		return this->items.size();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	Polynom<T> GetSuperposition(Polynom<T> a, Polynom<T> b) {
		Polynom<T> result = Polynom(a.GetLength());
		for (int i = 0; i < a.GetLength(); i++) {
			result.items[i] = a.items[i] + b.items[i];
		}
		return result;
	}
#pragma endregion
#pragma region SET
	/// <summary>
	/// 
	/// </summary>
	/// <param name="i"></param>
	/// <param name="value"></param>
	void Set(int i, T value) {
		if (Check(-1, items.size(), i))
			this->items[i] = value;
	}
#pragma endregion
#pragma region Other
	void Down(size_t n) {
		if (n < this->GetLength())
			for (int i = 0; i <= n; i++)
				this->items.erase(this->items.begin());
	}
	/// <summary>
/// 
/// </summary>
/// <param name="from"></param>
/// <param name="to"></param>
/// <param name="value"></param>
/// <returns></returns>
	bool Check(int from, int to, int value) {
		return (value > from) && (value < to);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void PushBack(T value) {
		this->items.push_back(value);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void PushFront(T value) {
		this->items.insert(this->items.begin(), value);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	vector<Polynom<T>> Division(Polynom<T> a, Polynom<T> b) {
		vector<Polynom<T>> result(2);
		if (a == b)
			result[0].PushBack(1);
		if (a > b) {
			Polynom<T> rest = a;
			vector<T> quotientItems;
			while (rest.GetLength() >= b.GetLength()) {
				T aFront = *rest.Get(rest.GetLength() - 1);
				T bFront = *b.Get(b.GetLength() - 1);
				T k = aFront / bFront;
				int dLength = rest.GetLength() - b.GetLength();
				vector<T> items;
				for (int i = 0; i < dLength; i++)
					items.push_back(0);
				items.push_back(k);
				//ПРОВЕРИТЬ ЦЕЛОЕ ОТ ДЕЛЕНИЯ!
				Polynom<T> multiplier = Polynom<T>(Reverse(items));
				if (quotientItems.size() < multiplier.GetLength())
					quotientItems = multiplier.items;
				else {
					for (int i = 0; i < multiplier.GetLength(); i++)
						quotientItems[i] = multiplier.items[i];
				}
				//for (int i = 0; i < items.size(); i++)
				//	quotientItems.push_back(items[i]);
				Polynom<T> divisor = b * multiplier;
				rest = rest - divisor;
			}
			Polynom<T> quotient = Polynom<T>(Reverse(quotientItems));
			quotient.Update();
			result[0] = quotient;
			result[1] = rest;
		}
		else
			result[0].PushBack(0);
		return result;
	}
	/// <summary>
	/// Удаляет незначащие нули
	/// </summary>
	void Update() {
		while (this->items.size() > 0 && this->items[this->items.size() - 1] == 0)
			this->items.erase(this->items.begin() + this->items.size() - 1);
	}
	/// <summary>
	/// Ищет вхождение указанного коэффициента в полиноме
	/// </summary>
	/// <param name="a">коэффицент</param>
	/// <returns></returns>
	bool Find(T a) {
		for (int i = 0; i < this->items.size(); i++)
			if (this->items[i] == a)
				return  true;
		return false;
	}
#pragma endregion
#pragma region Operators
	template <typename T>
	friend  istream& operator >> (istream& in, Polynom<T>& a) {
		size_t length;
		in >> length;
		vector<T> items;
		for (int i = 0; i < length; i++) {
			T value;
			in >> value;
			items.push_back(value);
		}
		a = Polynom<T>(items);
		return in;
	}
	template <typename T>
	friend  ostream& operator << (ostream& out, Polynom<T>& a) {
		for (int i = a.items.size() - 1; i >= 0; i--) {
			if (a.items[i] != 0) {
				if (i == a.items.size() - 1)
					out << a.items[i] << "*x^" << i;
				else {
					if (a.items[i] > 0)
						out << '+';
					out << a.items[i];
					if (i > 0)
						out << "*x^" << i;
				}
			}
		}
		return out;
	}
	template <typename T>
	friend Polynom<T> operator+ (Polynom<T> a, Polynom<T> b) {
		Polynom<T> result;
		while (a.GetLength() > b.GetLength())
			b.PushBack(0);
		while (a.GetLength() < b.GetLength())
			a.PushBack(0);
		for (int i = 0; i < a.GetLength(); i++)
			result.PushBack(a.items[i] + b.items[i]);
		return result;
	}
	template <typename T>
	friend Polynom<T> operator- (Polynom<T> a, Polynom<T> b) {
		Polynom<T> result;
		while (a.GetLength() > b.GetLength())
			b.PushFront(0);
		while (a.GetLength() < b.GetLength())
			a.PushFront(0);
		for (int i = 0; i < a.GetLength(); i++)
			result.PushBack(a.items[i] - b.items[i]);
		result.Update();
		return result;
	}
	template <typename T>
	friend Polynom<T> operator* (Polynom<T> a, T b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++)
			result.Set(i, a.items[i] * b);
		return result;
	}
	template <typename T>
	friend Polynom<T> operator* (Polynom<T> a, Polynom <T> b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++) {
			Polynom<T> item(a.GetLength() + b.GetLength() - 1);
			for (int j = 0; j < b.GetLength(); j++)
			{
				T itemA = *(a.Get(i));
				T itemB = *(b.Get(j));
				item.Set(i + j, itemA * itemB);
			}
			result = result + item;
		}
		return result;
	}
	template <typename T>
	friend Polynom<T> operator/ (Polynom<T> a, T b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++) {
			result.Set(i, a.items[i] / b);
		}
		return result;
	}
	template <typename T>
	Polynom<T> operator/ (Polynom<T> a) {
		return this->Division(*this, a)[0];
	}
	template <typename T>
	Polynom<T> operator% (Polynom<T> a) {
		return this->Division(*this, a)[1];
	}
	template <typename T>
	friend bool operator> (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() > b.GetLength())
			return true;
		if (a.GetLength() < b.GetLength())
			return false;
		if (a.GetLength() == b.GetLength())
			for (int i = 0; i < a.GetLength(); i++)
				if (*a.Get(i) > * b.Get(i))
					return true;
		return false;
	}
	template <typename T>
	friend bool operator< (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() < b.GetLength())
			return true;
		if (a.GetLength() > b.GetLength())
			return false;
		if (a.GetLength() == b.GetLength())
			for (int i = 0; i < a.GetLength(); i++)
				if (a.Get(i) < b.Get(i))
					return true;
		return false;
	}
	template <typename T>
	friend bool operator== (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() == b.GetLength()) {
			for (int i = 0; i < a.GetLength(); i++)
				if (*a.Get(i) != *b.Get(i))
					return false;
			return true;
		}
		return false;
	}
#pragma endregion
};
