#ifndef RECTFRAME_HPP
#define RECTFRAME_HPP

#include "idraw.hpp"

namespace top {
  f_t make_valid_frame(p_t p, int a, int b);
  p_t next_on_rect_perimeter(p_t current, f_t frame);
  p_t next_in_filled_rect(p_t current, f_t frame);
}

#endif
