#pragma once
#include "pchUnit.h"
//#include "Plotter.h"
//#include "Generator.h"
#include "Constants.h"
/// <summary>
/// Юнит тест
/// </summary>
template<typename T>
class UnitTest {
private:
	/// <summary>
	/// счетчик прогресса тетса(min:0%; max:100%)
	/// </summary>
	double pogressCounter = 0;
	/// <summary>
	/// Префикс
	/// </summary>
	string prefixName = "Тест ";
	/// <summary>
	/// Время выполнения - подпись
	/// </summary>
	string prefixMs = " Время выполнения:";
	/// <summary>
	/// Подписть для прогресса выполнения(префикс)
	/// </summary>
	string progressPrefix = "Прогресс выполнения";
	/// <summary>
	/// Подпись на случай неудачного подсчета прогресса
	/// </summary>
	string progressFail = "Подсчет прогресса невозможен, проверьте tickerCurrent/tickerMax!";
	/// <summary>
	/// Подписть для прогресса выполнения(постфикс)
	/// </summary>
	string progressPostfix = "%";
	/// <summary>
	/// Единицы измерения времени теста
	/// </summary>
	string postfixMs = " мс.";
	/// <summary>
	/// Индекс строки с несовпадающим значением
	/// </summary>
	int incorectIndex = -1;
	/// <summary>
	/// Показывать процесс 
	/// выполнения во время выолнения теста
	/// </summary>
	bool showProgress = false;
	/// <summary>
	/// Счетчик прогресса выполнения теста
	/// </summary>
	int tickerCurrent = 0;
	/// <summary>
	/// Максимальное значение счетчика прогресса выполнения теста
	/// </summary>
	int tickerMax = 0;
	/// <summary>
	/// список директорий с .txt файлами для построения графиков
	/// </summary>
	vector<string> fileNamesPlots;
	/// <summary>
	/// Печатает вектор в консоли
	/// </summary>
	void Print(vector<T> items, int incorectIndex = -1) {
		for (int i = 0; i < items.size(); i++) {
			if (incorectIndex == i)
				this->SetColor(ConsoleColor::white, ConsoleColor::light_red);
			cout << items[i] << endl;
			this->ResetColor();
		}
	}
	/// <summary>
	/// Отображает прогресс выполнения теста
	/// </summary>
	void PrintProgress() {
		while (true) {
			if (this->tickerMax > 0)
				cout << this->progressPrefix << (float)this->tickerCurrent / (float)this->tickerMax << this->progressPostfix << endl;
			else
				cout << this->progressFail << endl;
			std::chrono::seconds dura(1);
			std::this_thread::sleep_for(dura);
		}
	}

	/// <summary>
	/// Устанавлвает цвет в консоли
	/// </summary>
	/// <param name="text">цвет текста</param>
	/// <param name="background">цвет фона</param>
	void SetColor(int text, int background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
	/// <summary>
	/// Сбрасывает цвет текста и фона на значения поумолчанию
	/// </summary>
	void ResetColor() {
		this->SetColor(ConsoleColor::white, ConsoleColor::black);
	}

	/// <summary>
	/// Строит график по указанному .txt файлу
	/// </summary>
	/// <param name="filename">путь до .txt файла</param>
	void Plot(string filename) {
		stringstream ss;
		ss << this->prefixPython << "" << this->pathToPyton << " " << filename;
		system(ss.str());
	}
	/// <summary>
	/// Создает графики по файлам из списка fileNamesPlots
	/// </summary>
	void Plot() {
		for (string filename : this->fileNamesPlots) {
			//UnitTest<bool> test = UnitTest<bool>();
			//thread thread_obj(&UnitTest::Plot, test, filename);
			//thread_obj.join();
			//Plotter<T>* plotter = new Plotter<T>();
			//thread t(&Plotter<T>::Plot, plotter, filename);
			//t.join();
		}
	}
public:
	string name;
	vector<T> expected;
	vector<T> actual;
	/// <summary>
	/// Цвета в консоли
	/// </summary>
	enum ConsoleColor {
		/// <summary>
		///  0
		/// </summary>
		black,
		/// <summary>
		///  1
		/// </summary>
		dark_blue,
		/// <summary>
		/// 2
		/// </summary>
		dark_green,
		/// <summary>
		/// 3 
		/// </summary>
		dark_cyan,
		/// <summary>
		/// 4
		/// </summary>
		dark_red,
		/// <summary>
		/// 5
		/// </summary>
		dark_magenta,
		/// <summary>
		/// 6
		/// </summary>
		dark_yellow,
		/// <summary>
		/// 7
		/// </summary>
		light_gray,
		/// <summary>
		/// 8
		/// </summary>
		dark_gray,
		/// <summary>
		/// 9
		/// </summary>
		light_blue,
		/// <summary>
		/// 10
		/// </summary>
		light_green,
		/// <summary>
		/// 11
		/// </summary>
		light_cyan,
		/// <summary>
		/// 12
		/// </summary>
		light_red,
		/// <summary>
		/// 13
		/// </summary>
		light_magenta,
		/// <summary>
		/// 14
		/// </summary>
		light_yellow,
		/// <summary>
		/// 15
		/// </summary>
		white
	};
	UnitTest() {
		this->name = this->prefixName + Constants::Strings::undefined;
		this->expected = 0;
	}
	UnitTest(string name = Constants::Strings::undefined, vector<T> expected = {}, bool showProgress = false) {
		this->name = this->prefixName + name;
		this->expected = expected;
		this->showProgress = showProgress;
	}
	virtual void Test() = 0;
	virtual bool Compare(T actual) { return false; };
	virtual bool Compare(vector<T> actual) { return false; };
	/// <summary>
	/// Получает время между двумя тиками в миллисекундах
	/// </summary>
	/// <param name="start">начальный момент времени</param>
	/// <param name="end">конечный момент времени</param>
	/// <returns></returns>
	long long GetDuration(steady_clock::time_point start, steady_clock::time_point end) {
		auto duration = duration_cast<microseconds>(end - start);
		return duration.count() / 1000;
	}
	/// <summary>
	/// Добавляет указанные элементы в actual
	/// </summary>
	/// <param name="items">элементы для добавления</param>
	void Add(vector<T>items) {
		for (T item : items)
			this->actual.push_back(item);
	}
	/// <summary>
	/// Добавляет элементк полученным(actual) значениям
	/// </summary>
	/// <param name="item">элемент для добавления</param>
	void Add(T item) {
		this->actual.push_back(item);
	}
	/// <summary>
	/// Добавляет директорию с данными графика в список
	/// </summary>
	/// <param name="filename">путь до .txt файла</param>
	void AddPlot(string filename) {
		this->fileNamesPlots.push_back(filename);
	}
	/// <summary>
	/// Увчеличивает значение счетчика для прогресса выполнения теста
	/// </summary>
	void IncTicker() {
		this->tickerCurrent++;
	}
	/// <summary>
	/// Задает верхнее значение для счетчика прогресса выполнения
	/// </summary>
	/// <param name="tickerMax">Верхнее значение для счетчика</param>
	void SetTickerMax(int tickerMax) {
		this->tickerMax = tickerMax;
	}
	/// <summary>
	/// Сравнивает ожидаемое с полученным
	/// </summary>
	/// <param name="actual">полученный результат</param>
	/// <param name="expected">ожидаемый результат</param>
	/// <returns>true - если совпадает</returns>
	bool Compare(vector<T> actual, vector<T> expected) {
		if (actual.size() != expected.size())
			return false;
		for (int i = 0; i < actual.size(); i++)
			if (actual[i] != expected[i]) {
				this->incorectIndex = i;
				return false;
			}
		return true;
	}
	/// <summary>
	/// Сравнивает ожидаемое с полученным
	/// Необхожимо занести в actual данные для сравнения!
	/// </summary>
	/// <returns>true - если совпадает</returns>
	bool Compare() {
		return this->Compare(this->actual, this->expected);
	}
	/// <summary>
	/// Запцск теста
	/// </summary>
	void Start() {
		this->SetColor(ConsoleColor::black, ConsoleColor::white);
		cout << this->name << endl;
		this->ResetColor();
		try {
			auto start = high_resolution_clock::now();
			if (this->showProgress) {
				thread progressThread(&UnitTest::PrintProgress, this);
				progressThread.join();
			}
			Test();
			auto stop = high_resolution_clock::now();
			long long ms = this->GetDuration(start, stop);
			if (this->Compare()) {
				this->SetColor(ConsoleColor::white, ConsoleColor::light_green);
				cout << Constants::Strings::Messages::UnitTest::passed << this->prefixMs << ' ' << ms << this->postfixMs << endl;
				this->ResetColor();
				this->Plot();
			}
			else {
				this->SetColor(ConsoleColor::white, ConsoleColor::light_red);
				cout << Constants::Strings::Messages::UnitTest::failed << this->prefixMs << ' ' << ms << this->postfixMs << endl;
				this->ResetColor();
				cout << Constants::Strings::Messages::UnitTest::expected << endl;
				this->Print(this->expected, this->incorectIndex);
				cout << Constants::Strings::Messages::UnitTest::actual << endl;
				this->Print(this->actual, this->incorectIndex);
			}
		}
		catch (exception ex) {
			cout << ex.what() << endl;
		}

	}
};
/// <summary>
/// Стек юнит тестов
/// </summary>
class UnitTests {
private:
	string title;
public:
	UnitTests(string title) {
		this->title = title;
		cout << this->title << endl;
	}
	virtual void Start() = 0;
};

