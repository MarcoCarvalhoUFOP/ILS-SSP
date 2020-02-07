#pragma once

#include "KOpt.hpp"
#include "Solution.hpp"



class VND :  public Solution
{
private:
	int k0_, k1_;
	vector<KOpt*> neighborhoodStructures;
public:
	VND(MTSP* mtsp, int firstK, int lastK, bool print, string methodName);
	void ExecuteVND();

};

