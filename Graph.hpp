#pragma once

#include <cstdio>
#include <vector>
#include <utility>	  
#include <algorithm>
#include "Misc.hpp"




using namespace std;


enum GRAPH_TYPE { GRAPH_WEIGHTED, GRAPH_UNWEIGHTED};


class Graph
{
private:
	int n_, m_;
	GRAPH_TYPE type_;
	vector<vector<pair<int,double>>> graphWeighted_;
	vector<vector<int>> graphUnweighted_;

public:

	vector<vector<double>> graphWeightedM_;
	vector<pair<int,double>>& operator[](const int& x);
	Graph();

	Graph(int n, GRAPH_TYPE type);

	int getNumVertex();

	void addEdge(int tail, int head);
	void addEdge(int tail, int head, double cost);

	vector<vector<pair<int,double>>>& getWeightedGraph();
	vector<vector<int>>& getUnweightedGraph();

	double getCost(int tail, int head);

	int getEdge(int tail, int head);
	bool isTwinVertice(int x, int y, bool print = false);
	void resize(int n, GRAPH_TYPE type);

    void createGraphLowerBound(int numberOfJobs, int magazineCapacity, vector<vector<int>>& jobsTools);
    void createGraphUpperBound(int numberOfJobs, vector<vector<int>>& jobsTools);
	void createGraphAugusto(int numberofJobs, int numberOfTools, vector<vector<int>> &jobTools);
	void createGraphToolJob(int numberofJobs, int numberOfTools,  vector<vector<int>> &jobTools);

	double MST();
	Graph* createComplementaryGraph();
    

	void print();

};
