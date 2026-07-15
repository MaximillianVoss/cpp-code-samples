#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include "screen.h"
#include "shape.h"
using namespace std;

class myshape : public rectangle {
  cross* l_eye; // левый глаз
  cross* r_eye; // правый глаз
  line* mouth; // рот
public:
  myshape(point, point);
  void draw();
  void move(int, int);
};
myshape::myshape(point a, point b) : rectangle(a,b)
{
	int ll = neast().x-swest().x+1;
	int hh = neast().y-swest().y+1;
	l_eye = new cross(point(swest().x + 2, swest().y + hh * 3 / 4));
	r_eye = new cross(point(swest().x+ll-4,swest().y+hh*3/4));
	mouth = new line(point(swest().x+2,swest().y+hh/4),ll-4);
}
void myshape::draw()
{
	rectangle::draw();
	int a = (swest().x+neast().x)/2;
	int b = (swest().y+neast().y)/2;
	put_point(point(a,b));
}
void myshape::move(int a, int b)
{
	rectangle::move(a,b);
	l_eye->move(a,b);
	r_eye->move(a,b);
	mouth->move(a,b);
	//r_ear->move(a,b);
}
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	try
	{
		screen_init();
		shape* p1 = new rectangle(point(0, 0), point(10, 5));
		shape* p2 = new line(point(0, 15), 17);
		shape* p3 = new myshape(point(15, 10), point(27, 18));
		shape_refresh();
		_getch();
		p3->move(-10, -6);
		Up(p2, p3);
		Up(p1, p2);
		shape_refresh();
		_getch();
	}
	catch (exception ex)
	{
		printf(ex.what());
	}
	system("pause");
	return 0;
}
