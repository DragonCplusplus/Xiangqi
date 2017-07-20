
#include <cstdio>
#include "../include/Xiangqi.h"

using namespace Xiangqi;

int main(int argc, char* argv[])
{
	Map m;
	GSTART;

	m.showMap(100,50, 640,480);

	getchar();
	GEND;
	return 0;
}