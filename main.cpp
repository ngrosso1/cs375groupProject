#include <iostream>
#include <vector>
#include <time.h>
#include <utility>
#include "Graph.h"

using namespace std;

int main() {
	Graph g = Graph(5,6); // 0 to 4
	g.addWall(0,2);
	g.addWall(1,2);
	g.printMatrix();
	std::pair<int,int> start;
	std::pair<int,int> end;
	start.first=0;
	start.second=0;
	end.first=0;
	end.second=5;
	g.AStar(start,end);
	g.dijkstra(0);

  return 0;
}
