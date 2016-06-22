//Учебная программа на тему "Иерархия классов" (C)lgn,12.04.13
//shape.h -- Библиотека фигур 
enum color { black='*', white=' ' };
char screen[XMAX] [YMAX];
void screen_init()
{
  for (int y=0; y<YMAX; y++)
    for (int x=0; x<XMAX; x++)
       screen[x] [y] = white;
}

inline int on_screen(int a, int b) // проверка попадания
{ return 0<=a && a <XMAX && 0<=b && b<YMAX; }

void put_point(int a, int b)
{ if (on_screen(a,b)) screen[a] [b] = black; }

void put_line(int x0, int y0, int x1, int y1)
/*
Нарисовать отрезок прямой (x0,y0) - (x1,y1).
Уравнение прямой: b(x-x0) + a(y-y0) = 0.
Минимизируется величина abs(eps),
где eps = 2*(b(x-x0)) + a(y-y0).
См. Newman, Sproull
"Principles of interactive Computer Graphics"
McGraw-Hill, New York, 1979. pp. 33-34.
*/
{
  register int dx = 1;
  int a = x1 - x0;
  if (a < 0) dx = -1, a = -a;
  register int dy = 1;
  int b = y1 - y0;
  if (b < 0) dy = -1, b = -b;
  int two_a = 2*a;
  int two_b = 2*b;
  int xcrit = -b + two_a;
  register int eps = 0;

  for (;;) {
	put_point(x0,y0);
	if (x0==x1 && y0==y1) break;
	if (eps <= xcrit) x0 +=dx, eps +=two_b;
	if (eps>=a || a<b) y0 +=dy, eps -=two_a;
  }
}

void screen_clear() { screen_init(); } //Очистка экрана

void screen_refresh() // Обновление экрана
{
  for (int y=YMAX-1; 0<=y; y--) { // с верхней строки до нижней
    for (int x=0; x<XMAX; x++) // от левого столбца до правого
      cout << screen[x] [y];
    cout << '\n';
  }
}

//Библиотека фигур
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
};

shape * shape::list = 0;
class line : public shape {
/*
отрезок прямой ["w", "e" ]
north() определяет точку - "выше центра отрезка и
так далеко на север, как самая его северная точка"
*/
  point w, e;
public:
  point north() const { return point((w.x+e.x)/2, e.y<w.y? w.y: e.y); }
  point south() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point east() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point west() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point neast() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point seast() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point nwest() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  point swest() const { return point((w.x+e.x)/2, e.y<w.y? e.y: w.y); }
  void move(int a, int b)
	{ w.x +=a; w.y +=b; e.x +=a; e.y +=b; }
  void draw() { put_line(w,e); }
  line(point a, point b) { w = a; e = b; }
  line(point a, int l) { w = point(a.x+l-1,a.y); e = a; }
};
//Прямоугольник
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
  point north() const { return point((sw.x+ne.x)/2,ne.y); }
  point south() const { return point((sw.x+ne.x)/2,sw.y); }
  point east() const { return point(sw.x,(sw.y+ne.y)/2); }
  point west() const { return point(ne.x,(sw.y+ne.y)/2); }
  point neast() const { return ne; }
  point seast() const { return point(sw.x, ne.y); }
  point nwest() const { return point(ne.x, sw.y); }
  point swest() const { return sw; }
  void move(int a, int b)
	{ sw.x+=a; sw.y+=b; ne.x+=a; ne.y+=b; }
  void draw();
  rectangle(point,point);
};
rectangle::rectangle(point a, point b)
{
  if (a.x <= b.x) {
	if (a.y <= b.y) {
	   sw = a;
	   ne = b;
	}
	else {
	   sw = point(a.x,b.y);
	   ne = point(b.x,a.y);
	}
  }
  else {
	if (a.y <= b.y) {
	  sw = point(b.x,a.y);
	  ne = point(a.x,b.y);
	}
	else {
	  sw = b;
	  ne = a;
	}
  }
}  
void rectangle::draw()
{
  point nw(sw.x,ne.y);
  point se(ne.x,sw.y);
  put_line(nw,ne);
  put_line(ne,se);
  put_line(se,sw);
  put_line(sw,nw);
}
void shape_refresh(); // нарисовать все фигуры
void stack(shape* p, const shape* q); // поместить p над q

void shape_refresh() // Перерисовка всех фигур
{
  screen_clear();
  for (shape* p = shape::list; p; p=p->next) p->draw();
  screen_refresh();
}
void Up(shape* p, const shape* q) // поместить p над q
{
  point n = q->north();
  point s = p->south();
  p->move(n.x-s.x,n.y-s.y+1);
}



class saltire : public shape {
point w;
	public:
  point north() const { return point(0,0); }
  point south() const { return point(0,0); }
  point east()  const { return point(0,0); }
  point west()  const { return point(0,0); }
  point neast() const { return point(w.x+1,w.y+1); }
  point seast() const { return point(w.x+1,w.y-1); }
  point nwest() const { return point(w.x-1,w.y+1); }
  point swest() const { return point(w.x-1,w.y-1); }
  void move(int a,int b)
  { w.x+=a;w.y+=b; }
  void draw();
  saltire(point a)  { w=a; };
  };

  void saltire :: draw()
  { 
	  //point w(w.x-1,w.y-1);
	  put_point(w);
	  put_point(w.x+1,w.y+1);
	  put_point(w.x+1,w.y-1);
	  put_point(w.x-1,w.y+1);
	  put_point(w.x-1,w.y-1);
	 // put_point(w+1);
	}