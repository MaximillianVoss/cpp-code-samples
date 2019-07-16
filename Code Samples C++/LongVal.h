#pragma once
/// <summary>
///тип дл€ длинных чисел
/// </summary>
class LongVal
{
public:
#pragma region ѕол€
	/// <summary>
	///массив с цифрами числа записанными в обратном пор€дке
	/// </summary>
	vector<int> values;
	/// <summary>
	/// отрицательное или нет
	/// </summary>
	/// <returns></returns>
	bool negative;
#pragma endregion

#pragma region  онструкторы/ƒеструкторы
	/// <summary>
	/// 
	/// </summary>
	LongVal();
	/// <summary>
	/// /
	/// </summary>
	/// <param name="str"></param>
	LongVal(string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="items"></param>
	LongVal(vector<int>items);
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name="negative"></param>
	LongVal(vector<int>items, bool _negative);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="length"></param>
	LongVal(int length);
	/// <summary>
	/// деструктор
	/// </summary>
	~LongVal();
#pragma endregion

#pragma region ћетоды
	/// <summary>
	/// инвертирует знак числа
	/// </summary>
	/// <returns></returns>
	LongVal Invert() {
		return LongVal(values, !negative);
	}
	/// <summary>
	/// 
	/// </summary>
	string ToStr();
	/// <summary>
	/// добавл€ет число в конец
	/// </summary>
	/// <param name="value">число дл€ добавлени€</param>
	void PushBack(int value);
	/// <summary>
	/// добавл€ет число в начало
	/// </summary>
	/// <param name="value">число дл€ добавлени€</param>
	void PushFront(int value);
	/// <summary>
	/// увлечивиет размер до указанного значени€
	/// </summary>
	/// <param name="value"></param>
	void SetLength(int newLength);
	/// <summary>
	/// возвращает длину числа
	/// </summary>
	/// <returns></returns>
	int GetLength();
#pragma endregion

#pragma region ќператоры
	/// <summary>
	/// оператор сложени€
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	LongVal operator +(LongVal &a) {
		if (negative == a.negative)
		{
			int overflow = 0;
			int commonLength = max(a.GetLength(), GetLength());
			a.SetLength(commonLength);
			SetLength(commonLength);
			for (int i = commonLength - 1; i > -1; i--)
			{
				int sum = values[i] + a.values[i] + overflow;
				a.values[i] = sum % 10;
				overflow = sum / 10;
			}
			if (overflow > 0)
				a.PushFront(overflow);
			return a;
		}
		else
			return a - LongVal(values, negative);
	}
	/// <summary>
	/// оператор вычитани€
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	LongVal operator -(LongVal &a) {
		if (negative == a.negative && negative)
			return LongVal(values) + a;
		else {
			int overflow = 0;
			int commonLength = max(a.GetLength(), GetLength());
			a.SetLength(commonLength);
			SetLength(commonLength);
			if (LongVal(values, negative) < a)
			{
				LongVal temp = LongVal(values, negative);
				Init(a.values, a.negative);
				a = temp;
			}
			for (int i = commonLength - 1; i > -1; i--)
			{
				int sum = values[i] - a.values[i] - overflow;
				if (values[i] < a.values[i])
					overflow = 1;
				else
					overflow = 0;
				a.values[i] = abs(sum);
			}
			if (overflow > 0)
				a.PushFront(overflow);
			if (LongVal(values, negative) < a)
				return a;
			else
				return a.Invert();
		}
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	LongVal operator *(LongVal &a) {
		return LongVal();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	LongVal operator /(LongVal &a) {
		return LongVal();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	LongVal operator %(LongVal &a) {
		return LongVal();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	bool operator >(LongVal &a) {
		if (negative && !a.negative)
			return false;
		if (!negative && a.negative)
			return true;
		if (negative&&a.negative)
			return LongVal(a.values, false) > LongVal(values, false);
		if (a.length == length) {
			int equal = 0;
			for (int i = 0; i < length; i++) {
				if (values[i] < a.values[i])
					return false;
				if (values[i] > a.values[i])
					return true;
				if (values[i] == a.values[i])
					equal++;
			}
			return equal != length;
		}
		if (a.length > length)
			return false;
		else
			false;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	bool operator <(LongVal &a) {
		return !(LongVal(values, negative) > a);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="a"></param>
	/// <returns></returns>
	bool operator ==(LongVal &a) {
		LongVal temp = LongVal(values, negative);
		bool more = temp > a;
		bool less = temp < a;
		return !more && !less;
	}
#pragma endregion

private:
#pragma region ѕол€
	/// <summary>
	///длинна числа
	/// </summary>
	unsigned long int length;
#pragma endregion

#pragma region ћетоды
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_length"></param>
	void Init(int _length);
	/// <summary>
	/// 
	/// </summary>
	void Init(string str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="items"></param>
	void Init(vector<int>items);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="items"></param>
	/// <param name="_negative"></param>
	void Init(vector<int>items, bool _negative);
#pragma endregion
};