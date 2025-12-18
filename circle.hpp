#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "idraw.hpp"

namespace top {
  struct Circle: IDraw {
    Circle(p_t p, int r);
    Circle(int x, int y, int r);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
    int radius;
  };
}

#endif
