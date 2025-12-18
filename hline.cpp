#include <stdexcept>
#include "hline.hpp"

top::HLine::HLine(p_t p, int l):
  IDraw(),
  start{p.x, p.y},
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("lenght cannot be zero");
  }
  if (length < 0) {
    length *= -1;
    start.x -= length - 1;
  }
}

top::HLine::HLine(int x, int y, int l):
  HLine({x, y}, l)
{}

top::p_t top::HLine::begin() const
{
  return start;
}

top::p_t top::HLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) {
    return begin();
  }
  return p_t{p.x + 1, start.y};
}
