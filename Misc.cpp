#include "Misc.hpp"

#include <algorithm>

vector<string> getDirectoryFiles(string directory)
{
	vector<string> files;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (&directory[0])) != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			string f = string(ent->d_name) ;
			if(f.find("Solution") == string::npos && f.find(".txt") != string::npos)
			{
				files.push_back(f);
			}
		}
		closedir (dir);
	}
	else
	{
		printf("Erro ao abrir diretorio\n");
	}
	
	sort(files.begin(), files.end(), std::greater<string>());
	return files;
}

void createDirectory(const char* path, mode_t mode)
{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		CreateDirectory(path, NULL);
	#else
		mkdir(path, mode);
	#endif
}



void printVector(vector<int>& v)
{
	for(int i = 0; i < (int) v.size(); i++)
		printf("%d ", v[i]);
	printf("\n");
}



unionFind::unionFind(int n)
{
	this->n = n;
	for (int i = 0; i < n; i++)
	{
		set.push_back(i);
		rank.push_back(0);
	}
}

bool unionFind::unionSet(int x, int y)
{
	int x_raiz = find(x);
	int y_raiz = find(y);

	if (x_raiz == y_raiz)
		return false;

	if (rank[x] > rank[y])
		set[y_raiz] = x_raiz;
	else if (rank[y] > rank[x])
		set[x_raiz] = y_raiz;
	else
	{
		set[y_raiz] = x_raiz;
		rank[x_raiz]++;
	}

	return true;
}

int unionFind::find(int x)
{
	if (set[x] != x)
		set[x] = find(set[x]);
	return set[x];
}
