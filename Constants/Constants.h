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
		/// <summary>
		/// Пустая строка
		/// </summary>
		static constexpr const char* strEmpty = "";
		/// <summary>
		/// Непределенное значение-заглушка
		/// </summary>
		static constexpr const char* undefined = "undefined";
		/// <summary>
		/// Алфавиты
		/// </summary>
		class Alphabets {
		public:
			static constexpr const char* rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
			static constexpr const char* eng = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		};
		/// <summary>
		/// Сообщения/Инструкции
		/// </summary>
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
		/// <summary>
		/// Сообщения об ошибках/исключения
		/// </summary>
		class Errors {
		public:
			static constexpr const char* notImplemented = "Отсутствует реализация метода";
			class IO {
			public:
				static constexpr const char* input = "Ошибка ввода, повторите ввод";
				static constexpr const char* format = "Ошибка форматирования, проверьте формат данных  повторите ввод";
			};
			class Lists {
			public:
				static constexpr const char* empty = "Список пуст";
				static constexpr const char* incorrectIndex = "Некорректный иднекс";
				static constexpr const char* notFound = "Элемент не найден";
			};
		};
		/// <summary>
		/// Разделители
		/// </summary>
		class Separators {
		public:
			static constexpr const char* arrow = "->";
			static constexpr const char* column = ";";
			static constexpr const char* space = " ";
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