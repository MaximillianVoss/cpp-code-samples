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
		/// Блокчейн
		/// </summary>
		class BlockChain {
		public:
			static constexpr const char* logCleared = "Лог очищен";
			static constexpr const char* blockAdded = "Блок добавлен";
			static constexpr const char* blockDeleted = "Блок удален";
			static constexpr const char* clientAdded = "Клиент добавлен";
			static constexpr const char* clientDeleted = "Клиент удален";
			static constexpr const char* clientConnected = "Клиент соединился";
			static constexpr const char* clientDisconnected = "Клиент отсоединился";
			static constexpr const char* votingStarted = "Голосование началось";
			static constexpr const char* voitingRestarted = "Голосование перезапущено";
			static constexpr const char* voitingEnded = "Голосование окончено";
		};
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
			static constexpr const char* objectIsNULL = "Объект не существует(NULL)!";
			/// <summary>
			/// Ввод/вывод
			/// </summary>
			class IO {
			public:
				static constexpr const char* input = "Ошибка ввода, повторите ввод";
				static constexpr const char* format = "Ошибка форматирования, проверьте формат данных  повторите ввод";
			};
			/// <summary>
			/// Списки
			/// </summary>
			class Lists {
			public:
				static constexpr const char* elementAlreadyExists = "Элемент уже существует!";
				static constexpr const char* empty = "Список пуст";
				static constexpr const char* incorrectIndex = "Некорректный иднекс";
				static constexpr const char* incorrectSize = "Некорректный размер списка!";
				static constexpr const char* incorrectSizeTemplate = "Некорректный размер списка! \nОжидалось элементов:%i\nПолучено элементов:%i\n";
				static constexpr const char* notFound = "Элемент не найден";
				static constexpr const char* tooSmall = "Список слишком мал!";
				static constexpr const char* tooLarge = "Список слишком большой!";
			};
			/// <summary>
			/// Точки
			/// </summary>
			class Points {
			public:
				static constexpr const char* notPoint = "Не явялется точкой!";
			};
		};
		/// <summary>
		/// Разделители
		/// </summary>
		class Separators {
		public:
			/// <summary>
			/// стрелка вправо
			/// </summary>
			static constexpr const char* arrowRight = "->";
			/// <summary>
			/// стрелка влево
			/// </summary>
			static constexpr const char* arrowLeft = "<-";
			/// <summary>
			/// точка с запятой
			/// </summary>
			static constexpr const char* semicolon = ";";
			/// <summary>
			/// двоеточие
			/// </summary>
			static constexpr const char* colon = ":";
			/// <summary>
			/// пробел
			/// </summary>
			static constexpr const char* space = " ";
			/// <summary>
			/// запятая
			/// </summary>
			static constexpr const char* comma = ",";
		};
		/// <summary>
		/// Префиксы
		/// </summary>
		class Prefixes {
		public:
			/// <summary>
			/// открывающая квадратная скобка 
			/// </summary>
			static constexpr const char* squareBracket = "[";
			/// <summary>
			/// открывающая фигурная скобка 
			/// </summary>
			static constexpr const char* brace = "{";

		};
		/// <summary>
		/// Постфиксы
		/// </summary>
		class Postfixes {
		public:
			/// <summary>
			/// закрывающая фигурная скобка 
			/// </summary>
			static constexpr const char* brace = "}";
			/// <summary>
			/// закрывающая квадратная скобка 
			/// </summary>
			static constexpr const char* squareBracket = "]";
		};
	};
	/// <summary>
	/// Целочисленные константы
	/// </summary>
	class Ints {
	public:
		class Strings {
		public:
			static const size_t maxLength = 255;
		};
		class Lists {
		public:
			static const int notFoundIndex = -1;
		};
	};
	/// <summary>
	/// Дробные константы
	/// </summary>
	class Doubles {
	public:
	};
};