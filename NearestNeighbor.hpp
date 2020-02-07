#pragma once

#include "MTSP.hpp"
#include "Solution.hpp"

class NearestNeighbor :  public Solution
{
public:
	NearestNeighbor(MTSP* problem, bool print, string methodName);
	void makeATour(int initialJob);
	void nearestNeighbor();

};

