// MonteCarlo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "MonteCarloCalculator.h"
#include "ThreadHandler.h"
#include <ctime>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("wrong parametrs count\n");
		ExitProcess(1);
	}

	int maxThreads = atoi(argv[1]);
	int iterCount = atoi(argv[2]);


	std::clock_t start;
	double duration;

	start = std::clock();

	ThreadHandler handler(maxThreads, iterCount, MonteCarloCalculator::Calculate);
	handler.Start();
	handler.Wait();

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	PMYDATA* pDataArray = handler.pDataArray;

	double avgPI = 0.0;
	for (int i = 0; i < maxThreads; i++)
	{
		avgPI += pDataArray[i]->pi;
		printf("%i: %f \n", i, pDataArray[i]->pi);
	}
	printf("avg pi: %f \n", avgPI / maxThreads);
	std::cout << "time: " << duration << std::endl;
	std::cout << "iterCount: " << iterCount << std::endl;

	//openMP
	double pi_openMP = 0.0;
	#pragma omp parallel for num_threads(maxThreads)
	for (int i = 0; i < maxThreads; i++)
	{
		pi_openMP += MonteCarloAlgorithm(iterCount / maxThreads);
	}
	pi_openMP /= maxThreads;
	printf("openMP pi = %f \n", pi_openMP);
	
	return 0;
}

