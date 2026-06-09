
#pragma once
#include "pch.h"
#include "Node.h"
#include "Edge.h"
#include "BinarySearch.h"
///<summary>
/// Граф
/// построение графа онлайн 
/// https://graphonline.ru/
///</summary>
template<typename T>
class Graph
{
private:

#pragma region Поля
	/// <summary>
	/// счетчик вершин
	/// </summary>
	unsigned int nodesCounter;
	/// <summary>
	/// счетчик ребер
	/// </summary>
	unsigned int edgesCounter;
	/// <summary>
	/// список вершин
	/// </summary>
	vector<Node<T>> nodes;
	/// <summary>
	/// список ребер
	/// </summary>
	vector<Edge<T>> edges;
#pragma endregion

#pragma region Методы
	/// <summary>
	/// Добавляет указанное ребро
	/// </summary>
	/// <param name="edge">Ребро для добавления</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	void Add(Edge<T> edge, bool longFormat = true) {
		this->edgesCounter++;
		edge.SetId(to_string(this->edgesCounter), longFormat);
		this->edges.push_back(edge);
	}
	/// <summary>
	/// Добавлет ребро в граф
	/// </summary>
	/// <param name="from">начальная вершина</param>
	/// <param name="to">конечная вершина</param>
	void Add(Node<T>* from, Node<T>* to, double weight = 0, bool bidirectional = true) {
		if (from && to) {
			Edge<T> edge = Edge<T>(Constants::Strings::undefined, from, to, weight, bidirectional);
			this->Add(edge);
		}
		else {
			throw exception(Constants::Strings::Errors::objectIsNULL);
		}
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="id"></param>
	/// <param name="indexFrom"></param>
	/// <param name="indexTo"></param>
	/// <returns></returns>	
	Node<T>* GetNode(string id, size_t indexFrom, size_t indexTo) {
		/*if (indexFrom <= indexTo) {
			size_t index = indexFrom + (indexFrom + indexTo) / 2;
			string middleId = this->nodes[index].GetId();
			if (middleId == id)
				return this->GetNode(index);
			else if (middleId > id)
			{

			}
			else {

			}

		}
		else
			throw exception(Constants::Strings::Errors::Lists::incorrectIndex);*/
		return NULL;
	}
#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Добавлет вершину с указанными данными
	/// </summary>
	/// <param name="data">данные</param>
	void Add(T data, bool longFormat = true) {
		this->Add(Node<T>(Constants::Strings::undefined, data), longFormat);
	}
	/// <summary>
	/// Добавляет указанную вершину
	/// </summary>
	/// <param name="node">вершина для добавления</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	void Add(Node<T> node, bool longFormat = true)
	{
		this->nodesCounter++;
		node.SetId(to_string(this->nodesCounter), longFormat);
		this->nodes.push_back(node);
		//Sorts<Node<T>> sorts;
		//this->nodes = sorts.QuickSort(this->nodes);
	}
	/// <summary>
	/// Соединяет две вершины ребром
	/// </summary>
	/// <param name="idFrom">id исходной вершины</param>
	/// <param name="idTo">id конечной вершины</param>
	void Connect(string idFrom, string idTo, double weight = 0, bool bidirectional = true) {
		if (idFrom.length() < 32)
			idFrom = GraphItem(idFrom).GetId();
		if (idTo.length() < 32)
			idTo = GraphItem(idTo).GetId();
		Node<T>* from = this->GetNode(idFrom);
		Node<T>* to = this->GetNode(idTo);
		if (from && to) {
			this->Add(from, to, weight, bidirectional);
		}
		else {
			throw exception(Constants::Strings::Errors::Lists::notFound);
		}
	}
	/// <summary>
	/// Соединяет две вершины ребром
	/// </summary>
	/// <param name="indexFrom">индекс начальной вершины</param>
	/// <param name="indexTo">индекс конечной вершины</param>
	void Connect(size_t indexFrom, size_t indexTo, double weight = 0, bool bidirectional = true) {
		Node<T>* from = this->GetNode(indexFrom);
		Node<T>* to = this->GetNode(indexTo);
		if (from && to) {
			this->Add(from, to, weight, bidirectional);
		}
		else {
			throw exception(Constants::Strings::Errors::Lists::notFound);
		}
	}
	/// <summary>
	/// Удаляет вершину графа по индексу
	/// </summary>
	/// <param name="nodeIndex">индекс вершины</param>
	void DeleteNode(size_t nodeIndex) {
		Node<T>* node = this->GetNode(nodeIndex);
		if (node) {
			this->Disconnect(nodeIndex);
			node->SetDeleted(true);
			//this->nodes.erase(this->nodes.begin() + nodeIndex);
		}
	}
	/// <summary>
	/// Удаляет вершину по ID
	/// </summary>
	/// <param name="nodeId">ID вершины</param>
	void DeleteNode(string nodeId) {
		BinarySearch<Node<T>> bs;
		int index = bs.Find(this->nodes, Node<T>(nodeId));
		if (index != -1) {
			//this->Disconnect(index);
			this->DeleteNode(index);
		}
	}
	/// <summary>
	/// Удаляет ребро графа по индексу
	/// </summary>
	/// <param name="edgeIndex"></param>
	void DeleteEdge(size_t edgeIndex) {
		if (this->GetEdge(edgeIndex))
			this->edges.erase(this->edges.begin() + edgeIndex);
	}
	/// <summary>
	///  Удаляет вершину графа по индексу
	/// </summary>
	/// <param name="edgeId"></param>
	void DeleteEdge(string edgeId) {
		BinarySearch<Edge<T>> bs;
		int index = bs.Find(this->edges, Edge<T>(edgeId));
		if (index != -1)
			DeleteEdge(index);
	}
	/// <summary>
	/// Удаляет все связи для указанной веришны
	/// </summary>
	/// <param name="nodeId">ID вершины</param>
	void Disconnect(string nodeId) {
		Node<T>* node = this->GetNode(nodeId);
		if (node) {
			if (node->GetIdFormat())
				nodeId = GraphItem(nodeId).GetId();
			for (int i = 0; i < this->edges.size(); i++)
			{
				if (this->edges[i].GetDirection())
				{
					if (this->edges[i].GetTo()->GetId() == nodeId || this->edges[i].GetFrom()->GetId() == nodeId)
						this->DeleteEdge(i--);
				}
				else
					if (this->edges[i].GetFrom()->GetId() == nodeId)
						this->DeleteEdge(i--);
			}
		}
	}
	/// <summary>
	/// Удаляет все связи для указанной веришны
	/// </summary>
	/// <param name="nodeIndex">индекс вершины</param>
	void Disconnect(size_t nodeIndex) {
		if (this->GetNode(nodeIndex))
			this->Disconnect(this->nodes[nodeIndex].GetId());
	}
	/// <summary>
	/// Удаляет связимежду указанными вершинами
	/// </summary>
	/// <param name="idFrom">ID начальной вершины</param>
	/// <param name="idTo">ID конечной вершины</param>
	/// <param name="longFormat">преобразовывать ID в параметрах в длинный формат</param>
	void Disconnect(string idFrom, string idTo, bool longFormat = true) {
		if (longFormat)
		{
			idFrom = GraphItem(idFrom).GetId();
			idTo = GraphItem(idTo).GetId();
		}
		for (int i = 0; i < this->edges.size(); i++) {
			if (this->edges[i].GetFrom()->GetId() == idFrom && this->edges[i].GetTo()->GetId() == idTo) {
				this->DeleteEdge(i);
				break;
			}
		}
	}
	/// <summary>
	/// Удаляет связимежду указанными вершинами
	/// </summary>
	/// <param name="fromIndex">индекс начальной вершины</param>
	/// <param name="toIndex">индекс конечной вершины</param>
	void Disconnect(size_t fromIndex, size_t toIndex) {
		Node<T>* nodeFrom = this->GetNode(fromIndex);
		Node<T>* nodeTo = this->GetNode(toIndex);
		if (nodeFrom && nodeTo)
			Disconnect(nodeFrom->GetId(), nodeTo->GetId());
	}
	/// <summary>
	/// Возвращает вершины графа
	/// </summary>
	/// <param name="getAll">true -вернуть все вершины, включая удаленные</param>
	/// <returns></returns>
	vector<Node<T>>GetNodes(bool getAll = true) {
		vector<Node<T>> result;
		for (Node<T> node : this->nodes)
			if (!getAll && !node.GetDeleted() || getAll)
				result.push_back(node);
		return result;
	}
	/// <summary>
	/// Получает данные из всех нод
	/// </summary>
	/// <param name="getAll">true -вернуть все вершины, включая удаленные</param>
	/// <returns></returns>
	vector<T> GetNodesValues(bool getAll = true) {
		vector<Node<T>>nodes = this->GetNodes(getAll);
		vector<T>data;
		for (Node <T> node : nodes)
			data.push_back(node.GetData());
		return data;
	}
	/// <summary>
	/// Получает вершину по id
	/// </summary>
	/// <param name="id">id</param>
	/// <returns></returns>
	Node<T>* GetNode(string id) {
		BinarySearch<Node<T>> bs;
		int index = bs.Find(this->nodes, Node<T>(id));
		if (index == -1)
			return NULL;
		else
			return &nodes[index];
	}
	/// <summary>
	/// Получает вершину по индексу
	/// </summary>
	/// <param name="index">индекс</param>
	/// <returns></returns>
	Node<T>* GetNode(size_t index) {
		if (index >= 0 && index < this->nodes.size())
			return &this->nodes[index];
		return NULL;
	}
	/// <summary>
	/// Получает ребро по id
	/// </summary>
	/// <param name="id">id</param>
	/// <returns></returns>
	Edge<T>* GetEdge(string id) {
		BinarySearch<Edge<T>> bs;
		int index = bs.Find(this->edges, Edge<T>(id));
		if (index == -1)
			return NULL;
		else
			return &edges[index];
	}
	/// <summary>
	/// Получает ребро по индексу
	/// </summary>
	/// <param name="index">индекс</param>
	/// <returns></returns>
	Edge<T>* GetEdge(size_t index) {
		if (index >= 0 && index < this->edges.size())
			return &this->edges[index];
		return NULL;
	}
	/// <summary>
	/// Получает количество врершин в графе
	/// </summary>
	/// <returns></returns>
	size_t GetNodesCount() {
		return this->nodes.size();
	}
	/// <summary>
	/// Получает количество ребер в графе
	/// </summary>
	/// <returns></returns>
	size_t GetEdgesCount() {
		return this->edges.size();
	}
	/// <summary>
	/// Заменяет вершину по указанному ID
	/// </summary>
	/// <param name="id">ID вершины</param>
	/// <param name="node">новая вершина, ID не меняется</param>
	void Set(string id, Node<T> node) {
		Node<T>* _node = this->GetNode(id);
		if (_node)
			_node = Node<T>(id, node.GetData());
	}
	/// <summary>
	/// Заменяет ребро по указанному ID
	/// </summary>
	/// <param name="id">ID ребра</param>
	/// <param name="edge">новое ребро,ID не меняется</param>
	void Set(string id, Edge<T>edge) {
		Edge<T>* _edge = this->GetEdge(id);
		if (_edge) {
			_edge = Edge<T>(id, edge.GetFrom(), edge.GetTo(), edge.GetWeight(), edge.GetDirection().edge.GetFormat());
		}
	}
	/// <summary>
	/// Поиск значения в графе
	/// </summary>
	/// <param name="data">значение</param>
	/// <returns></returns>
	Node<T>* Find(T data) {
		for (int i = 0; i < this->nodes.size(); i++)
			if (data == this->nodes[i].GetData())
				return &this->nodes[i];
		return NULL;
	}
	/// <summary>
	/// Преборазует объект в строку
	/// Для просмотра визуально:https://graphonline.ru/
	/// </summary>
	/// </summary>
	/// <param name="format">формат вывода</param>
	/// <returns></returns>
	string ToString(OutputFormat format = OutputFormat::fields) {
		stringstream ss;
		if (format == OutputFormat::fields) {
			ss << "nodes count:" << this->nodesCounter << endl;
			ss << "edges count:" << this->edgesCounter << endl;
			for (Node<T> node : this->nodes)
				ss << node.ToString(format) << endl;
			for (Edge<T>edge : edges)
				ss << edge.ToString(format) << endl;
		}
		else if (format == OutputFormat::xml) {
			ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
			ss << "<graphml>" << endl;
			ss << "<graph id=\"Graph\" uidGraph=\"" << this->nodesCounter + 1 << "\" uidEdge=\"10001\">" << endl;
			ss << "<nodes>" << endl;
			size_t startX = 50;
			size_t startY = 50;
			size_t dx = 100;
			size_t dy = 100;
			size_t maxWidth = 1024;
			for (Node<T> node : this->nodes)
			{
				ss << node.ToString(format, startX, startY) << endl;
				startX += dx;
				if (startX > maxWidth)
					startY += dy;
			}
			ss << "</nodes>" << endl;
			ss << "<edges>" << endl;
			for (Edge<T>edge : edges)
			{
				ss << edge.ToString(format) << endl;
			}
			ss << "</edges>" << endl;
			ss << "</graph>" << endl;
			ss << "</graphml>" << endl;
		}
		else
			ss << Constants::Strings::undefined;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion

	Graph() {
		this->edgesCounter = 0;
		this->nodesCounter = 0;
	};
	~Graph() {};

};
