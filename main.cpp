#include <iostream>
#include <vector>
#include <time.h>
#include "Graph.h"
using namespace std;

void addEdge(vector<int> adj[], int x, int y){
  adj[x].push_back(y);
  adj[y].push_back(x);
}

int main() {
	Graph g = Graph(5); // 0 to 4
	g.addEdge(0,0);
	g.addEdge(3,1);
	g.addEdge(1,2);
	g.addEdge(1,2);
	g.printMatrix();
    /*int N; //Number of nodes
    float P; //Prob of nodes
    vector<int> g[N]; //adj list
    srand(time(0)); //so rand() actually creates a random number
	
    // start adding nodes to the vector 
    for(int i = 1; i < N + 1; i++){
      //unsure
    }

    //Add edges to the graph randomly
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        if(i < j){
          int R = rand(); //take a random number to compare P
          if(R < P) addEdge(g, i, j);
        }
      }
    }*/ 
	// ^^^ please put that in a function instead of main
    return 0;
}
