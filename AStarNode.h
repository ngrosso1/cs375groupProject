#include <stdio.h>
#include <utility>

#pragma once
class AStarNode{
	public:
		AStarNode(int one, int two, int g, int h, std::pair<int,int> parent);
		std::pair<int,int> loc;
		int g;
		int h;
		std::pair<int,int> parent;
};
