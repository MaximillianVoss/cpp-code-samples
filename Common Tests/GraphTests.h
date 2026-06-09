#pragma once
#include "UnitTest.h"
#include "Graph.h"
#pragma region Тесты
#pragma region Добавление вершин
///<summary>
/// Добавление вершины
///</summary>
class GraphAddNodeTest :public UnitTest<int> {
public:
	GraphAddNodeTest(vector<int>values) :UnitTest("Добавление вершин", values) {

	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 0; i < 10; i++)
			g.Add(i);
		this->Add(g.GetNodesCount());
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Удаление вершин
///<summary>
/// Удаление вершин
///</summary>
class GraphDeleteNodeTest :public UnitTest<string> {
public:
	GraphDeleteNodeTest(vector<string>values) :UnitTest("Удаление вершин", values) {

	}
	void Test() override {
		//TODO: неправильно удаляет вершину!
		//решение: скорее всего лучше ставить bool флажок "удалено" на вершине
		//удаление из массива смещает все вершины и указатели указывают не на те вершины, ребра сьезжают
		Graph<int> g = Graph<int>();
		for (int i = 1; i <= 10; i++)
			g.Add(i);
		g.Connect("1", "2");
		g.Connect("1", "3");
		g.Connect("1", "4");
		g.Connect("2", "5");
		g.Connect("2", "6");
		g.DeleteNode("1");
		this->Add(g.GetEdge(0)->GetFrom()->GetId());
		this->Add(g.GetEdge(0)->GetTo()->GetId());
		this->Add(g.GetEdge(1)->GetFrom()->GetId());
		this->Add(g.GetEdge(1)->GetTo()->GetId());
		this->Add(to_string(g.GetNodes().size()));
		this->Add(to_string(g.GetNodes(false).size()));
		this->Add(to_string(g.GetEdgesCount()));
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Добавление ребер
///<summary>
/// Добавление ребер
///</summary>
class GraphAddEdgeTest :public UnitTest<int> {
public:
	GraphAddEdgeTest(vector<int>values) :UnitTest("Добавление ребер", values) {

	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 0; i < 9; i++)
			g.Add(i);
		for (int i = 0; i < 8; i++)
			g.Connect(i, i + 1);
		this->Add(g.GetEdgesCount());
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Удаление ребер
///<summary>
/// Удаление ребер
///</summary>
class GraphDeleteEdgeTest :public UnitTest<string> {
public:
	GraphDeleteEdgeTest(vector<string>values) :UnitTest("Удаление ребер", values) {
	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 0; i < 10; i++)
			g.Add(i);
		for (int i = 1; i < 10; i++)
			g.Connect(0, i);
		for (int i = 1; i < 5; i++)
			g.DeleteEdge(to_string(i));
		for (int i = 5; i < 10; i++)
		{
			if (g.GetEdge(to_string(i)))
				this->Add(g.GetEdge(to_string(i))->GetId());
			else
				this->Add("NULL");
		}
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Поиск вершины
///<summary>
/// Поиск вершины
///</summary>
class GraphNodeSearchTest :public UnitTest<string> {
public:
	GraphNodeSearchTest(vector<string>values) :UnitTest("Поиск вершины", values) {

	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 0; i < 10; i++)
			g.Add(i);
		this->Add({
			g.GetNode("4")->GetId(),
			g.GetNode("5")->GetId(),
			g.GetNode("6")->GetId()
			});
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Соединение вершин
///<summary>
/// Соединение вершин
///</summary>
class GraphConnectNodesTest :public UnitTest<string> {
public:
	GraphConnectNodesTest(vector<string>values) :UnitTest("Соединение вершин", values) {

	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 1; i <= 10; i++)
			g.Add(i);
		g.Connect("1", "2");
		g.Connect("3", "4");
		g.Connect("5", "6");
		g.Connect("9", "10");
		IO io;
		io.WriteLines("GraphConnectNodesTest.graphml", { g.ToString(OutputFormat::xml) });
		for (int i = 0; i < g.GetEdgesCount(); i++)
			this->Add(g.GetEdge(i)->ToString());
		for (int i = 0; i < g.GetEdgesCount(); i++)
			this->Add(g.GetEdge(i)->ToString(OutputFormat::xml));
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Отсоединение вершин
///<summary>
/// Отсоединение вершин
///</summary>
class GraphDisconnectNodeTest :public UnitTest<string> {
public:
	GraphDisconnectNodeTest(vector<string>values) :UnitTest("Отсоединение вершин", values) {

	}
	void Test() override {
		Graph<int> g = Graph<int>();
		for (int i = 1; i <= 10; i++)
			g.Add(i);
		g.Connect("1", "2");
		g.Connect("1", "3");
		g.Connect("1", "4");
		g.Connect("2", "5");
		g.Connect("2", "6");
		g.Disconnect("1");
		g.Disconnect("2", "6");
		this->Add(g.GetEdge(0)->GetFrom()->GetId());
		this->Add(g.GetEdge(0)->GetTo()->GetId());
		this->Add(to_string(g.GetEdgesCount()));
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion

#pragma region Вывод графа
///<summary>
/// Вывод графа
///</summary>
class GraphOutputTest :public UnitTest<string> {
public:
	GraphOutputTest(vector<string>values) :UnitTest("Вывод графа", values) {

	}
	void Test() override {

		//this->Add(vector<string>items) для добавления результатов
		//сравнение результатов в конце 
		UnitTest::Compare();
	}
};
#pragma endregion
#pragma endregion
#pragma region Тест графа
///<summary>
/// Тест графа
///</summary>
class GraphTests :UnitTests {
public:
	GraphTests() : UnitTests("Тест графа") {}
	void Start()override {
		//Запуск одного теста: TestsClassName(vector<type>items).Start();
		GraphAddNodeTest({ 10 }).Start();
		GraphNodeSearchTest({ GraphItem("4").GetId(),GraphItem("5").GetId(),GraphItem("6").GetId() }).Start();
		GraphAddEdgeTest({ 8 }).Start();
		GraphDeleteNodeTest({ GraphItem("2").GetId(),GraphItem("5").GetId(),GraphItem("2").GetId(),GraphItem("6").GetId(),"10","9","2" }).Start();
		GraphDeleteEdgeTest({ GraphItem("5").GetId(),GraphItem("6").GetId(),GraphItem("7").GetId(),GraphItem("8").GetId(),GraphItem("9").GetId() }).Start();
		GraphConnectNodesTest({
			"id:00000000000000000000000000000001\nfrom:00000000000000000000000000000001\nto:00000000000000000000000000000002\nweight:0\nisDirect:1\n",
			"id:00000000000000000000000000000002\nfrom:00000000000000000000000000000003\nto:00000000000000000000000000000004\nweight:0\nisDirect:1\n",
			"id:00000000000000000000000000000003\nfrom:00000000000000000000000000000005\nto:00000000000000000000000000000006\nweight:0\nisDirect:1\n",
			"id:00000000000000000000000000000004\nfrom:00000000000000000000000000000009\nto:00000000000000000000000000000010\nweight:0\nisDirect:1\n",
			"<edge vertex1=\"00000000000000000000000000000001\" vertex2=\"00000000000000000000000000000002\" isDirect=\"true\" weight=\"0.000000\" useWeight=\"true\" hasPair=\"false\" id=\"00000000000000000000000000000001\" text=\"\" arrayStyleStart=\"\" arrayStyleFinish=\"\" model_width=\"4\" model_type=\"0\" model_curvedValue=\"0.1\"></edge>",
			"<edge vertex1=\"00000000000000000000000000000003\" vertex2=\"00000000000000000000000000000004\" isDirect=\"true\" weight=\"0.000000\" useWeight=\"true\" hasPair=\"false\" id=\"00000000000000000000000000000003\" text=\"\" arrayStyleStart=\"\" arrayStyleFinish=\"\" model_width=\"4\" model_type=\"0\" model_curvedValue=\"0.1\"></edge>",
			"<edge vertex1=\"00000000000000000000000000000005\" vertex2=\"00000000000000000000000000000006\" isDirect=\"true\" weight=\"0.000000\" useWeight=\"true\" hasPair=\"false\" id=\"00000000000000000000000000000005\" text=\"\" arrayStyleStart=\"\" arrayStyleFinish=\"\" model_width=\"4\" model_type=\"0\" model_curvedValue=\"0.1\"></edge>",
			"<edge vertex1=\"00000000000000000000000000000009\" vertex2=\"00000000000000000000000000000010\" isDirect=\"true\" weight=\"0.000000\" useWeight=\"true\" hasPair=\"false\" id=\"00000000000000000000000000000009\" text=\"\" arrayStyleStart=\"\" arrayStyleFinish=\"\" model_width=\"4\" model_type=\"0\" model_curvedValue=\"0.1\"></edge>"
			}).Start();
		GraphDisconnectNodeTest({ GraphItem("2").GetId(),GraphItem("5").GetId(),"1" }).Start();
	}
};
#pragma endregion