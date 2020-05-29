// OpenMpiBFS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <fstream>

#include <fstream>
#include <omp.h>
#include <ctime>

using namespace std;
const int n = 2000;
int i, j;
int GM[n][n];

void ReadFromFile() {
	ifstream in("matr2000.txt");

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in >> GM[i][j];
		}
	}
}
//матрица суміжності
void BFS(bool* visited, int unit)
{

	int* queue = new int[n];
	int count, head;
	for (i = 0; i < n; i++) queue[i] = 0;
	count = 0; head = 0;
	queue[count++] = unit;
	visited[unit] = true;
//	cout << unit + 1 << " ";
	while (head < count)
	{
		unit = queue[head++];

#pragma omp parallel for
		for (i = 0; i < n; i++)
		{
			
			if (GM[unit][i] && !visited[i])
			{

				cout << i + 1 << " ";
				queue[count++] = i;
				visited[i] = true;
			}
		}
		}
	
	delete[]queue;
}

int main()
{ 
		
	double duration; double starttime, endtime;
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)
	{
		visited[i] = false;
	}
	ReadFromFile();
	int rank, count;
	visited[0] = true;

	clock_t timestart;
	int start=1;
    omp_set_num_threads(8);
	cout << "Order: ";
	timestart = clock();
	BFS(visited, start - 1);
	delete[]visited;
	duration = (clock() - timestart) / (double)CLOCKS_PER_SEC;
	std::cout << endl << "duration: " << duration << '\n';

	return 0;
}


//printf("Hello world! I'm thread %d out of %d threads.\n",omp_get_thread_num(), omp_get_num_threads());

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
