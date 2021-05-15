#include <iostream>
#include <time.h>
#include <vector>
#include <utility>
#include <queue>
#include <cstdlib>
#include <map>
#include <limits>
#include <climits>
#include <algorithm>
#include <random>
#include "Graph.h"

Graph randG(std::pair<int, int> x, std::pair<int, int> y, int N, int M, float P){
  //int N = y.second + 1; //Number of nodes

  Graph g = Graph(N, M); //adj list
  //std::srand(time(0)); //so rand() actually creates a random number

  //Add edges to the graph randomly
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
        float R = (float) rand() / RAND_MAX; //take a random number to compare P
	  if(R < P){ //if random number is less than prob than add a wall
          if(x.first == i && x.second == j) continue; //if start or end point dont add wall
          else if(y.first == i && y.second == j) continue;
          else g.addWall(i, j);
        }
    }
  }

  return g;
}

/*
// start adding nodes to the vector
for(int i = 1; i < N + 1; i++){
  //unsure
}
*/
