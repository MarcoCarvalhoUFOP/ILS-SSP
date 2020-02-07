#include "Greedy.hpp"


#include <random>
#include <vector>

using namespace std;


Greedy::Greedy(MTSP* problem, bool print, string methodName) : Solution(problem, print, methodName)
{
}

int Greedy::singleStart()
{
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distribution(0, problem_->getNumJobs()-1);
	int initialJob = distribution(generator);
	return start(initialJob);
}

int Greedy::multipleStart()
{
	int totalSwitches = (int)1e8;
	vector<int> bestSequence;

	for(int i = 0; i < numberOfJobs_; i++)
	{
		Greedy::start(i);
		if(i == 0 || numberOfSwitches_ < totalSwitches)
		{
			bestSequence.assign(sequence_.begin(), sequence_.end());
			totalSwitches = numberOfSwitches_;
		}

	}
	if(print_)
	{
		printf("Best sequence -> (");
		for(int i = 0; i < numberOfJobs_-1; i++)
			printf("%d, ", bestSequence[i]);
		printf("%d)\n", bestSequence[numberOfJobs_-1]);
		printf("Number of Switches = %d \n", totalSwitches);
	}
	sequence_.assign(bestSequence.begin(), bestSequence.end());
	problem_->setSequence(bestSequence);
	problem_->KTNS();
	return 0;
}

int Greedy::start(int initialJob)
{
    int totalJobs = 0, leastSwitches = 0, nextJob, numberOfJobs = problem_->getNumJobs();
	
	vector<bool> jobsExecuted(numberOfJobs, false); 
	
	vector<int>& sequence = problem_->getSequence();
	sequence[0] = initialJob;
	jobsExecuted[initialJob].flip();
	totalJobs++;
	
	if(print_)
		printf("Initial Job %d \n\n", sequence[0]);

	while(totalJobs  < problem_->getNumJobs())
	{
		leastSwitches = (int)1e8; nextJob = -1;

		for(int i = 0; i < numberOfJobs; i++)
		{
			if(!jobsExecuted[i])
			{ 
				sequence[totalJobs] = i;
				numberOfSwitches_ = problem_->KTNS(totalJobs+1);
				if(print_)
					printf("Trying to put Job %d in the %dth position -> number of Switches : %d \n", i, totalJobs+1, numberOfSwitches_);
				if(numberOfSwitches_ < leastSwitches)
				{
					leastSwitches = numberOfSwitches_;
					nextJob = i;
				}

			}
		}
		if(print_)
			printf("Job choosen %d \n\n", nextJob);
		jobsExecuted[nextJob].flip();
		sequence[totalJobs++] = nextJob;
	}
	
	sequence_.assign(sequence.begin(), sequence.end());
	numberOfSwitches_ = leastSwitches;
	return 0;
}









