#include <stdio.h>
#include <vector>
#include <utility>
#pragma once
class Graph{
	public:
		Graph(int l, int w); // size (number of nodes)
		void addWall(int u, int v);
		void printMatrix();
		void AStar(std::pair<int,int> start, std::pair<int, int> end);
		int heuristic(std::pair<int,int> one, std::pair<int,int> two);
	private:
		std::vector<std::vector<int>> adjMatrix;
		int length;
		int width;
};
