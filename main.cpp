#include <iostream>
#include "tdraw.hpp"

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
