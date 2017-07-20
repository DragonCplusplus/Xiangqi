/*

  �й�����C++��
  ʹ��EasyXͼ�ο�������ͼ�λ����й����塣
  ���ıȽϼ򵥣�����д�Ĳ�������¡�

  ���ߣ�CppDragon
  ���ڣ�2017��7��7��
  ��ϵ��ʽ��270638232(QQ)
*/

#ifndef XIANGQI_H
#define XIANGQI_H

// ʹ��EasyX������ͼ�λ����ӡ�
#include <easyx.h>
// ʹ�ñ�׼���string�࣬�������ӵ����֡�
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

		// ������򣬺��Ⱥں�
		enum team
		{
			OFFENSIVE = RED,
			DEFENSIVE = BLACK
		};

		// �����������Ҫ�ԣ���/��Ϊ�ͣ���/�ں�ʿ/��Ϊ�еȣ�܇Ϊ�ߣ���/˧Ϊ��ߡ�
		enum importance
		{
			LOW,
			MEDIUM,
			HIGH,
			VERY_HIGH
		};

		// ���ӵ��������Ͷ��塣
		struct point
		{
			typedef size_t pos;  // ������������͡�
			point() = default;
			point(pos x, pos y, pos x_off, pos y_off) :
				_x(x), _y(y), _x_off(x_off), _y_off(y_off) {}

			pos toGraphX()const { return _x * _x_off; }
			pos toGraphY()const { return _y *_y_off; }

			pos _x = 0;  // �����е�X�ᡣ
			pos _y = 0;  // �����е�Y�ᡣ
			pos _x_off = 0;  // ����X��ƫ������ʵ��������ͼ�λ������ƫ������
			pos _y_off = 0;  // ����Y��ƫ������ʵ��������ͼ�λ������ƫ������
		};

		// �������Խṹ�塣
		struct attribute
		{
			attribute(const std::string n, team t, importance i, const point & p) :
				m_name(n), m_team(t), m_importance(i), m_point(p), m_status(false) {}

			std::string m_name;  // ���ӵ����֡�
			team m_team;  // ���ӵĵ�ǰ�Ŷӡ��μ�enum team��
			importance m_importance;  // ���ӵĵ�ǰ��Ҫ�ԡ��μ�enum importance��
			point m_point;  // ���ӵĵ�ǰ���ꡣ
			bool m_status;  // ���ӵ�״̬�����ʾ���ڣ��ٱ�ʾ�����ڡ�
		};

	public:

		Pieces(const attribute & a) :
			m_attribute(a) {}

		// �������ӵĵ�ǰ��Ҫ�ԡ�
		importance getImportance()const { return m_attribute.m_importance; }
		// �������ӵ������Ŷӡ�
		team getTeam()const { return m_attribute.m_team; }
		// �������ӵĵ�ǰ���ꡣ
		point getPoint()const { return m_attribute.m_point; }
		// �������ӵ�״̬��
		bool getStatus()const { return m_attribute.m_status; }
		// �������ӵ����ԡ�
		attribute getAttribute()const { return m_attribute; }

		// ���ӵ�ͼ�λ���ͼ�������˺����Ǵ��麯����
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