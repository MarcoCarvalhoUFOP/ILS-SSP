#pragma once

#include "MTSP.hpp"
#include "Solution.hpp"

const int KOPT_TOTAL = 0;
const int KOPT_PARTIAL = 1;


class KOpt :  public Solution
{
protected:
	int k_;
	int type_;
	double partialSize_;
    int numberOfSwitchesFound;
	long long numberofPermutationGenerated;
	vector<vector<int>> combinations_, permutations_;
	vector<int> bestFoundSequence_;
	void generateCombinations();
	void generateCombinations2();
	void generateKPermutations(bool restricted);
	vector<int> permutate(vector<int>& currentSequence, vector<int>& comb);
	vector<int> permutate2(vector<int>& currentSequence, vector<int>& comb);

public:
	KOpt(MTSP* mtsp, int k, const int type, double partialSize, bool print, string methodName);
	KOpt(MTSP* mtsp, int k, bool print, string methodName);

	void kOptExecute();
	void kOptExecute2();
	void kOptExecuteRandom();
	void kOptExecutePartial();
	void kOpt();
	void kOptRestricted();
	void kOptPrepare();
	void kOptPrepare2();
	void swap2();


};

