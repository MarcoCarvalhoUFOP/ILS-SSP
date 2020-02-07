#include "FarthestInsertion.hpp"


FarthestInsertion::FarthestInsertion(MTSP* problem, bool print, string methodName) : Solution(problem, print, methodName)
{
}

int FarthestInsertion::findFarthestNode(vector<bool>& jobsExecuted)
{
	Graph* graph = problem_->getGraph();

	int farthestNode = -1;
	int costFarInsertion = 0;

	for(int i = 0; i < numberOfJobs_; i++)
	{
		if(!jobsExecuted[i]) // The node has not been executed, it must be skipped.
			continue;

		for(auto e : graph->getWeightedGraph()[i])
		{
			int job = e.first;
			int cost = (int) e.second;

			if(jobsExecuted[job]) // The node has been executed, it must be skipped.
				continue;

			if(farthestNode == -1 || cost > costFarInsertion)
			{
				costFarInsertion = cost;
				farthestNode = job;
			}
		}
	}
	if(print_) printf("Farthest node %d has cost %d\n", farthestNode, costFarInsertion);
	return farthestNode;
}



int FarthestInsertion::findBestPosition(int farthestNode, int totalJobs)
{
	int bestPosition = totalJobs - 1, cost = (int) 1e7, currentCost;
	Graph* graph = problem_->getGraph();

	for(int i = 0 ; i < totalJobs-1; i++) // Checking in the middle of the sequence
	{
		currentCost = ((int) graph->getCost(sequence_[i], farthestNode) + (int) graph->getCost(farthestNode, sequence_[i+1])) - (int) graph->getCost(sequence_[i], sequence_[i+1]);
		if(cost == (int) 1e7 || cost > currentCost)
		{
			cost = currentCost;
			bestPosition = i;
		}
	}

	currentCost = (int) graph->getCost(sequence_[totalJobs-1], farthestNode); // Checking at the end of the sequence
	if(cost > currentCost)
	{
		cost = currentCost;
		bestPosition = totalJobs-1;
	}

	currentCost = (int) graph->getCost(farthestNode, sequence_[0]); // Checking at the begin of the sequence
	if(cost > currentCost)
	{
		cost = currentCost;
		bestPosition = -1;
	}

	if(print_) printf("Best position to insert %d is %d with cost %d\n\n", farthestNode, bestPosition + 1, cost);
	numberOfSwitches_ +=  cost;
	return bestPosition;
}


void FarthestInsertion::makeATour(int initialJob)
{
    int totalJobs = 0, farthestNode, bestPosition;
    int costFarInsertion = 0;
	vector<bool> jobsExecuted(numberOfJobs_, false);
	Graph* graph = problem_->getGraph();
		
	farthestNode = -1;
	numberOfSwitches_ = 0;
	sequence_ = vector<int>(numberOfJobs_);

	sequence_[totalJobs++] = initialJob;
	jobsExecuted[initialJob].flip();


	for(auto e : graph->getWeightedGraph()[initialJob]) // Checking what has to be the 2nd job.
	{
		int job = e.first;
		int cost = (int) e.second;

		if(jobsExecuted[job]) // The node is on the o set, it must be skipped.
			continue;

		if(farthestNode == -1 || cost > costFarInsertion)
		{
			costFarInsertion = cost;
			farthestNode = job;
		}
	}

	sequence_[totalJobs++] = farthestNode;
	jobsExecuted[farthestNode].flip();
	numberOfSwitches_ +=  (int) graph->getCost(sequence_[0], sequence_[1]);


	for(; totalJobs < numberOfJobs_; totalJobs++)
	{
		farthestNode = findFarthestNode(jobsExecuted); // Find the farthest Node
		bestPosition = findBestPosition(farthestNode, totalJobs); // Find the position to insert the Farthest Node

		if(print_) printf("Choosed to put %d at %d\n", farthestNode, bestPosition);

		for(int i = totalJobs - 1; i > bestPosition; i--)
			sequence_[i+1] = sequence_[i]; // Making room for the farthest node.
		sequence_[bestPosition+1] = farthestNode; // Put the farthest node at the best position.

		jobsExecuted[farthestNode].flip();
	}

	if(print_) printf("Last sequence -> (");
	if(print_)
		for(int i = 0; i < numberOfJobs_-1; i++)
			printf("%d, ", sequence_[i]);
	if(print_) printf("%d)\n", sequence_[numberOfJobs_-1]);

	if(print_)	printf("Total switches %d \n\n", numberOfSwitches_);
	problem_->setSequence(sequence_);
}



void FarthestInsertion::farthestInsertion()
{
	int totalSwitches = (int)1e8;
	vector<int> bestSequence;

	for(int i = 0; i < numberOfJobs_; i++)
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
		for(int i = 0; i < numberOfJobs_-1; i++)
			printf("%d, ", bestSequence[i]);
		printf("%d)\n", bestSequence[numberOfJobs_-1]);
		printf("Number of Switches = %d \n", totalSwitches);
	}
	sequence_.assign(bestSequence.begin(), bestSequence.end());
	problem_->setSequence(sequence_);
	problem_->KTNS();
}



