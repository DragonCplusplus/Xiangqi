/*

  中国象棋C++版
  使用EasyX图形库来制作图形化的中国象棋。
  做的比较简单，代码写的不好请见谅。

  作者：CppDragon
  日期：2017年7月7日
  联系方式：270638232(QQ)
*/

#ifndef XIANGQI_H
#define XIANGQI_H

// 使用EasyX，用于图形化棋子。
#include <easyx.h>
// 使用标准库的string类，代表棋子的名字。
#include <string>

#include <vector>

#define GSTART (initgraph(800,600))
#define GEND (closegraph())

namespace Xiangqi
{

	class Map;
	class Pieces;
	class Referee;
	class Player;
	class Xiangqi;

	class Pieces
	{
	public:

		// 象棋规则，红先黑后。
		enum team
		{
			OFFENSIVE = RED,
			DEFENSIVE = BLACK
		};

		// 象棋的棋子重要性：兵/卒为低，马/炮和士/相为中等，車为高，将/帅为最高。
		enum importance
		{
			LOW,
			MEDIUM,
			HIGH,
			VERY_HIGH
		};

		// 棋子的坐标类型定义。
		struct point
		{
			typedef size_t pos;  // 坐标的数据类型。
			point() = default;
			point(pos x, pos y, pos x_off, pos y_off) :
				_x(x), _y(y), _x_off(x_off), _y_off(y_off) {}

			pos toGraphX()const { return _x * _x_off; }
			pos toGraphY()const { return _y *_y_off; }

			pos _x = 0;  // 坐标中的X轴。
			pos _y = 0;  // 坐标中的Y轴。
			pos _x_off = 0;  // 坐标X的偏移量。实际坐标在图形化坐标的偏移量。
			pos _y_off = 0;  // 坐标Y的偏移量。实际坐标在图形化坐标的偏移量。
		};

		// 棋子属性结构体。
		struct attribute
		{
			attribute(const std::string n, team t, importance i, const point & p) :
				m_name(n), m_team(t), m_importance(i), m_point(p), m_status(false) {}

			std::string m_name;  // 棋子的名字。
			team m_team;  // 棋子的当前团队。参见enum team。
			importance m_importance;  // 棋子的当前重要性。参见enum importance。
			point m_point;  // 棋子的当前坐标。
			bool m_status;  // 棋子的状态，真表示存在，假表示不存在。
		};

	public:

		Pieces(const attribute & a) :
			m_attribute(a) {}

		// 返回棋子的当前重要性。
		importance getImportance()const { return m_attribute.m_importance; }
		// 返回棋子的所属团队。
		team getTeam()const { return m_attribute.m_team; }
		// 返回棋子的当前坐标。
		point getPoint()const { return m_attribute.m_point; }
		// 返回棋子的状态。
		bool getStatus()const { return m_attribute.m_status; }
		// 返回棋子的属性。
		attribute getAttribute()const { return m_attribute; }

		// 棋子的图形化绘图函数。此函数是纯虚函数。
		virtual int draw(size_t width, size_t highth) = 0;
		virtual int move(Map& map, const point & newPoint) = 0;
		virtual Pieces* attack(Map& map, const point & newPoint) = 0;

	protected:

		void setStatus(bool status) { m_attribute.m_status = status; }
		attribute m_attribute;
	};

	class Map
	{
	public:

		enum size
		{
			HIGHTH = 10,
			WIDTH = 9
		};

	public:
		Pieces* get(const Pieces::point & point)const { return get(point._x, point._y); }
		Pieces* get(Pieces::point::pos x, Pieces::point::pos y)const { return m_map[y][x]; }

		Pieces* set(Pieces* pieces, const Pieces::point & point);
		Pieces* set(Pieces* pieces, Pieces::point::pos x, Pieces::point::pos y);

		int showMap(size_t x, size_t y, size_t width, size_t highth)const;
		int showPieces(size_t width, size_t highth)const;

	private:
		Pieces* m_map[HIGHTH][WIDTH];
		std::vector<Pieces*> m_diePiecesBuffer;
	};

}

#endif