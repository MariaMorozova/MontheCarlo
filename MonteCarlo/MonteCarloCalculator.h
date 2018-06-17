#pragma once
#include <windows.h>
#include<math.h> 
#include <random>

#define BUF_SIZE 255

//сторона квадрата
#define A 100 

class MonteCarloCalculator
{
public:
	MonteCarloCalculator();
	~MonteCarloCalculator();

	static DWORD WINAPI Calculate(LPVOID lpParam);
};

inline double circle(double x, double radius);
double MonteCarloAlgorithm(int steps);