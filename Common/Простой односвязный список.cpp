// ConsoleApplication12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

class ListItem {
public:
	int data;
	ListItem* next;
	ListItem(int data) {
		this->data = data;
		this->next = NULL;
	}
	ListItem() :ListItem(0) {

	}
	~ListItem() {
		this->next = NULL;
	}
	string ToString() {
		return to_string(this->data);
	}
};

class OWLList {
private:
	ListItem* GetByIndex(int index) {
		ListItem* current = head;
		if (current) {
			int i = 0;
			while (current->next && i < index)
				current = current->next;
			if (i < index)
				current = NULL;
		}
		return current;
	}
	int GetLength() {
		int i = 0;
		if (head) {
			ListItem* current = head;
			while (current->next) {
				current = current->next;
				i++;
			}
		}
		return i;
	}
public:
	ListItem* head;
	OWLList() {
		head = NULL;
	}
	~OWLList() {
		ListItem* current = head;
		while (current)
		{
			ListItem* toDel = current;
			current = current->next;
			delete(toDel);
		}
	}
	void AddBegin(int data) {
		if (!head)
			this->head = new  ListItem(data);
		else {
			ListItem* newHead = new  ListItem(data);
			newHead->next = head;
			this->head = newHead;
		}
	}
	void Add(int data) {
		if (!head)
			this->head = new  ListItem(data);
		else {
			ListItem* current = head;
			while (current->next)
				current = current->next;
			current->next = new  ListItem(data);
		}

	}
	void Add(int data, int index) {
		if (!head)
			this->head = new  ListItem(data);
		else {
			ListItem* current = head;
			int i = 0;
			while (current->next && i < index) {
				current = current->next;
				i++;
			}
			if (i < index)
				throw exception("Некорректный индекс - список слишком мал!");
			ListItem* next = NULL;
			if (current)
				next = current->next;
			current->next = new  ListItem(data);
			current->next->next = next;
		}
	}
	void DeleteBegin() {
		if (head) {
			ListItem* newHead = head->next;
			delete(this->head);
			this->head = newHead;
		}
	}
	void Delete() {
		if (head) {
			ListItem* current = head;
			while (current->next)
				current = current->next;
			ListItem* toDel = current;
			free(toDel);
			current = NULL;
		}
	}
	void Delete(int index) {
		if (head) {
			ListItem* prev = GetByIndex(index - 1);
			ListItem * current = GetByIndex(index);
			if (!prev || !current)
				throw exception("Некорректный индекс - список слишком мал!");
			prev->next = current->next;
			delete(current);
		}
	}
	string ToString() {
		if (head) {
			string str = "";
			ListItem* current = head;
			while (current)
			{
				str += current->ToString() + "->";
				current = current->next;
			}
			return str;
		}
		else {
			return "список пуст!";
		}
	}
};

int GetInt(string message) {
	cout << message << endl;
	int value;
	cin >> value;
	return value;
}

int main()
{
	setlocale(LC_ALL, "rus");
	OWLList list = OWLList();
	for (int i = 0; i < 10; i++)
		list.Add(i);
	while (true)
	{
		try {
			cout << "1. Просмотреть содержимого списка\n"
				<< "2. Добавить элемент в начало\n"
				<< "3. Добавить элемент в конец\n"
				<< "4. Удалить элемент в начале\n"
				<< "5. Удалить элемент в конце\n"
				<< "6. Добавить элемент по индексу\n"
				<< "7. Удалить элемент по индексу\n"
				<< "9. Выйти из программы\n" << endl;
			int menu;
			cin >> menu;
			switch (menu) {
			case 1:
				cout << list.ToString() << endl;
				break;
			case 2:
				list.AddBegin(GetInt("Введите значение"));
				break;
				// ДОБАВИТЬ В КОНЕЦ
			case 3:
				list.Add(GetInt("Введите значение"));
				break;
			case 4:  // УДАЛЕНИЕ В НАЧАЛЕ
				list.DeleteBegin();
				break;

			case 5:  // УДАЛЕНИЕ В КОНЦЕ
				list.Delete();
				break;

			case 6:  // ДОБАВЛЕНИЕ ПО ИНДЕКСУ
				list.Add(GetInt("Введите значение"), GetInt("Введите индекс"));
				break;
			case 7:  // УДАЛЕНИЕ ПО ИНДЕКСУ
				list.Delete(GetInt("Введите индекс"));
				break;
			default:
				cout << "Ошибка! Вы ввели неправильное число\n";
				break;
			}
		}
		catch (exception ex) {
			cout << ex.what() << endl;
		}
		system("pause");
		system("cls");
	}

	// написать освобождения памяти из под списка, do while
	// добавление в конец, после элемента списка с заданым номером
	// удаление с начала списка, с конца, с заданым номером, всего списка
	// работа с файлом 
	return 0;
}