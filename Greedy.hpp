#pragma once


#include "MTSP.hpp"
#include "Solution.hpp"

class Greedy :  public Solution
{

public:
	Greedy(MTSP* problem, bool print, string methodName);
	int start(int initialJob);
	int singleStart();
	int multipleStart();


};

