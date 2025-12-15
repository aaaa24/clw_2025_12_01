#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace top {
  struct p_t {
    int x, y;
  };

  struct f_t {
    p_t left_bot;
    p_t right_top;
  };

  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);

  size_t rows(f_t fr);
  size_t cols(f_t fr);
  f_t build_frame(const p_t * ps, size_t s);
}
#endif
