#include "rectangle.hpp"
#include "rectframe.hpp"

top::Rectangle::Rectangle(p_t p, int a, int b):
  IDraw(),
  frame(make_valid_frame(p, a, b))
{}

top::Rectangle::Rectangle(int x, int y, int a, int b):
  Rectangle({x, y}, a, b)
{}

top::Rectangle::Rectangle(p_t left_bot, p_t rigth_top):
  Rectangle(left_bot, rigth_top.x - left_bot.x, rigth_top.y - left_bot.y)
{}

top::Rectangle::Rectangle(f_t frame):
  Rectangle(frame.left_bot, frame.right_top)
{}

top::p_t top::Rectangle::begin() const
{
  return frame.left_bot;
}

top::p_t top::Rectangle::next(p_t p) const 
{
  return next_on_rect_perimeter(p, frame);
}
