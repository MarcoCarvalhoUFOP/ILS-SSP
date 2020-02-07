
#include "NearestNeighbor.hpp"


NearestNeighbor::NearestNeighbor(MTSP* problem, bool print, string methodName) : Solution(problem, print, methodName)
{
}



void NearestNeighbor::makeATour(int initialJob)
{
	int totalJobs = 0, leastSwitches, nextJob, currentJob;
	vector<bool> jobsExecuted(numberOfJobs_, false);
	Graph* graph = problem_->getGraph();
	
	numberOfSwitches_ = 0;
	sequence_ = vector<int>(numberOfJobs_);
	sequence_[totalJobs++] = initialJob;

	jobsExecuted[initialJob].flip();
	currentJob = initialJob;

	while(totalJobs  < numberOfJobs_)
	{
		leastSwitches = (int)1e8; nextJob = -1;

		for(auto e : graph->getWeightedGraph()[currentJob])
		{
			int job = e.first;
			int cost = (int) e.second;

			
			if(jobsExecuted[job])
				continue;
			if(print_)
				printf("Trying to put Job %d in the %dth position -> number of Switches : %d \n", job, totalJobs+1, cost);
			if(cost < leastSwitches)
			{
				leastSwitches = cost;
				nextJob = job;
			}

		}
		if(print_)
			printf("Job choosen %d \n\n", nextJob);
		jobsExecuted[nextJob].flip();
		currentJob = nextJob;
		numberOfSwitches_ += leastSwitches;
		sequence_[totalJobs++] = nextJob;

	}
	if(print_)
		printf("Total switches %d \n\n", numberOfSwitches_);
	problem_->setSequence(sequence_);
}

void NearestNeighbor::nearestNeighbor()
{
	int totalSwitches = (int)1e8, numberOfJobs = problem_->getNumJobs();
	vector<int> bestSequence;

	for(int i = 0; i < numberOfJobs; i++)
	{
		if(print_)
			printf("\n\nStarting a sequence with Job %d\n\n", i);

		makeATour(i);
		if(i == 0 || numberOfSwitches_ < totalSwitches)
		{
			bestSequence.assign(sequence_.begin(), sequence_.end());
			totalSwitches = numberOfSwitches_;
		}

		
	}
	if(print_)
	{
		printf("Best sequence -> (");
		for(int i = 0; i < numberOfJobs-1; i++)
			printf("%d, ", bestSequence[i]);
		printf("%d)\n", bestSequence[numberOfJobs-1]);
		printf("Number of Switches = %d \n", totalSwitches);
	}
	sequence_.assign(bestSequence.begin(), bestSequence.end());
	problem_->setSequence(bestSequence);
	problem_->KTNS();
}



