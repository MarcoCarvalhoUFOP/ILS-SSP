#pragma once
#include "Solution.hpp"
#include "Misc.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class AntonioAugusto : public Solution
{
public:
	AntonioAugusto(MTSP* mtsp, bool print, string methodName);
	void antonioAugusto();
	int findNextJob(int nextTool);
	void updateMagazine(int nextJob);
	void checkMagazine();
private:
	Graph *graph;
	vector<int> vDegree;
	multimap<int, int> degree;
	unordered_map<int, int> switchesRequired;
	vector<bool> isOnMagazine;
	int capacity, jobsExecuted;
	vector<bool> isExecuted;
	unordered_set<int> magazine;
};

