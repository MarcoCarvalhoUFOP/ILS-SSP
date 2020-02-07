
#include "MTSP.hpp"
#include "FirstTry.hpp"
#include "KOpt.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS


MTSP::MTSP(string& filePath)
{
	numToolSwitches_ = 0;
	numJobs_ = 0;
	numTools_ = 0;
	magazineCapacity_ = 0;
	graph_ = NULL;
	kopt = NULL;
	filePath_ = filePath;
}

MTSP::~MTSP()
{
}

void MTSP::createGraph(int n,  GRAPH_TYPE type)
{
	if(graph_ != NULL)
		delete graph_;
	graph_ = new Graph(n, type);
}

void MTSP::createGraphLowerBound()
{
	createGraph(numJobs_, GRAPH_WEIGHTED);
	graph_->createGraphLowerBound(numJobs_, magazineCapacity_, jobTools_);
}

void MTSP::createGraphUpperBound()
{
	createGraph(numJobs_, GRAPH_WEIGHTED);
    graph_->createGraphUpperBound(numJobs_, jobTools_);
}

void MTSP::createGraphAugusto()
{
	createGraph(numTools_, GRAPH_WEIGHTED);
	graph_->createGraphAugusto(numJobs_, numTools_, jobTools_);
}

void MTSP::createGraphToolJob()
{
	createGraph(numTools_, GRAPH_WEIGHTED);
	graph_->createGraphToolJob(numJobs_, numTools_, jobTools_);
}


vector<vector<int>>& MTSP::getToolJobBinary()
{
	return toolJobBinary_;
}

void MTSP::setToolJobBinary(vector<vector<int>>& toolJobMatrix)
{
	toolJobBinary_.assign(toolJobMatrix.begin(), toolJobMatrix.end());
}

Graph* MTSP::getGraph()
{
	return graph_;
}

vector<int>& MTSP::getSequence()
{
	return sequence_;
}

vector<int>& MTSP::getNumToolInstant()
{
	return numToolIstant_;
}

void MTSP::setSequence(vector<int>& sequence)
{
	sequence_.assign(sequence.begin(), sequence.end());
}

int MTSP::getCapacity()
{
	return magazineCapacity_;
}

void MTSP::setCapacity(int  capacity)
{
	magazineCapacity_ = capacity;
}

vector<vector<int>>& MTSP::getToolSequence()
{
	return toolSequence_;
}

void MTSP::setToolSequence(vector<vector<int>>& toolSequence)
{
	toolSequence_.assign(toolSequence.begin(), toolSequence.end());
}

vector<vector<int>>& MTSP::getJobTools()
{
	return jobTools_;
}

void MTSP::setJobTools(vector<vector<int>>& jobTools)
{
	jobTools_.assign(jobTools.begin(), jobTools.end());
}

int MTSP::getNumSwitches()
{
	return numToolSwitches_;
}

int MTSP::getNumJobs()
{
	return numJobs_;
}

void MTSP::setNumJobs(int  numJob)
{
	numJobs_ = numJob;
}


void MTSP::setTimeElapsed(chrono::duration<double> timeElapsed)
{
	timeElapsed_ = timeElapsed;
}

chrono::duration<double>& MTSP::getTimeElapsed()
{
	return timeElapsed_;
}	

void MTSP::setTimeBestSolution(chrono::duration<double> timeElapsed)
{
	timeBestSolution_ = timeElapsed;
}

chrono::duration<double>& MTSP::getTimeBestSolution()
{
	return timeBestSolution_;
}



void MTSP::setTimeToBestSolution(chrono::high_resolution_clock::time_point end)
{
	endbestSolution_ = end;
}

chrono::high_resolution_clock::time_point& MTSP::getTimeToBestSolution()
{
	return endbestSolution_;
}


int MTSP::getIterBestSolution()
{
	return iterBestSolution_;
}

void swap(int *rhs, int *lhs)
{
	int aux = *rhs;
	*rhs = *lhs;
	*lhs = aux;
}

int MTSP::nextInstant(int tool, int time, int limit)
{
	for(int i = time + 1; i < limit; i++)
		if(toolSequence_[tool][sequence_[i]])
			return i;

	return limit+1;
}

/*
	Execute the KTNS (Keep Tools Needed Soonest) for the current sequence_.
	To discover the optimal loading layout.
	Need to set toolJobBinary_ matrix.
	return the number of tool switches.
*/
int MTSP::KTNS()
{
	return KTNS(numJobs_);
}

/*
		Execute the KTNS (Keep Tools Needed Soonest) for the interval [0, numbJobs).
		To discover the optimal loading layout.
		Need to set toolJobBinary_ matrix. 
		return the number of tool switches.
	*/
	int MTSP::KTNS(int numbJobs)
	{
		vector<pair<int, int>> toolInstant; // Guarda o tempo que a ferramenta será utilizada nas proximas tarefas e a respectiva ferramenta.
		toolSequence_ = vector<vector<int>>(toolJobBinary_);
		int numInserted = 0;

		for(int i = 0; i < numbJobs; i++)
		{

			if(numToolIstant_[sequence_[i]] == magazineCapacity_)
				continue; // A magazine neste tempo já está cheia.
		
			int toolsLeft = magazineCapacity_ - numToolIstant_[sequence_[i]]; // Quantidade de ferramentas que "faltam" para completar a capacidade da magazine
			
			if(i == 0)
			{
				//printf("TAREFA %d\n", sequence_[i]);
				/*for(int j = 0; j < numTools_; j++)
					if(toolSequence_[j][sequence_[i]])
						printf("Usa a ferramenta %d", j);
					printf("\n");*/
				/*vector<int> shouldBe, inserted;
				for(int j = 0; j < numTools_; j++)
					if(!toolSequence_[j][sequence_[i]]) // Para toda ferramenta que já não está presente na tarefa da posição 0.
						toolInstant.push_back(pair<int,int>(nextInstant(j, i, numbJobs), j)); // Insere a ferramenta e seu proximo tempo de uso.
			
				sort(toolInstant.begin(), toolInstant.end()); // Ordena as ferramentas pelo tempo.

				for(int j = 0; j < (int) toolInstant.size() && toolsLeft; j++)
				{
					toolsLeft--;
					toolSequence_[toolInstant[j].second][sequence_[i]] = 1; // Adiciona a ferrmenta toolInstant[j].second na tarefa i
					shouldBe.push_back(toolInstant[j].second);
					//printf("Inserted %d instant %d\n",toolInstant[j].second, toolInstant[j].first);
				}
				numInserted = 0;
				*/
				toolsLeft = magazineCapacity_ - numToolIstant_[sequence_[i]];

				for(int k = i + 1; k < numbJobs; k++)
				{
					for(int j = 0; j < numTools_; j++)
					{
						if(toolSequence_[j][sequence_[i]])
							continue;
						
						if(toolSequence_[j][sequence_[k]]) // Para toda ferramenta que já esta na magazine no i-1 e não faz parte da tarefa da posicao i.
						{
							toolSequence_[j][sequence_[i]] = 1; // Adiciona a ferrmenta toolInstant[j].second na tarefa i
							if(++numInserted == toolsLeft) break;
						}

					}
					if(numInserted == toolsLeft) break;
				}
			}
			else
			{

				/*toolInstant.clear();
				for(int j = 0; j < numTools_; j++)
					if(toolSequence_[j][sequence_[i-1]] && !toolSequence_[j][sequence_[i]]) // Para toda ferramenta que já esta na magazine no i-1 e não faz parte da tarefa da posicao i.
						toolInstant.push_back(pair<int,int>(nextInstant(j, i, numbJobs), j));// Insere a ferramenta e seu proximo tempo de uso.
				sort(toolInstant.begin(), toolInstant.end()); // Ordena as ferramentas pelo tempo.

				for(int j = 0; j < (int) toolInstant.size() && toolsLeft; j++)
				{
					toolsLeft--;
					toolSequence_[toolInstant[j].second][sequence_[i]] = 1; // Adiciona a ferrmenta toolInstant[j].second na tarefa i
				}
				
				toolsLeft = magazineCapacity_ - numToolIstant_[sequence_[i]]; // Quantidade de ferramentas que "faltam" para completar a capacidade da magazine
				*/
				numInserted = 0;
				for(int k = i + 1; k < numbJobs; k++)
				{
					for(int j = 0; j < numTools_; j++)
					{
						if(toolSequence_[j][sequence_[i]])
							continue;
						if(toolSequence_[j][sequence_[i-1]] && toolSequence_[j][sequence_[k]]) // Para toda ferramenta que já esta na magazine no i-1 e não faz parte da tarefa da posicao i.
						{
							toolSequence_[j][sequence_[i]] = 1; // Adiciona a ferrmenta toolInstant[j].second na tarefa i
							if(++numInserted == toolsLeft) break;
						}
					}
					if(numInserted == toolsLeft) break;
				}
			}
		}

		return evaluate(numbJobs);
	}

	int MTSP::evaluate()
	{
		return evaluate(numJobs_);
	}

	int MTSP::evaluate(int numJobs)
	{
		numToolSwitches_ = 0;

		for(int i = 0; i < numTools_; i++)
			numToolSwitches_ += toolSequence_[i][sequence_[0]];

		for(int i = 0; i < numTools_; i ++)
			for(int j = 1; j < numJobs ; j++)
				if(toolSequence_[i][sequence_[j]] == 1 && toolSequence_[i][sequence_[j-1]] == 0)
					numToolSwitches_++;

		return numToolSwitches_;
	}

	void MTSP::resizeProblem()
	{
		sequence_.clear();
		sequence_.assign(numJobs_,0);
		toolJobBinary_.clear();
		toolJobBinary_.resize(numTools_);
		jobTools_.clear();
		jobTools_.resize(numJobs_);
		toolSequence_.clear();
		toolSequence2_.clear();
		toolSequence_.resize(numTools_);
		toolSequence2_.resize(numTools_);
		numToolIstant_.clear();
		numToolIstant_.assign(numJobs_,0);
		for(int i = 0; i < numTools_; i++)
		{
			toolJobBinary_[i].clear();
			toolJobBinary_[i].assign(numJobs_, 0);
			toolSequence_[i].clear();
			toolSequence_[i].assign(numJobs_, 0);
		}

	}


	void MTSP::printSolutionToFile(char* filename)
	{
		FILE* output = fopen(&filename[0], "w");

		if(output == NULL)
		{
			printf("Erro ao abrir o arquivo %s\n", filename);
			return;
		}


		evaluate(numJobs_);
		fprintf(output, "Number of Tool Switches: %d \n\n", numToolSwitches_);
		fprintf(output, "Time elapsed: %lf \n", timeElapsed_.count());
		fprintf(output, "Tool Sequence:\n");

		fprintf(output, "    ");
		for(int i = 0; i < numJobs_; i++)
		{
			fprintf(output, "%3dJ", sequence_[i] + 1);
		}
		fprintf(output, "\n");

		for(int i = 0; i < numTools_; i++)
		{
			fprintf(output, "%3dT", i + 1);
			for(int j = 0; j < numJobs_; j++)
			{
				fprintf(output, "%4d", toolSequence_[i][sequence_[j]]);
			}
			fprintf(output, "\n");
		}

		fclose(output);
	}


	/*
	Problem is formatted as:

		@Three intengers
		NumberJobs NumberTools Capacity

		@Binary Matrix [Tools,Jobs]
		@Matrix[i][j] = 1, if job j requires tool i.
	*/
	void MTSP::readInputYanasse()
	{
		//printf("%s\n", &filePath_[0]);
		FILE* f = fopen( &filePath_[0] , "r" );
		assert(f != NULL);
		fscanf(f,"%d %d %d", &numJobs_, &numTools_, &magazineCapacity_);

		resizeProblem();


		for(int j = 0; j < numJobs_; j++)
		{
			sequence_[j] = j;
		}
		for(int i = 0; i < numTools_; i++)
		{
			for(int j = 0; j < numJobs_; j++)
			{
				fscanf(f, "%d", &toolJobBinary_[i][j]);
				if(toolJobBinary_[i][j])
				{
					jobTools_[j].push_back(i);
					numToolIstant_[j]++;
				}
			}
		}
		toolSequence_ = vector<vector<int>>(toolJobBinary_);
		fclose(f);
	}


	void MTSP::printToolJobBinary()
	{
		printf("Tools-Jobs Binary Matrix:\n");

		printf("    ");
		for(int i = 0; i < numJobs_; i++)
		{
			printf("%3dJ", sequence_[i] + 1);
		}
		printf("\n");

		for(int i = 0; i < numTools_; i++)
		{
			printf("%3dF", i + 1);
			for(int j = 0; j < numJobs_; j++)
			{
				printf("%4d", toolJobBinary_[i][sequence_[j]]);
			}
			printf("\n");
		}
		printf("\n");
	}


	void MTSP::printToolSequence()
	{
		printf("Tool Sequence:\n");

		printf("    ");
		for(int i = 0; i < numJobs_; i++)
		{
			printf("%3dJ", sequence_[i] + 1);
		}
		printf("\n");

		for(int i = 0; i < numTools_; i++)
		{
			printf("%3dT", i + 1);
			for(int j = 0; j < numJobs_; j++)
			{
				printf("%4d", toolSequence_[i][sequence_[j]]);
			}
			printf("\n");
		}
		printf("\n");
	}

	void MTSP::printToolJob()
	{
		printf("Tools-Job matrix:\n");
		for(int i = 0; i < numJobs_; i++)
		{
			printf("%3dJ", i + 1);
		}
		printf("\n");

		for(int i = 0; i < magazineCapacity_; i++)
		{
			for(int j = 0; j < numJobs_; j++)
			{
				if((int)jobTools_[j].size() > i)
					printf("%4d", jobTools_[j][i] + 1);
				else
					printf("    ");
			}
			printf("\n");
		}
		printf("\n");
	}

	void MTSP::printProblem()
	{
		printf("Number of Jobs: %d\n", numJobs_);
		printf("Number of Tools: %d\n", numTools_);
		printf("Capacity: %d\n\n", magazineCapacity_);


		evaluate();

		printToolJobBinary();
		printToolJob();

	}


	void MTSP::printSolution()
	{
		evaluate(numJobs_);
		printf("\n\n --- Current Solution ---\n\n");
		printf("Time elapsed: %lf \n", timeElapsed_.count());
		printf("Number of Tool Switches: %d \n\n", numToolSwitches_);
		printToolSequence();
	}



	void MTSP::printSolutionSumary(FILE* summaryFile, FILE* allSummaryFile)
	{	
		assert(summaryFile != NULL);
		assert(allSummaryFile != NULL);

		fprintf(summaryFile, "%-60s \t %5d \t %4.12lf\n", &filePath_[0], getNumSwitches(), getTimeElapsed().count());
		fprintf(allSummaryFile, "%-60s \t %5d \t %4.12lf\n", &filePath_[0], getNumSwitches(), getTimeElapsed().count());
	}

	void MTSP::printSolutionSumary(FILE* summaryFile, FILE* allSummaryFile, string& summaryEntry)
	{	
		assert(summaryFile != NULL);
		assert(allSummaryFile != NULL);

		fprintf(summaryFile, "%s\n", &summaryEntry[0]);
		fprintf(allSummaryFile, "%s\n", &summaryEntry[0]);
	}



	/*
		Check if Job X dominates Y, i.e. all tools needed to executed job y is also needed to executed x but not necessarily the opposite.
	*/
	bool MTSP::isDominated(int dominant, int dominated, bool print)
	{
		if (dominant == dominated)
			return false;
		for (int i = 0; i < numTools_; i++)
		{
			if (toolJobBinary_[i][dominated] && !toolJobBinary_[i][dominant]) // If the Dominated Job need the ith and the Dominant Job doesnt it doesn't has a dominant relationship.
			{
				if (print)
					printf("Job %d need tool %d but job %d doesn't need!\n", dominated, i, dominant);
				return false;
			}
		}
		return true;
	}


void MTSP::localSearch(int function, bool print, int numIterStalled)
{
	if (function == ILS_2OPT)
	{
		if (kopt == NULL)
		{
			kopt = new KOpt(this, 2, print, "");
			kopt->kOpt();
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else
	{
		vector<int> bestSequence(sequence_.begin(), sequence_.end());
		int bestNumberOfSwitches = KTNS();
		vector<int> currentSequence(sequence_.begin(), sequence_.end());
		vector<int> rotateStart(sequence_.begin(), sequence_.end());
		vector<int> rotateEnd(sequence_.begin(), sequence_.end());
		int currentStallNumber = 0;
		int numIter = 0;
		while (currentStallNumber++ < numIterStalled)
		{
			numIter++;
			int indexOfOne = -1, indexOfLastOne;
			if (print) printf("Started With %d number of switches \n", bestNumberOfSwitches);

			for (int i = 0; i < numTools_; i++)
			{
				indexOfOne = -1;
				for (int j = 0; j < numJobs_; j++)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1)
								j++;
							indexOfLastOne = j;

						}
						else
							indexOfOne = -1;
					}
					else // Finding another One's block.
					{


						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock + 1 < numJobs_ && toolSequence_[i][currentSequence[endOfTheBlock + 1]] == 1)
							{
								endOfTheBlock++;
							}

							for (int k = indexOfLastOne; k >= indexOfOne; k--)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.begin() + k, rotateStart.begin() + k + 1, rotateStart.begin() + j);

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.begin() + k, rotateEnd.begin() + k + 1, rotateEnd.begin() + endOfTheBlock + 1);

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int currentSwitches = KTNS();

								int bestInsert = 0;

								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);

								currentSwitches = KTNS();
								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}

								if (bestInsert == 1)
								{
									j--;
								}


								currentSequence.assign(bestSequence.begin(), bestSequence.end());
								rotateStart.assign(bestSequence.begin(), bestSequence.end());
								rotateEnd.assign(bestSequence.begin(), bestSequence.end());
							}
							j = indexOfOne;
							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1)
							{
								j++;  //Find then end of the first block.
							}
							
							indexOfOne = -1;
						}

					}
				}

			}

			currentSequence.assign(bestSequence.begin(), bestSequence.end());
			for (int i = 0; i < numTools_; i++)
			{
				indexOfOne = -1;
				for (int j = numJobs_ - 1; j >= 0; j--)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							indexOfLastOne = j;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
							{
								j--;
							}
							indexOfLastOne = j;

						}
						else
						{
							indexOfOne = -1;
						}
					}
					else // Finding another One's block.
					{
						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock - 1 >= 0 && toolSequence_[i][currentSequence[endOfTheBlock - 1]] == 1)
							{
								endOfTheBlock--;
							}

							for (int k = indexOfLastOne; k <= indexOfOne; k++)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.rbegin() + (numJobs_ - k - 1), rotateStart.rbegin() + (numJobs_ - k), rotateStart.rbegin() + (numJobs_ - j - 1));

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.rbegin() + (numJobs_ - k - 1), rotateEnd.rbegin() + (numJobs_ - k), rotateEnd.rbegin() + (numJobs_ - endOfTheBlock));

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int bestInsert = 0;
								int currentSwitches = KTNS();

								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);
								currentSwitches = KTNS();
								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;

									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}

								if (bestInsert == 1)
									j++;

								currentSequence.assign(bestSequence.begin(), bestSequence.end());
								rotateStart.assign(bestSequence.begin(), bestSequence.end());
								rotateEnd.assign(bestSequence.begin(), bestSequence.end());

							}


							j = indexOfOne;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
							{
								j--;
							}
							indexOfOne = -1;
						}

					}
				}
			}
		}
		setSequence(bestSequence);
		KTNS();
		//printf("Number of changes = %d \n", numIter - numIterStalled);
		if (print) printf("Best sequence With %d number of switches \n", bestNumberOfSwitches);
	}

}


void MTSP::localSearchIterative(int function, bool print, int numIterStalled, double partialSize )
{
	if (function == ILS_2OPT)
	{
		if (kopt == NULL)
		{
			kopt = new KOpt(this, 2, print, "");
			kopt->kOpt();	
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else if(function == ILS_LS_PART_2OPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, KOPT_PARTIAL, partialSize, print, "");		
			kopt->kOpt();
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else if(function == ILS_LS_22SWAPOPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, print, "");		
			kopt->swap2();
		}
		else
		{
			kopt->kOptExecute2();
		}
	}
	else if(function == ILS_LS_PART_22SWAPOPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, KOPT_PARTIAL, partialSize, print, "");		
			kopt->swap2();
		}
		else
		{
			kopt->kOptExecute2();
		}
	}
	else
	{
		vector<int> bestSequence(sequence_.begin(), sequence_.end());
		int bestNumberOfSwitches = KTNS();
		vector<int> currentSequence(sequence_.begin(), sequence_.end());
		vector<int> rotateStart(sequence_.begin(), sequence_.end());
		vector<int> rotateEnd(sequence_.begin(), sequence_.end());
		vector<int> randomRow;

		for(int i = 0;  i < numTools_; i++) {
			randomRow.push_back(i);
		}
		int currentStallNumber = 0;
		int numIter = 0;
		while (currentStallNumber++ < numIterStalled)
		{
			numIter++;
			int indexOfOne = -1, indexOfLastOne;
			if (print) printf("Started With %d number of switches \n", bestNumberOfSwitches);
			std::random_shuffle(randomRow.begin(), randomRow.end());

			for (int i : randomRow)
			{
				/*printf("Current Sequence : ");
				for (int j = 0; j < numJobs_; j++)
				{
					printf(" %d", currentSequence[j]);
				}
				printf("\n");	

				printToolSequence();
				printf("\n");
*/
				indexOfOne = -1;
				for (int j = 0; j < numJobs_; j++)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1)
							{
//								printf("%d, %d\n", j+1, toolSequence_[i][currentSequence[j + 1]] );
								j++;
							}
							indexOfLastOne = j;
//							printf("%d\n", indexOfLastOne);

						}
						else
						{
							indexOfOne = -1;
						}
					}
					else // Finding another One's block.
					{


						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock + 1 < numJobs_ && toolSequence_[i][currentSequence[endOfTheBlock + 1]] == 1)
							{
								endOfTheBlock++;
							}

							for (int k = indexOfLastOne; k >= indexOfOne; k--)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.begin() + k, rotateStart.begin() + k + 1, rotateStart.begin() + j);

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.begin() + k, rotateEnd.begin() + k + 1, rotateEnd.begin() + endOfTheBlock + 1);

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int currentSwitches = KTNS();

								int bestInsert = 0;
/*
								printf("rotate start %d (%d, %d) (%d, %d): ", k, indexOfOne, indexOfLastOne, j, endOfTheBlock);
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", rotateStart[j]);
								} 
								printf("    -- %d\n", currentSwitches);


*/

								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf(">Found sequence With %d number of switches \n", bestNumberOfSwitches);

								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);


								/*printf("rotate end : ");
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", rotateEnd[j]);
								}
								printf("    -- %d\n", currentSwitches);
*/
								currentSwitches = KTNS();
								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf(">Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}

								if (bestInsert == 1)
								{
									j--;
								}


								currentSequence.assign(bestSequence.begin(), bestSequence.end());
								rotateStart.assign(bestSequence.begin(), bestSequence.end());
								rotateEnd.assign(bestSequence.begin(), bestSequence.end());


								/*printf("Current Sequence After Change : ");
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", currentSequence[j]);
								}
								printf(" new j = %d \n", j); 
							*/
							}
							j = indexOfOne;
							indexOfOne = -1;
							/*printf("Current Sequence After Change : ");
							for (int j = 0; j < numJobs_; j++)
							{
								printf(" %d", currentSequence[j]);
							}
							printf(" new j = %d \n", j); 
						*/
						}

					}
				}

			}

			currentSequence.assign(bestSequence.begin(), bestSequence.end());
			std::random_shuffle(randomRow.begin(), randomRow.end());

			for (int i : randomRow)
			{
				indexOfOne = -1;
				for (int j = numJobs_ - 1; j >= 0; j--)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							indexOfLastOne = j;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
							{
								j--;
							}
							indexOfLastOne = j;

						}
						else
						{
							indexOfOne = -1;
						}
					}
					else // Finding another One's block.
					{
						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock - 1 >= 0 && toolSequence_[i][currentSequence[endOfTheBlock - 1]] == 1)
							{
								endOfTheBlock--;
							}

							for (int k = indexOfLastOne; k <= indexOfOne; k++)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.rbegin() + (numJobs_ - k - 1), rotateStart.rbegin() + (numJobs_ - k), rotateStart.rbegin() + (numJobs_ - j - 1));

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.rbegin() + (numJobs_ - k - 1), rotateEnd.rbegin() + (numJobs_ - k), rotateEnd.rbegin() + (numJobs_ - endOfTheBlock));

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int bestInsert = 0;
								int currentSwitches = KTNS();

								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);
								currentSwitches = KTNS();
								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;

									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}

								if (bestInsert == 1)
									j++;

								currentSequence.assign(bestSequence.begin(), bestSequence.end());
								rotateStart.assign(bestSequence.begin(), bestSequence.end());
								rotateEnd.assign(bestSequence.begin(), bestSequence.end());

							}


							j = indexOfOne;
							indexOfOne = -1;
						}

					}
				}
			}
		}
		setSequence(bestSequence);
		KTNS();
		//printf("Number of changes = %d \n", numIter - numIterStalled);
		if (print) printf("Best sequence With %d number of switches \n", bestNumberOfSwitches);
	}

}


void MTSP::localSearchFull(int function, bool print, int numIterStalled)
{
	if (function == ILS_2OPT)
	{
		if (kopt == NULL)
		{
			kopt = new KOpt(this, 2, print, "");
			kopt->kOpt();
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else
	{
		vector<int> bestSequence(sequence_.begin(), sequence_.end());
		int bestNumberOfSwitches = KTNS();
		vector<int> currentSequence(sequence_.begin(), sequence_.end());
		vector<int> rotateStart(sequence_.begin(), sequence_.end());
		vector<int> rotateEnd(sequence_.begin(), sequence_.end());
		int currentStallNumber = 0;
		int numIter = 0;
		while (currentStallNumber++ < numIterStalled)
		{
			numIter++;
			int indexOfOne = -1, indexOfLastOne;
			if(print) printf("Started With %d number of switches \n", bestNumberOfSwitches);
			/*Left to Right ->*/
			for (int i = 0; i < numTools_; i++)
			{
				indexOfOne = -1;
				
				for (int j = 0; j < numJobs_; j++)
				{
					
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{

							indexOfOne = j;

							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1) // Find the end of the current block!
							{
								j++;
							}
							indexOfLastOne = j;
							vector<int> currentLocalSequence(currentSequence.begin(), currentSequence.end());
							vector<int> bestLocalSequence(currentSequence.begin(), currentSequence.end());

							int localSwitches;

							localSwitches = bestNumberOfSwitches;
							bool changed = false;
							//printf("for (int x = %d + 1; x < %d; x++)\n", j, numJobs_);
							for (int x = j + 1; x < numJobs_; x++)
							{
								if (toolSequence_[i][currentSequence[x]] == 1) // Found a One's Block!
								{
									int endOfTheBlock = x;
									while (endOfTheBlock + 1 < numJobs_ && toolSequence_[i][currentSequence[endOfTheBlock + 1]] == 1)
									{
										endOfTheBlock++;   // Finding the end of this One's Block
									}

									currentLocalSequence.assign(currentSequence.begin(), currentSequence.end());
									bestLocalSequence.assign(currentSequence.begin(), currentSequence.end());
									rotateStart.assign(currentSequence.begin(), currentSequence.end());
									rotateEnd.assign(currentSequence.begin(), currentSequence.end());

									for (int k = indexOfLastOne; k >= indexOfOne; k--) // Try to reduce inversions.
									{
										/*Rotate to the start of the The current One's Block*/
										rotate(rotateStart.begin() + k, rotateStart.begin() + k + 1, rotateStart.begin() + x);

										/*Rotate to the start of the The current One's Block*/
										rotate(rotateEnd.begin() + k, rotateEnd.begin() + k + 1, rotateEnd.begin() + endOfTheBlock + 1);

										/*Check rotate to the start*/
										setSequence(rotateStart);
										int currentSwitches = KTNS();
										int bestInsert = 0;

										if (currentSwitches <= localSwitches)
										{
											changed = true;
											bestLocalSequence.assign(rotateStart.begin(), rotateStart.end());
											if (currentSwitches < localSwitches)
												currentStallNumber = 0;
											localSwitches = currentSwitches;
											bestInsert = 1;
											if (print) printf("Found sequence With %d number of switches \n", localSwitches);
										}
										/*Check rotate to the end*/
										setSequence(rotateEnd);

										currentSwitches = KTNS();
										if (currentSwitches <= localSwitches)
										{
											changed = true;
											bestLocalSequence.assign(rotateEnd.begin(), rotateEnd.end());
											if (currentSwitches < localSwitches)
												currentStallNumber = 0;
											localSwitches = currentSwitches;
											bestInsert = 1;
											if (print) printf("Found sequence With %d number of switches \n", localSwitches);
										}

										if (bestInsert == 1)
										{
											x--;
										}


										currentLocalSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
										rotateStart.assign(bestLocalSequence.begin(), bestLocalSequence.end());
										rotateEnd.assign(bestLocalSequence.begin(), bestLocalSequence.end());
									}

									x = endOfTheBlock; // Jump to the next block. 
									//break;
								}
							}

							if (changed == true && localSwitches <= bestNumberOfSwitches)
							{
								bestNumberOfSwitches = localSwitches;
								bestSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
								currentSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
								//localX = x;
							}

							j = indexOfOne;	
							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1) // Find the end of the current block!
							{
								j++;
							}
							indexOfOne = -1;

							/*printf("Linha no Final ");
							for (int yyy = 0; yyy < numJobs_; yyy++)
							{
								printf(" %d ", toolSequence_[i][currentSequence[yyy]]);
							}
							printf("\n novo j = %d \n\n", j);	 */

						}
					}
				}
			}


			currentSequence.assign(bestSequence.begin(), bestSequence.end());
			/*Right to left <-*/

			for (int i = 0; i < numTools_; i++)
			{
				indexOfOne = -1;
				for (int j = numJobs_ - 1; j >= 0; j--)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							indexOfLastOne = j;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
							{
								j--;
							}
							indexOfLastOne = j;

							vector<int> currentLocalSequence(currentSequence.begin(), currentSequence.end());
							vector<int> bestLocalSequence(currentSequence.begin(), currentSequence.end());

							int localSwitches;
							bool changed = false;

							localSwitches = bestNumberOfSwitches;

							for (int x = j - 1; x >= 0; x--)
							{
								if (toolSequence_[i][currentSequence[x]] == 1) // Found a One's Block!
								{
									int endOfTheBlock = x;
									while (endOfTheBlock - 1 >= 0 && toolSequence_[i][currentSequence[endOfTheBlock - 1]] == 1)
									{
										endOfTheBlock--;     // Finding the end of this One's Block
									}

									currentLocalSequence.assign(currentSequence.begin(), currentSequence.end());
									bestLocalSequence.assign(currentSequence.begin(), currentSequence.end());
									rotateStart.assign(bestLocalSequence.begin(), bestLocalSequence.end());
									rotateEnd.assign(bestLocalSequence.begin(), bestLocalSequence.end());

									for (int k = indexOfLastOne; k <= indexOfOne; k++) // Try to reduce inversions.
									{
										/*Rotate to the start of the The current One's Block*/
										rotate(rotateStart.rbegin() + (numJobs_ - k - 1), rotateStart.rbegin() + (numJobs_ - k), rotateStart.rbegin() + (numJobs_ - x - 1));

										/*Rotate to the start of the The current One's Block*/
										rotate(rotateEnd.rbegin() + (numJobs_ - k - 1), rotateEnd.rbegin() + (numJobs_ - k), rotateEnd.rbegin() + (numJobs_ - endOfTheBlock));

										/*Check rotate to the start*/
										setSequence(rotateStart);
										int currentSwitches = KTNS();
										int bestInsert = 0;

										if (currentSwitches <= localSwitches)
										{
											changed = true;
											bestLocalSequence.assign(rotateStart.begin(), rotateStart.end());
											if (currentSwitches < localSwitches)
												currentStallNumber = 0;
											localSwitches = currentSwitches;
											bestInsert = 1;
											if (print) printf("Found sequence With %d number of switches \n", localSwitches);
										}
										/*Check rotate to the end*/
										setSequence(rotateEnd);

										currentSwitches = KTNS();
										if (currentSwitches <= localSwitches)
										{
											changed = true;
											bestLocalSequence.assign(rotateEnd.begin(), rotateEnd.end());
											if (currentSwitches < localSwitches)
												currentStallNumber = 0;
											localSwitches = currentSwitches;
											bestInsert = 1;
											if (print) printf("Found sequence With %d number of switches \n", localSwitches);
										}

										if (bestInsert == 1)
											x++;
										
										currentLocalSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
										rotateStart.assign(bestLocalSequence.begin(), bestLocalSequence.end());
										rotateEnd.assign(bestLocalSequence.begin(), bestLocalSequence.end());
									}
									x = endOfTheBlock - 1; // Jump to the next block.
								}
								
							}

							if (changed == true && localSwitches <= bestNumberOfSwitches)
							{
								bestNumberOfSwitches = localSwitches;
								bestSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
								currentSequence.assign(bestLocalSequence.begin(), bestLocalSequence.end());
							}
							j = indexOfOne;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
								j--;
							indexOfOne = -1;
						}
					}						
				}
			}
		}
		setSequence(bestSequence);
		KTNS();

		//printf("Number of changes = %d \n", numIter - numIterStalled);
		if (print) printf("Best sequence With %d number of switches \n", bestNumberOfSwitches);
	}

}

void MTSP::ILS(int numIter, double beta, const int function,  bool print, int numIterLocalSearch, double partialSize, long timeLimit)
{
	//FirstTry fst(this, print, "");
	//fst.firstTry(FST_BFS, FST_NOTWINS);

    vector<int> randomSolution;

    for( int i = 0; i < getNumJobs(); i++) {
        randomSolution.push_back(i);
    }
    std::random_shuffle(randomSolution.begin(), randomSolution.end());

    setSequence(randomSolution);


    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();


	localSearchIterative(ILS_LOCALSEARCH, print, numIterLocalSearch);

	vector<int> bestSequence(sequence_.begin(), sequence_.end());
	int bestNumberOfSwitches = KTNS();
	vector<int> currentSequence(sequence_.begin(), sequence_.end());
	int curIter = 0;
	iterBestSolution_ = 0;

	int plateauNumber = 0;
	int maxPlateau = 200;

	while (++curIter <= numIter)
	{
		if(plateauNumber == maxPlateau)
			break;

        currentTime = chrono::high_resolution_clock::now();

        auto time_elapsed =  std::chrono::duration_cast<std::chrono::seconds>(currentTime - start);
        printf("time elapsed %d from %d\n", time_elapsed.count(), timeLimit);
        if ( time_elapsed.count() >= timeLimit) {
            break;
        }

		//Pertubation
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator(seed);
		uniform_int_distribution<int> distribution(0, numJobs_ - 1);

		for (int i = 0; i < (int) ( numJobs_ * beta); i++)
		{
			int rhs, lhs;
			rhs = distribution(generator);
			lhs = rhs;

			while (lhs == rhs)
				lhs = distribution(generator);

			swap(currentSequence[rhs], currentSequence[lhs]);
		}
		

		//Local Search step
		setSequence(currentSequence);

		if(function == ILS_LS_2OPT)
		{
			localSearchIterative(ILS_2OPT, print, numIterLocalSearch);
			localSearchIterative(ILS_LOCALSEARCH, print, numIterLocalSearch);
		}
		else if (function == ILS_LS_PART_2OPT)
		{
			localSearchIterative(ILS_LS_PART_2OPT, print, numIterLocalSearch, partialSize);
			localSearchIterative(ILS_LOCALSEARCH, print, numIterLocalSearch);
		}
		else if (function == ILS_LS_22SWAPOPT)
		{
			localSearchIterative(ILS_LS_22SWAPOPT, print, numIterLocalSearch);
			localSearchIterative(ILS_LOCALSEARCH, print, numIterLocalSearch);
		}
		else if (function == ILS_LS_PART_22SWAPOPT)
		{
			localSearchIterative(ILS_LS_PART_22SWAPOPT, print, numIterLocalSearch, partialSize);
			localSearchIterative(ILS_LOCALSEARCH, print, numIterLocalSearch);
		}
		else
		{
			localSearchIterative(function, print, numIterLocalSearch);
		}


		currentSequence.assign(getSequence().begin(), getSequence().end());

		/*Criterio de Aceitacao*/
		int currentSwitches = getNumSwitches();
		
		if ( currentSwitches <= bestNumberOfSwitches)
		{
			if (function == ILS_2OPT && currentSwitches == bestNumberOfSwitches)
			{
				currentSequence.assign(bestSequence.begin(), bestSequence.end());
			}
			else
			{
				if (iterBestSolution_ == 0 || currentSwitches < bestNumberOfSwitches)
				{
					plateauNumber = 0;
					endbestSolution_ = chrono::high_resolution_clock::now();
					iterBestSolution_ = curIter;
					//printf("switches: %d, iter: %d\n", bestNumberOfSwitches, curIter);
				}

				bestSequence.assign(currentSequence.begin(), currentSequence.end());
				bestNumberOfSwitches = currentSwitches;

			}
		}
		else
		{
			currentSequence.assign(bestSequence.begin(), bestSequence.end());
		}

		plateauNumber++;

	}
	setSequence(bestSequence);
	KTNS();
}




















void MTSP::localSearchIterativeCORRECT(int function, bool print, int numIterStalled, double partialSize )
{
	if (function == ILS_2OPT)
	{
		if (kopt == NULL)
		{
			kopt = new KOpt(this, 2, print, "");
			kopt->kOpt();	
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else if(function == ILS_LS_PART_2OPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, KOPT_PARTIAL, partialSize, print, "");		
			kopt->kOpt();
		}
		else
		{
			kopt->kOptExecute();
		}
	}
	else if(function == ILS_LS_22SWAPOPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, print, "");		
			kopt->swap2();
		}
		else
		{
			kopt->kOptExecute2();
		}
	}
	else if(function == ILS_LS_PART_22SWAPOPT)
	{
		if (kopt == NULL)
		{

			kopt = new KOpt(this, 2, KOPT_PARTIAL, partialSize, print, "");		
			kopt->swap2();
		}
		else
		{
			kopt->kOptExecute2();
		}
	}
	else
	{
		vector<int> bestSequence(sequence_.begin(), sequence_.end());
		vector<int> bestStart(sequence_.begin(), sequence_.end());
		vector<int> bestEnd(sequence_.begin(), sequence_.end());
		int bestNumberOfSwitches = KTNS();
		int bestSwitchesStart = KTNS();
		int bestSwitchesEnd = KTNS();
		vector<int> currentSequence(sequence_.begin(), sequence_.end());
		vector<int> rotateStart(sequence_.begin(), sequence_.end());
		vector<int> rotateEnd(sequence_.begin(), sequence_.end());
		int currentStallNumber = 0;
		int numIter = 0;

		vector<int> randomRow;

		for(int i = 0 ; i < numTools_; i++) {
			randomRow.push_back(i);
		}


		while (currentStallNumber++ < numIterStalled)
		{
			numIter++;
			int indexOfOne = -1, indexOfLastOne;
			if (print) printf("Started With %d number of switches \n", bestNumberOfSwitches);
			
			std::random_shuffle(randomRow.begin(), randomRow.end());
			
			for (int i : randomRow)
			{
				printf("Current Sequence : ");
				for (int j = 0; j < numJobs_; j++)
				{
					printf(" %d", currentSequence[j]);
				}
				printf("\n");	

				printToolSequence();
				printf("\n");

				indexOfOne = -1;
				for (int j = 0; j < numJobs_; j++)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							while (j + 1 < numJobs_ && toolSequence_[i][currentSequence[j + 1]] == 1)
							{
								printf("%d, %d\n", j+1, toolSequence_[i][currentSequence[j + 1]] );
								j++;
							}
							indexOfLastOne = j;

						}
						else
						{
							indexOfOne = -1;
						}
					}
					else // Finding another One's block.
					{


						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock + 1 < numJobs_ && toolSequence_[i][currentSequence[endOfTheBlock + 1]] == 1)
							{
								endOfTheBlock++;
							}

							for (int k = indexOfLastOne; k >= indexOfOne; k--)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.begin() + k, rotateStart.begin() + k + 1, rotateStart.begin() + j);

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.begin() + k, rotateEnd.begin() + k + 1, rotateEnd.begin() + endOfTheBlock + 1);

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int currentSwitches = KTNS();

								int bestInsert = 0;

								printf("rotate start %d (%d, %d) (%d, %d): ", k, indexOfOne, indexOfLastOne, j, endOfTheBlock);
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", rotateStart[j]);
								} 
								printf("    -- %d\n", currentSwitches);


								if (currentSwitches <= bestSwitchesStart)
								{
									bestStart.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestSwitchesStart)
										currentStallNumber = 0;
									bestSwitchesStart = currentSwitches;
									j--;	
									if (print) printf(">Found sequence With %d number of switches \n", bestSwitchesStart);

								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);


								printf("rotate end : ");
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", rotateEnd[j]);
								}
								printf("    -- %d\n", currentSwitches);

								currentSwitches = KTNS();
								if (currentSwitches <= bestSwitchesEnd)
								{
									bestEnd.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestSwitchesEnd)
										currentStallNumber = 0;
									bestSwitchesEnd = currentSwitches;
									bestInsert = 1;
									if (print) printf(">Found sequence With %d number of switches \n", bestSwitchesEnd);
								}


								rotateStart.assign(bestStart.begin(), bestStart.end());
								rotateEnd.assign(bestEnd.begin(), bestEnd.end());

									
								printf("Current Sequence After Change : ");
								for (int j = 0; j < numJobs_; j++)
								{
									printf(" %d", currentSequence[j]);
								}
								printf(" new j = %d \n", j); 
							}

							if(bestSwitchesEnd < bestSwitchesStart && bestSwitchesEnd < bestNumberOfSwitches )
							{
								currentSequence.assign(bestEnd.begin(), bestEnd.end());
								bestNumberOfSwitches = bestSwitchesEnd;
							}
							else if(bestSwitchesStart < bestSwitchesEnd && bestSwitchesStart < bestNumberOfSwitches )
							{
								currentSequence.assign(bestStart.begin(), bestStart.end());
								bestNumberOfSwitches = bestSwitchesStart;
							}

							j = indexOfOne;
							indexOfOne = -1;
							printf("Current Sequence After Change : ");
							for (int j = 0; j < numJobs_; j++)
							{
								printf(" %d", currentSequence[j]);
							}
							printf(" new j = %d \n", j); 
						}

					}
				}

			}

			currentSequence.assign(bestSequence.begin(), bestSequence.end());
			
			std::random_shuffle(randomRow.begin(), randomRow.end());
			
			for (int i : randomRow)
			{
				indexOfOne = -1;
				for (int j = numJobs_ - 1; j >= 0; j--)
				{
					if (indexOfOne == -1) // If index is -1 than we are on the searching for a One phase.
					{
						if (toolSequence_[i][currentSequence[j]] == 1)	// There is a One.
						{
							indexOfOne = j;
							indexOfLastOne = j;
							while (j - 1 >= 0 && toolSequence_[i][currentSequence[j - 1]] == 1)
							{
								j--;
							}
							indexOfLastOne = j;

						}
						else
						{
							indexOfOne = -1;
						}
					}
					else // Finding another One's block.
					{
						if (toolSequence_[i][currentSequence[j]] == 1) // Found a One's Block!
						{

							int endOfTheBlock = j;

							while (endOfTheBlock - 1 >= 0 && toolSequence_[i][currentSequence[endOfTheBlock - 1]] == 1)
							{
								endOfTheBlock--;
							}

							for (int k = indexOfLastOne; k <= indexOfOne; k++)
							{
								/*Rotate to the start of the The current One's Block*/
								rotate(rotateStart.rbegin() + (numJobs_ - k - 1), rotateStart.rbegin() + (numJobs_ - k), rotateStart.rbegin() + (numJobs_ - j - 1));

								/*Rotate to the start of the The current One's Block*/
								rotate(rotateEnd.rbegin() + (numJobs_ - k - 1), rotateEnd.rbegin() + (numJobs_ - k), rotateEnd.rbegin() + (numJobs_ - endOfTheBlock));

								/*Check rotate to the start*/
								setSequence(rotateStart);
								int bestInsert = 0;
								int currentSwitches = KTNS();

								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateStart.begin(), rotateStart.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;
									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}
								/*Check rotate to the end*/
								setSequence(rotateEnd);
								currentSwitches = KTNS();
								if (currentSwitches <= bestNumberOfSwitches)
								{
									bestSequence.assign(rotateEnd.begin(), rotateEnd.end());
									if (currentSwitches < bestNumberOfSwitches)
										currentStallNumber = 0;
									bestNumberOfSwitches = currentSwitches;
									bestInsert = 1;

									if (print) printf("Found sequence With %d number of switches \n", bestNumberOfSwitches);
								}

								if (bestInsert == 1)
									j++;

								currentSequence.assign(bestSequence.begin(), bestSequence.end());
								rotateStart.assign(bestSequence.begin(), bestSequence.end());
								rotateEnd.assign(bestSequence.begin(), bestSequence.end());

							}


							j = indexOfOne;
							indexOfOne = -1;
						}

					}
				}
			}
		}
		setSequence(bestSequence);
		KTNS();
		//printf("Number of changes = %d \n", numIter - numIterStalled);
		if (print) printf("Best sequence With %d number of switches \n", bestNumberOfSwitches);
	}

}

