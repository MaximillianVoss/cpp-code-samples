// Educational Shamir secret-sharing demonstration. Do not use for real secrets.
#include "pch.h"
#include "InfoIO.h"
#include "Polynom.h"
#include "FileIO.h"

class Shamir {
private:
	static int MultiplyModulo(int left, int right, int modulus) {
		return static_cast<int>((static_cast<long long>(left) * right) % modulus);
	}

	int Power(int value, int exponent, int modulus) const {
		int result = 1;
		int factor = value % modulus;

		while (exponent > 0) {
			if (exponent % 2 == 1) {
				result = MultiplyModulo(result, factor, modulus);
			}
			factor = MultiplyModulo(factor, factor, modulus);
			exponent /= 2;
		}

		return result;
	}

	int PowerInverse(int value, int modulus) const {
		return Power(value, modulus - 2, modulus);
	}

public:
	vector<int> usersInitialization(int count, int modulus) const {
		vector<int> users(count);
		users[0] = rand() % (modulus - 1) + 1;

		for (int index = 1; index < count; ++index) {
			bool duplicate;
			do {
				duplicate = false;
				users[index] = rand() % (modulus - 1) + 1;
				for (int previous = 0; previous < index; ++previous) {
					if (users[index] == users[previous]) {
						duplicate = true;
						break;
					}
				}
			} while (duplicate);
		}

		return users;
	}

	vector<int> polynomialGenerator(int threshold, int modulus) const {
		vector<int> polynomial(threshold);
		for (int index = 0; index < threshold; ++index) {
			polynomial[index] = rand() % modulus;
		}

		// A non-zero highest coefficient keeps the configured threshold meaningful.
		polynomial.back() = rand() % (modulus - 1) + 1;
		return polynomial;
	}

	int getUserKey(int userNumber,
		const vector<int>& polynomial,
		int threshold,
		int modulus) const {
		int userKey = 0;
		for (int index = 0; index < threshold; ++index) {
			const int term = MultiplyModulo(
				Power(userNumber, index, modulus),
				polynomial[index],
				modulus);
			userKey = (userKey + term) % modulus;
		}
		return userKey;
	}

	int secretResolving(const vector<int>& userNumbers,
		const vector<int>& polynomial,
		int threshold,
		int modulus) const {
		vector<int> userKeys(threshold);
		vector<int> weights(threshold, 1);
		int secret = 0;

		for (int index = 0; index < threshold; ++index) {
			userKeys[index] = getUserKey(userNumbers[index], polynomial, threshold, modulus);
		}

		for (int index = 0; index < threshold; ++index) {
			for (int other = 0; other < threshold; ++other) {
				if (other == index) {
					continue;
				}

				int difference = (userNumbers[other] - userNumbers[index]) % modulus;
				if (difference < 0) {
					difference += modulus;
				}

				weights[index] = MultiplyModulo(weights[index], userNumbers[other], modulus);
				weights[index] = MultiplyModulo(
					weights[index],
					PowerInverse(difference, modulus),
					modulus);
			}

			secret = (secret + MultiplyModulo(userKeys[index], weights[index], modulus)) % modulus;
		}

		return secret;
	}
};

static bool IsPrime(int value) {
	if (value < 2) {
		return false;
	}
	for (int divisor = 2; divisor <= value / divisor; ++divisor) {
		if (value % divisor == 0) {
			return false;
		}
	}
	return true;
}

static void SaveVisualizationData(const vector<vector<Pair<double, double>>>& data) {
	FileIO fileIO;
	vector<string> lines;
	for (const auto& series : data) {
		string xValues;
		string yValues;
		for (const auto& point : series) {
			xValues += to_string(point.GetKey()) + " ";
			yValues += to_string(point.GetValue()) + " ";
		}
		lines.push_back(xValues + "\n");
		lines.push_back(yValues + "\n");
	}
	fileIO.WriteLines("data.txt", lines);
}

static bool RunSelfTest() {
	const Shamir shamir;
	const vector<int> polynomial = {11, 8, 7};
	const vector<int> users = {1, 2, 3};
	return shamir.secretResolving(users, polynomial, 3, 13) == polynomial.front();
}

static int ReadThreshold(InfoIO& infoIO) {
	for (;;) {
		const int threshold = infoIO.GetInt("Введите порог восстановления секрета (не менее 2):");
		if (threshold >= 2) {
			return threshold;
		}
		infoIO.PrintLn("Порог должен быть не меньше 2.");
	}
}

static int ReadModulus(InfoIO& infoIO, int threshold) {
	for (;;) {
		const int modulus = infoIO.GetInt("Введите простое значение модуля, большее порога:");
		if (modulus > threshold && IsPrime(modulus)) {
			return modulus;
		}
		infoIO.PrintLn("Модуль должен быть простым числом и превышать порог.");
	}
}

static int ReadUserCount(InfoIO& infoIO, int threshold, int modulus) {
	for (;;) {
		const int count = infoIO.GetInt("Введите количество пользователей:");
		if (count >= threshold && count <= modulus - 1) {
			return count;
		}
		infoIO.PrintLn("Количество пользователей должно быть не меньше порога и не больше p - 1.");
	}
}

int main(int argc, char* argv[]) {
	if (argc == 2 && string(argv[1]) == "--self-test") {
		if (!RunSelfTest()) {
			cerr << "Shamir regression test failed" << endl;
			return EXIT_FAILURE;
		}
		cout << "Shamir regression test passed" << endl;
		return EXIT_SUCCESS;
	}
	if (argc != 1) {
		cerr << "Usage: Shamir_Secret.exe [--self-test]" << endl;
		return EXIT_FAILURE;
	}

	srand(static_cast<unsigned int>(time(nullptr)));
	InfoIO infoIO;
	infoIO.SetRusIO();
	const Shamir shamir;

	const int threshold = ReadThreshold(infoIO);
	const int modulus = ReadModulus(infoIO, threshold);
	const int userCount = ReadUserCount(infoIO, threshold, modulus);

	const vector<int> users = shamir.usersInitialization(userCount, modulus);
	infoIO.Print(users, "Список пользователей:");
	const vector<int> coefficients = shamir.polynomialGenerator(threshold, modulus);

	vector<int> displayCoefficients = coefficients;
	reverse(displayCoefficients.begin(), displayCoefficients.end());
	Polynom<int> polynomial(displayCoefficients);
	infoIO.PrintLn("Полином:");
	cout << polynomial << endl;
	infoIO.PrintLn("Секрет (свободный член):");
	cout << coefficients.front() << endl;

	vector<int> keys;
	for (int user : users) {
		keys.push_back(shamir.getUserKey(user, coefficients, threshold, modulus));
	}
	infoIO.Print(keys, "Список долей пользователей:");
	infoIO.PrintLn("Восстановленный секрет: "
		+ to_string(shamir.secretResolving(users, coefficients, threshold, modulus)));

	constexpr int MaxVisualizationSeries = 25;
	const int seriesCount = min(coefficients.front() + 1, MaxVisualizationSeries);
	vector<vector<Pair<double, double>>> visualizationData;
	for (int candidate = 0; candidate < seriesCount; ++candidate) {
		Polynom<int> candidatePolynomial(polynomial);
		candidatePolynomial.Set(0, candidate * 1000);
		visualizationData.push_back(candidatePolynomial.GetValues(-100, 100, 0.5));
	}
	SaveVisualizationData(visualizationData);
	infoIO.PrintLn("Данные графика записаны в data.txt. Для просмотра запустите: python Main.py");
	if (coefficients.front() + 1 > MaxVisualizationSeries) {
		infoIO.PrintLn("Число рядов графика ограничено 25 для защиты от чрезмерного расхода памяти.");
	}

	return EXIT_SUCCESS;
}
