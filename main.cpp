#include <iostream>
#include <cmath>
#include "tdraw.hpp"

namespace top {
  struct FilledSquare: IDraw {
    FilledSquare(p_t p, int a);
    FilledSquare(int x, int y, int a);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };

  struct Circle: IDraw {
    Circle(p_t p, int r);
    Circle(int x, int y, int r);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
    int radius;
  };
}

void make_f(top::IDraw ** b, size_t k);

int main()
{
  using namespace top;
  int err = 0;
  const size_t count = 9;
  IDraw * f[count] = {};
  p_t * p = nullptr;
  size_t s = 0;
  char * cnv = nullptr;
  std::ostream & output = std::cout;
  try {
    make_f(f, count);
    for (size_t i = 0; i < count; ++i) {
      get_points((*f[i]), &p, s);
    }
    f_t fr = build_frame(p, s);
    cnv = build_canvas(fr, '.');
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(output, cnv, fr);
  } catch (...) {
    err = 1;
  }
  for (size_t i = 0; i < count; ++i) {
    delete f[i];
  }
  delete [] p;
  delete [] cnv;
  return err;
}

void make_f(top::IDraw ** b, size_t k)
{
  using namespace top;
  b[0] = new Dot(10, 10);
  b[1] = new HLine(2, 2, 3);
  b[2] = new VLine(3, 3, 4);
  b[3] = new DLine(-10, -10, -4);
  b[4] = new Square(-10, 10, 5);
  b[5] = new Rectangle(0, 0, 7, 6);
  b[6] = new FilledRectangle(0, -5, -7, -6);
  b[7] = new FilledRectangle(0, -5, 7, 6);
  b[8] = new FilledSquare(-5, 0, -3);
}

top::FilledSquare::FilledSquare(p_t p, int a):
  IDraw(),
  frame(make_valid_frame(p, a, a))
{}

top::FilledSquare::FilledSquare(int x, int y, int a):
  FilledSquare({x, y}, a)
{}

top::p_t top::FilledSquare::begin() const
{
  return frame.left_bot;
}

top::p_t top::FilledSquare::next(p_t p) const 
{
  return next_in_filled_rect(p, frame);
}

top::Circle::Circle(p_t p, int r):
  IDraw(),
  o{p.x, p.y},
  radius(r)
{
  if (radius == 0) {
    throw std::invalid_argument("radius can not be 0");
  }
  if (radius < 0) {
    radius *= -1;
  }
}

top::Circle::Circle(int x, int y, int r):
  Circle({x, y}, r)
{}

top::p_t top::Circle::begin() const
{
  return p_t{o.x + radius, o.y};
}

// Does not work
top::p_t top::Circle::next(p_t p) const
{
  if (radius == 1) {
    return begin();
  }
  const double PI = acos(-1.0);
  int dx = p.x - o.x;
  int dy = p.y - o.y;
  int angle = atan2(dy, dx) * 180.0 / PI;
  if (angle < 0) {
    angle += 360;
  }
  for (int i = 0; i < 360; ++i) {
    int new_angle = (angle + i) % 360;
    int new_x = o.x + radius * cos(new_angle);
    int new_y = o.y + radius * sin(new_angle);
    p_t new_p{new_x, new_y};
    if (new_p != p) {
      return new_p;
    }
  }
  return p;
}
