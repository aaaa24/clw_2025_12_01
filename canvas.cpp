#include <iostream>
#include "canvas.hpp"

char * top::build_canvas(f_t fr, char fill)
{
  char * cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i) {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paint_canvas(char * cnv, f_t fr, const p_t * ps, size_t k, char figure)
{
  for (size_t i = 0; i < k; ++i) {
    int dx = ps[i].x - fr.left_bot.x;
    int dy = fr.right_top.y - ps[i].y;
    cnv[dy * cols(fr) + dx] = figure;
  }
}

void top::print_canvas(std::ostream & output, const char * cnv, f_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i) {
    for (size_t j = 0; j < cols(fr); ++j) {
      output << cnv[i * cols(fr) + j];
    }
    output << "\n";
  }
}
