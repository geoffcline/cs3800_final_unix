#include "bruteforce.h"
#include <cmath>
#include <windows.h>
#include <ppl.h>
#include <mutex>
#include <atomic>

int bruteforceKS(const KS_List& item, const int maxw)
{
  
  int n = item.getsize(); //used multiple times so variable for total amount of items

  int bestValue=0;     //keeps track of max value obtained by a combo of items
  int bestWeight=0;    //same as above except for weight

	mutex geoff; 

	concurrency::parallel_for(int(1), static_cast<int>(pow(2, n)), [&](const int i)
	{
		int currentV = 0;
		int currentW = 0;

		int* A = new int[n];

		for (int x = 0; x<item.getsize(); x++) //sets all elements to 0
		{
			A[x] = 0;
		}

		for (int j = 0; j < n; ++j)
		{
			A[j] = i & (1 << j) ? 1 : 0;
		}

		for (int k = 0; k<n; k++) //creates combo out of items and keeps track of weight and value
		{
			if (A[k] == 1)
			{
				currentW += item[k]->getweight();
				currentV += item[k]->getvalue();
			}

		}

		geoff.lock();

		if ((currentV > bestValue) && (currentW <= maxw)) //replaces max if needed
		{
			bestValue = bestValue;
			bestWeight = currentW;
		}

		geoff.unlock();

		delete A;

	});
	   

  return bestValue; //returns max set

}
