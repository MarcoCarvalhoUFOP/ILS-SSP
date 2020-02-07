#include "KOpt.hpp"
#include "Misc.hpp"

#include <algorithm>
#include <chrono>

KOpt::KOpt(MTSP* mtsp, int k, const int type, double partialSize, bool print, string methodName) : Solution(mtsp, print, methodName)
{
	k_ = k;
	type_ = type;
	partialSize_ = partialSize;
}

/**
 * @brief      K-Opt class constructor for a complete k-opt
 *
 * @param      mtsp        a pointer to a MTSP object that represent the problem to be solved
 * @param[in]  k           the number of elements to swap
 * @param[in]  print       true if want to show the log of the method
 * @param[in]  methodName  trash, need to clean up
 */
KOpt::KOpt(MTSP* mtsp, int k, bool print, string methodName): Solution(mtsp, print, methodName)
{
	k_ = k;
	type_ = KOPT_TOTAL;
}

/**
 * @brief      Generate combinations from k-swap
 */
void KOpt::generateCombinations()
{
	int numberOfJobs = problem_->getNumJobs();
	string bitmask(k_, 1);
	bitmask.resize(numberOfJobs, 0);

	vector<int> nextCombination(k_, 0);

	do {
		int count = 0;
        for (int i = 0; i < numberOfJobs; ++i)
			if (bitmask[i]) nextCombination[count++] = i;
		combinations_.push_back(nextCombination);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    
	if ( type_ == KOPT_PARTIAL)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
 		shuffle (combinations_.begin(), combinations_.end(), std::default_random_engine(seed));
 		for(int i = 0; i < (int)(combinations_.size() * (1 - partialSize_) ); i++)
 			combinations_.pop_back();
	}
}

/**
 * @brief      Generate combinations for swap(k,2)
 */
void KOpt::generateCombinations2()
{
	int numberOfJobs = problem_->getNumJobs() / 2; // Since swap(k,2) works with pairs, the
	                                               // number of jobs need to be divided by two
	string bitmask(k_, 1); // Creating a k mask for generating the combinations
	bitmask.resize(numberOfJobs, 0);

	vector<int> nextCombination(k_, 0);

	do {
		int count = 0;

        for (int i = 0; i < numberOfJobs; ++i)
			if (bitmask[i]) nextCombination[count++] = i;

		combinations_.push_back(nextCombination);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    
	if ( type_ == KOPT_PARTIAL)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
 		shuffle (combinations_.begin(), combinations_.end(), std::default_random_engine(seed));
 		for(int i = 0; i < (int)(combinations_.size() * (1 - partialSize_) ); i++)
 			combinations_.pop_back();
	}
}


/**
 * @brief      Generate all the k-permutations possible
 *
 * @param[in]  restricted true if the permutated sequence needs to have
 * exactly k exchanges, false otherwise.
 */
void KOpt::generateKPermutations(bool restricted)
{
	vector<int> permut;
	for(int i = 0 ; i < k_; i++)
		permut.push_back(i);

	permutations_ = vector<vector<int>>();

	bool changed;

	do
	{
		changed = true;
		for(int i = 0 ; i < (int) permut.size(); i++)
		{
			if(i == permut[i])
			{
				changed = false;
				break;
			}
		}

		if(restricted && changed){
			permutations_.push_back(permut);
			if(print_) printVector(permut);
		}
		else if(!restricted)
		{
			permutations_.push_back(permut);
			if(print_) printVector(permut);
		}
	}while(next_permutation(permut.begin(), permut.end()));

}


/**
 * @brief      makes the permutation on a sequence using the neighborhood k-swap, swapping k
 * elements from the sequence
 *
 * @param      currentSequence  the current sequence of jobs
 * @param      comb             all combinations possible
 *
 * @return     the best permutated sequence
 */	
vector<int> KOpt::permutate(vector<int>& currentSequence, vector<int>& comb)
{
	vector<int> phiSequence;
	vector<int> currentCombination(comb);
	numberofPermutationGenerated++;


	for(int k = 0; k < (int) permutations_.size(); k++)
	{
		numberofPermutationGenerated++;
		phiSequence.assign(currentSequence.begin(), currentSequence.end());
		for(int i = 0; i < (int) comb.size(); i++)
		{
			phiSequence[comb[i] ] = currentSequence[comb[permutations_[k][i]]];
			if(print_) printf(" %d ", currentSequence[comb[permutations_[k][i]]]);
		}
		if(print_) printf("\n");

		if(print_) for(int i = 0; i < (int) phiSequence.size(); i++) printf(" %d ", phiSequence[i]);
		problem_->setSequence(phiSequence);
		problem_->KTNS();
		if(problem_->getNumSwitches() < numberOfSwitchesFound)
		{
			bestFoundSequence_.assign(phiSequence.begin(), phiSequence.end());
			numberOfSwitchesFound = problem_->getNumSwitches();
		}
		if(print_) printf("; %d switches\n", problem_->getNumSwitches());
	}
	return bestFoundSequence_;
}


/**
 * @brief      makes the permutation on a sequence using the neighborhood swap(k,2), swapping k
 * pairs from the sequence
 *
 * @param      currentSequence  the current sequence of jobs
 * @param      comb             all combinations possible
 *
 * @return     the best permutated sequence
 */		
vector<int> KOpt::permutate2(vector<int>& currentSequence, vector<int>& comb)
{
	vector<int> phiSequence;
	vector<int> currentCombination(comb);
	numberofPermutationGenerated++;


	for(int k = 0; k < (int) permutations_.size(); k++)
	{

		//
		// First Permutation ..., I-1, I-2, .... , J-1, J-2
		//

		numberofPermutationGenerated++;
		phiSequence.assign(currentSequence.begin(), currentSequence.end());
		for(int i = 0; i < (int) comb.size(); i++)
		{
			phiSequence[comb[i]*2] = currentSequence[comb[permutations_[k][i]]*2];
			phiSequence[comb[i]*2+1] = currentSequence[comb[permutations_[k][i]]*2+1];

			if(print_) printf(" %d ", currentSequence[comb[permutations_[k][i]]]);
		}
		
		if(print_) printf("\n");

		if(print_) for(int i = 0; i < (int) phiSequence.size(); i++) printf(" %d ", phiSequence[i]);
		
		problem_->setSequence(phiSequence);
		problem_->KTNS();
		
		if(problem_->getNumSwitches() < numberOfSwitchesFound)
		{
			bestFoundSequence_.assign(phiSequence.begin(), phiSequence.end());
			numberOfSwitchesFound = problem_->getNumSwitches();
		}
		
		if(print_) printf("; %d switches\n", problem_->getNumSwitches());



		//
		// Second Permutation ..., I-2, I-1, .... , J-2, J-1
		//
		
		numberofPermutationGenerated++;
		phiSequence.assign(currentSequence.begin(), currentSequence.end());
		for(int i = 0; i < (int) comb.size(); i++)
		{
			phiSequence[comb[i]*2] = currentSequence[comb[permutations_[k][i]]*2+1];
			phiSequence[comb[i]*2+1] = currentSequence[comb[permutations_[k][i]]*2];

			if(print_) printf(" %d ", currentSequence[comb[permutations_[k][i]]]);
		}
		
		if(print_) printf("\n");
		if(print_) for(int i = 0; i < (int) phiSequence.size(); i++) printf(" %d ", phiSequence[i]);
		
		problem_->setSequence(phiSequence);
		problem_->KTNS();
		
		if(problem_->getNumSwitches() < numberOfSwitchesFound)
		{
			bestFoundSequence_.assign(phiSequence.begin(), phiSequence.end());
			numberOfSwitchesFound = problem_->getNumSwitches();
		}
		
		if(print_) printf("; %d switches\n", problem_->getNumSwitches());

	}
	return bestFoundSequence_;
}



void KOpt::kOptPrepare()
{
	KOpt::generateCombinations();
	KOpt::generateKPermutations(false);
}

/**
 * @brief      Prepare the k-opt with swap(2,2) to work.
 */
void KOpt::kOptPrepare2()
{
	KOpt::generateCombinations2();
	KOpt::generateKPermutations(false);
}

void KOpt::kOpt()
{
	KOpt::kOptPrepare();
	KOpt::kOptExecute();
}

void KOpt::kOptRestricted()
{
	KOpt::kOptPrepare();
	KOpt::kOptExecute();
}


void KOpt::swap2()
{
	KOpt::generateCombinations2();
	KOpt::generateKPermutations(false);
	KOpt::kOptExecute2();
}


/**
 * @brief      Execute the k-opt method.
 */
void KOpt::kOptExecute()
{
	bool hasImproved = true;
	vector<int>currentSequence = vector<int>(problem_->getSequence());
	bestFoundSequence_ = currentSequence;

	numberofPermutationGenerated = 0;


	problem_->KTNS();
	numberOfSwitches_ = problem_->getNumSwitches();
	numberOfSwitchesFound = numberOfSwitches_;
	if(print_) printf("Initial Sequence has %d switches\n", numberOfSwitches_);


	while(hasImproved)
	{
		hasImproved = false;
		for(auto comb : combinations_)
			permutate(currentSequence, comb);

		if(numberOfSwitchesFound < numberOfSwitches_)
		{
			currentSequence.assign(bestFoundSequence_.begin(), bestFoundSequence_.end());
			numberOfSwitches_ = numberOfSwitchesFound;
			hasImproved = true;
			if(print_) printf("\n\n ------ Found a better solution with %d switches -------\n\n", numberOfSwitches_);
		}

	}

	if(print_) printf("\n\n ------ Best solution found has %d switches -------\n\n", numberOfSwitches_);
	if(print_) printf("\nNumber of solutions generated: %lld \n", numberofPermutationGenerated);

	problem_->setSequence(currentSequence);
 	problem_->KTNS();
}

/**
 * @brief      Execute the k-opt method with swap(k, 2) neighborhood.
 */
void KOpt::kOptExecute2()
{
	bool hasImproved = true;
	vector<int>currentSequence = vector<int>(problem_->getSequence());
	bestFoundSequence_ = currentSequence;

	numberofPermutationGenerated = 0;

	problem_->KTNS();
	numberOfSwitches_ = problem_->getNumSwitches();
	numberOfSwitchesFound = numberOfSwitches_;
	if(print_) printf("Initial Sequence has %d switches\n", numberOfSwitches_);


	while(hasImproved)
	{
		hasImproved = false;
		for(auto comb : combinations_)
			permutate2(currentSequence, comb);

		if(numberOfSwitchesFound < numberOfSwitches_)
		{
			currentSequence.assign(bestFoundSequence_.begin(), bestFoundSequence_.end());
			numberOfSwitches_ = numberOfSwitchesFound;
			hasImproved = true;
			if(print_) printf("\n\n ------ Found a better solution with %d switches -------\n\n", numberOfSwitches_);
		}

	}

	if(print_) printf("\n\n ------ Best solution found has %d switches -------\n\n", numberOfSwitches_);
	if(print_) printf("\nNumber of solutions generated: %lld \n", numberofPermutationGenerated);

	problem_->setSequence(currentSequence);
 	problem_->KTNS();
}


/**
 * @brief      Execute kopt shuffling the combinations and permuation that will be verified.
 */
void  KOpt::kOptExecuteRandom()
{
		bool hasImproved = true;
	vector<int>currentSequence = vector<int>(problem_->getSequence());
	bestFoundSequence_ = currentSequence;

	numberofPermutationGenerated = 0;


	problem_->KTNS();
	numberOfSwitches_ = problem_->getNumSwitches();
	numberOfSwitchesFound = numberOfSwitches_;
	if(print_) printf("Initial Sequence has %d switches\n", numberOfSwitches_);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (combinations_.begin(), combinations_.end(), std::default_random_engine(seed));
	shuffle (permutations_.begin(), permutations_.end(), std::default_random_engine(seed));


	while(hasImproved)
	{
		hasImproved = false;
		for(auto comb : combinations_)
			permutate(currentSequence, comb);

		if(numberOfSwitchesFound < numberOfSwitches_)
		{
			currentSequence.assign(bestFoundSequence_.begin(), bestFoundSequence_.end());
			numberOfSwitches_ = numberOfSwitchesFound;
			hasImproved = true;
			if(print_) printf("\n\n ------ Found a better solution with %d switches -------\n\n", numberOfSwitches_);
		}

	}

	if(print_) printf("\n\n ------ Best solution found has %d switches -------\n\n", numberOfSwitches_);
	if(print_) printf("\nNumber of solutions generated: %lld \n", numberofPermutationGenerated);

	problem_->setSequence(currentSequence);
 	problem_->KTNS();
}
