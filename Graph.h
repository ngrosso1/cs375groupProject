#include <stdio.h>
#include <vector>
#pragma once
class Graph{
	public:
		Graph(int n); // size (number of nodes)
		void addEdge(int u, int v);
		void printMatrix();
	private:
		std::vector<std::vector<int>> adjMatrix;
		int size;
};
