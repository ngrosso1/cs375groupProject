#include <iostream>
#include <vector>
#include <time.h>
#include <utility>
#include <chrono>
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
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

	std::pair<int,int> start;
	std::pair<int,int> end;
	start.first=0;
	start.second=0;
	end.first=8;
	end.second=12;
	Graph g = randG(start, end, 10, 16, 0.25);
	cout << "Input Grid" << endl;
	g.printMatrix();
	cout << "--------------------------------------------------------------------------------" << endl;

	auto time1 = high_resolution_clock::now();
	std::vector<std::pair<int,int>> pairs = g.AStar(start,end);
	auto time2 = high_resolution_clock::now();
	g.printSolution(pairs);
	duration<double, std::milli> ms1 = time2 - time1;
	cout << "A* execution time: " << ms1.count() << " ms" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	auto time3 = high_resolution_clock::now();
	pairs=g.dijkstra(start,end);
	g.printSolution(pairs);
	auto time4 = high_resolution_clock::now();
	duration<double, std::milli> ms2 = time4 - time3;
	cout << "Dijkstra's execution time: " << ms2.count() << " ms" << endl;


  return 0;
}
