#include <stdio.h>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <cstdlib>
#include <map>

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
			std::cout << adjMatrix.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
}
void Graph::AStar(std::pair<int,int> start, std::pair<int,int> end){
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
	std::cout << "Reverse path\n";
	while(!(currentPair.first==start.first&&currentPair.second==start.second)){
		std::cout << "["<<currentPair.first<<","<<currentPair.second<<"] ";
		f=endMap[currentPair].first;
		s=endMap[currentPair].second;
		currentPair.first=f;
		currentPair.second=s;
	}
	std::cout << "["<<start.first<<","<<start.second<<"]\n";
	return;
	
}
int Graph::heuristic(std::pair<int,int> u, std::pair<int,int> v){
	return std::abs(u.first-v.first)+std::abs(u.second-v.second); //manhattan distance
}
