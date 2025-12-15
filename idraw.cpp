#include <cstddef>
#include "idraw.hpp"

using top::p_t;

namespace {
  void extend(p_t ** ps, size_t s, p_t p)
  {
  p_t * res = new p_t[s + 1];
  for (size_t i = 0; i < s; ++i) {
      res[i] = (*ps)[i];
  }
  res[s] = p;
  delete [] *ps;
  *ps = res;
  }
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
