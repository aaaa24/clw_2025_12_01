#include "filled_square.hpp"
#include "rectframe.hpp"

top::FilledSquare::FilledSquare(p_t p, int a):
  IDraw(),
  frame(make_valid_frame(p, a, a))
{}

top::FilledSquare::FilledSquare(int x, int y, int a):
  FilledSquare({x, y}, a)
{}

top::p_t top::FilledSquare::begin() const
{
  return frame.left_bot;
}

top::p_t top::FilledSquare::next(p_t p) const 
{
  return next_in_filled_rect(p, frame);
}
