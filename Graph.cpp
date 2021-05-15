#include <stdio.h>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <cstdlib>
#include <map>
#include <limits>
#include <climits>
#include <algorithm>

#define Infinity 9999

#include "Graph.h"
#include "AStarNode.h"

Graph::Graph(int x, int y){
	int i;
	int j;
	length=x;
	width=y;
	for(i=0; i<x; i++){
		std::vector<int> beginningList;
		for(j=0; j<y; j++){
			beginningList.push_back(0);
		}
		adjMatrix.push_back(beginningList);
	}
}
void Graph::addWall(int u, int v){
	adjMatrix.at(u).at(v)=1;
	//if(u-v){
	//	adjMatrix.at(v).at(u)+=1;
	//}
}
void Graph::printMatrix(){
	int i;
	int j;
	std::cout << "  ";
	for(i=0; i<width; i++){
		std::cout << i << " ";
	}
	std::cout << "\n";
	for(i=0; i<length; i++){
		std::cout << i << " ";
		for(j=0; j<width; j++){
			if(adjMatrix.at(i).at(j)){
				std::cout << adjMatrix.at(i).at(j) << " ";
			}
			else{
				std::cout << ". ";
			}
		}
		std::cout << "\n";
	}
}
std::vector<std::pair<int,int>> Graph::AStar(std::pair<int,int> start, std::pair<int,int> end, bool print){
	/*auto cmp = [](std::pair<std::pair<int,int>,int>	left, std::pair<std::pair<int,int>,int> right){
		return left.second > right.second;
	};
	std::priority_queue<std::pair<std::pair<int,int>,int>, std::vector<std::pair<std::pair<int,int>,int>>, decltype(cmp)> q(cmp);
	q.push(start);*/
	//int count=0;
	std::map<std::pair<int,int>,std::pair<int,int>> endMap;
	std::map<std::pair<int,int>,std::pair<int,int>> dist;
	unsigned long int j;
	std::pair<int,int> nullPair;
	nullPair.first=-1;
	nullPair.second=-1;
	//AStarNode startNode=AStarNode(start.first, start.second, 0, 0, nullPair);
	std::pair<int,int> currentPair;
	std::vector<std::pair<int,int>> successorList;
	auto cmp = [&dist](std::pair<int,int> left, std::pair<int,int> right){
		return dist[left].first+dist[left].second > dist[right].first+dist[right].second;
	};
	//AStarNode currentNode = startNode;
	std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>,decltype(cmp)> openQueue(cmp);
	openQueue.push(start);
	dist[start]=std::make_pair(0,0);
	std::pair<int,int> currentNode;
	while(!openQueue.empty()){
		currentNode = openQueue.top();
		openQueue.pop();
//		count++;
		int x = currentNode.first;
		int y = currentNode.second;
		//std::cout << x <<" " <<y <<"\n";
		int g = dist[currentNode].first+1;
		if(x==end.first&&y==end.second){
			break;
		}
		successorList=succList(currentNode);
		//k=openAndClosedList.size();
		for(j=0; j<successorList.size(); j++){
			currentPair=successorList.at(j);
			if(!adjMatrix.at(currentPair.first).at(currentPair.second)){
				int h=heuristic(successorList.at(j),end);
				if(!dist.count(successorList.at(j))||dist[successorList.at(j)].first+dist[successorList.at(j)].second>g+h){
					dist[successorList.at(j)]=std::make_pair(g,h);
					endMap[successorList.at(j)]=currentNode;
					openQueue.push(successorList.at(j));
				}
			}
		}
		successorList.clear();
	}
//	std::cout << count<<"\n";
	successorList.clear();
	if(openQueue.empty()){
		return successorList;
	}
	currentPair.first=currentNode.first;
	currentPair.second=currentNode.second;
	int f;
	int s;
	std::vector<std::pair<int,int>> retPairs;
	//std::cout << "Reverse path\n";
	if(print){
		std::cout << "A* Output:" << std::endl;
		std::cout << "Shortest Path: ";
	}
	while(!(currentPair.first==start.first&&currentPair.second==start.second)){
		if(print){
			std::cout << "["<<currentPair.first<<","<<currentPair.second<<"] ";
		}
		retPairs.push_back(currentPair);
		f=endMap[currentPair].first;
		s=endMap[currentPair].second;
		currentPair.first=f;
		currentPair.second=s;
	}
	if(print){
		std::cout << "["<<start.first<<","<<start.second<<"]\n";
	}
	retPairs.push_back(start);
	return retPairs;
		
}
void Graph::printSolution(std::vector<std::pair<int,int>> sols){
	int i;
	int j;
	std::cout << "  ";
	for(i=0; i<width; i++){
		std::cout << i << " ";
	}
	std::cout << "\n";
	for(i=0; i<length; i++){
		std::cout << i << " ";
		for(j=0; j<width; j++){
			std::pair<int,int> h;
			h.first=i;
			h.second=j;
			if(std::count(sols.begin(), sols.end(), h)){
				std::cout << "#" << " ";
			}
			else if(adjMatrix.at(i).at(j)){
				std::cout << adjMatrix.at(i).at(j) << " ";
			}
			else{
				std::cout << ". ";
			}
		}
		std::cout << "\n";
	}
}
int Graph::heuristic(std::pair<int,int> u, std::pair<int,int> v)
{
	return std::abs(u.first-v.first)+std::abs(u.second-v.second); //manhattan distanceance
}



std::vector<std::pair<int,int>> Graph::succList(std::pair<int,int> src){
	std::vector<std::pair<int,int>> succ;
	std::pair<int,int> curr;
	if(src.first!=0){//&&!adjMatrix[src.first-1][src.second]){
		curr.first=src.first-1;
		curr.second=src.second;
		succ.push_back(curr);
	}
	if(src.second!=0){//&&!adjMatrix[src.first][src.second-1]){
		curr.first=src.first;
		curr.second=src.second-1;
		succ.push_back(curr);
	}
	if(src.first!=length-1){//&&!adjMatrix[src.first+1][src.second]){
		curr.first=src.first+1;
		curr.second=src.second;
		succ.push_back(curr);
	}
	if(src.second!=width-1){//&&adjMatrix[src.first][src.second+1]){
		curr.first=src.first;
		curr.second=src.second+1;
		succ.push_back(curr);
	}
	return succ;
}
std::vector<std::pair<int,int>> Graph::dijkstra(std::pair<int,int> source, std::pair<int,int> target, bool print)
{
	/*auto cmp = [](DJnode left, DJnode right){
		return left.dist > right.dist;
	};*/
	std::map<std::pair<int,int>,int> dist;
	auto cmp = [&dist](std::pair<int,int> left, std::pair<int,int> right){
		return dist[left] > dist[right];
	};
	unsigned long int i;
	//int count=0;
	std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>,decltype(cmp)> prioQ(cmp);
	std::map<std::pair<int,int>,std::pair<int,int>> prev;
	std::pair<int,int> curr;
	std::pair<int,int> nullPair;
	nullPair.first=-1;
	nullPair.second=-1;
	std::vector<std::pair<int,int>> succL;
	std::vector<std::pair<int,int>> path;
	// make node from pair
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j <width ; j++)
		{
			if(adjMatrix[i][j] == 0){ 
				curr.first=i;
				curr.second=j;
				//prioQ.push(curr);
				dist[curr]= 999999;
				prev[curr]=nullPair;
			}
		}
	}
	dist[source]=0;
	prioQ.push(source);
	while(!prioQ.empty()){
		curr=prioQ.top();
		prioQ.pop();
	//	count++;
		//std::cout << curr.first << " " <<curr.second << "\n";
		succL=succList(curr);
		for(i=0; i<succL.size(); i++){
			int alt = dist[curr]+1;
			if(alt < dist[succL.at(i)]){
				dist[succL.at(i)]=alt;
				prev[succL.at(i)]=curr;
				prioQ.push(succL.at(i));
			}
		}
		if(curr.first==target.first&&curr.second==target.second){
			break;
		}
	}
	//std::cout << count<<"\n";
	int f;
	int s;
	if(prioQ.empty()){
		succL.clear();
		return succL;
	}
	if(print){
		std::cout << "Dijkstra's Output:" << std::endl;
		std::cout << "Shortest Path: ";
	}
	while(!(curr.first==source.first&&curr.second==source.second)){
		if(print){
			std::cout << "["<<curr.first<<","<<curr.second<<"] ";
		}
		path.push_back(curr);
		f=prev[curr].first;
		s=prev[curr].second;
		curr.first=f;
		curr.second=s;
	}
	if(print){
		std::cout << "["<<source.first<<","<<source.second<<"]\n";
	}
	path.push_back(source);
	return path;
	

}












