// bfs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <fstream>



using namespace std;
const int n = 10000;
int i, j;
int GM[n][n];

void ReadFromFile() {
	ifstream in;
		string path = "matr10000.txt";
		in.open(path);
		
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			in >> GM[i][j];
			

		}
		
	}
}

//пошук в ширину
void BFS(bool* visited, int unit)
{
	int* queue = new int[n];
	int count, head;
	for (i = 0; i < n; i++) queue[i] = 0;
	count = 0; head = 0;
	queue[count++] = unit;
	visited[unit] = true;
	//cout << unit << " ";
	while (head < count)
	{
		unit = queue[head++];
		
		for (i = 0; i < n; i++)
			if (GM[unit][i] && !visited[i])
			{
				
				queue[count++] = i;
				visited[i] = true;
				//cout << i << " ";
			}
	}
	delete[]queue;
}
//головна функція
void main()
{
	clock_t timestart;
	double duration;
	ReadFromFile();
	int start=42;
	
	timestart = clock();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)
	{
		visited[i] = false;
	}
	
	
	BFS(visited, start - 1);
	delete[]visited;
	duration = (clock() - timestart) / (double)CLOCKS_PER_SEC;
	std::cout << endl << "duration: " << duration << '\n';
	system("pause>>void");
	
}


