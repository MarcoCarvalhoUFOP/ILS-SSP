#ifndef SOLUTIONHPP__
#define SOLUTIONHPP__
#include "MTSP.hpp"
#include "Configuration.hpp"

#include <cstdio>

class Solution
{
public:
	Solution(MTSP* problem, bool print, string methodName)
	{
		problem_ = problem;
		print_ = print;
		numberOfJobs_ = problem->getNumJobs();
		numberOfSwitches_ = 0;
		methodName_ = methodName;
	}
	virtual ~Solution() {

	};
	
	string* getSummaryEntry()
	{
		char summaryEntry[500];
		snprintf(summaryEntry, 500, "%30s/%-30s \t %5d \t %4.12lf", &(problem_->getDirectory())[0], &(problem_->getFileName())[0], problem_->getNumSwitches(), problem_->getTimeElapsed().count());
		
		return new string(summaryEntry);
	}


protected:
	MTSP* problem_;
	vector<int> sequence_;
	int numberOfSwitches_, numberOfJobs_;
	string methodName_;
	bool print_;
};


#endif