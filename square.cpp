#include "square.hpp"
#include "rectframe.hpp"

top::Square::Square(p_t p, int a):
  IDraw(),
  frame(make_valid_frame(p, a, a))
{}

top::Square::Square(int x, int y, int a):
  Square({x, y}, a)
{}

top::p_t top::Square::begin() const
{
  return frame.left_bot;
}

top::p_t top::Square::next(p_t p) const 
{
  return next_on_rect_perimeter(p, frame);
}
