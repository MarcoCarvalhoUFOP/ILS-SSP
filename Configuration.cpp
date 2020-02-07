#include "Configuration.hpp"




std::map <int, std::string> methodMap{ {0,"SolutionMSG"}, 
							{1,"SolutionNN"}, 
							{2,"SolutionFI"}, 
							{3,"SolutionKOPT"}, 
							{4,"SolutionBPI"}, 
							{5,"SolutionAnt"}, 
							{6,"SolutionFST"}, 
							{7,"SolutionFST_OPT"}, 
							{8,"SolutionILS"}, 
							{9,"SolutionILS_OPT"},
							{10,"SolutionFSTI"}, 
							{11,"SolutionFSTF"},
							{12,"SolutionILS_LS_2OPT"},  
							{13,"SolutionVND"},  
							{14,"SolutionILS_LS_PART_2OPT"}, 
							{15,"SolutionILS_LS_22Swap"},
							{16,"SolutionILS_LS_PART_22Swap"},
							{90,"Dominance"}, 
							{91,"TwinTools"},
							{92,"MSTLowerBound"}, 
							{93,"YanasseLowerBound"} };
									
std::map <int, std::string> methodNameMap { {0,"Multiple Start Greedy"}, 
							{1,"Nearest Neighbor (TSP Adapted Heuristic)"}, 
							{2,"Farthest Insertion (TSP Adapted Heuristic)"}, 
							{3,"K-Opt"}, 
							{4,"Best Position Insertion"}, 
							{5,"Antonio Augusto's Constructive Heuristic"}, 
							{6,"First Try Heuristic with Inversion Local Search"}, 
							{7,"First Try Heuristic 2-OPT"}, 
							{8,"ILS First Try Heuristic with Inversion Local Search Iterative"}, 
							{9,"ILS with 2-OPT"},
							{10,"ILS First Try Heuristic with Inversion Local Search Iterative "}, 
							{11,"First Try Heuristic with Inversion Local Search Full"},  
							{12,"ILS with inversion Local Search and 2-OPT"},  
							{13,"VND with k-Opt neighborhood"},  
							{14,"ILS with inversion Local Search and Partial-2-OPT"},   
							{15,"ILS with inversion Local Search with Swap(2,2) neighborhood"},   
							{16,"ILS with inversion Local Search with Swap(2,2) partial neighborhood"},   
							{90,"Tool Dominance Checker"}, 
							{91,"Twin Tools Checker"},
							{92,"MST Lower Bound"}, 
							{93,"Yanasse Lower Bound"} };


std::map <std::string, long> instance_time_limit
							{
								{"s3n001.txt", 140},
								{"s3n001_1.txt", 127},
								{"s3n001_2.txt", 121},
								{"s3n001_3.txt", 104},
								{"s3n002.txt", 140},
								{"s3n002_1.txt", 127},
								{"s3n002_2.txt", 121},
								{"s3n002_3.txt", 104},
								{"s3n003.txt", 140},
								{"s3n003_1.txt", 127},
								{"s3n003_2.txt", 121},
								{"s3n003_3.txt", 104},
								{"s3n004.txt", 140},
								{"s3n004_1.txt", 127},
								{"s3n004_2.txt", 121},
								{"s3n004_3.txt", 104},
								{"s3n005.txt", 140},
								{"s3n005_1.txt", 127},
								{"s3n005_2.txt", 121},
								{"s3n005_3.txt", 104},
								{"s3n006.txt", 140},
								{"s3n006_1.txt", 127},
								{"s3n006_2.txt", 121},
								{"s3n006_3.txt", 104},
								{"s3n007.txt", 140},
								{"s3n007_1.txt", 127},
								{"s3n007_2.txt", 121},
								{"s3n007_3.txt", 104},
								{"s3n008.txt", 140},
								{"s3n008_1.txt", 127},
								{"s3n008_2.txt", 121},
								{"s3n008_3.txt", 104},
								{"s3n009.txt", 140},
								{"s3n009_1.txt", 127},
								{"s3n009_2.txt", 121},
								{"s3n009_3.txt", 104},
								{"s3n010.txt", 140},
								{"s3n010_1.txt", 127},
								{"s3n010_2.txt", 121},
								{"s3n010_3.txt", 104},
								//c-4
								{"s4n001.txt", 600},
								{"s4n001_1.txt", 557},
								{"s4n001_2.txt", 533},
								{"s4n001_3.txt", 473},
								{"s4n002.txt", 600},
								{"s4n002_1.txt", 557},
								{"s4n002_2.txt", 533},
								{"s4n002_3.txt", 473},
								{"s4n003.txt", 600},
								{"s4n003_1.txt", 557},
								{"s4n003_2.txt", 533},
								{"s4n003_3.txt", 473},
								{"s4n004.txt", 600},
								{"s4n004_1.txt", 557},
								{"s4n004_2.txt", 533},
								{"s4n004_3.txt", 473},
								{"s4n005.txt", 600},
								{"s4n005_1.txt", 557},
								{"s4n005_2.txt", 533},
								{"s4n005_3.txt", 473},
								{"s4n006.txt", 600},
								{"s4n006_1.txt", 557},
								{"s4n006_2.txt", 533},
								{"s4n006_3.txt", 473},
								{"s4n007.txt", 600},
								{"s4n007_1.txt", 557},
								{"s4n007_2.txt", 533},
								{"s4n007_3.txt", 473},
								{"s4n008.txt", 600},
								{"s4n008_1.txt", 557},
								{"s4n008_2.txt", 533},
								{"s4n008_3.txt", 473},
								{"s4n009.txt", 600},
								{"s4n009_1.txt", 557},
								{"s4n009_2.txt", 533},
								{"s4n009_3.txt", 473},
								{"s4n010.txt", 600},
								{"s4n010_1.txt", 557},
								{"s4n010_2.txt", 533},
								{"s4n010_3.txt", 473},

							};

const std::string INSTANCE_DIR = std::string("Instancias") + std::string(SLASH);
const std::string SOLUTION_DIR = std::string("Instancias") + std::string(SLASH) + std::string("Resultados") + std::string(SLASH);

void printHelp()
{
	printf("Minimization of Tool Switch Problem Solver\n"
			"Execution flags :\n"
			"\t -n= to specify the number of instances to be solved\n"
			"\t -method= to specify the method to solve the MTSP\n"
			"\t -dir= to specify the directory of the instances to be solved\n"
			"\t -n= to specify the number of instances to be solved\n"
			"Choose a method from the above: \n"
			);
	for(auto m : methodNameMap)
	{
		printf("%d: %s\n", m.first, &m.second[0]);
	}
}

bool parseArguments(int argc, char *argv[], config& parameters)
{
	for(int i = 1; i < argc; i++)
	{
		//printf("parsing : %s\n", argv[i]);

		if ( strncmp(argv[i], "-n=", 3)  == 0){
			parameters.n = atoi( &argv[i][3] );
		}
		else if( strncmp(argv[i], "-method=", 8)  == 0){
			parameters.method = atoi( &argv[i][8] );
		}
		else if( strncmp(argv[i], "-silent=", 8)  == 0){
			parameters.method = atoi( &argv[i][8] );
		}
		else if( strncmp(argv[i], "-dir=", 5)  == 0){
			parameters.directoryName = new char[strlen(argv[i]) - 4];
			strcpy(parameters.directoryName, &argv[i][5]);
			parameters.directory = true;
		}
		else if( strncmp(argv[i], "-file=", 6)  == 0){
			parameters.fileName = new char[strlen(argv[i]) - 5];
			strcpy(parameters.fileName, &argv[i][6]);
		}
		else if( strncmp(argv[i], "-k=", 3)  == 0){
			parameters.k = atoi( &argv[i][3] );
		}
		else if( strncmp(argv[i], "-lastk=", 7)  == 0){
			parameters.lastK = atoi( &argv[i][7] );
		}
		else if( strncmp(argv[i], "-v", 2)  == 0){
			parameters.verbose = true;
		}
		else if( strncmp(argv[i], "-t", 2)  == 0){
			parameters.tuning = true;
		}
		else if( strncmp(argv[i], "-p=", 3)  == 0){
			parameters.perturbation = atof( &argv[i][3] );
		}
		else if( strcmp(argv[i], "-help")  == 0){
			printHelp();
			return 1;
		}
		else if( strncmp(argv[i], "-partial=", 9)  == 0){
			parameters.perturbation = atof( &argv[i][9] );
		}
		else if( strncmp(argv[i], "-iter=", 6)  == 0){
			parameters.iter = atoi( &argv[i][6] );
		}
		else if( strncmp(argv[i], "-counter=", 9)  == 0){
			parameters.counter = atoi( &argv[i][9] );
		}
	}	
	return 0;
}
