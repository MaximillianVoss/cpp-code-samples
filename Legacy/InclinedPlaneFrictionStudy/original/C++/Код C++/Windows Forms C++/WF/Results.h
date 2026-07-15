#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include "PlotPoint.h"
#define PI 3.14159265358979323846 
#define G 9.81
using namespace System;
#pragma once
public class Results
{
private:
	int axisXLength;
	int axisYLength;
public:
	double firstMass;
	double secondMass;
	double mu;
	double angle;
	int plotScale;
	int plotOffsetX;
	int plotOffsetY;
	std::vector<PlotPoint> accWithMu;
	std::vector<PlotPoint> accWithAngle;
	std::vector<PlotPoint> forceWithAngle;
	std::vector<PlotPoint> forceWtithMu;

	std::vector<PlotPoint> axisX;
	std::vector<PlotPoint> axisY;
	std::vector<PlotPoint> marksX;
	std::vector<PlotPoint> marksY;

	Results()
	{
	}

	Results(std::map < std::string, std::string > strValues, std::map < std::string, int > intValues)
	{
		enum marksTypes { vertical = 1, horizontal = 2 };
		enum marksScale { small = 15, meduim = 30, large = 50 };
		firstMass = atof(strValues.at("mas").c_str());
		secondMass = firstMass / 2;
		mu = atof(strValues.at("mu").c_str());
		angle = atof(strValues.at("angle").c_str());
		plotScale = intValues.at("scale");
		plotOffsetX = intValues.at("offsetX");
		plotOffsetY = intValues.at("offsetX");
		axisXLength = intValues.at("axis x length");
		axisYLength = intValues.at("axis y length");
		GetAxis(axisXLength,axisYLength);
		GetPoints();
		SetMarks(axisY[0], axisY[1], small, vertical);
		SetMarks(axisX[0], axisX[1], small, horizontal);
	}
	float Parabolic(float  x)
	{
		return x*x + 2 * x;
	}
#pragma region LOGICS
	float ConvertAngle(float _angle)
	{
		return _angle *  PI / 180;
	}
	float GetSin(float angle)
	{
		return sin(ConvertAngle(angle));
	}
	float GetCos(float angle)
	{
		return cos(ConvertAngle(angle));
	}
	float GetAceleration()
	{
		return G*(firstMass*(GetSin(angle) - mu*GetCos(angle)) - secondMass) / (firstMass + secondMass);
	}
	double GetAceleration(double _mu, double _angle)
	{
		double value = G*(firstMass*(GetSin(_angle) - _mu*GetCos(_angle)) - secondMass) / (firstMass + secondMass);
		return value;
	}
	float GetT()
	{
		return secondMass*GetAceleration() + secondMass*G;
	}
	float GetForce()
	{
		return 2 * GetT();
	}
	void ConvertString(String ^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
#pragma endregion
#pragma region GET POINTS	
	void GetPoints()
	{
		for (double _mu = 0;_mu < 20;_mu += 0.1)
		{
			accWithMu.push_back(PlotPoint((_mu* plotScale), (GetAceleration(_mu, angle)*plotScale) + plotOffsetY));
		}
		for (int i = 0;i < accWithMu.size();i++)
		{
			accWithMu[i].x = -accWithMu[i].x + accWithMu[accWithMu.size() - 1].x +axisX[0].x;
			accWithMu[i].y = accWithMu[i].y + axisYLength; //- accWithMu[0].y;
		}
	}
	void GetAxis(int axisXLenght,int axisYLength)
	{
		axisX.push_back(PlotPoint(plotOffsetX, plotOffsetY+ axisYLength));
		axisX.push_back(PlotPoint(plotOffsetX + axisXLenght, plotOffsetY+ axisYLength));
		axisY.push_back(PlotPoint(axisX[0].x, plotOffsetY));
		axisY.push_back(PlotPoint(axisX[0].x, plotOffsetY + axisYLength));
	}
	void SetMarks(PlotPoint start, PlotPoint end, int scaleValue, int type)
	{
		//1 vertical , 2 horizontal
		if (type == 1)
		{
			int count = abs(start.y - end.y) / scaleValue;
			int min = std::min(start.y, end.y);
			for (int i = 0;i < count;i++)
			{
				marksY.push_back(PlotPoint(start.x - 10, min + i*scaleValue));
				marksY.push_back(PlotPoint(start.x + 10, min + i*scaleValue));
			}
		}
		if (type == 2)
		{
			int count = abs(start.x - end.x) / scaleValue;
			int min = std::min(start.x, end.x);
			for (int i = 0;i < count;i++)
			{
				marksX.push_back(PlotPoint(min + i*scaleValue, start.y - 10));
				marksX.push_back(PlotPoint(min + i*scaleValue, start.y + 10));
			}
		}
	}

#pragma endregion
};

