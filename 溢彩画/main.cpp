#include "head.h"

int main() {
	initgraph(100 + heng * blocksize, 100 + shu * blocksize, NOCLOSE | SHOWCONSOLE);
	setbkcolor(RGB(255, 255, 255));
	YCH s;
	s.printmap();
	system("pause");
}