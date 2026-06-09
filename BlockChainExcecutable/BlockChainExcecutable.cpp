// BlockChainExcecutable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <pch.h>
#include "../Crypto/BlockChain.h"
#include <SObject.h>
#include <Plotter.h>
#include <Converter.h>
#include <IO.h>
#include <StrHelper.h>
#include <UnitTest.h>

#pragma region Тестовые параметры
//'{fieldX:Число клиентов;fieldY:Число голосований с несколькими победителями;startX:0;endX:0;stepX:0;count:0;outputFileName:C:\\commonPlot.txt;}'
#pragma endregion

#pragma region Названия полей объекта с параметрами
class Fields {
public:
	class Names {
	public:
		class Axes {
		public:
			static constexpr const char* x = "fieldNameX";
			static constexpr const char* y = "fieldNameY";
		};
		class Values {
		public:
			static constexpr const char* start = "valueStart";
			static constexpr const char* end = "valueEnd";
			static constexpr const char* step = "valueStep";
		};
		class Count {
		public:
			static constexpr const char* experiments = "countExperiments";
			static constexpr const char* clients = "countClients";
			static constexpr const char* tokens = "countTokens";
			static constexpr const char* votesPercent = "countVotesPercent";
		};
		class Files {
		public:
			static constexpr const char* output = "outputFileName";
		};
		class Flags {
		public:
			static constexpr const char* isAvg = "isFieldAvgY";
			static constexpr const char* isChangable = "isFieldChangedX";
		};
	};
	class Values {
	public:
		class Axes {
		public:
			class X {
			public:
				static constexpr const char* clientsCount = "Число клиентов";
				static constexpr const char* tokensCount = "Число монет";
				static constexpr const char* votePercent = "Порог голосования(%)";
				static constexpr const char* clientID = "ID учатсника";
			};
			class Y {
			public:
				static constexpr const char* failedCount = "Число проваленных голосований";
				static constexpr const char* failedMult = "Число голосований с несколькими победителями";
				static constexpr const char* tokensCount = "Число монет";
				static constexpr const char* timeCount = "Время(мс)";
			};
		};
	};
};
#pragma endregion

#pragma region Базовый класс для тестов
///<summary>
/// Базовый тест для Блокчейна
///</summary>
class BlockChainBaseTest :public UnitTest<string> {
public:
#pragma region Поля
	SObject<string> paramsObj = SObject<string>();
#pragma endregion

#pragma region Методы
	BlockChainBaseTest(string title, SObject<string>paramsObj, vector<string>values) :UnitTest(title, values) {
		this->paramsObj = this->GetParams(paramsObj);
	}
	BlockChain GenerateBlockchain(int clientsCount, int tokensCount, float votePercent = 0.51) {
		BlockChain bc = BlockChain();
		vector<Client*> clients;
		for (int i = 0; i < clientsCount; i++) {
			Client* client = bc.Add(to_string(i));
			clients.push_back(client);
			bc.Connect(client->GetId(), to_string(i));
			for (int j = 0; j < tokensCount; j++)
				bc.GenerateBlock(clients[i]->GetId());
		}
		bc.SetVotesPercent(votePercent);
		//bc.CalcLedger();
		return bc;
	}
	SObject<string>GetParams(SObject<string>paramsObj) {
		string convertedPath = Converter<string>::Paths().ToString(Converter<string>::Lists().Convert(paramsObj.Get(Fields::Names::Files::output)->value));
		paramsObj.Set(Fields::Names::Files::output, convertedPath);
		StrHelper strh = StrHelper();
		string _fieldXName = strh.Replace(paramsObj.Get(Fields::Names::Axes::x)->value, "_", " ");
		string _fieldYName = strh.Replace(paramsObj.Get(Fields::Names::Axes::y)->value, "_", " ");
		paramsObj.Set(Fields::Names::Axes::x, _fieldXName);
		paramsObj.Set(Fields::Names::Axes::y, _fieldYName);
		return paramsObj;
	}
	virtual void InternalTest(
		string titleX,
		string titleY,
		float initialClients,
		float initialCoins,
		float votesPercentInitial,
		float startValue,
		float step,
		float finalValue,
		bool isFieldXChanged,
		bool isFieldYAvg,
		size_t testsCount,
		size_t plotGoup = 1) = 0;
	void Test() override {
		cout << paramsObj.ToString(true) << endl;
		InternalTest(
			paramsObj.Get(Fields::Names::Axes::x)->value,
			paramsObj.Get(Fields::Names::Axes::y)->value,
			paramsObj.GetFloat(Fields::Names::Count::clients),
			paramsObj.GetFloat(Fields::Names::Count::tokens),
			paramsObj.GetFloat(Fields::Names::Count::votesPercent) / 100.0,
			paramsObj.GetFloat(Fields::Names::Values::start),
			paramsObj.GetFloat(Fields::Names::Values::step),
			paramsObj.GetFloat(Fields::Names::Values::end),
			paramsObj.GetBool(Fields::Names::Flags::isChangable),
			paramsObj.GetBool(Fields::Names::Flags::isAvg),
			paramsObj.GetInt(Fields::Names::Count::experiments)
		);
		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
#pragma endregion

};
#pragma endregion

#pragma region Тесты

#pragma region Тест на изменения числа монет
///<summary>
/// Тест на изменения числа монет
///</summary>
class CoinsTest :public BlockChainBaseTest {

public:
	CoinsTest(SObject<string>paramsObj, vector<string>values = {}) :BlockChainBaseTest("Тест на изменение числа монет", paramsObj, values) {

	}
	void InternalTest(
		string titleX,
		string titleY,
		float initialClients,
		float initialTokens,
		float initialVotesPercent,
		float startValue,
		float step,
		float finalValue,
		bool isFieldXChanged,
		bool isFieldYAvg,
		size_t testsCount,
		size_t plotGoup = 1) override
	{
		BlockChain bc = GenerateBlockchain(initialClients, 0, initialVotesPercent);
		Plotter<float> plotData("Распределение токенов по участникам");
		DataPack<float> dp = DataPack<float>(
			"Распределение токенов по участникам",
			titleX,
			titleY,
			plotGoup
			);
		if (isFieldYAvg) {
			vector<Client>clients;
			for (int i = 0; i < testsCount; i++) {
				bc = GenerateBlockchain(initialClients, 0, initialVotesPercent);
				if (i == 0)
					clients = bc.GetClients();
				for (int j = 0; j < initialTokens; j++)
					bc.GenerateBlock(true);
				vector<Client>cleintsTemp = bc.GetClients();
				for (int i = 0; i < clients.size(); i++)
					clients[i].AddTokens(cleintsTemp[i].GetTokensCount());
			}
			for (int i = 0; i < clients.size(); i++)
				dp.AddPoint(i + 1, (float)clients[i].GetTokensCount());
			dp.SetYTitle("Среднее " + dp.GetYTitle());
			plotData.Add(dp);
		}
		else {
			for (int j = 0; j < initialTokens; j++)
				bc.GenerateBlock(true);
			vector<Client>clients = bc.GetClients();
			for (int i = 0; i < clients.size(); i++)
				dp.AddPoint(i + 1, clients[i].GetTokensCount());
			plotData.Add(dp);
		}
		IO().WriteLines(this->paramsObj.Get(Fields::Names::Files::output)->value, { plotData.ToString() });
	}
};
#pragma endregion

#pragma region Тест на изменение числа клиентов
///<summary>
/// Тест на изменение числа клиентов
///</summary>
class ClientsTest :public BlockChainBaseTest {
public:
	ClientsTest(SObject<string>paramsObj, vector<string>values = {}) :BlockChainBaseTest("Тест на изменение числа клиентов", paramsObj, values) {

	}
	void InternalTest(
		string titleX,
		string titleY,
		float initialClients,
		float initialTokens,
		float initialVotesPercent,
		float startValue,
		float step,
		float finalValue,
		bool isFieldXChanged,
		bool isFieldYAvg,
		size_t testsCount,
		size_t plotGoup = 1) override {
		Plotter<int> plotData("Результаты голосований при изменении числа клиентов");
		DataPack<int> dp = DataPack<int>(
			"Зависимость проваленных голосований от числа клиентов",
			titleX,
			titleY,
			plotGoup
			);
		for (startValue; startValue < finalValue; startValue += step) {
			BlockChain bc = GenerateBlockchain(startValue, initialTokens, initialVotesPercent);
			auto start = high_resolution_clock::now();
			for (int j = 0; j < testsCount; j++)
				bc.GenerateBlock(true);
			auto stop = high_resolution_clock::now();

			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedCount)
				dp.AddPoint(startValue, bc.GetCounterVotingFailed());
			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedMult)
				dp.AddPoint(startValue, bc.GetCounterVotingMultWinners());
			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::timeCount)
				dp.AddPoint(startValue, (float)this->GetDuration(start, stop) / (float)testsCount);
		}
		plotData.Add(dp);
		IO().WriteLines(this->paramsObj.Get(Fields::Names::Files::output)->value, { plotData.ToString() });
	}
};
#pragma endregion

#pragma region Тест на изменение порога голосования
///<summary>
/// Тест на изменение порога голосования
///</summary>
class VotingPercentTest :public BlockChainBaseTest {
public:
	VotingPercentTest(SObject<string>paramsObj, vector<string>values = {}) :
		BlockChainBaseTest("Тест на изменение порога голосования", paramsObj, values) {

	}
	void InternalTest(
		string titleX,
		string titleY,
		float initialClients,
		float initialTokens,
		float initialVotesPercent,
		float startValue,
		float step,
		float finalValue,
		bool isFieldXChanged,
		bool isFieldYAvg,
		size_t testsCount,
		size_t plotGoup = 1) override {
		Plotter<int> plotData("Результаты голосований при изменении порога голосования");
		DataPack<int> dp = DataPack<int>(
			"Зависимость проваленных голосований от порога голосования",
			titleX,
			titleY,
			plotGoup
			);
		for (startValue; startValue < finalValue; startValue += step) {
			BlockChain bc = GenerateBlockchain(initialClients, initialTokens, startValue / 100.0);
			auto start = high_resolution_clock::now();
			for (int j = 0; j < testsCount; j++)
				bc.GenerateBlock(true);
			auto stop = high_resolution_clock::now();
			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedCount)
				dp.AddPoint(startValue, bc.GetCounterVotingFailed());
			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedMult)
				dp.AddPoint(startValue, bc.GetCounterVotingMultWinners());
			if (paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::timeCount)
				dp.AddPoint(startValue, (float)this->GetDuration(start, stop) / (float)testsCount);
		}
		plotData.Add(dp);
		IO().WriteLines(this->paramsObj.Get(Fields::Names::Files::output)->value, { plotData.ToString() });
	}

};
#pragma endregion

#pragma endregion

#pragma region Методы
void PrintArgs(int argc, char* argv[]) {
	cout << "You have entered " << argc
		<< " arguments:" << "\n";
	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";
}
//SObject<string> GetArgs(char* argv[]) {
//
//}
#pragma endregion


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	//PrintArgs(argc, argv);
	if (argc > 1) {

		SObject<string> paramsObj = SObject<string>(argv[1]);
		StrHelper strh = StrHelper();
		string _fieldXName = strh.Replace(paramsObj.Get(Fields::Names::Axes::x)->value, "_", " ");
		string _fieldYName = strh.Replace(paramsObj.Get(Fields::Names::Axes::y)->value, "_", " ");
		paramsObj.Set(Fields::Names::Axes::x, _fieldXName);
		paramsObj.Set(Fields::Names::Axes::y, _fieldYName);
#pragma region Тест на изменение числа монет
		if (paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::clientID
			&&
			paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::tokensCount)
			CoinsTest(SObject<string>(argv[1])).Start();
#pragma endregion

#pragma region Тест на изменение числа клиентов
		if (
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::clientsCount
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedCount)
			||
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::clientsCount
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedMult)
			||
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::clientsCount
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::timeCount)
			)
			ClientsTest(SObject<string>(argv[1])).Start();
#pragma endregion


#pragma region Тест на изменение порога голосования
		if (
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::votePercent
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedCount)
			||
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::votePercent
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::failedMult)
			||
			(paramsObj.Get(Fields::Names::Axes::x)->value == Fields::Values::Axes::X::votePercent
				&&
				paramsObj.Get(Fields::Names::Axes::y)->value == Fields::Values::Axes::Y::timeCount)
			)
			VotingPercentTest(SObject<string>(argv[1])).Start();
#pragma endregion

	}

	return 0;
}
