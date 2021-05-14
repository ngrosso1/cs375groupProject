#include <stdio.h>
#include <utility>
#include "Dijkstra.h"

Dijkstra::DJnode(int i, int j, int distance)
{
	loc.first = i;
	loc.second = j;
    dist = distance;

	
}