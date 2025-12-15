#ifndef CANVAS_HPP
#define CNAVAS_HPP

#include <iosfwd>
#include "geom.hpp"

namespace top {
  char * build_canvas(f_t fr, char fill);
  void paint_canvas(char * cnv, f_t fr, const p_t * ps, size_t k, char fill);
  void print_canvas(std::ostream & output, const char * cnv, f_t fr);
}

#endif
