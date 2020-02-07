#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <map>
#include <string>
#include <cstring>

#include "Misc.hpp"

extern std::map <int, std::string> methodMap;

extern std::map <int, std::string> methodNameMap;

extern std::map <std::string, long> instance_time_limit;

extern const std::string INSTANCE_DIR;
extern const std::string SOLUTION_DIR;
const double PERTURBATION = 0.2;
const double PARTIAL_SIZE = 0.26;
const double ITER = 200;

typedef struct config_
{
	int n = 0;
	int counter = -1;
	int method = 0;
	int k = 2, lastK = 4;
	int iter = ITER;
	bool verbose = false;
	bool directory = false;
	char* directoryName;
	char* fileName = NULL;
	bool tuning = false;
	double perturbation, partial;

	config_()
	{
		directoryName = new char[3];
		strcpy(directoryName,".");
	}

	void print()
	{
		printf(	"n = %d\n"
				"method = %d\n"
				"k = %d\n"
				"last k = %d\n"
				"verbose = %s\n"
				"directory = %s\n"
				"directoryName = %s\n"
				"fileName = %s\n"
				"tuning = %s\n"
				"perturbation = %lf\n"
				"partial size = %lf\n"
				"ils = %d\n"
				"counter = %d",
				n,
				method,
				k,
				lastK,
				verbose ? "True":"False",
				directory ? "True":"False",
				directoryName,
				fileName,
				tuning ? "True":"False",
				perturbation,
				partial,
				iter,
				counter
			);
	}
} config;

bool parseArguments(int argc, char *argv[], config& parameters);





#endif