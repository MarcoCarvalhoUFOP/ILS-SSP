#ifndef MISCHPP__
#define MISCHPP__


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "Misc\dirent.h"
#include <windows.h>
#define SLASH "\\"
#else
#include "dirent.h"
#include <sys/types.h>
#include <sys/stat.h>
#define SLASH "/"
#endif

#include <vector>
#include <string>
#include <functional>
#include <sstream>

using namespace std;


vector<string> getDirectoryFiles(string directory);
void createDirectory(const char* path, mode_t);
void printVector(vector<int>& v);

template<typename T>
string toString(T param)
{
	stringstream str;
	str << param;
	return str.str();
}



class unionFind
{
public:
	
	vector<int> set, rank;
	int n;
	unionFind(int n);
	bool unionSet(int x, int y);
	int find(int x);
};

#endif