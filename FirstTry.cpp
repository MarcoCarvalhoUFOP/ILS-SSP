#include "FirstTry.hpp"
#include "Misc.hpp"


void FirstTry::run()
{
	
}

FirstTry::FirstTry(MTSP* problem, bool print, string methodName) : Solution(problem, print, methodName), checker(problem, print, methodName)
{
	if (print_) printf("Creating Graph");
	problem->createGraphToolJob();
	graph = problem->getGraph();
	if (print_) printf("Printing Graph");
	if (print_) graph->print();
}

bool comparePair(const pair<double, int>& lhs, const pair<double, int>&rhs)
{
	if (lhs.first == rhs.first)
	{
		return lhs.second < rhs.second;
	}
	return lhs.first > rhs.first;
}



void FirstTry::firstTry(int BFS, int Twins)
{
	this->BFS = BFS;
	this->Twins = Twins;
	numberOfSwitches_ = -1;
	vector<int> bestSequence;
	if (BFS == FST_BFS)
	{
		if(Twins == FST_TWINS)
			checker.checkTwinTools(false);
		for (int i = 0; i < graph->getNumVertex(); i++)
		{
			makeToolSequenceBFS(i);
			if (print_)
				for (auto j : toolSequence)
					printf("%d ", j);
			makeJobSequence();
			problem_->setSequence(sequence_);
			int currentSwitches = problem_->KTNS();
			if(print_)
				for (auto j : toolSequence)
					printf("%d ", j);
			if (print_)printf(" >> %d\n", currentSwitches);

			if (numberOfSwitches_ == -1 || currentSwitches < numberOfSwitches_)
			{
				
					
				numberOfSwitches_ = currentSwitches;
				bestSequence.assign(sequence_.begin(), sequence_.end());
			}

		}
		
	}
	else
	{

		minimumDegreeGreedy();
		extensionRotation();
		makeJobSequence();

		problem_->setSequence(sequence_);
		numberOfSwitches_ = problem_->KTNS();
		bestSequence.assign(sequence_.begin(), sequence_.end());
		
	}
	problem_->setSequence(bestSequence);
	problem_->KTNS();

}



void FirstTry::makeToolSequenceBFS(int initialTool)
{
	queue<int> Q;
	vector<bool> visited(graph->getNumVertex(), false);
	toolSequence.clear();

	if (Twins == FST_TWINS)
	{
		vector<bool> twins(graph->getNumVertex(), false);
		for (int i = 0; i < graph->getNumVertex(); i++)
		{
			if (twins[i] == true )
				continue;
			for (int j = 0; j < (int) checker.getTwinTools()[i].size(); j++)
			{
				if (checker.getTwinTools()[i][j] == initialTool)
					continue;
				twins[checker.getTwinTools()[i][j]] = true;
				visited[checker.getTwinTools()[i][j]] = true;
			}
		}
	}	   


	bool exploredAllVertex = false;

	int currentInitialTool = initialTool;
	do
	{
		Q.push(currentInitialTool);
		visited[currentInitialTool] = true;

		while (!Q.empty())
		{
			int next = Q.front();
			toolSequence.push_back(next);
			Q.pop();

			map<double, int> neighbors;
			vector<pair<double, int>> neigh;
			if (print_) printf("Visiting vertex %d\n", next);
			
			for (auto edge : (*graph)[next])
			{
				if (!visited[edge.first])
				{
					visited[edge.first] = true;
					neighbors[edge.second] = edge.first;
					neigh.push_back(pair<double, int>(edge.second, edge.first));
				}
			}

			sort(neigh.begin(), neigh.end(), comparePair);
			for (auto edge : neigh)
			{
				Q.push(edge.second);
				if (print_)
					printf("Inseriu no queue %d com peso %d\n", edge.second, (int)edge.first);
			}
		}

		exploredAllVertex = true;

		for (int i = 0; i < graph->getNumVertex(); i++)
		{
			if (!visited[i])
			{
				exploredAllVertex = false;
				currentInitialTool = i;
				break;
			}
		}

	} while (  !exploredAllVertex );
	
	if (Twins == FST_TWINS)
	{
		vector<bool> twins(graph->getNumVertex(), false);
		for (int i = 0; i < graph->getNumVertex(); i++)
		{
			if (twins[i] == true)
				continue;
			if (find(checker.getTwinTools()[i].begin(), checker.getTwinTools()[i].end(), initialTool) != checker.getTwinTools()[i].end())
				continue;
			for (int j = 0; j < (int) checker.getTwinTools()[i].size(); j++)
			{
				//printf("Trying to insert %d \n", checker.getTwinTools()[i][j]);
				if (checker.getTwinTools()[i][j] == initialTool)
					continue;
				twins[checker.getTwinTools()[i][j]] = true;
				vector<int>::iterator it = find(toolSequence.begin(), toolSequence.end(),i);

				it++;
				//printf("Inserting %d after %d, position %d\n", checker.getTwinTools()[i][j], i, it - toolSequence.begin());
				toolSequence.insert(it, checker.getTwinTools()[i][j]);
			}
		}
	}	 	

}

void FirstTry::makeToolSequenceBFSWithClique()
{
	queue<int> Q;
	vector<bool> visited(graph->getNumVertex(), false);
	toolSequence.clear();
	minimumDegreeGreedy();

	for (int i = 0; i < (int)path.size(); i++)
	{
		Q.push(path[i]);
		visited[path[i]] = true;
	}

	bool exploredAllVertex = false;
	do
	{
		while (!Q.empty())
		{
			int next = Q.front();
			toolSequence.push_back(next);
			Q.pop();

			map<double, int> neighbors;
			vector<pair<double, int>> neigh;
			if (print_) printf("Visiting vertex %d\n", next);
			for (auto edge : (*graph)[next])
			{
				if (!visited[edge.first])
				{
					visited[edge.first] = true;
					neighbors[edge.second] = edge.first;
					neigh.push_back(pair<double, int>(edge.second, edge.first));
				}
			}

			sort(neigh.begin(), neigh.end(), comparePair);
			for (auto edge : neigh)
			{
				Q.push(edge.second);
				if (print_)
					printf("Inseriu no queue %d com peso %d\n", edge.second, (int)edge.first);
			}
		}

		exploredAllVertex = true;

		for (int i = 0; i < graph->getNumVertex(); i++)
		{
			if (!visited[i])
			{
				exploredAllVertex = false;

				Q.push(i);
				visited[i] = true;
				break;
			}
		}

	} while (!exploredAllVertex);
	problem_->KTNS();
}

bool FirstTry::canExecute(int Job, int maxTool)
{
	vector<vector<int>> &toolJobMatrix = problem_->getToolJobBinary();
	int numberOfRequiredTools = (int) problem_->getJobTools()[Job].size(), toolsMatched = 0;
	for (int i = 0; i < maxTool; i++)
		toolsMatched += toolJobMatrix[toolSequence[i]][Job]; // If the Job needs the Ith tool it will be 1, leading to a tool matched.
	return toolsMatched == numberOfRequiredTools;
}

void FirstTry::makeJobSequence()
{
	isExecuted.assign(numberOfJobs_, false);
	jobsExecuted = 0;
	sequence_.clear();
	for (int i = 0; i < (int) toolSequence.size(); i++)
	{
		vector<int> nextJobs;

		for (int j = 0; j < numberOfJobs_; j++)
			if (!isExecuted[j] && canExecute(j, i+1)) // If the jth job has not been executed and can be executed with the current tools available.
			{
				if(print_) printf("job %d can be executed\n", j);
				nextJobs.push_back(j); // Add the jth job to the vector of next jobs to be executed.
			}
		while (!nextJobs.empty())
		{
			if (jobsExecuted == 0)
			{
                int jobWithMaxTools = 0, maxTools = 0;

				for (int job = 0; job < (int) nextJobs.size(); job++)
				{
					if ((int) problem_->getJobTools()[nextJobs[job]].size() > maxTools)
					{
						jobWithMaxTools = job;
						maxTools = (int) problem_->getJobTools()[nextJobs[job]].size();
					}
				}

				isExecuted[nextJobs[jobWithMaxTools]] = true;
				sequence_.push_back(nextJobs[jobWithMaxTools]);
				jobsExecuted++;
				nextJobs.erase(nextJobs.begin() + jobWithMaxTools);
			}
			else
			{
                int leastSwitches = (int) 2e8, bestJob = 0, currentSwitches;
				for (int job = 0; job < (int)nextJobs.size(); job++)
				{
					sequence_.push_back(nextJobs[job]);
					problem_->setSequence(sequence_);
					if (print_) printf("Current sequence size %d\n", (int) sequence_.size());
					currentSwitches = problem_->KTNS(sequence_.size());
					if (currentSwitches < leastSwitches)
					{
						leastSwitches = currentSwitches;
						bestJob = job;
					}
					sequence_.pop_back();
				}
				isExecuted[nextJobs[bestJob]] = true;
				sequence_.push_back(nextJobs[bestJob]);
				jobsExecuted++;
				nextJobs.erase(nextJobs.begin() + bestJob);
			}
		}
	}
}




void FirstTry::minimumDegreeGreedy()
{
	Graph* newGraph = graph->createComplementaryGraph();
	vector<int> independentSet;
	vector<bool> closedVertexes(newGraph->getNumVertex(), false);
	
	int numberOfVertexes = newGraph->getNumVertex();
	

	while(numberOfVertexes)
	{
		int minDegree = newGraph->getNumVertex() + 1, minVertex, currentDegree;

		for (int i = 0; i < (int) newGraph->graphWeightedM_.size(); i++)  // Check each vertex for the minimum degree vertex
		{
			if (closedVertexes[i])
				continue;
			currentDegree = 0;
			for (int j = 0; j < (int) newGraph->graphWeightedM_[i].size(); j++) // Check the degree of the ith vertex
			{
				if (closedVertexes[(int)newGraph->graphWeightedM_[i][j]]) // Ignore vertexes that are closed.
					continue;
				currentDegree += (int)newGraph->graphWeightedM_[i][j];
			}

			if (currentDegree < minDegree)
			{
				minDegree = currentDegree;
				minVertex = i;
			}

		}


		independentSet.push_back(minVertex); // Add the minimum degree vertex to the independent set.
		closedVertexes[minVertex] = true;
		numberOfVertexes--;
		for (int i = 0; i < (int)newGraph->graphWeightedM_[minVertex].size(); i++)
		{
			if (!closedVertexes[i] && newGraph->graphWeightedM_[minVertex][i]) // Close each neighboor from the minimum degree vertex
			{
				closedVertexes[i] = true;
				numberOfVertexes--;
			}
		}
	}

	if (print_) printf("The Independent Set is : ");

	if (print_) 
		for (auto e : independentSet)
			printf("%d ", e);
	if (print_) printf("\n");

	path.assign(independentSet.begin(), independentSet.end());

}


void FirstTry::extensionRotation()
{
	vector<bool> closedVertexes((int)graph->getNumVertex(), false);
	int maxVertex, someVertex, seqRotation;

	for (int i = 0; i < (int)path.size(); i++)
		closedVertexes[path[i]] = true;

	seqRotation = 0;
	do
	{
		int lastVertex = path[(int)path.size() - 1];

		int degree = -1;
		maxVertex = -1;
		someVertex = -1;
		for (int i = 0; i < (int) graph->graphWeightedM_[lastVertex].size(); i++) // Get the maximum degree neighbor from the last vertex of the Path.
		{
			if (graph->graphWeightedM_[lastVertex][i] == 0 || closedVertexes[i]) 
				continue; // Skip i if it is not adjacent or if it is a closed vertex.
			int currentDegree = 0;
			
			for (int j = 0; j < (int)graph->graphWeightedM_[i].size(); j++) 
			{
				if (graph->graphWeightedM_[i][j] && !closedVertexes[j]) // If there is an edege (i,j) sum 1 to the degree.
					currentDegree++;
			}

			if (currentDegree > degree)
			{
				degree = currentDegree;
				maxVertex = i;
			}
		}

		if (degree != -1)   // There is a vertex to extend
		{
			seqRotation = 0;
			if (print_) printf("The maximum degree vertex is %d\n", maxVertex);
			path.push_back(maxVertex);
			closedVertexes[maxVertex] = true;
		}
		else  // There should be a rotation
		{
			seqRotation++;
			if (seqRotation == 5)
				break;
			someVertex = -1;
			int index = -1; // The Index of someVertex on the path vector.
			vector<int> randomSequence;
			for (int i = 1; i < (int)path.size() - 1; i++)
				randomSequence.push_back(i);

			unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
			if ((int)randomSequence.size() > 1)
				shuffle(randomSequence.begin(), randomSequence.end(), std::default_random_engine(seed));

			for (int i = 0; i < (int)randomSequence.size(); i++)
			{
				if (graph->getEdge(path[randomSequence[i] - 1], lastVertex) != 0)
				{
					index = randomSequence[i];
					someVertex = path[randomSequence[i]];
					break;
				}
			}

			if (index == -1)
				index = 0;

			if (print_) printf("Last Path: \n");
			if (print_)
				for (auto e : path)
					printf("%d ", e);
			if (print_) printf("\n");

			reverse(path.begin() + index, path.end());
												

			if (print_) printf("Found a vertex to rotate %d\n", someVertex);
		}

		if ((int)path.size() == graph->getNumVertex())
			break;

	} while (maxVertex != -1 || someVertex != -1);

    if ( (int) path.size() != graph->getNumVertex())
	{
		for (int i = 0; i < (int)graph->getNumVertex(); i++)
		{
			if (!closedVertexes[i])
			{
				closedVertexes[i] = true;
				printf("Adding %d at the end of the path.\n", i);
				path.push_back(i);
			}
		}
	}

	if (print_) printf("Path has been completed!");
	if (print_) 
		for (auto e : path)
			printf("%d ", e);
	if (print_) printf("\n");
	toolSequence.assign(path.begin(), path.end());
}



 int FirstTry::lowerBoundYanasse()
 {
 	minimumDegreeGreedy();

 	int cliqueSize =  (int) path.size();

    int minDegree = graph->getNumVertex() + 1;
 	for (int i = 0; i < (int) graph->graphWeightedM_.size(); i++)  // Check each vertex for the minimum degree vertex
	{
		int currentDegree = 0;
		for (int j = 0; j < (int) graph->graphWeightedM_[i].size(); j++) // Check the degree of the ith vertex
		{
			if(graph->graphWeightedM_[i][j] != 0 )
					currentDegree += 1;
		}

		if (currentDegree < minDegree)
			minDegree = currentDegree;
	}

	int cStar = max(cliqueSize, minDegree);
	int c = problem_->getCapacity();

	bool foundK = false;
	int k = 0;

	while(!foundK)
	{
		int lhs = c + (( (k+1) - 1 )*(c-1));
		int rhs = c + ((k+1) * (c-1));
		if(lhs < cStar && cStar <= rhs)
			k++;
		else
			foundK = true;
	}
	int lowerBound = graph->getNumVertex() + (cStar - c);
	for(int i = 2; i <= k; i++)
	{	
		lowerBound += c-1;
		lowerBound += cStar - (i*c) + (i - 1);
		if( i == k)
			lowerBound += cStar - (i*c) + (i - 1);
	}

	printf("C: %d C*: %d k: %d, lowerBound = %d\n", c, cStar, k, lowerBound);


	return lowerBound;
 }




