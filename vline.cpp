#include <stdexcept>
#include "vline.hpp"

top::VLine::VLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght can not be 0");
  }
  if (length < 0) {
    length *= -1;
    start.y -= length - 1;
  }
}

top::VLine::VLine(int x, int y, int l):
  VLine({x, y}, l)
{}

top::p_t top::VLine::begin() const
{
  return start;
}

top::p_t top::VLine::next(p_t p) const
{
  if (p.y == start.y + length - 1) {
    return begin();
  }
  return p_t{start.x, p.y + 1};
}
