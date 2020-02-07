
#include "VND.hpp"
#include "FirstTry.hpp"

VND::VND(MTSP* mtsp, int firstK, int lastK, bool print, string methodName) : Solution(mtsp, print, methodName)
{


	neighborhoodStructures = vector<KOpt*>(lastK - firstK + 1);
	//KOpt(MTSP* mtsp, int k, const int type, double partialSize, bool print, string methodName);

	for(int i = firstK; i <= lastK; i++)
	{
		neighborhoodStructures[i - firstK] =  new KOpt(mtsp, i, print, ""); // new KOpt(mtsp, i, KOPT_PARTIAL, 0.5, false, methodName);
		neighborhoodStructures[i - firstK]->kOptPrepare2();
	}
	k0_ = firstK;
	k1_ = lastK;
}


void VND::ExecuteVND()
{
	int currentK = 0;
	
	FirstTry fst(problem_, false, "");
	fst.firstTry(FST_BFS, FST_NOTWINS);

	int bestNumberOfSwitches = problem_->KTNS();
	vector<int> bestFoundSequence =  problem_->getSequence();

	while(currentK < ( k1_ - k0_ + 1) )
	{
		neighborhoodStructures[currentK]->kOptExecute2();//kOptExecuteRandom();

		problem_->localSearchIterative(ILS_LOCALSEARCH, print_, 50);
		int currentSwitches = problem_->KTNS();

		if(bestNumberOfSwitches > currentSwitches)
		{
			bestNumberOfSwitches = currentSwitches;
			currentK = 0;
			bestFoundSequence =  problem_->getSequence();
			if(print_) printf("Best solution with %d switches.\n", bestNumberOfSwitches);
		}
		else
		{
			problem_->setSequence(bestFoundSequence);
			currentK++;
			if(print_) printf("No better solution found with k = %d.\n", k0_ + currentK);
		}
	}
	problem_->KTNS();
}

