// Трение.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <Windows.h>
#include <math.h>
# define PI 3.14159265358979323846 
#define G 9.81

using namespace std;

float ConvertAngle(float angle)
{
	return angle *  PI/180;
}

float GetAceleration(float m1, float m2, float angle)
{
		return ((m2 - m1*sin(ConvertAngle(angle)))*G) / (m1 + m2);
}

float GetT(float m1, float m2, float mu, float angle)
{
	return (m2*G + mu*m1*G*cos(ConvertAngle(angle)) + m1*G*sin(ConvertAngle(angle))) / 2;
}

float GetForce(float T, float angle)
{
	return sqrt(2 * T*T + 2 * T*T*cos(ConvertAngle(angle)));
}

struct Point
{
	int x;
	int y;
};
int main()
{
	
    return 0;
}

