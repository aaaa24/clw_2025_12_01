#ifndef DOT_HPP
#define DOT_HPP
#include "idraw.hpp"

namespace top {
  struct Dot: IDraw {
    Dot(int x, int y);
    explicit Dot(p_t p);
    p_t begin() const override;
    p_t next(p_t p) const override;
    p_t o;
  };
}

#endif
