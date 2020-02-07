#include <chrono>
#include <string>
#include <cstring>

#include "assert.h"

#include "Graph.hpp"
#include "MTSP.hpp"
#include "Greedy.hpp"
#include "Misc.hpp"
#include "NearestNeighbor.hpp"
#include "FarthestInsertion.hpp"
#include "KOpt.hpp"
#include "BestPositionInsertion.hpp"
#include "AntonioAugusto.hpp"
#include "InstanceChecker.hpp"
#include "FirstTry.hpp"
#include "Alphanum.hpp"
#include "Configuration.hpp"
#include "VND.hpp"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void execute(string filePath, string file, string outputFile, config parameters, FILE* summaryFile, FILE* allSummaryFile, string fileName = string(""))
{
	MTSP prob = MTSP(filePath);
	prob.readInputYanasse();
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
		
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	if(!parameters.tuning)
	{
		fflush(summaryFile);
		fflush(allSummaryFile);
	}
	string outputfile = outputFile + file;
	char summaryEntry[500];


	if (parameters.method == 0)//{0,"SolutionMSG"}
	{
		Greedy greedy(&prob, parameters.verbose, methodMap[parameters.method]);
		greedy.multipleStart();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 1)//{1,"SolutionNN"}
	{
		//prob.createGraphLowerBound();
		prob.createGraphUpperBound();
		NearestNeighbor n(&prob, parameters.verbose, methodMap[parameters.method]);
		n.nearestNeighbor();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 2)//{2,"SolutionFI"}
	{
		//prob.createGraphLowerBound();
		prob.createGraphUpperBound();
		FarthestInsertion f(&prob, parameters.verbose, methodMap[parameters.method]);
		f.farthestInsertion();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 3)//{3,"SolutionKOPT"}
	{
		KOpt kopt(&prob, parameters.k, parameters.verbose, methodMap[parameters.method]);
		kopt.kOpt();
		//kopt.kOptRestricted();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 4)//{4,"SolutionBPI"}
	{
		BestPositionInsertion bpi = BestPositionInsertion(&prob, parameters.verbose, methodMap[parameters.method]);
		bpi.bestPositionInsertion();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 5)//{5,"SolutionAnt"} 
	{
		AntonioAugusto  constru(&prob, parameters.verbose, methodMap[parameters.method]);
		constru.antonioAugusto();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 6)//{6,"SolutionFST"}
	{
		FirstTry  fst(&prob, parameters.verbose, methodMap[parameters.method]);
		fst.firstTry(FST_BFS, FST_NOTWINS);
		//prob.localSearchIterativeCORRECT(ILS_LOCALSEARCH, parameters.verbose, 15);
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 7)//{7,"SolutionFST_OPT"}, 
	{
		FirstTry  fst(&prob, parameters.verbose, methodMap[parameters.method]);
		fst.firstTry(FST_BFS, FST_NOTWINS);
		prob.localSearch(ILS_2OPT, parameters.verbose);
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 8)//{8,"SolutionILS"}, 
	{
		uniform_real_distribution<double> distribution(0.2, 0.5);
		prob.ILS(parameters.iter, parameters.tuning? parameters.perturbation : PERTURBATION, ILS_LOCALSEARCH, parameters.verbose, ILS_LS_PART_2OPT, parameters.tuning ? parameters.partial : PARTIAL_SIZE);
		
		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);
						
			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);
			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf("%d\n", prob.getNumSwitches());
		}

		return;
	}
	else if (parameters.method == 9)//{9,"SolutionILS_OPT"},
	{
		uniform_real_distribution<double> distribution(0.2, 0.4);
		prob.ILS(parameters.iter, parameters.tuning? parameters.perturbation : distribution(generator), ILS_2OPT, parameters.verbose);
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 10)//{10,"SolutionFSTI"}, 
	{
		uniform_real_distribution<double> distribution(0.2, 0.4);
		prob.ILS(parameters.iter, parameters.tuning? parameters.perturbation : PERTURBATION, ILS_LOCALSEARCH, parameters.verbose, 5, parameters.tuning ? parameters.partial : PARTIAL_SIZE);
		
		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);

			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);

			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf("%d\n", prob.getNumSwitches());
		}
		return;
	}
	else if (parameters.method == 11)//{11,"SolutionFSTF"},
	{
		FirstTry  fst(&prob, parameters.verbose, methodMap[parameters.method]);
		fst.firstTry(FST_BFS, FST_NOTWINS);
		prob.localSearchFull(ILS_LOCALSEARCH, parameters.verbose, 15);
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 12)//{12,"SolutionILS_LS_2OPT"},  
	{
		uniform_real_distribution<double> distribution(0.4, 0.5);
		prob.ILS(parameters.iter, parameters.tuning? parameters.perturbation : PERTURBATION, ILS_LS_PART_2OPT, parameters.verbose, 5, parameters.tuning ? parameters.partial : PARTIAL_SIZE);
		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);
			
			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);

			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf("%d\n", prob.getNumSwitches());
		}

		return;
	}
	else if (parameters.method == 13)//{13,"SolutionVND"},
	{
		VND vnd = VND(&prob, parameters.k, parameters.lastK, parameters.verbose, methodMap[parameters.method]);
		vnd.ExecuteVND();
		snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count());
	}
	else if (parameters.method == 14)//{14,"SolutionILS_LS_PART_2OPT"}, 
	{
		uniform_real_distribution<double> distribution(0.2, 0.4);
		prob.ILS(parameters.iter, parameters.tuning ? parameters.perturbation : PERTURBATION, ILS_LS_PART_2OPT, parameters.verbose, ILS_LS_PART_2OPT, parameters.tuning ? parameters.partial : PARTIAL_SIZE, instance_time_limit[fileName]);

		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);
			
			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);

			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf("%d\n", prob.getNumSwitches());
		}
		return;
	}
	else if (parameters.method == 15)//{15,"SolutionILS_LS_22Swap"},
	{
		uniform_real_distribution<double> distribution(0.2, 0.4);
		prob.ILS(parameters.iter, parameters.tuning ? parameters.perturbation : PERTURBATION, ILS_LS_22SWAPOPT, parameters.verbose, 5, parameters.tuning ? parameters.partial : PARTIAL_SIZE);

		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);
			
			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);

			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf(" %d \n", prob.getNumSwitches());
		}
		return;
	}
	else if (parameters.method == 16)//{15,"SolutionILS_LS_22Swap"},
	{
		uniform_real_distribution<double> distribution(0.2, 0.4);
		prob.ILS(parameters.iter, parameters.tuning ? parameters.perturbation : PERTURBATION, ILS_LS_PART_22SWAPOPT, parameters.verbose, 5);

		if(!parameters.tuning)
		{
			prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
			chrono::duration<double> bestSolution = chrono::duration_cast<chrono::duration<double>>(prob.getTimeToBestSolution() - start);
			
			printf("Time elapsed: %4.12lf %4.12lf\n\n\n", prob.getTimeElapsed().count(), bestSolution.count());
			snprintf(summaryEntry, 500, "%-60s \t %5d \t %4.12lf %4.12lf %d", &filePath[0], prob.getNumSwitches(), prob.getTimeElapsed().count(), bestSolution.count(), prob.getIterBestSolution()	);
			
			prob.printSolutionToFile(&outputfile[0]);

			string sEntry = string(summaryEntry);
			prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		}
		else
		{
			printf(" %d \n", prob.getNumSwitches());
		}
		return;
	}
	else if (parameters.method == 90)
	{
		InstanceChecker  checker(&prob, parameters.verbose, methodMap[parameters.method]);
		checker.checkDominance();
		string outputfile = outputFile + file;
		checker.printDominanceToFile(&outputfile[0]);
		snprintf(summaryEntry, 500, "%-60s \t %s", &filePath[0], (checker.hasDominance() ? "there is dominance" : "there isn't dominance"));
		
		string sEntry = string(summaryEntry);
		prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		return;
	}
	else if (parameters.method == 91)
	{
		InstanceChecker  checker(&prob, parameters.verbose, methodMap[parameters.method]);
		checker.checkTwinTools();
		string outputfile = outputFile + file;
		checker.printTwinToolsToFile(&outputfile[0]);
		snprintf(summaryEntry, 500, "%-60s \t %s", &filePath[0], (checker.hasTwinTools() ? "there is twin tools" : "there isn't twin tools"));
		string sEntry = string(summaryEntry);
		prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		return;
	}
	else if (parameters.method == 92)
	{
		prob.createGraphLowerBound();
		double cost = prob.getGraph()->MST();

		string outputfile = outputFile + file;
		fprintf(summaryFile, "%-30s \t %.0lf\n", &file[0], cost);

		snprintf(summaryEntry, 500, "%-60s \t  %.0lf", &filePath[0], cost);		

		string sEntry = string(summaryEntry);
		prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		return;
	}
	else if (parameters.method == 93)
	{
		prob.createGraphLowerBound();
		FirstTry  fst(&prob, parameters.verbose, methodMap[parameters.method]);
		int cost = fst.lowerBoundYanasse();

		string outputfile = outputFile + file;
		snprintf(summaryEntry, 500, "%-60s \t  %d", &filePath[0], cost);
		string sEntry = string(summaryEntry);
		prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
		return;
	}

	prob.setTimeElapsed(chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - start));
	printf("Time elapsed: %4.12lf\n\n", prob.getTimeElapsed().count());

	prob.printSolutionToFile(&outputfile[0]);

	string sEntry = string(summaryEntry);
	prob.printSolutionSumary(summaryFile, allSummaryFile, sEntry);
}



int main(int argc, char *argv[])
{
	config parameters;
	if( parseArguments(argc, argv, parameters) )
		return 0;

	vector<string> directorys;
	string currentDir;
	int cont;
	
	if(parameters.tuning)
	{
		execute(parameters.fileName, parameters.directoryName, " ", parameters, NULL, NULL);
		return 0;
	}
	
	currentDir = string(parameters.directoryName);
	directorys.push_back(currentDir);

	string allSumaryDirectory = SOLUTION_DIR + currentDir + string(SLASH) + string("Summary") + string(SLASH);
	string allSummary;
	if(parameters.counter == -1)
		allSummary = allSumaryDirectory + methodMap[parameters.method] + string(".txt");
	else
		allSummary = allSumaryDirectory + methodMap[parameters.method] + string("_") + toString(parameters.counter)  + string(".txt");

	for (auto dir : directorys)
	{
		cont = 0;
		string directory = INSTANCE_DIR + dir + string(SLASH);
		
		vector<string> files = getDirectoryFiles(&directory[0]);
		sort(files.begin(), files.end(), doj::alphanum_less<std::string>());	 // Sort the instances name with Natural Sort Algorithm.

		string outputDirectory = SOLUTION_DIR + dir + string(SLASH) + methodMap[parameters.method] + string(SLASH);
		
		createDirectory( &outputDirectory.c_str()[0], 0700);
		//printf("%s\n", &allSumaryDirectory[0]);
		createDirectory( &allSumaryDirectory.c_str()[0], 0700);
			
		string outputFile = outputDirectory  + methodMap[parameters.method] + string("_");
		string summary = outputFile + string("_Summary.txt");


		FILE* allSummaryFile = fopen(&allSummary[0], "w"); assert(allSummaryFile != NULL);
		printf("%s\n", &summary[0]);
		FILE* summaryFile = fopen(&summary[0], "w"); assert(summaryFile != NULL);

		for (auto file : files)
		{
			string filename = directory + file;
			printf("Instance name: %s\nRunning method: %s \n", &filename[0], &(methodNameMap[parameters.method].c_str()[0]) );
			
			execute(filename, dir, outputFile, parameters, summaryFile, allSummaryFile, file);
			if (++cont == parameters.n)
				break;
		}

		fclose(summaryFile);
	}

	return 0;
}


