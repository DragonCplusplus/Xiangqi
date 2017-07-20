
#include "../include\Xiangqi.h"

using namespace Xiangqi;

Pieces * Map::set(Pieces * pieces, const Pieces::point & point)
{
	return set(pieces, point._x, point._y);
}

Pieces * Map::set(Pieces * pieces, Pieces::point::pos x, Pieces::point::pos y)
{
	Pieces *p = get(x, y);
	m_map[y][x] = pieces;
	return p;
}

int Map::showMap(size_t x, size_t y, size_t width, size_t highth) const
{
	size_t x_off = (width + x) / WIDTH;
	size_t y_off = (highth + y) / HIGHTH;

	width = x_off * WIDTH - x_off + x;
	highth = y_off * HIGHTH - y_off + y;

	rectangle(x, y, width, highth);
	line(x + x_off * 3, y, x + x_off * 5, y + y_off * 2);
	line(x + x_off * 5, y, x + x_off * 3, y + y_off * 2);

	line(x + x_off * 3, highth, x + x_off * 5, y + y_off * 7);
	line(x + x_off * 5, highth, x + x_off * 3, y + y_off * 7);

	for (size_t n = 1; n < 9 ; ++n)
	{
		size_t x_val = x + x_off * n;
		size_t y_val = y + y_off * n;

		if (n < WIDTH - 1)
		{
			line(x_val, y, x_val, y + y_off * 4);
			line(x_val, y + y_off * 5, x_val, highth);
		}
		if(n < HIGHTH - 1)
			line(x, y_val, width, y_val);
	}

	return 0;
}

int Map::showPieces(size_t width, size_t highth) const
{
	return 0;
}
