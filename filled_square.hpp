#ifndef FILLED_SQUARE_HPP
#define FILLED_SQUARE_HPP

#include "idraw.hpp"

namespace top {
  struct FilledSquare: IDraw {
    FilledSquare(p_t p, int a);
    FilledSquare(int x, int y, int a);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };
}

#endif
