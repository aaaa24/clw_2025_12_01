#ifndef DLINE_HPP
#define DLINE_HPP

#include "idraw.hpp"

namespace top {
  struct DLine: IDraw {
    DLine(p_t p, int l);
    DLine(int x, int y, int l);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t start;
    int length;
  };
}

#endif
