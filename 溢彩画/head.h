#pragma once
#include <iostream>
#include <vector>
#include <graphics.h>
using namespace std;

const int heng = 20;
const int shu = 15;
const int areanum = 100;
const int colornum = 7;
const int blocksize = 40;
const int colorset[][3] = { {255,0,0} ,{0,255,0},{0,0,255} ,{153,51,250},{255,0,255},{0,255,255},{255,97,0},{94,38,18},{252,230,201},{0,255,127} };
const int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
const int Vircode[] = { 561,818,1075,1332,1589,1846,2103,2360,2617,2864 };
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
	int step = 0;
	int Sele = 1;

	YCH();
	point bcj(point a);
	void sortmap();
	void printmap(int kind = 1);
	bool Compare(point a, point b);
	bool checkisok();
	void ChangeBlock(int x, int y, int tar);
	point listenmouse();
	void routine();
	bool isFinish();
};
