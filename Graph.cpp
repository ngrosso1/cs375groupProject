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
#define V 5

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
std::vector<std::pair<int,int>> Graph::AStar(std::pair<int,int> start, std::pair<int,int> end){
	/*auto cmp = [](std::pair<std::pair<int,int>,int>	left, std::pair<std::pair<int,int>,int> right){
		return left.second > right.second;
	};
	std::priority_queue<std::pair<std::pair<int,int>,int>, std::vector<std::pair<std::pair<int,int>,int>>, decltype(cmp)> q(cmp);
	q.push(start);*/
	std::map<std::pair<int,int>,std::pair<int,int>> endMap;
	unsigned long int i;
	unsigned long int j;
	unsigned long int k;
	std::pair<int,int> nullPair;
	nullPair.first=-1;
	nullPair.second=-1;
	AStarNode startNode=AStarNode(start.first, start.second, 0, 0, nullPair);
	std::pair<int,int> currentPair;
	std::vector<AStarNode> successorList;
	auto cmp = [](AStarNode left, AStarNode right){
		return left.g+left.h > right.g+right.h;
	};
	bool add = true;
	bool added = false;
	AStarNode currentNode = startNode;
	std::priority_queue<AStarNode, std::vector<AStarNode>,decltype(cmp)> openQueue(cmp);
	openQueue.push(startNode);
	std::vector<AStarNode> openAndClosedList;
	openAndClosedList.push_back(startNode);
	while(!openQueue.empty()){
		currentNode = openQueue.top();
		openQueue.pop();
		int x = currentNode.loc.first;
		int y = currentNode.loc.second;
		int g = currentNode.g+1;
		if(x!=0&&adjMatrix.at(x-1).at(y)==0){
			currentPair.first=x-1;
			currentPair.second=y;
			if(currentPair.first==end.first&&currentPair.second==end.second){
				endMap[std::make_pair(end.first,end.second)]=currentNode.loc;
				currentNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
			}
			AStarNode successorNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
			successorList.push_back(successorNode);
		}
		if(y!=0&&adjMatrix.at(x).at(y-1)==0){
			currentPair.first=x;
			currentPair.second=y-1;
			if(currentPair.first==end.first&&currentPair.second==end.second){
				endMap[std::make_pair(end.first,end.second)]=currentNode.loc;
				currentNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
				break;
			}
			AStarNode successorNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
			successorList.push_back(successorNode);
		}
		if(x!=length-1&&adjMatrix.at(x+1).at(y)==0){
			currentPair.first=x+1;
			currentPair.second=y;
			if(currentPair.first==end.first&&currentPair.second==end.second){
				endMap[std::make_pair(end.first,end.second)]=currentNode.loc;
				currentNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
				break;
			}
			AStarNode successorNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
			successorList.push_back(successorNode);
		}
		if(y!=width-1&&adjMatrix.at(x).at(y+1)==0){
			currentPair.first=x;
			currentPair.second=y+1;
			if(currentPair.first==end.first&&currentPair.second==end.second){
				endMap[std::make_pair(end.first,end.second)]=currentNode.loc;
				currentNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
				break;
			}
			AStarNode successorNode=AStarNode(currentPair.first,currentPair.second,g,heuristic(currentPair,end),currentNode.loc);
			successorList.push_back(successorNode);
		}
		k=openAndClosedList.size();
		for(j=0; j<successorList.size(); j++){
			for(i=0; i<k; i++){
				AStarNode checkNode=openAndClosedList.at(i);
				if(successorList.at(j).loc.first==checkNode.loc.first&&successorList.at(j).loc.second==checkNode.loc.second){
					if(successorList.at(j).g+successorList.at(j).h>=checkNode.g+checkNode.h){
					/*	openAndClosedList.erase(openAndClosedList.begin()+i);
						openAndClosedList.push_back(successorList.at(j));*/
						add = false;
					}		
				}
			}
			if(add&&!added){
				openQueue.push(successorList.at(j));
				openAndClosedList.push_back(successorList.at(j));
				endMap[successorList.at(j).loc]=currentNode.loc;
				added=true;
				add=true;
			}
			added=false;
			add=true;
		}
		//openAndClosedList.push_back(currentNode);
		successorList.clear();
	}
	//at end: go though and do linkedlist stuff
	/*Node* head = new Node();
	head->next=NULL;
	head->data=currentNode;
	while(currentNode.parent.loc.first!=-1){
		Node* t = new Node();
		t->data = currentNode.parent;
		t->next = head;
		head=t;
	}*/	
	i=0;
	currentPair.first=currentNode.loc.first;
	currentPair.second=currentNode.loc.second;
	int f;
	int s;
	std::vector<std::pair<int,int>> retPairs;
	std::cout << "Reverse path\n";
	while(!(currentPair.first==start.first&&currentPair.second==start.second)){
		std::cout << "["<<currentPair.first<<","<<currentPair.second<<"] ";
		retPairs.push_back(currentPair);
		f=endMap[currentPair].first;
		s=endMap[currentPair].second;
		currentPair.first=f;
		currentPair.second=s;
	}
	std::cout << "["<<start.first<<","<<start.second<<"]\n";
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


/* void Graph::dijkstra(int n, int source)
{
	int cost[5][5];
	int distance[5];
	int pred[5];
	int visited[5];
	int count, mindistance, next, i, j;

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
	if(adjMatrix[i][j] == 0)
		cost[i][j] = INFINITY;
	else 
		cost[i][j] = adjMatrix[i][j];
				
	for(i = 0; i < n; i++)
	{
		distance[i] = cost[source][i];
		pred[i] = source;
		visited[i] = 0;
	}
	distance[source] = 0;
	visited[source] = 1;
	count = 1;

	while(count < n-1)
	{
		mindistance = INFINITY;
		for(i = 0; i < n; i++)
			if((distance[i] < mindistance) &&(!visited[i]))
			{
				mindistance = distance[i];
				next = i;
			}
		visited[next] = 1;
		for(i = 0; i < n; i++)
			if(!visited[i])
		if((mindistance + cost[next][i]) < distance[i])
		{
			distance[i] = mindistance + cost[next][i];
			pred[i] = next;
		}
		count++;
	}
		
	for(i = 0; i < n; i++)
	if(i!= source)
	{
		std::cout << "\ndistanceance of node" <<i<<"="<<distance[i];
		std::cout << "\nPath = "<<i;
		j = i;
		do {
			j = pred[j];
			std::cout << "<-" << j;
		}while(j != source);	
	}	
}
*/
/*void output(int distance[])
{
    printf("Vertex \t\t distanceance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, distance[i]);
}
*/
int minDistance(int distance[], bool Tset[])
{
	int min = INT_MAX, min_index;
	for(int i = 0; i < V; i++)
	{
		if(Tset[i] == false && distance[i] <= min)
		{
			min = distance[i];
			min_index = i;
		}
	}
	return min_index;
}
void Graph::dijkstra(int source)
{
	int distance[V];
	bool Tset[V];

	for(int i = 0; i < V; i++)
	{
		distance[i] = INT_MAX,Tset[i] = false;
	}
	distance[source] = 0;

	for(int count = 0; count < V-1; count++)
	{
		int u = minDistance(distance, Tset);

		Tset[u] = true;

		for(int v = 0; v < V; v++)
		{
			if (!Tset[v] && adjMatrix[u][v] && distance[u] != INT_MAX && distance[u] + adjMatrix[u][v] < distance[v])
                distance[v] = distance[u] + adjMatrix[u][v];
		}
	}
	//output(distance);
}













