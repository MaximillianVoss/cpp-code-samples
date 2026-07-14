// Shamir_Secret.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/// <summary>
///https://github.com/developer512/Shamir-s-Secret-Sharing
///https://ru.wikipedia.org/wiki/%D0%A1%D1%85%D0%B5%D0%BC%D0%B0_%D1%80%D0%B0%D0%B7%D0%B4%D0%B5%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F_%D1%81%D0%B5%D0%BA%D1%80%D0%B5%D1%82%D0%B0_%D0%A8%D0%B0%D0%BC%D0%B8%D1%80%D0%B0 
/// </summary>
#include "pch.h"
#include "InfoIO.h"
#include "Polynom.h"
#include "FileIO.h"
class Shamir {
private:
	int Power(int a, int exponent, int modulus) {

		int result = 1;
		int A = a;
		int n = exponent;
		while (n > 0) {
			if (n % 2 == 1) {
				result *= A;
				result %= modulus;
				n--;
			}
			else {
				A *= A;
				A %= modulus;
				n /= 2;
			}
		}
		return result;
	}
	int PowerInverse(int a, int modulus) {
		int result = Power(a, modulus - 2, modulus);
		return result;
	}
public:
	vector<int> usersInitialization(int n, int modulus) {
		vector<int> r = vector<int>(n);
		bool check;
		r[0] = rand() % (modulus - 1) + 1;
		for (int i = 1; i < n; i++) {
			do {
				check = false;
				r[i] = rand() % (modulus - 1) + 1;
				for (int j = 0; j < i; j++)
					if (r[i] == r[j]) {
						check = true;
						break;
					}
			} while (check);
		}
		return r;
	}
	vector<int> polynomialGenerator(int t, int modulus) {
		vector<int> polynomial = vector<int>(t);
		for (int i = 0; i < t; i++)
			polynomial[i] = rand() % modulus;
		return polynomial;
	}
	int getUserKey(int userNumber, vector<int> polynomial, int t, int modulus) {
		vector<int> rVector = vector<int>(t);
		int userKey = 0;
		int temp;
		for (int i = 0; i < t; i++) {
			rVector[i] = Power(userNumber, i, modulus);
			temp = (rVector[i] * polynomial[i]) % modulus;
			userKey += temp;
			userKey %= modulus;
		}
		return userKey;
	}
	int secretResolving(vector<int> userNumbers, vector<int> polynomial, int t, int modulus) {
		vector<int> userKeys = vector<int>(t);
		vector<int> w = vector<int>(t);
		int mainKey = 0, difference;
		int temp;
		for (int i = 0; i < t; i++)
			userKeys[i] = getUserKey(userNumbers[i], polynomial, t, modulus);

		for (int i = 0; i < t; i++) {
			w[i] = 1;
			for (int j = 0; j < t; j++) {
				if (j != i) {
					difference = (userNumbers[j] - userNumbers[i]) % modulus;
					if (difference < 0)
						difference += modulus;
					w[i] *= userNumbers[j];
					w[i] %= modulus;
					w[i] *= PowerInverse(difference, modulus);
					w[i] %= modulus;
				}

			}
			temp = (userKeys[i] * w[i]) % modulus;
			mainKey += temp;
			mainKey %= modulus;
		}
		return mainKey;
	}
};


void Save(vector<vector<Pair<double, double>>> data) {
	FileIO fileIO = FileIO();
	vector<string> lines;
	for (int i = 0; i < data.size(); i++) {
		string strX = "";
		string strY = "";
		for (int j = 0; j < data[i].size(); j++) {
			strX += to_string(data[i][j].GetKey()) + " ";
			strY += to_string(data[i][j].GetValue()) + " ";
		}
		lines.push_back(strX);
		lines.push_back("\n");
		lines.push_back(strY);
		lines.push_back("\n");
	}
	fileIO.WriteLines("data.txt", lines);
}



int main() {
	srand(time(NULL));
	InfoIO infoIO = InfoIO();
	infoIO.SetRusIO();
	Shamir shamir = Shamir();
	while (true) {
		vector<int> A, R;
		int n;
		int t = infoIO.GetInt("Введите количество пользователей, учавствующих в объединении частей:");
		int p = infoIO.GetInt("Введите значение модуля(простое число):");
		do {
			n = infoIO.GetInt("Введите колчество пользователей");
			if (n >= p - 1)
				infoIO.PrintLn("Слишком много пользователей: количество пользователей больше значения модуля!");
		} while (n >= p - 1);

		R = shamir.usersInitialization(n, p);
		infoIO.Print(R, "Список пользователей:");
		A = shamir.polynomialGenerator(t, p);
		infoIO.PrintLn("Полином:");
		vector<int> copy = A;
		reverse(copy.begin(), copy.end());
		Polynom<int> pol = Polynom<int>(copy);
		cout << pol << endl;
		infoIO.PrintLn("Секрет(свободный член):");
		cout << pol.GetItems()[0] << endl;
		vector<int> keys;
		for (int i = 0; i < n; i++)
			keys.push_back(shamir.getUserKey(R[i], A, t, p));
		infoIO.Print(keys, "Список ключей пользователей:");
		infoIO.Print("Полином восстановленный:" + to_string(shamir.secretResolving(R, A, t, p)));
		//////
		vector<vector<Pair<double, double>>> data;
		for (int i = 0; i <= pol.GetItems()[0]; i++) {
			Polynom<int> polynomToDraw = Polynom<int>(pol);
			polynomToDraw.Set(0, i * 1000);
			data.push_back(polynomToDraw.GetValues(-100, 100, 0.5));
		}
		Save(data);
		system("python Main.py");
	}
	
	////полином 7x^2+8+11
	//vector<int> polynom = { 11,8,7 };
	//int t = 3;
	//int n = 5;
	//int p = 13;
	//vector<int> R = shamir.usersInitialization(n, p);
	//cout << shamir.secretResolving(R, polynom, t, p) << endl;
	//infoIO.Pause();
	return 0;
}