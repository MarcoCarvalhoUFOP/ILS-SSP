#pragma once

#include "Solution.hpp"
#include <string>


class InstanceChecker : Solution
{
public:
    InstanceChecker(MTSP* problem, bool print, string methodName);
    void checkDominance();
    void printDominance();
    void printDominanceToFile(char* filename);
    bool hasDominance();
    void checkTwinTools(bool createGraph = true);
    void printTwinTools();
    void printTwinToolsToFile(char* filename);
	bool hasTwinTools();


	vector<vector<int>>& getTwinTools();
private:
    vector<vector<int>> dominance_;
    bool hasDominance_;
    vector<vector<int>> twinTools_;
    bool hasTwinTools_;

};

