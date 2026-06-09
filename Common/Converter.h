
#pragma once
#include "pch.h"
#include "StrHelper.h"
#include "Constants.h"
template<typename T>
///<summary>
/// Описание_класса
///</summary>
class Converter
{
public:

#pragma region Методы



#pragma endregion

#pragma region Дочерние классы
	class Paths {
	public:
		/// <summary>
		/// Получает путь из массива и преобразует в строку
		/// [C,somefile.txt] -> C:\\somegfile.txt 
		/// </summary>
		/// <param name="items"></param>
		/// <returns></returns>
		string ToString(vector<string> items) {
			string path = "";
			if (items.size() > 1) {
				path = items[0] + ":";
				for (int i = 1; i < items.size(); i++)
					path += "\\" + items[i];
			}
			return path;
		}
		/// <summary>
		/// Преобразует путь и строки в массив:
		/// C:\\somegfile.txt -> [C,somefile.txt]
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		vector<string>FromString(string path) {

		}

	};

	class Strings {
	public:
		T Convert(string str)
		{
			istringstream ss(str);
			T num;
			ss >> num;
			return num;
		}
	};

	class Integers {
	public:
		float ToPercent(string value) {
			return ToPercent(atoi(value.c_str()));
		}
		float ToPercent(int value) {
			return (float)value / 100.0;
		}
	};

	class Lists {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="str"></param>
		/// <param name="separator"></param>
		/// <param name="notDelete"></param>
		/// <param name="prefix"></param>
		/// <param name="postfix"></param>
		/// <returns></returns>
		vector<T> Convert(
			string str,
			string separator = Constants::Strings::Separators::comma,
			string notDelete = Constants::Strings::strEmpty,
			string prefix = Constants::Strings::Prefixes::squareBracket,
			string postfix = Constants::Strings::Postfixes::squareBracket
		) {
			if (str.length() > 1) {
				StrHelper sh;
				str = sh.Remove(str, prefix);
				str = sh.Remove(str, postfix);
				vector<string> items = sh.Split(str, separator, notDelete);
				vector<T> result;
				for (string item : items)
					result.push_back(Converter<T>::Strings().Convert(item));
				return result;
			}
			throw exception(Constants::Strings::Errors::Lists::incorrectSize);
		}
		/// <summary>
		/// 
		/// </summary>
		/// <param name="items"></param>
		/// <param name="separator"></param>
		/// <param name="notDelete"></param>
		/// <param name="prefix"></param>
		/// <param name="postfix"></param>
		/// <returns></returns>
		string Convert(vector<T>items,
			string separator = Constants::Strings::Separators::comma,
			string notDelete = Constants::Strings::strEmpty,
			string prefix = Constants::Strings::Prefixes::squareBracket,
			string postfix = Constants::Strings::Postfixes::squareBracket
		)
		{
			stringstream ss;
			ss << prefix;
			for (int i = 0; i < items.size(); i++) {
				ss << items[i];
				if (i < items.size() - 1)
					ss << separator;
			}
			ss << postfix;
			return ss.str();
		}
	};
#pragma endregion
};

