#include <iostream>
#include <cmath>

namespace top {
  struct p_t {
    int x, y;
  };

  struct IDraw {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Dot: IDraw {
    Dot(int x, int y);
    explicit Dot(p_t p);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
  };

  struct VLine: IDraw {
    VLine(int x, int y, int l);
    VLine(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct HLine: IDraw {
    HLine(int x, int y, int l);
    HLine(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct DLine: IDraw {
    DLine(int x, int y, int l);
    DLine(p_t p, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };

  struct Circle: IDraw {
    Circle(int x, int y, int r);
    Circle(p_t p, int r);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
    int radius;
  };

  struct frame_t {
    p_t left_bot;
    p_t right_top;
  };

  void extend(p_t ** ps, size_t s, p_t p);
  void make_f(IDraw ** b, size_t k);
  void get_points(top::IDraw & b, p_t ** ps, size_t & s);
  frame_t build_frame(const p_t * ps, size_t s);
  size_t rows(frame_t fr);
  size_t cols(frame_t fr);
  char * build_canvas(frame_t fr, char fill);
  void paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char fill);
  void print_canvas(std::ostream & output, const char * cnv, frame_t fr);
}

int main()
{
  using namespace top;
  int err = 0;
  const size_t count = 4;
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
    frame_t fr = build_frame(p, s);
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

void top::make_f(IDraw ** b, size_t k)
{
  b[0] = new Dot(0, 0);
  b[1] = new HLine(2, 2, 3);
  b[2] = new VLine(3, 3, 4);
  b[3] = new DLine(-10, -10, 4);
}

top::Dot::Dot(int x, int y):
  IDraw(),
  o{x, y}
{}

top::Dot::Dot(p_t p):
  IDraw(),
  o(p)
{}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t p) const
{
  return begin();
}

top::VLine::VLine(int x, int y, int l):
  VLine({x, y}, l)
{}

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
    start.y -= length;
  }
}

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

top::HLine::HLine(int x, int y, int l):
  HLine({x, y}, l)
{}

top::HLine::HLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght can not be 0");
  }
  if (length < 0) {
    length *= -1;
    start.x -= length;
  }
}

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

top::DLine::DLine(int x, int y, int l):
  DLine({x, y}, l)
{}

top::DLine::DLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght can not be 0");
  }
  if (length < 0) {
    length *= -1;
    start.x -= length;
  }
}

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

top::Circle::Circle(int x, int y, int r):
  Circle({x, y}, r)
{}

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

top::p_t top::Circle::begin() const
{
  return p_t{o.x + radius, o.y};
}

// Не работает
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

void top::extend(p_t ** ps, size_t s, p_t p)
{
  p_t * res = new p_t[s + 1];
  for (size_t i = 0; i < s; ++i) {
    res[i] = (*ps)[i];
  }
  res[s] = p;
  delete [] *ps;
  *ps = res;
}

void top::get_points(IDraw & b, p_t ** ps, size_t & s)
{
  p_t p = b.begin();
  extend(ps, s, p);
  size_t new_size = s + 1;
  while (b.next(p) != b.begin()) {
    p = b.next(p);
    extend(ps, new_size, p);
    new_size++;
  }
  s = new_size;
}

top::frame_t top::build_frame(const p_t * ps, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  int minx = ps[0].x, maxx = minx;
  int miny = ps[0].y, maxy = miny;
  for (size_t i = 1; i < s; ++i) {
    minx = std::min(minx, ps[i].x);
    maxx = std::max(maxx, ps[i].x);
    miny = std::min(miny, ps[i].y);
    maxy = std::max(maxy, ps[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}

size_t top::rows(frame_t fr)
{
  return (fr.right_top.y - fr.left_bot.y + 1);
}

size_t top::cols(frame_t fr)
{
  return (fr.right_top.x - fr.left_bot.x + 1);
}

char * top::build_canvas(frame_t fr, char fill)
{
  char * cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i) {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char fill)
{
  for (size_t i = 0; i < k; ++i) {
    int dx = ps[i].x - fr.left_bot.x;
    int dy = fr.right_top.y - ps[i].y;
    cnv[dy * cols(fr) + dx] = fill;
  }
}

void top::print_canvas(std::ostream & output, const char * cnv, frame_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i) {
    for (size_t j = 0; j < cols(fr); ++j) {
      output << cnv[i * cols(fr) + j];
    }
    output << "\n";
  }
}
