#include <iostream>
#include <time.h>
#include <vector>

void addEdge(vector<int> adj[], int x, int y){
  adj[x].push_back(y);
  adj[y].push_back(x);
}

int N; //Number of nodes
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
      float R = (float) rand() / MAX_RAND; //take a random number to compare P
      if(R < P){
        addEdge(g, i, j);
    }
  }
}