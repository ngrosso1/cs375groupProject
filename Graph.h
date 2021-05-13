#include <stdio.h>
#include <vector>
#pragma once
class Graph{
	public:
		Graph(int l, int w); // size (number of nodes)
		void addWall(int u, int v);
		void printMatrix();
	private:
		std::vector<std::vector<int>> adjMatrix;
		int length;
		int width;
};
