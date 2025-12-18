#ifndef VLINE_HPP
#define VLINE_HPP

#include "idraw.hpp"


namespace top {
  struct VLine: IDraw {
    VLine(p_t p, int l);
    VLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}

#endif
