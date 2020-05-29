
// MpiBFS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "mpi.h"
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;
const int n = 100;
int i, j;
bool check = true;
bool* visited = new bool[n];
int GM[n][n];

void ReadFromFile() {
	ifstream in("D:\\3 курс\\3 курс 2 семестр\\паралельне\\лаба\\matr100.txt");
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
	string res;
	int* queue = new int[n];
	int count, head;
	for (i = 0; i < n; i++) queue[i] = 0;
	count = 0; head = 0;
	queue[count++] = unit;
	visited[unit] = true;
	
	while (head < count)
	{
		unit = queue[head++];
		
		for (i = 0; i < n; i++)
			if (GM[unit][i] && !visited[i])
			{ 
				//cout <<i + 1<<" " ;
				
				queue[count++] = i;
				visited[i] = true;
			}
	}
	delete[]queue;

}
//mpiexec -n 4 MpiBFS.exe
int ProcNum;     
int ProcRank;
//головна функція
void main(int argc, char* argv[])
{

	int elemsproc;
	if (check) { ReadFromFile(); check = false; }

	double duration; double starttime, endtime;
	
	for (i = 0; i < n; i++)
	{
		visited[i] = false;
	}

	int rank, count;
	visited[0] = true;
	int p[n]; int proccount = 0;
	for (i = 0; i < n; i++)
		if (GM[0][i] && !visited[i])
		{
			proccount++;
			p[proccount] = i;
		}

	MPI_Init(&argc, &argv);
    starttime = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &count);

	elemsproc = (proccount / (count ));
	
	if (rank == 0)
	{
		int* procpart = new int[proccount];
		for (int i = 0; i < proccount; i++) {
			procpart[i] = p[i + 1];
		}

		for (int j = 1; j < count; j++)
		{
			if (elemsproc != 0) {
				int* dividedArr = new int[elemsproc];
				for (int i = 0; i < elemsproc; i++) {
					dividedArr[i] = procpart[(j - 1) * elemsproc + i];
				}
				MPI_Send(dividedArr, elemsproc, MPI_INT, j, 0, MPI_COMM_WORLD);
			}
			
		}
	}
	else
	{
		MPI_Status status;
		int* buffer = new int[elemsproc];
		for (i = 0; i < elemsproc; i++)
			buffer[i] = -1;
		MPI_Recv(buffer, elemsproc, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	for (int i = 0; i < elemsproc; i++) {
			
			BFS(visited, buffer[0]);
		}
	}

	delete[]visited;
	endtime = MPI_Wtime();
	duration = endtime - starttime;
	MPI_Finalize();
	cout<<endl <<" "<< "duration: " << duration ;
}
