#pragma once

#include "MTSP.hpp"
#include "Solution.hpp"

class FarthestInsertion :  public Solution
{
public:
	FarthestInsertion(MTSP* problem, bool print, string methodName);
	int findFarthestNode(vector<bool>& jobsExecuted);
	int findBestPosition(int farthestNode, int totalJobs);
	void makeATour(int initialJob);
	void farthestInsertion();
};

