#include "BestPositionInsertion.hpp"
#include "Misc.hpp"

#include <functional>
#include <algorithm>


BestPositionInsertion::BestPositionInsertion(MTSP* mtsp, bool print, string methodName) : Solution(mtsp, print, methodName)
{
}

void BestPositionInsertion::findBestInsertion(vector<int> &bestSequence, int nextJob)
{
	vector<int> auxSequence, bestFoundSequence;
	int leastSwitches = 99999999;
	for(int j = 0 ; j <= (int) bestSequence.size(); j++)
	{
		auxSequence.clear();
		auxSequence.insert(auxSequence.begin(), bestSequence.begin(), bestSequence.begin() + j); // Insert the interval [0, j) from the best sequence to the new sequence. 
		auxSequence.push_back(nextJob); // Insert the nextJob at the j position.
		auxSequence.insert(auxSequence.end(), bestSequence.begin() + j, bestSequence.end()); // Insert the reamining interval [j, end) from the best sequence to the new sequence.

		problem_->setSequence(auxSequence); // Test this new sequence.
		problem_->KTNS(auxSequence.size()); // Discover the minimum number of switches.

		if(print_)
		{
			printVector(auxSequence);
			printf(" Switches: %d\n", problem_->getNumSwitches());
		}

		if(problem_->getNumSwitches() < leastSwitches) // If the number of switches is the minimum set this as the new best found sequence.
		{
			leastSwitches = problem_->getNumSwitches();
			bestFoundSequence =  auxSequence;
		}
	}
	numberOfSwitches_ = leastSwitches;
	bestSequence = bestFoundSequence; // Return the best sequence found.
}


void BestPositionInsertion::bestPositionInsertion()
{
    int numberOfJobs = problem_->getNumJobs();
	vector<int> bestSequence;
	vector<int> &numToolInstant = problem_->getNumToolInstant();
	vector<pair<int,int>> orderedJobs;

	for(int i = 0; i < numberOfJobs; i++)
		orderedJobs.push_back(make_pair(numToolInstant[i],i));

	sort(orderedJobs.begin(), orderedJobs.end(), greater<pair<int,int>>()); // Sort the jobs by the number of Tools.

	bestSequence.push_back(orderedJobs[0].second); // Initialize the best sequence as the job with the most number of tools.

	for(int i = 1; i < numberOfJobs; i++)
		findBestInsertion(bestSequence, orderedJobs[i].second); // Find where the next job has to be inserted.


	if(print_)
	{
		printf("Best sequence -> (");
		for(int i = 0; i < numberOfJobs-1; i++)
			printf("%d, ", bestSequence[i]);
		printf("%d)\n", bestSequence[numberOfJobs-1]);
		printf("Number of Switches = %d \n", numberOfSwitches_);
	}
	sequence_.assign(bestSequence.begin(), bestSequence.end());
	problem_->setSequence(sequence_);
	problem_->KTNS();
}



