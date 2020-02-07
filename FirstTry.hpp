#pragma once
#include "Solution.hpp"
#include "InstanceChecker.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <utility>
#include <chrono>
#include <random>

#define FST_BFS 0
#define FST_HAM 1
#define FST_TWINS 0
#define FST_NOTWINS	1

class FirstTry :  public Solution
{
public:
	FirstTry(MTSP* problem, bool print, string methodName);
	void firstTry(int BFS, int Twins = FST_NOTWINS);
	void makeToolSequenceBFS(int initialTool);
	void makeToolSequenceBFSWithClique();
	void makeJobSequence();
	bool canExecute(int Job, int maxTool);

	void minimumDegreeGreedy();
	void extensionRotation();

    int lowerBoundYanasse();

    virtual void run();


private:
	Graph *graph;
	vector<int> toolSequence;
	vector<int> path;  
	InstanceChecker checker;
	int jobsExecuted, BFS, Twins;
	vector<bool> isExecuted;
};

