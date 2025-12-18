#include "filled_rectangle.hpp"
#include "rectframe.hpp"

top::FilledRectangle::FilledRectangle(p_t p, int a, int b):
  IDraw(),
  frame(make_valid_frame(p, a, b))
{}

top::FilledRectangle::FilledRectangle(int x, int y, int a, int b):
  FilledRectangle({x, y}, a, b)
{}

top::FilledRectangle::FilledRectangle(p_t left_bot, p_t rigth_top):
  FilledRectangle(left_bot, rigth_top.x - left_bot.x, rigth_top.y - left_bot.y)
{}

top::FilledRectangle::FilledRectangle(f_t frame):
  FilledRectangle(frame.left_bot, frame.right_top)
{}

top::p_t top::FilledRectangle::begin() const
{
  return frame.left_bot;
}

top::p_t top::FilledRectangle::next(p_t p) const 
{
  return next_in_filled_rect(p, frame);
}
