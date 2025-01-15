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
	routine();
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

void YCH::printmap(int kind) {
	cleardevice();
	BeginBatchDraw();

	TCHAR message__[100];
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("宋体"));
	swprintf_s(message__, _T("按键选择颜色："));
	outtextxy(30, 30, message__);
	settextstyle(30, 0, _T("宋体"));
	swprintf_s(message__, _T("已走步数:%d"), step);
	outtextxy(heng * blocksize - 130, 30, message__);
	swprintf_s(message__, _T("已选颜色"));
	outtextxy(heng * blocksize - 130, 100, message__);
	setfillcolor(RGB(colorset[Sele - 1][0], colorset[Sele - 1][1], colorset[Sele - 1][2]));
	fillrectangle(heng * blocksize, 80,heng * blocksize + blocksize, 120);
	for (int i = 0; i < colornum; i++) {
		swprintf_s(message__, _T("%d"), i + 1);
		outtextxy(265 + (blocksize + 10) * i, 90, message__);
		setfillcolor(RGB(colorset[i][0], colorset[i][1], colorset[i][2]));
		fillrectangle(250 + i * (blocksize + 10), 40, 250 + i * (blocksize + 10) + blocksize, 80);
	}
	for (int i = 0; i < shu; i++) {
		for (int j = 0; j < heng; j++) {
			if(kind) cout << map[i][j] << (map[i][j] >= 10 ? " " : "  ");
			int r = colorset[map[i][j] - 1][0], g = colorset[map[i][j] - 1][1], b = colorset[map[i][j] - 1][2];
			setfillcolor(RGB(r, g, b));
			fillrectangle(50 + j * blocksize, 150 + i * blocksize, 50 + j * blocksize + blocksize, 150 + i * blocksize + blocksize);
		}
		if (kind) cout << endl;
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

void YCH::ChangeBlock(int x, int y, int tar) {
	if (map[y][x] == tar) return;
	printmap(0);
	int ori = map[y][x];
	map[y][x] = tar;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0], ny = y + dir[i][1];
		if (nx < 0 || nx >= heng || ny < 0 || ny >= shu) continue;
		if (map[ny][nx] == ori) ChangeBlock(nx, ny, tar);
	}
	printmap(0);
}

point YCH::listenmouse() {
	point a = { -1,-1 };
	ExMessage m; // 定义消息变量
	while (true)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);
		if (m.message == WM_LBUTTONDOWN || m.message == WM_RBUTTONDOWN) {
			cout << "检测到点击，位于(" << m.x << "," << m.y << ")" << endl;
			m.x -= 50;
			m.y -= 150;
			while (m.x > 0) {
				a.x++;
				m.x -= blocksize;
			}
			while (m.y > 0) {
				a.y++;
				m.y -= blocksize;
			}
			if(a.x >= 0 && a.x < heng && a.y >= 0 && a.y < shu) break;
		}
		else if (m.message == WM_KEYDOWN) {
			cout << "检测到按键按下，虚拟键码: " << m.wParam << endl;
			for (int i = 0; i < colornum; i++) {
				if (m.wParam == Vircode[i]) {
					Sele = i + 1;
				}
			}
		}
		printmap(0);
	}
	return a;
}

void YCH::routine() {
	while (!isFinish()) {
		printmap(0);
		point loca = listenmouse();
		if (map[loca.y][loca.x] != Sele) step++;
		ChangeBlock(loca.x, loca.y, Sele);
	}
}

bool YCH::isFinish() {
	for (int i = 0; i < heng * shu - 1; i++) {
		if (map[i / heng][i % heng] != map[(i + 1) / heng][(i + 1) / shu]) return false;
	}
	return true;
}