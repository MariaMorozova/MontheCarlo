#include "stdafx.h"
#include "MonteCarloCalculator.h"
#include "MyData.h"

MonteCarloCalculator::MonteCarloCalculator()
{
}


MonteCarloCalculator::~MonteCarloCalculator()
{
}

DWORD MonteCarloCalculator::Calculate(LPVOID lpParam)
{
	HANDLE hStdout;
	PMYDATA pDataArray;
	
	// Make sure there is a console to receive output results. 

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.
	pDataArray = (PMYDATA)lpParam;	
	pDataArray->pi = MonteCarloAlgorithm(pDataArray->num);

	return 0;
}

double MonteCarloAlgorithm(int steps)
{
	double x, y;
	int Ncirc = 0;

	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<> dis{ 0, RAND_MAX };

	for (int i = 0; i < steps; ++i)
	{
		x = ((double)dis(gen) / RAND_MAX) * A;
		y = ((double)dis(gen) / RAND_MAX) * A;
		if (y * y <= circle(x, A))  //Условие принадлежности точки к кругу
			++Ncirc;
	}
	return ((double)Ncirc / steps) * 4;
}

inline double circle(double x, double radius)
{
	return radius * radius - x * x;
}
