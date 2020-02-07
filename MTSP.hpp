#pragma once

#include "Graph.hpp"
#include <chrono>
#include <random>
#include <map>
#include <string>
#include <assert.h>

const int ILS_2OPT = 0;
const int ILS_LOCALSEARCH = 1;
const int ILS_LS_2OPT = 2;
const int ILS_LS_PART_2OPT = 3;
const int ILS_LS_22SWAPOPT = 4;
const int ILS_LS_PART_22SWAPOPT = 5;


class KOpt;
class FistTry;

class MTSP
{
private:
	Graph* graph_;
	vector<vector<int>> toolJobBinary_, toolSequence_, toolSequence2_, jobTools_;
	vector<int> sequence_, numToolIstant_;
	int numToolSwitches_;
	int numTools_, numJobs_, partialSequence_, magazineCapacity_;
	chrono::duration<double> timeElapsed_, timeBestSolution_;		
	chrono::high_resolution_clock::time_point endbestSolution_;		
	int iterBestSolution_;
	KOpt* kopt;
	FistTry* fst;
	string filePath_;
public:
	MTSP(string& filePath);
	~MTSP();


	void createGraph(int n = 0,  GRAPH_TYPE type = GRAPH_UNWEIGHTED);
	void createGraphLowerBound();
	void createGraphUpperBound();
	void createGraphAugusto();
	void createGraphToolJob();

	vector<vector<int>>& getToolJobBinary();
	void setToolJobBinary(vector<vector<int>>& toolJobBinary);

	vector<int>& getSequence();
	void setSequence(vector<int>& sequence);
	vector<int>& getNumToolInstant();

	void setTimeElapsed(chrono::duration<double> timeElapsed);
	chrono::duration<double>& getTimeElapsed();

	void setTimeBestSolution(chrono::duration<double> timeElapsed);
	chrono::duration<double>& getTimeBestSolution();

	void setTimeToBestSolution(chrono::high_resolution_clock::time_point);
	chrono::high_resolution_clock::time_point& getTimeToBestSolution();


	int getIterBestSolution();
	vector<vector<int>>& getToolSequence();
	void setToolSequence(vector<vector<int>>& toolSequence);

	vector<vector<int>>& getJobTools();
	void setJobTools(vector<vector<int>>& jobTools);

	Graph* getGraph();

	bool isDominated(int x, int y, bool print = false);

	int getNumSwitches();

	int getNumJobs();
	void setNumJobs(int  numJob);

	int getCapacity();
	void setCapacity(int  capacity);


	int nextInstant(int tool, int time, int limit);
	int KTNS();
	int KTNS(int numJobs);

	int evaluate();
	int evaluate(int numJobs);

	void readInputYanasse();
	void resizeProblem();


	void printToolJobBinary();
	void printToolSequence();
	void printToolJob();
	void printSolution();
	void printProblem();
	void printSolutionToFile(char* filename);

	const string& getDirectory() const;
	const string& getFileName() const;

	void printSolutionSumary(FILE* summaryFile, FILE* allSummaryFile);
	void printSolutionSumary(FILE* summaryFile, FILE* allSummaryFile, string& summaryEntry);

	void localSearch(int function, bool print = false, int numIter = 200);
	void localSearchIterative(int function, bool print = false, int numIter = 200, double partialSize = 0.5);
	void localSearchIterativeCORRECT(int function, bool print = false, int numIter = 200, double partialSize = 0.5);
	void localSearchFull(int function, bool print = false, int numIter = 200);

	void ILS(int numIter, double beta, const int function, bool print = false, int numIterStalled = 10, double partialSize = 0.5, long timeLimit = 99999999);


};

