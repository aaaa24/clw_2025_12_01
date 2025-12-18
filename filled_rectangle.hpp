#ifndef FILLED_RECTANGLE_HPP
#define FILLED_RECTANGLE_HPP

#include "idraw.hpp"

namespace top {
  struct FilledRectangle: IDraw {
    FilledRectangle(p_t p, int a, int b);
    FilledRectangle(int x, int y, int a, int b);
    FilledRectangle(p_t left_bot, p_t rigth_top);
    FilledRectangle(f_t frame);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };
}

#endif
