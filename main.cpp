#include <iostream>
#include <vector>
#include <time.h>
#include <utility>
#include "Graph.h"
#include "ERmodel.cpp"

using namespace std;

int main() {
	/*Graph g = Graph(5,6); // 0 to 4
	g.addWall(0,2);
	g.addWall(1,2);
	g.addWall(2,3);
	g.printMatrix();
	*/
	std::pair<int,int> start;
	std::pair<int,int> end;
	start.first=0;
	start.second=0;
	end.first=0;
	end.second=5;
	Graph g = randG(start, end, 5, 6, 0.25);
	g.printMatrix();
	std::vector<std::pair<int,int>> pairs = g.AStar(start,end);
	g.printSolution(pairs);
	pairs=g.dijkstra(start,end);
	g.printSolution(pairs);

  return 0;
}
