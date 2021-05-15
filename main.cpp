#include <iostream>
#include <vector>
#include <time.h>
#include <utility>
#include <numeric>
#include <chrono>
#include <random>
#include <ctime>
#include "Graph.h"
#include "ERmodel.cpp"


using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

void testInputOutput(std::pair<int,int> start, std::pair<int,int> end, int l, int w, float p){
	Graph g = randG(start, end, l, w, p);

	cout << "Input Grid" << endl;
	g.printMatrix();
	cout << "--------------------------------------------------------------------------------" << endl;
	auto time1 = high_resolution_clock::now();
	std::vector<std::pair<int,int>> pairs = g.AStar(start,end,true);
	auto time2 = high_resolution_clock::now();
	if(pairs.empty()){
		cout << "Path blocked off\n";
	}
	else{
		g.printSolution(pairs);
		duration<double, std::milli> ms1 = time2 - time1;
		cout << "A* execution time: " << ms1.count() << " ms" << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
	
		auto time3 = high_resolution_clock::now();
		pairs=g.dijkstra(start,end,true);
		g.printSolution(pairs);
		auto time4 = high_resolution_clock::now();
		duration<double, std::milli> ms2 = time4 - time3;
		cout << "Dijkstra's execution time: " << ms2.count() << " ms" << endl;
	}
}	
void testInput(std::pair<int,int> start, std::pair<int,int> end, int l, int w, float p, int n){
	
	Graph g = randG(start, end, l, w, p);
	int count=n;
	std::vector<double> AStarTimes;
	std::vector<double> DijkstraTimes;
	while(count>0){
		g=randG(start,end,l,w,p);
		/*cout << "Input Grid" << endl;
		g.printMatrix();
		cout << "--------------------------------------------------------------------------------" << endl;
		*/
		auto time1 = high_resolution_clock::now();
		std::vector<std::pair<int,int>> pairs = g.AStar(start,end,false);
		auto time2 = high_resolution_clock::now();
		if(pairs.empty()){
			//cout << "Path blocked off\n";
			continue;
			
		}
		else{
			//g.printSolution(pairs);
			duration<double, std::milli> ms1 = time2 - time1;
			//cout << "A* execution time: " << ms1.count() << " ms" << endl;
			AStarTimes.push_back(ms1.count());
			//cout << "--------------------------------------------------------------------------------" << endl;
		
			auto time3 = high_resolution_clock::now();
			pairs=g.dijkstra(start,end,false);
			//g.printSolution(pairs);
			auto time4 = high_resolution_clock::now();
			duration<double, std::milli> ms2 = time4 - time3;
			DijkstraTimes.push_back(ms2.count());
			count--;
	//		cout << count <<"\n";
			//cout << "Dijkstra's execution time: " << ms2.count() << " ms" << endl;
		}
	}
	
	std::vector<double> diffs;
	unsigned long int i;
	for(i=0; i<AStarTimes.size(); i++){
		diffs.push_back(DijkstraTimes[i]-AStarTimes[i]);
	}
	double sq_sum=std::inner_product(diffs.begin(), diffs.end(), diffs.begin(), 0.0);
	double avg= accumulate(diffs.begin(), diffs.end(), 0.0)/diffs.size();
	double stdev=std::sqrt(sq_sum / diffs.size() - avg*avg);
	avg= accumulate(AStarTimes.begin(), AStarTimes.end(), 0.0)/AStarTimes.size();
	cout << "Input: start: ["<<start.first<<","<<start.second<<"] , end: ["<<end.first<<","<<end.second<<"] length: "<<l<<" width: "<<w << " density: "<<p<< " n: "<<n<<"\n";
	cout<< "A* average: "<<avg<<" ms\n";
	avg= accumulate(DijkstraTimes.begin(), DijkstraTimes.end(), 0.0)/DijkstraTimes.size();
	cout << "Dijkstra average: " <<avg<<" ms\n";
	cout << "Stdev of differences: " << stdev<<"\n";
}

int main() {
	/*Graph g = Graph(5,6); // 0 to 4
	g.addWall(0,2);
	g.addWall(1,2);
	g.addWall(2,3);
	g.printMatrix();
	*/

	std::pair<int,int> start;
	std::pair<int,int> end;
	start.first=1;
	start.second=1;
	end.first=8;
	end.second=8;
	srand(time(NULL));
	testInputOutput(end,start,10,10,.33);
	testInput(start,end,10,10,.25, 100);
	testInput(start,end,10,10,.33, 100);
	//testInputOutput(start,end,50,50,.25);
	end.first=45;
	end.second=45;
	testInput(start,end,50,50,.25,100);
	testInput(start,end,50,50,.33,100);
	end.first=200;
	end.second=200;
	testInput(start,end,250,250,.25,100);
	testInput(start,end,250,250,.33,100);
	/*Graph g = randG(start, end, 50, 50, 0.25);
	cout << "Input Grid" << endl;
	g.printMatrix();
	cout << "--------------------------------------------------------------------------------" << endl;

	auto time1 = high_resolution_clock::now();
	std::vector<std::pair<int,int>> pairs = g.AStar(start,end);
	auto time2 = high_resolution_clock::now();
	if(pairs.empty()){
		cout << "Path blocked off\n";
	}
	else{
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
	}*/

  return 0;
}
