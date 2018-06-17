#include "stdafx.h"
#include "ThreadHandler.h"
#include <iostream>

void ErrorHandler(LPTSTR lpszFunction);
#define PER_THREAD 1000000 //itarations count

//LPTHREAD_START_ROUTINE pointer on function
ThreadHandler::ThreadHandler(int threads, int iterCounts, LPTHREAD_START_ROUTINE func) 
{
	pDataArray = new MYDATA*[threads];
	dwThreadIdArray = new DWORD[threads]; 
	hThreadArray = new HANDLE[threads];
	m_threads = threads;
	m_func = func;
	m_iterCounts = iterCounts / m_threads;
}

ThreadHandler::~ThreadHandler()
{
	for (int i = 0; i < m_threads; i++)
	{
		CloseHandle(hThreadArray[i]); 
		if (pDataArray[i] != NULL)
		{
			HeapFree(GetProcessHeap(), 0, pDataArray[i]);
			pDataArray[i] = NULL;
		}
	}

	delete[] pDataArray;
	delete[] dwThreadIdArray;
	delete[] hThreadArray;
}

void ThreadHandler::Start()
{
	for (int i = 0; i < m_threads; i++)
	{
		pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(MYDATA));

		if (pDataArray[i] == NULL)
		{
			ExitProcess(2);
		}

		pDataArray[i]->num = m_iterCounts;
		
		hThreadArray[i] = CreateThread(
			NULL,
			0,
			m_func,
			pDataArray[i],
			0,
			&dwThreadIdArray[i]);

		if (hThreadArray[i] == NULL)
		{
			ErrorHandler(TEXT("CreateThread"));
			ExitProcess(3);
		}
	}
}

void ThreadHandler::Wait()
{
	WaitForMultipleObjects(m_threads, hThreadArray, TRUE, INFINITE);
}

void ErrorHandler(LPTSTR lpszFunction)
{
	std::cout << lpszFunction << std::endl;
}