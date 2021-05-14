#include <stdio.h>
#include <vector>
#include <utility>
#pragma once
class Graph{
	public:
		Graph(int l, int w); // size (number of nodes)
		void addWall(int u, int v);
		void printMatrix();
		std::vector<std::pair<int,int>> AStar(std::pair<int,int> start, std::pair<int, int> end);
		int heuristic(std::pair<int,int> one, std::pair<int,int> two);
		std::vector<std::pair<int,int>> dijkstra(std::pair<int,int> source, std::pair<int,int> target);
		void printSolution(std::vector<std::pair<int,int>> a);
		std::vector<std::pair<int,int>> succList(std::pair<int,int> src);
	private:
		std::vector<std::vector<int>> adjMatrix;
		int length;
		int width;
};
