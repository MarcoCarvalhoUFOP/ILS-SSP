#include "Graph.hpp"

#include <unordered_set>

Graph::Graph()
{
	type_ = GRAPH_UNWEIGHTED;
	m_ = 0;
}

Graph::Graph(int n,  GRAPH_TYPE type)
{
	n_ = n;
	type_ = type;
	m_ = 0;
	if(type_ ==  GRAPH_UNWEIGHTED)
		graphUnweighted_ = vector<vector<int>>(n);
	else
	{
		graphWeighted_ = vector<vector<pair<int,double>>>(n) ;
		graphWeightedM_.assign(n, vector<double>(n, 0)) ;
	}
}

int Graph::getNumVertex()
{
	return n_;
}

void Graph::addEdge(int tail, int head)
{
	graphUnweighted_[tail].push_back(head);
	m_++;
}

void Graph::addEdge(int tail, int head, double cost)
{
	graphWeighted_[tail].push_back( pair<int,double>(head, cost));
	graphWeightedM_[tail][head] = cost;
	m_++;
}


double Graph::getCost(int tail, int head)
{
	return graphWeightedM_[tail][head];
}

vector<vector<pair<int,double>>>& Graph::getWeightedGraph()
{
	return graphWeighted_;
}

vector<vector<int>>& Graph::getUnweightedGraph()
{
	return graphUnweighted_;
}


void Graph::resize(int n, GRAPH_TYPE type)
{
	n_ = n;
	m_ = 0;

	type_ = type;
	if(type_ ==  GRAPH_UNWEIGHTED)
		graphUnweighted_ = vector<vector<int>>(n);
	else
	{
		graphWeighted_ = vector<vector<pair<int, double>>>(n);
		graphWeightedM_.assign(n, vector<double>(n, 0));
	}
}


vector<pair<int,double>>& Graph::operator[](const int& x)
{
	return graphWeighted_[x];
}


void Graph::createGraphAugusto(int numberofJobs, int numberOfTools, vector<vector<int>> &jobTools)
{
	resize(numberOfTools, GRAPH_WEIGHTED);

	for (int i = 0; i < numberofJobs; i++)
	{
		for (int j = 0; j < (int)jobTools[i].size(); j++)
		{
			for (int k = j + 1; k < (int)jobTools[i].size(); k++)
			{
				addEdge(jobTools[i][j], jobTools[i][k], i);
				addEdge(jobTools[i][k], jobTools[i][j], i);
			}
		}

	}
}

void Graph::createGraphToolJob(int numberofJobs, int numberOfTools, vector<vector<int>> &jobTools)
{
	//printf("Number of Tools %d", numberOfTools);
	resize(numberOfTools, GRAPH_WEIGHTED);

	for (int i = 0; i < numberofJobs; i++)
	{
		for (int j = 0; j < (int)jobTools[i].size(); j++)
		{
			for (int k = j + 1; k < (int) jobTools[i].size(); k++)
			{

				if (graphWeightedM_[jobTools[i][j]][jobTools[i][k]] == 0)
				{
					//printf("Inserting (%d,%d)\n", jobTools[i][j], jobTools[i][k]);
					addEdge(jobTools[i][j], jobTools[i][k], 1);
					addEdge(jobTools[i][k], jobTools[i][j], 1);
				}
				else
				{
					for (int l = 0; l < (int) graphWeighted_[jobTools[i][j]].size(); l++)
					{
						if (graphWeighted_[jobTools[i][j]][l].first == jobTools[i][k])
						{
							graphWeighted_[jobTools[i][j]][l].second++;// graphWeighted_[jobTools[i][j]].erase(graphWeighted_[jobTools[i][j]].begin() + l);
							break;
						}
					}

					for (int l = 0; l < (int) graphWeighted_[jobTools[i][k]].size(); l++)
					{
						if (graphWeighted_[jobTools[i][k]][l].first == jobTools[i][j])
						{
							graphWeighted_[jobTools[i][k]][l].second++;//graphWeighted_[jobTools[i][k]].erase(graphWeighted_[jobTools[i][k]].begin() + l);
							break;
						}
					}
					graphWeightedM_[jobTools[i][k]][jobTools[i][j]]++;
					graphWeightedM_[jobTools[i][j]][jobTools[i][k]]++;

				}
			}
		}

	}
}



void Graph::createGraphLowerBound(int numberOfJobs, int magazineCapacity, vector<vector<int>>& jobsTools)
{
	resize(numberOfJobs, GRAPH_WEIGHTED);

	unordered_set<int> unionTools;

	for(int i = 0; i < numberOfJobs; i++)
	{
		for(int j = i+1; j < numberOfJobs; j++)
		{
			unionTools.clear();

			for(auto t : jobsTools[i])
			{
				unionTools.insert(t);
			}
			for(auto t : jobsTools[j])
			{
				unionTools.insert(t);
			}
			addEdge(i,j, max((int) unionTools.size() - magazineCapacity,  0) );
			addEdge(j,i, max((int) unionTools.size() - magazineCapacity,  0) );
		}
	}

}

void Graph::createGraphUpperBound(int numberOfJobs, vector<vector<int>>& jobsTools)
{
	resize(numberOfJobs, GRAPH_WEIGHTED);

	unordered_set<int> unionTools;
	int value;
	for(int i = 0; i < numberOfJobs; i++)
	{
		for(int j = 0; j < numberOfJobs; j++)
		{
			if(i == j) continue;
			unionTools.clear();
			value = 0;
			for(auto t : jobsTools[i])
			{
				unionTools.insert(t);
				value++;
			}
			for(auto t : jobsTools[j])
			{
				if(unionTools.find(t) != unionTools.end())
					value--;
			}		
			addEdge(i,j, value );
		}
	}

}


Graph* Graph::createComplementaryGraph()
{	   
	Graph* newGraph = new Graph(n_ , GRAPH_WEIGHTED);
	newGraph->resize(n_, GRAPH_WEIGHTED);

	for (int i = 0; i < (int)graphWeightedM_.size(); i++)
	{
		for (int j = 0; j < (int)graphWeightedM_[i].size(); j++)
		{
			if (graphWeightedM_[i][j] == 0 && i != j)
			{
				newGraph->addEdge(i, j, 1);
			}
		}
	}

	return newGraph;
}




void Graph::print()
{
	printf("Numero de Vertices: %d -- Numero de Arestas: %d \n", n_, m_);
	int edge = 1;
	for(int i = 0; i < n_; i++)
	{
		if(type_ ==  GRAPH_UNWEIGHTED)
		{
			for(auto v : graphUnweighted_[i])
			{
				printf("Aresta %d : (%d, %d)\n", edge++, i, v);
			}
		} 
		else
		{
			for(auto v : graphWeighted_[i])
			{
				printf("Aresta %d : (%d, %d) cost %0.2lf\n", edge++, i, v.first, (double) v.second);
			}
		}
	}
}




int Graph::getEdge(int tail, int head)
{
	if (type_ == GRAPH_UNWEIGHTED)
	{
		for (auto v : graphUnweighted_[tail])
		{
			if (v == head)
				return 1;
		}
		return 0;
	}
	else
	{
		return graphWeightedM_[tail][head];
	}
	return 0;
}




bool Graph::isTwinVertice(int x, int y, bool print)
{

	if (graphWeightedM_[x][y] == 0)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < n_; i++)
		{
			if (i == x || i == y)
			{
				continue;
			}
			if(print) printf("(%d,%d) == %d && (%d,%d) == %d \n",x,i, (int)graphWeightedM_[x][i], y, i, (int)graphWeightedM_[y][i]);
			if (graphWeightedM_[x][i] != graphWeightedM_[y][i])
			{
				if (print)
				{
					if (graphWeightedM_[x][i])
					{
						printf("There is an edge (%d,%d) and there isnt an edge (%d,%d)\n", x, i, y, i);
					}
					else
					{
						printf("There is an edge (%d,%d) and there isnt an edge (%d,%d)\n", y, i, x, i);
					}
				}
				return false;
			}

		}

	}
	return true;
}


struct edge
{
	int head, tail;
	double cost;
	edge(int head, int tail, double cost)
	{
		this->head = head;
		this->tail = tail;
		this->cost = cost;
	}
};

bool edgeCompare(const edge& lhs, const edge& rhs)
{
	return lhs.cost < rhs.cost;
}

double Graph::MST()
{
	int edgesTaken;
	double mstCost;
	vector<edge> edgesWeighted;
	unionFind cycleFinding(n_);

	for (int i = 0; i < n_; i++)
	{
		for (auto v : graphWeighted_[i])
		{
			//printf("Aresta %d : (%d, %d) cost %0.2lf\n", i, v.first, (double)v.second);
			edgesWeighted.push_back(edge(i, v.first, v.second));
		}
	}

	sort(edgesWeighted.begin(), edgesWeighted.end(), edgeCompare);

	edgesTaken = 0;
	mstCost = 0;
	int index = 0;

	while (edgesTaken < n_ - 1)
	{
		if (cycleFinding.unionSet(edgesWeighted[index].tail, edgesWeighted[index].head))
		{
			
			//printf("Aresta %d : (%d, %d) cost %0.2lf\n", index, edgesWeighted[index].tail , edgesWeighted[index].head , (double)edgesWeighted[index].cost);
			mstCost += edgesWeighted[index].cost;
			edgesTaken++;
		}
		index++;
	}


	return mstCost;
}
