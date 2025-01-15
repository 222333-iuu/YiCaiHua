#include "head.h"

YCH::YCH() {
	srand(time(NULL));
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			fa[i][j] = { j,i };
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < areanum; i++) {
		int temp = rand() % (heng * shu);
		while (map[temp / heng][temp % heng]) {
			temp = rand() % (heng * shu);
		}
		point a = { temp % heng, temp / heng };
		map[a.y][a.x] = i % colornum + 1;
		area.push_back(a);
		color.push_back(i % colornum + 1);
	}
	vector<vector<int>> pool;
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			int temp = i * heng + j;
			if (i != shu - 1) pool.push_back({ temp, temp + heng });
			if (j != heng - 1) pool.push_back({ temp, temp + 1 });
		}
	}

	while (!checkisok() && pool.size()) {
	AGAIN:
		int res = rand() % pool.size();
		int x1 = pool[res][1] % heng, y1 = pool[res][1] / heng;
		int x2 = pool[res][0] % heng, y2 = pool[res][0] / heng;
		if (!Compare(fa[y1][x1], { x1,y1 }) && !Compare(fa[y2][x2], { x2,y2 })) goto AGAIN;
		if (!map[y1][x1] && !map[y2][x2] || map[y1][x1] && map[y2][x2]) goto AGAIN;
		pool.erase(pool.begin() + res, pool.begin() + res + 1);
		if (map[y2][x2]) fa[y1][x1] = { x2,y2 };
		else fa[y2][x2] = { x1,y1 };
		sortmap();
	}
}



point YCH::bcj(point a) {
	if (fa[a.y][a.x].x == a.x && fa[a.y][a.x].y == a.y) return a;
	fa[a.y][a.x] = bcj(fa[a.y][a.x]);
	map[a.y][a.x] = map[fa[a.y][a.x].y][fa[a.y][a.x].x];
	return fa[a.y][a.x];
}

void YCH::sortmap() {
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			point a = { j,i };
			bcj(a);
		}
	}
}

void YCH::printmap() {
	cleardevice();
	BeginBatchDraw();
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			cout << map[i][j] << (map[i][j] >= 10 ? " " : "  ");
			int r = colorset[map[i][j] - 1][0], g = colorset[map[i][j] - 1][1], b = colorset[map[i][j] - 1][2];
			setfillcolor(RGB(r, g, b));
			fillrectangle(50 + j * blocksize, 50 + i * blocksize, 50 + j * blocksize + blocksize, 50 + i * blocksize + blocksize);
		}
		cout << endl;
	}
	FlushBatchDraw();
}

bool YCH::Compare(point a, point b) {
	return a.x == b.x && a.y == b.y;
}

bool YCH::checkisok() {
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			if (!map[i][j]) return false;
		}
	}
	return true;
}