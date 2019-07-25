#pragma once
#include "pch.h"
/// <summary>
/// Схема разделения секрета Шамира
/// </summary>
class ShamirsSecretSharing {
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