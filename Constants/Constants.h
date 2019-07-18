#pragma once
/// <summary>
/// Константы
/// </summary>
class Constants {
public:
	/// <summary>
	/// Строковые константы
	/// </summary>
	class Strings {
	public:
		static constexpr const char* undefined = "undefined";
		class Alphabets {
		public:
			static constexpr const char* rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
			static constexpr const char* eng = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		};
		class Messages {
		public:
			class Inputs {
			public:
				static constexpr const char* inputValue = "Введите значение";

			};
			class UnitTest {
			public:
				static constexpr const char* passed = "тест пройден!";
				static constexpr const char* failed = "тест провален!";
				static constexpr const char* expected = "ожидалось";
				static constexpr const char* actual = "получено";
			};
		};
		class Errors {
		public:
			static constexpr const char* notImplemented = "Отсутствует реализация метода";
			class IO {
			public:
				static constexpr const char* input = "Ошибка ввода, повторите ввод";
				static constexpr const char* format = "Ошибка форматирования, проверьте формат данных  повторите ввод";
			};
		};
	};
	/// <summary>
	/// Целочисленные константы
	/// </summary>
	class Ints {
	public:
		static const size_t strMaxLength = 255;
	};
	/// <summary>
	/// Дробные константы
	/// </summary>
	class Doubles {
	public:
	};
};