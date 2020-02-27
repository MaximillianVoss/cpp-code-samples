#include "stdafx.h"
//
//class Game {
//private:
//	int field_size;
//	int turns;
//	vector<vector<char>> field;
//
//public:
//	Game(int n = 3) {
//		field_size = n;
//		field.resize(n);
//		turns = 0;
//		for (int i = 0; i < field_size; i++) {
//			field[i].resize(n);
//			for (int j = 0; j < field_size; j++) {
//				field[i][j] = '.';
//			}
//		}
//	}
//
//	void showField() {
//		system("cls");
//		cout << " ";
//		for (int i = 0; i < field_size; i++) {
//			if (i < 10 && field_size > 9) {
//				cout << " ";
//			}
//			cout << " " << i + 1;
//		}
//
//		cout << endl;
//		for (int i = 0; i < field_size; i++) {
//			cout << i + 1;
//			for (int j = 0; j < field_size; j++) {
//				if (field_size > 9 && (!(i >= 9) || j != 0)) {
//					cout << " ";
//				}
//				cout << " " << field[i][j];
//			}
//			cout << endl;
//		}
//	}
//
//	void setX() {
//		cout << "Введите координаты : " << endl;
//		int x, y;
//		cin >> x;
//		cin >> y;
//		--x;
//		--y;
//		if (x < 0 || y < 0 || y >= field_size || x >= field_size || field[y][x] != '.') {
//			showField();
//			cout << "Координаты введены неверно" << endl;
//			setX();
//		}
//		else {
//			field[y][x] = 'X';
//			showField();
//			++turns;
//		}
//	}
//
//	void setO() {
//		bool b = false;
//
//		for (int i = 0; i < field_size; i++) {
//			int x = 0;
//			for (int j = 0; j < field_size; j++) {
//				if (field[i][j] == 'X') {
//					++x;
//				}
//			}
//			if (x == field_size - 1) {
//				for (int j = 0; j < field_size; j++) {
//					if (field[i][j] == '.') {
//						field[i][j] = 'O';
//						b = true;
//						++turns;
//						break;
//					}
//				}
//			}
//		}
//
//		if (!b) {
//			for (int i = 0; i < field_size; i++) {
//				int x = 0;
//				for (int j = 0; j < field_size; j++) {
//					if (field[j][i] == 'X') {
//						++x;
//					}
//				}
//				if (x == field_size - 1) {
//					for (int j = 0; j < field_size; j++) {
//						if (field[j][i] == '.') {
//							field[j][i] = 'O';
//							b = true;
//							++turns;
//							break;
//						}
//					}
//				}
//			}
//		}
//
//		if (!b) {
//			int x = 0;
//			for (int i = 0; i < field_size; i++) {
//				if (field[i][i] == 'X') {
//					++x;
//				}
//			}
//			if (x == field_size - 1) {
//				for (int i = 0; i < field_size; i++) {
//					if (field[i][i] == '.') {
//						field[i][i] = 'O';
//						b = true;
//						++turns;
//						break;
//					}
//				}
//			}
//		}
//
//		if (!b) {
//			int x = 0;
//			for (int i = 0; i < field_size; i++) {
//				if (field[i][field_size - i - 1] == 'X') {
//					++x;
//				}
//			}
//			if (x == field_size - 1) {
//				for (int i = 0; i < field_size; i++) {
//					if (field[i][field_size - i - 1] == '.') {
//						field[i][field_size - i - 1] = 'O';
//						b = true;
//						++turns;
//						break;
//					}
//				}
//			}
//		}
//
//		if (!b) {
//			int x, y;
//			srand(time(NULL));
//			x = rand() % field_size;
//			y = rand() % field_size;
//			while (field[y][x] != '.') {
//				srand(time(NULL));
//				x = rand() % field_size;
//				y = rand() % field_size;
//			}
//			field[y][x] = 'O';
//			++turns;
//		}
//		showField();
//	}
//
//	void initGame() {
//		bool b = false;
//		showField();
//		while (turns != field_size * field_size && !b) {
//			setX();
//			b = checkWin();
//			if (!b) {
//				setO();
//				b = checkWin();
//			}
//		}
//	}
//
//	bool checkWin() {
//		if (turns >= field_size) {
//			if (turns == field_size * field_size) {
//				cout << "Ничья" << endl;
//				return true;
//			}
//			if (checkFirstDiagonal()) {
//				return true;
//			}
//			else if (checkSecondDiagonal()) {
//				return true;
//			}
//			else {
//				bool b = false;
//				for (int i = 0; i < field_size; i++) {
//					if (checkLine(i)) {
//						b = true;
//						return true;
//					}
//					if (checkColumn(i)) {
//						b = true;
//						return true;
//					}
//				}
//			}
//		}
//		else {
//			return false;
//		}
//		return false;
//	}
//
//	bool checkLine(int n) {
//		bool b = true;
//		for (int i = 0; i < field_size; i++) {
//			if (field[i][n] != field[0][n] || field[0][n] == '.') {
//				b = false;
//				return b;
//			}
//		}
//		cout << "Победа " << field[0][n] << endl;
//		return b;
//	}
//
//	bool checkColumn(int n) {
//		bool b = true;
//		for (int i = 0; i < field_size; i++) {
//			if (field[n][i] != field[n][0] || field[n][0] == '.') {
//				b = false;
//				return b;
//			}
//		}
//		cout << "Победа " << field[n][0] << endl;
//		return b;
//	}
//
//	bool checkFirstDiagonal() {
//		bool b = true;
//		for (int i = 0; i < field_size; i++) {
//			if (field[i][i] != field[0][0] || field[i][i] == '.') {
//				b = false;
//				return b;
//			}
//		}
//		cout << "Победа " << field[0][0] << endl;
//		return b;
//	}
//
//	bool checkSecondDiagonal() {
//		bool b = true;
//		for (int i = 0; i < field_size; i++) {
//			if (field[i][field_size - i - 1] != field[field_size - 1][0] || field[i][field_size - i - 1] == '.') {
//				b = false;
//				return b;
//			}
//		}
//		cout << "Победа " << field[field_size - 1][0] << endl;
//		return b;
//	}
//
//
//};
//
//int main() {
//	setlocale(LC_ALL, "rus");
//	Game g(3);
//	g.initGame();
//	system("pause");
//	return 0;
//}
//
