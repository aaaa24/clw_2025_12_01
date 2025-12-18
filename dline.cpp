#include <stdexcept>
#include "dline.hpp"

top::DLine::DLine(p_t p, int l):
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

top::DLine::DLine(int x, int y, int l):
  DLine({x, y}, l)
{}

top::p_t top::DLine::begin() const
{
  return start;
}

top::p_t top::DLine::next(p_t p) const
{
  if (p.x == start.x + length - 1) {
    return begin();
  }
  return p_t{p.x + 1, p.y + 1};
}
