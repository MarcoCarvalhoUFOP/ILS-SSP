#include "AntonioAugusto.hpp"

AntonioAugusto::AntonioAugusto(MTSP* mtsp, bool print, string methodName) : Solution(mtsp, print, methodName)
{
	mtsp->createGraphAugusto();
	graph = mtsp->getGraph();
	//graph->print();

	vDegree.assign(graph->getNumVertex(), 0); // Creates a new empty vector.
	isOnMagazine.assign(graph->getNumVertex(), false); // Creates a new boolean vector with values equals to false.

	for(int i = 0 ; i  < graph->getNumVertex(); i++)
	{
		degree.insert(make_pair((int) (*graph)[i].size(), i)); // Used for locating the tool with least degree in o(1), amortized.
		vDegree[i] = (int) (*graph)[i].size(); // Used to check the degree of each tool in o(1).
	}

	if(print_)
		for(auto v :  degree)
			printf("Degree(%d) = %d\n", v.first, v.second);

	capacity = 0;
}

/*
	Antonio's Cronstuct Heuristic
*/
void AntonioAugusto::antonioAugusto()
{
	isExecuted.assign(numberOfJobs_, false);
	jobsExecuted = 0;

	while(jobsExecuted < numberOfJobs_) // Choose a job to be the next while there is still an job to be executed.
	{
		int nextTool = -1;
		std::multimap<int, int>::iterator mmIt = degree.begin();
		nextTool = mmIt->second; // The tool with least degree number.

		while (isOnMagazine[nextTool] == false)
		{
			mmIt++;
			if (mmIt == degree.end())
			{	  
				nextTool = degree.begin()->second;
			break;
			}
			nextTool = mmIt->second;
		}		  


		if(print_) printf("Next Tool %d, degree %d\n", nextTool, vDegree[nextTool]);

		if(vDegree[nextTool] == 0) // If it is the degree of a Tool is 0  remove it from the degree's Map.
			degree.erase(degree.begin());

		while(vDegree[nextTool]) // While there is a tool with degree greater than zero.
		{
			int nextJob = findNextJob(nextTool); // Find the next job.

			updateMagazine(nextJob); // Update the magazine to execute the next job.
			isExecuted[nextJob] = true; // Flag the nextJob as executed.
			sequence_.push_back(nextJob); // Add nextJob to the end of the current Job Sequence.											 
			jobsExecuted++;
			checkMagazine(); // Check if there is jobs that can be executed without any addition of tools.

			if (print_)
			{
				printVector(sequence_);
				printf("Current magazine: ");
				for (int i = 0; i < (int)isOnMagazine.size(); i++)
					if (isOnMagazine[i]) printf(" %d", i);
				printf("\n");
			}
		}
	}

	problem_->setSequence(sequence_);
	problem_->KTNS();
}


int AntonioAugusto::findNextJob(int nextTool)
{
	switchesRequired.clear();

	

	for (int i = 0; i < (int)(*graph)[nextTool].size(); i++)
	{
		if (isExecuted[(int)(*graph)[nextTool][i].second]) // Ignore edges that represent jobs that has been executed.
			continue;
		if (!isOnMagazine[(*graph)[nextTool][i].first]) // If the tool is not in the magazine
		{
			if (switchesRequired.find((int)(*graph)[nextTool][i].second) != switchesRequired.end())
				switchesRequired[(int)(*graph)[nextTool][i].second] += 1; // Increment the number of switches
			else
				switchesRequired[(int)(*graph)[nextTool][i].second] = 1; // Increment the number of switches
		}
		else
		{
			if (switchesRequired.find((int)(*graph)[nextTool][i].second) == switchesRequired.end())
				switchesRequired[(int)(*graph)[nextTool][i].second] = 0; // If the tool is on the magazine and not in the map insert it.
		}

	}
	int nextJob = switchesRequired.begin()->first;

	if (jobsExecuted == 0)
	{
		int max = switchesRequired.begin()->second;
		for (auto v : switchesRequired)
			(max < v.second) ? (nextJob = v.first, max = v.second) : nextJob = nextJob;
	}
	else
	{
		int min = switchesRequired.begin()->second;
		for (auto v : switchesRequired)
			(min > v.second) ? (nextJob = v.first, min = v.second) : nextJob = nextJob;
	}

	return nextJob;
}


void AntonioAugusto::updateMagazine(int nextJob)
{
	vector<int>& tools = problem_->getJobTools()[nextJob];

	int spaceRequired = 0;

	for(int i = 0; i < (int) tools.size(); i++)
		if(!isOnMagazine[tools[i]])
			spaceRequired++; // Count the number of tools that are not on the magazine

	for(int i = 0 ; i < (int) isOnMagazine.size(); i++)
	{
		if(isOnMagazine[i] && vDegree[i] == 0) // If the tool i is on the magazine but is not need anymore
		{
			isOnMagazine[i] = false; // Remove it
			capacity--;
		}
	}

	int space = 0; // The amount of space needed to make room ( This takes account the number of tools that has been removed from the magazine).
	if( capacity + spaceRequired > problem_->getCapacity() ) // If the space required is higher than the capacity
		space = capacity + spaceRequired - problem_->getCapacity(); // then you should make room for 'space' tools.
	while(space > 0)
	{
		int id = -1;
		for(int i = 0 ; i < (int) isOnMagazine.size(); i++)
			if(isOnMagazine[i] && problem_->getToolJobBinary()[i][nextJob] == 0) // Ignore tools that isn't on the magazine or tools that are needed to execute the nextJob.
				(id == -1  || vDegree[id] < vDegree[i]) ? id = i : id = id; // Found the tool with maximum degree.
		//printf("%d\n", id);
		isOnMagazine[id] = false; // Remove the id tool ( the tool with maximum degree).
		space--;
		capacity--;
	}

	for(int i = 0; i < (int) tools.size(); i++)
	{
		if (isOnMagazine[tools[i]] == false) {
			capacity++; // Insert the ith tool of the current job on the magazine.
			isOnMagazine[tools[i]] = true; // Flag the ith tool in the magazine.
		}
		map<int, int>::iterator it = degree.find(vDegree[tools[i]]); // Find the ith tool iterator on the map.

		for(; it != degree.end() && it->first == vDegree[tools[i]]; it++)
		{
			if(it->second == tools[i]) // Find the ith tool in the map
			{
				degree.erase(it); // Delete the current degree.
				break;
			}
		}
		vDegree[tools[i]] -= tools.size() - 1; // Decrease the degree of utilization of the current tool.
		if(vDegree[tools[i]] > 0) // If the degree is greater than 0 put it on the degree container otherwise this tool is not needed to the next jobs.																	   
			degree.insert(make_pair(vDegree[tools[i]], tools[i])); // Update the degree of the ith tool
	}

	if(print_)
		for(auto v :  degree)
			printf("Degree(%d) = %d\n", v.first, v.second);

}

void AntonioAugusto::checkMagazine()
{
	for(int i = 0; i < numberOfJobs_; i++) // Check if any of the jobs can be executed.
	{
		if(isExecuted[i]) continue;

		vector<int>& tools = problem_->getJobTools()[i]; // Get the Tool requirement set for a job i.

		if (all_of(tools.begin(), tools.end(), [this](int x) { return isOnMagazine[x]; })) // If all tools are on the magazine then this job can be executed.
		{
			sequence_.push_back(i); // Insert the ith job into the sequence of jobs.
			isExecuted[i] = true; // Flag the ith job as executed.
			jobsExecuted++;

			for(int i = 0; i < (int) tools.size(); i++) // For each tool of this Job reduce the degree of the tool.
			{
				map<int,int>::iterator it = degree.find(vDegree[tools[i]]); // Find the iterator to the first tool with same tool
				for(; it != degree.end() && it->first == vDegree[tools[i]]; it++) // While it hasn't reached the end of the container or the degree of the current tool isn't the same, look for the next tool.
					if(it->second == tools[i]) // Check if this is the correct tool.
					{
						degree.erase(it); // Delete it and stop looking for it.
						break;
					}

				vDegree[tools[i]] -= tools.size() - 1; // Reduce the degree of the tool.

				if(vDegree[tools[i]] > 0) // If the degree is greater than 0 put it on the degree container otherwise this tool is not needed to the next jobs.
					degree.insert(make_pair(vDegree[tools[i]], tools[i])); // Update the degree of the ith tool.
			}

			if(print_) printf("Executed Job %d after checking magazine\n", i);
		}
	}
}
