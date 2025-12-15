#include <iostream>
#include <cmath>
#include "geom.hpp"
#include "idraw.hpp"
#include "dot.hpp"
#include "canvas.hpp"

namespace top {
  struct VLine: IDraw {
    VLine(p_t p, int l);
    VLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct HLine: IDraw {
    HLine(p_t p, int l);
    HLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct DLine: IDraw {
    DLine(p_t p, int l);
    DLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct Rectangle: IDraw {
    Rectangle(p_t p, int a, int b);
    Rectangle(int x, int y, int a, int b);
    Rectangle(p_t left_bot, p_t rigth_top);
    Rectangle(f_t frame);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };

  struct FilledRectangle: IDraw {
    FilledRectangle(p_t p, int a, int b);
    FilledRectangle(int x, int y, int a, int b);
    FilledRectangle(p_t left_bot, p_t rigth_top);
    FilledRectangle(f_t frame);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };

  struct Square: IDraw {
    Square(p_t p, int a);
    Square(int x, int y, int a);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };

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

  f_t make_valid_frame(p_t p, int a, int b);
  p_t next_on_rect_perimeter(p_t current, f_t frame);
  p_t next_in_filled_rect(p_t current, f_t frame);
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

top::VLine::VLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght can not be 0");
  }
  if (length < 0) {
    length *= -1;
    start.y -= length - 1;
  }
}

top::VLine::VLine(int x, int y, int l):
  VLine({x, y}, l)
{}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length - 1) {
    return begin();
  }
  return p_t{start.x, p.y + 1};
}

top::HLine::HLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght cannot be zero");
  }
  if (length < 0) {
    length *= -1;
    start.x -= length - 1;
  }
}

top::HLine::HLine(int x, int y, int l):
  HLine({x, y}, l)
{}

top::p_t top::HLine::begin() const
{
  return start;
}

top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) {
    return begin();
  }
  return p_t{p.x + 1, start.y};
}

top::DLine::DLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght cannot be zero");
  }
  if (length < 0) {
    length *= -1;
    start.x -= length - 1;
  }
}

top::DLine::DLine(int x, int y, int l):
  DLine({x, y}, l)
{}

top::p_t top::DLine::begin() const
{
  return start;
}

top::p_t top::DLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) {
    return begin();
  }
  return p_t{p.x + 1, p.y + 1};
}

top::f_t top::make_valid_frame(p_t p, int a, int b) {
    if (a == 0 || b == 0)
        throw std::invalid_argument("side cannot be zero");
    p_t lb = p;
    int w = a, h = b;
    if (w < 0) { w = -w; lb.x -= w - 1; }
    if (h < 0) { h = -h; lb.y -= h - 1; }
    return { lb, {lb.x + w - 1, lb.y + h - 1} };
}

top::p_t top::next_on_rect_perimeter(p_t current, f_t frame) {
    p_t lb = frame.left_bot;
    p_t rt = frame.right_top;
    int w = rt.x - lb.x + 1;
    int h = rt.y - lb.y + 1;

    if (current.x == lb.x && current != lb) {
        return {current.x, current.y - 1};
    }
    if (current.y == rt.y) {
        return {current.x - 1, current.y};
    }
    if (current.x == rt.x) {
        return {current.x, current.y + 1};
    }
    return {current.x + 1, lb.y};
}

top::p_t top::next_in_filled_rect(p_t current, f_t frame) {
    p_t lb = frame.left_bot;
    p_t rt = frame.right_top;
    if (current.x == rt.x && current.y == rt.y) {
        return lb;
    }
    if (current.x == rt.x) {
        return {lb.x, current.y + 1};
    }
    return {current.x + 1, current.y};
}

top::Rectangle::Rectangle(p_t p, int a, int b):
  IDraw(),
  frame(make_valid_frame(p, a, b))
{}

top::Rectangle::Rectangle(int x, int y, int a, int b):
  Rectangle({x, y}, a, b)
{}

top::Rectangle::Rectangle(p_t left_bot, p_t rigth_top):
  Rectangle(left_bot, rigth_top.x - left_bot.x, rigth_top.y - left_bot.y)
{}

top::Rectangle::Rectangle(f_t frame):
  Rectangle(frame.left_bot, frame.right_top)
{}

top::p_t top::Rectangle::begin() const
{
  return frame.left_bot;
}

top::p_t top::Rectangle::next(p_t p) const 
{
  return next_on_rect_perimeter(p, frame);
}

top::FilledRectangle::FilledRectangle(p_t p, int a, int b):
  IDraw(),
  frame(make_valid_frame(p, a, b))
{}

top::FilledRectangle::FilledRectangle(int x, int y, int a, int b):
  FilledRectangle({x, y}, a, b)
{}

top::FilledRectangle::FilledRectangle(p_t left_bot, p_t rigth_top):
  FilledRectangle(left_bot, rigth_top.x - left_bot.x, rigth_top.y - left_bot.y)
{}

top::FilledRectangle::FilledRectangle(f_t frame):
  FilledRectangle(frame.left_bot, frame.right_top)
{}

top::p_t top::FilledRectangle::begin() const
{
  return frame.left_bot;
}

top::p_t top::FilledRectangle::next(p_t p) const 
{
  return next_in_filled_rect(p, frame);
}

top::Square::Square(p_t p, int a):
  IDraw(),
  frame(make_valid_frame(p, a, a))
{}

top::Square::Square(int x, int y, int a):
  Square({x, y}, a)
{}

top::p_t top::Square::begin() const
{
  return frame.left_bot;
}

top::p_t top::Square::next(p_t p) const 
{
  return next_on_rect_perimeter(p, frame);
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
