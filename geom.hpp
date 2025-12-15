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

  struct IDraw {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);

  size_t rows(f_t fr);
  size_t cols(f_t fr);
}
#endif