#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "PlotPoint.h"
#define PI 3.14159265358979323846 
#define G 9.81
using namespace System;
using namespace std;
#pragma once
public class Results
{
public:
	double firstMass;
	double secondMass;
	double mu;
	double angle;
	vector<PlotPoint> accWithMu;
	vector<PlotPoint> accWithAngle;
	vector<PlotPoint> forceWithAngle;
	vector<PlotPoint> forceWtithMu;
	Results(string _mass, string _mu, string _angle)
	{
		firstMass = atof(_mass.c_str());
		secondMass = firstMass / 2;
		mu = atof(_mu.c_str());
		angle = atof(_angle.c_str());
		GetPoints();
	}
#pragma region LOGICS
	double ConvertAngle(float _angle)
	{
		return (_angle*  PI) / 180;
	}
	double GetSin(float angle)
	{
		return sin(ConvertAngle(angle));
	}
	double GetCos(float angle)
	{
		return cos(ConvertAngle(angle));
	}
	double GetAceleration()
	{
		return GetAceleration(mu, angle);
	}
	double GetAceleration(double _mu, double _angle)
	{
		if (angle < 30)
			return (G*(-1 * firstMass*(_mu*GetCos(_angle) + GetSin(_angle) + secondMass)) / (firstMass + secondMass));
		if (angle == 30)
			return 0;
		if (angle > 30 && angle <= 90)
			return (mu*firstMass*G + GetCos(_angle) + secondMass*G - firstMass*G*GetSin(_angle)) / (-firstMass - secondMass);
	}
	double GetForce()
	{
		return GetForce(GetAceleration(),angle,mu);
	}
	double GetForce(double aceleration,double angle,double mu)
	{
		if (angle < 30)
			return (secondMass*G - (secondMass*(G - ((G*(-firstMass*(mu*GetCos(angle) + GetSin(angle)) + secondMass)) / (firstMass + secondMass)))))*(1 + GetSin(angle));
		if (angle >= 30 && angle <= 90)
			return (1 + GetSin(angle))*(secondMass*((mu*firstMass*G*GetCos(angle) + secondMass*G - firstMass*G*GetSin(angle)) / (-firstMass - secondMass)) + secondMass*G);
	}
	void ConvertString(String ^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
#pragma endregion
#pragma region 
	double accWithMuStatic[4] = { 2.134, 1.49, 0.846, 0.202 };
	double accWithAngleStatic[10] = { 1.961, 0.846, -0.196, -1.132 };
	double forceWithAngleStatic[10] = {};
	double forceWtithMuStatic[10] = {};
#pragma endregion
#pragma region GET POINTS	
	void GetPoints()
	{
		for (double _mu = 0;_mu <= 0.3;_mu += 0.1)
		{
			accWithMu.push_back(PlotPoint(_mu, GetAceleration(_mu, angle)));
		}
		for (double _angle = 0;_angle < 30;_angle += 1)
		{
			accWithAngle.push_back(PlotPoint(_angle, GetAceleration(mu, _angle)));
		}
		for (double _angle = 0;_angle < 30;_angle += 1)
		{
			forceWithAngle.push_back(PlotPoint(_angle, GetForce(GetAceleration(mu, _angle),mu,_angle)));
		}
		for (double _mu = 0;_mu <= 0.3;_mu += 0.1)
		{
			forceWtithMu.push_back(PlotPoint(_mu, GetForce(GetAceleration(_mu, angle), _mu, angle)));
		}
	}
	void GetPointsStatic()
	{
		int i = 0;
		for (double _mu = 0;_mu <= 0.3;_mu += 0.1)
		{
			accWithMu.push_back(PlotPoint(_mu, accWithMuStatic[i++]));
		}
		i = 0;
		for (double _angle = 0;_angle <= 90;_angle += 10)
		{
			accWithAngle.push_back(PlotPoint(_angle, accWithAngleStatic[i++]));
		}
		/*
		for (int i = 0;i<10;i++)
		{
			forceWithAngle.push_back(PlotPoint(_angle, GetForce(GetAceleration(mu, _angle), mu, _angle)));
		}
		for (int i = 0;i<10;i++)
		{
			forceWtithMu.push_back(PlotPoint(_mu, GetForce(GetAceleration(_mu, angle), _mu, angle)));
		}*/
	}
#pragma endregion
};

