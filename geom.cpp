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
