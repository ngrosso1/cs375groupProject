#include <stdio.h>
#include <vector>
#include <iostream>

#include "Graph.h"

Graph::Graph(int n){
	int i;
	int j;
	size=n;
	for(i=0; i<n; i++){
		std::vector<int> beginningList;
		for(j=0; j<n; j++){
			beginningList.push_back(0);
		}
		adjMatrix.push_back(beginningList);
	}
}
void Graph::addEdge(int u, int v){
	adjMatrix.at(u).at(v)+=1;
	if(u-v){
		adjMatrix.at(v).at(u)+=1;
	}
}
void Graph::printMatrix(){
	int i;
	int j;
	std::cout << "  ";
	for(i=0; i<size; i++){
		std::cout << i << " ";
	}
	std::cout << "\n";
	for(i=0; i<size; i++){
		std::cout << i << " ";
		for(j=0; j<size; j++){
			std::cout << adjMatrix.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
}

