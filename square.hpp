#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "idraw.hpp"

namespace top {
  struct Square: IDraw {
    Square(p_t p, int a);
    Square(int x, int y, int a);
    p_t begin() const override;
    p_t next(p_t p) const override;
    f_t frame;
  };
}

#endif
