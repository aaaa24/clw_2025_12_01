#ifndef HLINE_HPP
#define HLINE_HPP

#include "idraw.hpp"

namespace top {
  struct HLine: IDraw {
    HLine(p_t p, int l);
    HLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}

#endif
