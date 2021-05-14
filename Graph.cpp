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
std::vector<std::pair<int,int>> Graph::AStar(std::pair<int,int> start, std::pair<int,int> end){
	/*auto cmp = [](std::pair<std::pair<int,int>,int>	left, std::pair<std::pair<int,int>,int> right){
		return left.second > right.second;
	};
	std::priority_queue<std::pair<std::pair<int,int>,int>, std::vector<std::pair<std::pair<int,int>,int>>, decltype(cmp)> q(cmp);
	q.push(start);*/
	std::map<std::pair<int,int>,std::pair<int,int>> endMap;
	std::map<std::pair<int,int>,std::pair<int,int>> dist;
	std::map<std::pair<int,int>,bool> added;
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
	added[start]=true;
	dist[start]=std::make_pair(0,0);
	std::pair<int,int> currentNode;
	while(!openQueue.empty()){
		currentNode = openQueue.top();
		openQueue.pop();
		int x = currentNode.first;
		int y = currentNode.second;
		int g = dist[currentNode].first+1;
		if(x==end.first&&y==end.second){
			break;
		}
		/*if(x!=0&&adjMatrix.at(x-1).at(y)==0){
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
		}*/
		successorList=succList(currentNode);
		//k=openAndClosedList.size();
		for(j=0; j<successorList.size(); j++){
			if(!adjMatrix.at(successorList.at(j).first).at(successorList.at(j).second)){
				int h=heuristic(successorList.at(j),end);
				if(!dist.count(successorList.at(j))||dist[successorList.at(j)].first+dist[successorList.at(j)].second>=g+h){
					dist[successorList.at(j)]=std::make_pair(g,h);
					endMap[successorList.at(j)]=currentNode;
					openQueue.push(successorList.at(j));
				}
			}
		}
		/*for(j=0; j<successorList.size(); j++){
			for(i=0; i<k; i++){
				AStarNode checkNode=openAndClosedList.at(i);
				if(successorList.at(j).loc.first==checkNode.loc.first&&successorList.at(j).loc.second==checkNode.loc.second){
					if(successorList.at(j).g+successorList.at(j).h>=checkNode.g+checkNode.h){
				//		openAndClosedList.erase(openAndClosedList.begin()+i);
				//		openAndClosedList.push_back(successorList.at(j));
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
		}*/
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
	
	currentPair.first=currentNode.first;
	currentPair.second=currentNode.second;
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
}*/

/*int minDistance(int distance[], bool Tset[])
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
}*/
/*
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
			if (!Tset[v] && !adjMatrix[u][v] && distance[u] != INT_MAX && distance[u] + 1 < distance[v])
                distance[v] = distance[u] + 1;
		}
	}
	output(distance);
}
*/
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
std::vector<std::pair<int,int>> Graph::dijkstra(std::pair<int,int> source, std::pair<int,int> target)
{
	/*auto cmp = [](DJnode left, DJnode right){
		return left.dist > right.dist;
	};*/
	std::map<std::pair<int,int>,int> dist;
	auto cmp = [&dist](std::pair<int,int> left, std::pair<int,int> right){
		return dist[left] > dist[right];
	};
	unsigned long int i;
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
	int f;
	int s;
	while(!(curr.first==source.first&&curr.second==source.second)){
		std::cout << "["<<curr.first<<","<<curr.second<<"] ";
		path.push_back(curr);
		f=prev[curr].first;
		s=prev[curr].second;
		curr.first=f;
		curr.second=s;
	}
	std::cout << "["<<source.first<<","<<source.second<<"]\n";
	path.push_back(source);
	return path;
	

}












