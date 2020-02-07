#include "InstanceChecker.hpp"

#include <cstdlib>
#include <unordered_set>

using namespace std;

InstanceChecker::InstanceChecker(MTSP* problem, bool print, string methodName) : Solution(problem, print, methodName)
{

}


bool InstanceChecker::hasDominance()
{
    return hasDominance_;
}

void InstanceChecker::checkDominance()
{
    int numberOfJobs = problem_->getNumJobs();
    dominance_ = vector<vector<int>>(numberOfJobs, vector<int>());

    for(int i = 0; i < numberOfJobs; i++)
    {
        for(int j = 0; j < numberOfJobs; j++)
        {
            if(problem_->isDominated(i, j, print_))
                dominance_[i].push_back(j);

        }
    }
}



void InstanceChecker::printDominance()
{

    for(int i = 0; i < int(dominance_.size()); i++)
    {
        printf("Dominance of job %d: ", i);
        for(int j = 0; j < int(dominance_[i].size()); j++)
            printf(" %d ", dominance_[i][j]);
        printf("\n");
    }
}


void InstanceChecker::printDominanceToFile(char* filename)
{
    FILE* output = fopen(filename, "w");

    if(output == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    for(int i = 0; i < int(dominance_.size()); i++)
    {
        fprintf(output,"Dominance of job %d: ", i);
        for(int j = 0; j < int(dominance_[i].size()); j++)
            fprintf(output, " %d ", dominance_[i][j]);
        fprintf(output, "\n");
    }

    fclose(output);
}



bool InstanceChecker::hasTwinTools()
{
    return hasTwinTools_;
}

void InstanceChecker::checkTwinTools(bool createGraph)
{

    if(createGraph)
		problem_->createGraphToolJob();
    Graph* graph = problem_->getGraph();
    //graph->print();
    int numberOfTools = graph->getNumVertex();

    twinTools_ = vector<vector<int>>(numberOfTools, vector<int>());
    for(int i = 0; i < numberOfTools; i++)
    {
        for(int j = 0; j < numberOfTools; j++)
        {
			if (graph->isTwinVertice(i,j, print_))
			{
				twinTools_[i].push_back(j), (hasTwinTools_ = true);
				if (print_) printf("TOOLS %d IS A TWIN TOOL OF %d \n\n", i, j);
			}
			else
			{
				if (print_) printf("TOOLS %d IS NOT A TWIN TOOL OF %d \n\n", i, j);
			}
        }
    }
}



void InstanceChecker::printTwinTools()
{

    for(int i = 0; i < int(twinTools_.size()); i++)
    {
        printf("TwinTools of job %d: ", i);
        for(int j = 0; j < int(twinTools_[i].size()); j++)
            printf(" %d ", twinTools_[i][j]);
        printf("\n");
    }
}


void InstanceChecker::printTwinToolsToFile(char* filename)
{
    FILE* output = fopen(filename, "w");

    if(output == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    for(int i = 0; i < int(twinTools_.size()); i++)
    {
        fprintf(output,"Tool %d is twin of tools: ", i);
        for(int j = 0; j < int(twinTools_[i].size()); j++)
            fprintf(output, " %d ", twinTools_[i][j]);
        fprintf(output, "\n");
    }

    fclose(output);
}



vector<vector<int>>& InstanceChecker::getTwinTools()
{
	return twinTools_;
}
