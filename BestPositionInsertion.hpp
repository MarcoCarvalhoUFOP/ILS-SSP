#pragma once
#include "Solution.hpp"

class BestPositionInsertion :  public Solution
{
public:
	BestPositionInsertion(MTSP* mtsp, bool print, string methodName);
	void bestPositionInsertion();
    void findBestInsertion(vector<int> &bestSequence, int nextJob);

};

