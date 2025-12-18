#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "idraw.hpp"

namespace top {
  struct Rectangle: IDraw {
    Rectangle(p_t p, int a, int b);
    Rectangle(int x, int y, int a, int b);
    Rectangle(p_t left_bot, p_t rigth_top);
    Rectangle(f_t frame);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };
}

#endif
