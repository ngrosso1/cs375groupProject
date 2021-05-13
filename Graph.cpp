#include <stdio.h>
#include <vector>
#include <iostream>

#include "Graph.h"

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

