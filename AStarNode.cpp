#include <stdio.h>
#include <utility>

#include "AStarNode.h"

AStarNode::AStarNode(int one, int two, int gee, int ach, std::pair<int, int> p){
	loc.first=one;
	loc.second=two;
	g=gee;
	h=ach;
	parent=p;
}
