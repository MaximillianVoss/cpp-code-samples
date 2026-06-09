
#pragma once
#include "pch.h"
#include "StrHelper.h"
#include "Node.h"
#include "GraphItem.h"
template<typename T>
///<summary>
/// Ребро графа
///</summary>
class Edge :public GraphItem
{
private:

#pragma region Поля
	/// <summary>
	/// Начальная вершина
	/// </summary>
	Node<T>* from;
	/// <summary>
	/// Конечная вершина
	/// </summary>
	Node<T>* to;
	/// <summary>
	/// Вес ребра
	/// </summary>
	double weight;
	/// <summary>
	/// Является ли ребро двунаправленным
	/// Если нет - напрвавление от начальной вершины к конечной
	/// </summary>
	bool bidirectional;

#pragma endregion

#pragma region Методы

#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы
	/// <summary>
	/// Устанавливает начальную вершину
	/// </summary>
	/// <param name="node">вершина</param>
	void SetFrom(Node<T>* node) {
		this->from = node;
	}
	/// <summary>
	/// Устанавливает конечную вершину
	/// </summary>
	/// <param name="node">вершина</param>
	void SetTo(Node<T>* node) {
		this->to = node;
	}
	/// <summary>
	/// Получает начальную вершину
	/// </summary>
	/// <returns></returns>
	Node<T>* GetFrom() {
		return this->from;
	}
	/// <summary>
	/// Получает конечную вершину
	/// </summary>
	/// <returns></returns>
	Node<T>* GetTo() {
		return this->to;
	}
	/// <summary>
	/// Задает вес ребра
	/// </summary>
	/// <param name="weight">вес ребра</param>
	void SetWight(double weight) {
		this->weight = weight;
	}
	/// <summary>
	/// Получает вес ребра
	/// </summary>
	/// <returns></returns>
	double GetWeight() {
		return this->weight;
	}
	/// <summary>
	/// Получает направленность ребра, true - двунаправленная
	/// </summary>
	/// <returns></returns>
	bool GetDirection() {
		return this->bidirectional;
	}
	/// <summary>
	/// Получает формат ID, true - длинный формат
	/// </summary>
	/// <returns></returns>
	bool GetFormat() {
		return this->longFormat;
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
			ss << "id:" << this->GetId() << endl;
			ss << "from:" << this->from->GetId() << endl;
			ss << "to:" << this->to->GetId() << endl;
			ss << "weight:" << this->weight << endl;
			ss << "isDirect:" << this->bidirectional << endl;
		}
		else if (format == OutputFormat::xml) {
			StrHelper sh;
			ss << "<edge" <<
				" vertex1=" + sh.AddQoute(this->from->GetId()) +
				" vertex2=" + sh.AddQoute(this->to->GetId()) +
				" isDirect=" + sh.AddQoute(sh.BoolToStr(this->bidirectional)) +
				" weight=" + sh.AddQoute(to_string(this->weight)) +
				" useWeight=\"true\"" +
				" hasPair=\"false\"" +
				" id=" + sh.AddQoute(this->from->GetId()) +
				" text=\"\"" +
				" arrayStyleStart=\"\"" +
				" arrayStyleFinish=\"\"" +
				" model_width=\"4\"" +
				" model_type=\"0\"" +
				" model_curvedValue=\"0.1\"></edge>";
		}
		else
			ss << Constants::Strings::undefined;
		return ss.str();
	}
#pragma endregion

#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// Создает вершину с указанными параметрами
	/// </summary>
	/// <param name="from">начальная вершина</param>
	/// <param name="to">конечная вершина</param>
	/// <param name="weight">вес ребра</param>
	/// <param name="bidirectional">явялется ли ребро двунаправленным</param>
	/// <param name="longFormat">Длиный формат, true - ID будут в 32 разрядном представлении</param>
	Edge(string id, Node<T>* from = NULL, Node<T>* to = NULL, double weight = 0, bool bidirectional = true, bool longFormat = true) {
		this->SetId(id, longFormat);
		this->SetFrom(from);
		this->SetTo(to);
		this->SetWight(weight);
		this->bidirectional = bidirectional;
		this->SetDeleted(false);
	}
	/// <summary>
	/// Создает ребро в id undefined, без нод, двунаправленное
	/// </summary>
	Edge() :Edge(Constants::Strings::undefined) {
		this->SetDeleted(false);
	};
	/// <summary>
	/// Деструктор
	/// </summary>
	~Edge() {};
#pragma endregion

#pragma region Операторы
	bool operator > (Edge n) {
		return this->GetId() > n.GetId();
	}
	bool operator < (Edge n) {
		return this->GetId() < n.GetId();
	}
	bool operator == (Edge n) {
		return this->GetId() == n.GetId();
	}
#pragma endregion

#pragma region Обработчики событий

#pragma endregion


};
