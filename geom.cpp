#include <stdexcept>
#include "geom.hpp"

bool top::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool top::operator!=(p_t a, p_t b)
{
  return !(a == b);
}

size_t top::rows(f_t fr)
{
  return (fr.right_top.y - fr.left_bot.y + 1);
}

size_t top::cols(f_t fr)
{
  return (fr.right_top.x - fr.left_bot.x + 1);
}

top::f_t top::build_frame(const p_t * ps, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  int minx = ps[0].x, maxx = minx;
  int miny = ps[0].y, maxy = miny;
  for (size_t i = 1; i < s; ++i) {
    minx = std::min(minx, ps[i].x);
    maxx = std::max(maxx, ps[i].x);
    miny = std::min(miny, ps[i].y);
    maxy = std::max(maxy, ps[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}
