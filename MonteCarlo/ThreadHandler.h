#pragma once
#include <windows.h>
#include "MyData.h"

class ThreadHandler
{
public:
	ThreadHandler(int threads, int iterCounts, LPTHREAD_START_ROUTINE func);
	~ThreadHandler();

	void Start();
	void Wait();

	PMYDATA* pDataArray;
private:
	DWORD* dwThreadIdArray;
	HANDLE* hThreadArray;
	int m_threads;
	int m_iterCounts;
	LPTHREAD_START_ROUTINE m_func;
};

