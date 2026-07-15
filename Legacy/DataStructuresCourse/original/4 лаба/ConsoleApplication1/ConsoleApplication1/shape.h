//Учебная программа на тему "Иерархия классов" (C)lgn,12.04.13
//shape.h -- Библиотека фигур 
//#pragma region
//#pragma endregion
#include <vector>
using namespace std;
#pragma region Библиотека фигур
#pragma region Gloabals
enum color { black = '*', white = ' ' };
char screen[XMAX][YMAX];
const char* wrongParamError = "Некорректные параметры при формировании фигуры\n";
const char* missPointError = "Непопадание точки на экран\n";
const char* notEnougthSpace = "Нехватка места для фигуры на экране\n";
#pragma endregion
#pragma region Фигура
struct shape { //Виртуальный базовый класс "фигура"
	static shape* list;
	shape* next;
	shape() { next = list; list = this; }
	virtual point north() const = 0;
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;
	virtual void move(int, int) = 0;
public:
	///<summary>проверка попадания</summary>
	int on_screen(point p)
	{
		if (0 <= p.x && p.x < XMAX && 0 <= p.y && p.y < YMAX)
			return true;
		else
			throw exception(missPointError);
		//return false;
	}
	///<summary>проверка координат на привальность</summary>
	bool IsCoordCorrect(vector<point> points)
	{
		for each (point p in points)
		{
			if (!on_screen(p))
				throw exception(wrongParamError);
		}
	}
	///<summary>проверка координат на привальность</summary>
	bool IsCoordCorrect(point p)
	{
		if (!on_screen(p))
			throw exception(wrongParamError);
	}
};
shape * shape::list = 0;
#pragma endregion
#pragma region Линия
class line : public shape {
	/*
	отрезок прямой ["w", "e" ]
	north() определяет точку - "выше центра отрезка и
	так далеко на север, как самая его северная точка"
	*/
	point w, e;
public:
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point west() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point neast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point seast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point swest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	void move(int a, int b)
	{
		w.x += a; w.y += b; e.x += a; e.y += b;
	}
	void draw()
	{
		try
		{
			on_screen(w);
			on_screen(e);
		}
		catch (exception ex)
		{
			throw exception(notEnougthSpace);
		}
		put_line(w, e);
	}
	line(point a, point b)
	{
		IsCoordCorrect(vector<point> {a, b});
		w = a; e = b;
	}
	line(point a, int l)
	{
		IsCoordCorrect(vector<point> {a});
		if (l <= 0) throw exception(wrongParamError);
		w = point(a.x + l - 1, a.y); e = a;
	}
};
#pragma endregion
#pragma region Прямоугольник
class rectangle : public shape {
	/* nw ------ n ----- ne
	   |				 |
	   |				 |
	   w		 c		 e
	   |				 |
	   |				 |
	   sw ------ s ----- se
	*/
	point sw, ne;
public:
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point west() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(sw.x, ne.y); }
	point nwest() const { return point(ne.x, sw.y); }
	point swest() const { return sw; }
	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
	}
	void draw();
	rectangle(point, point);
};
rectangle::rectangle(point a, point b)
{
	try
	{
		IsCoordCorrect(vector<point> {a, b});
		if (a.x <= b.x) {
			if (a.y <= b.y) {
				sw = a;
				ne = b;
			}
			else {
				sw = point(a.x, b.y);
				ne = point(b.x, a.y);
			}
		}
		else {
			if (a.y <= b.y) {
				sw = point(b.x, a.y);
				ne = point(a.x, b.y);
			}
			else {
				sw = b;
				ne = a;
			}
		}
	}
	catch (exception ex)
	{
		throw exception(notEnougthSpace);
	}
}
void rectangle::draw()
{
	point nw(sw.x, ne.y);
	point se(ne.x, sw.y);
	put_line(nw, ne);
	put_line(ne, se);
	put_line(se, sw);
	put_line(sw, nw);
}
#pragma endregion
#pragma region Крест
class saltire : public shape {
	point w;
public:
	point north() const { return point(0, 0); }
	point south() const { return point(0, 0); }
	point east()  const { return point(0, 0); }
	point west()  const { return point(0, 0); }
	point neast() const { return point(w.x + 1, w.y + 1); }
	point seast() const { return point(w.x + 1, w.y - 1); }
	point nwest() const { return point(w.x - 1, w.y + 1); }
	point swest() const { return point(w.x - 1, w.y - 1); }
	void move(int a, int b)
	{
		w.x += a;w.y += b;
	}
	void draw();
	saltire(point a)
	{
		IsCoordCorrect(vector<point> {a});
		w = a;
	};
};
void saltire::draw()
{
	put_point(w);
	put_point(w.x + 1, w.y + 1);
	put_point(w.x + 1, w.y - 1);
	put_point(w.x - 1, w.y + 1);
	put_point(w.x - 1, w.y - 1);
}
#pragma endregion
#pragma region Крест
class cross : public shape {
	point w;
public:
	point north() const { return point(w.x, w.y - 1); }
	point south() const { return point(w.x, w.y + 1); }
	point east()  const { return point(w.x + 2, w.y); }
	point west()  const { return point(w.x - 2, w.y); }
	point neast() const { return point(w.x + 1, w.y + 1); }
	point seast() const { return point(w.x + 1, w.y - 1); }
	point nwest() const { return point(w.x - 1, w.y + 1); }
	point swest() const { return point(w.x - 1, w.y - 1); }
	void move(int a, int b)
	{
		w.x += a;w.y += b;
	}
	void draw();
	cross(point a)
	{
		IsCoordCorrect(vector<point> {a});
		w = a;
	};
};
void cross::draw()
{
	put_point(w);
	put_point(north());
	put_point(south());
	put_point(west());
	put_point(east());
}
#pragma endregion
#pragma region Методы
void screen_init()
{
	for (int y = 0; y < YMAX; y++)
		for (int x = 0; x < XMAX; x++)
			screen[x][y] = white;
}
///<summary>Очистка экрана</summary>
void screen_clear() {
	screen_init();
}
///<summary>Обновление экрана</summary>
void screen_refresh()
{
	for (int y = YMAX - 1; 0 <= y; y--) { // с верхней строки до нижней
		for (int x = 0; x < XMAX; x++) // от левого столбца до правого
			cout << screen[x][y];
		cout << '\n';
	}
}
///<summary>Перерисовка всех фигур</summary>
void shape_refresh()
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) p->draw();
	screen_refresh();
}
///<summary>поместить фигуру p над фигурой q</summary>
void Up(shape* p, const shape* q)
{
	point n = q->north();
	point s = p->south();
	p->move(n.x - s.x, n.y - s.y + 1);
}
///<summary>проверка попадания</summary>
int on_screen(int a, int b)
{
	//return 0 <= a && a <XMAX && 0 <= b && b<YMAX;
	if (0 <= a && a < XMAX && 0 <= b && b < YMAX)
		return true;
	else
		return false;
	//throw exception("Некорретные координаты точки\n");
}
///<summary>отрисовка прямой между двумя точками</summary>
void put_line(int x0, int y0, int x1, int y1)
{
	register int dx = 1;
	int a = x1 - x0;
	if (a < 0) dx = -1, a = -a;
	register int dy = 1;
	int b = y1 - y0;
	if (b < 0) dy = -1, b = -b;
	int two_a = 2 * a;
	int two_b = 2 * b;
	int xcrit = -b + two_a;
	register int eps = 0;
	for (;;) {
		put_point(x0, y0);
		if (x0 == x1 && y0 == y1) break;
		if (eps <= xcrit) x0 += dx, eps += two_b;
		if (eps >= a || a < b) y0 += dy, eps -= two_a;
	}
}
///<summary>добавление точки на экран</summary>
void put_point(int a, int b)
{
	try
	{
		if (on_screen(a, b)) screen[a][b] = black;
	}
	catch (exception ex)
	{
		printf(ex.what());
	}
}
#pragma endregion
#pragma endregion