#pragma once
#include <iostream>
#include <vector>
#include <graphics.h>
using namespace std;

const int heng = 20;
const int shu = 15;
const int areanum = 5;
const int colornum = 5;
const int blocksize = 50;
const int colorset[][3] = { {255,0,0} ,{0,255,0},{0,0,255} ,{255,255,0},{255,0,255} };

struct point {
	int x;
	int y;
};

class YCH {
public:
	int map[shu][heng];
	point fa[shu][heng];
	vector<point> area;
	vector<int> color;

	YCH();
	point bcj(point a);
	void sortmap();
	void printmap();
	bool Compare(point a, point b);
	bool checkisok();
};
