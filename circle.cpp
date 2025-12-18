#include <stdexcept>
#include <cmath>
#include "circle.hpp"

top::Circle::Circle(p_t p, int r):
  IDraw(),
  o{p.x, p.y},
  radius(r)
{
  if (radius == 0) {
    throw std::invalid_argument("radius can not be 0");
  }
  if (radius < 0) {
    radius *= -1;
  }
}

top::Circle::Circle(int x, int y, int r):
  Circle({x, y}, r)
{}

top::p_t top::Circle::begin() const
{
  return p_t{o.x + radius, o.y};
}

// Does not work
top::p_t top::Circle::next(p_t p) const
{
  if (radius == 1) {
    return begin();
  }
  const double PI = acos(-1.0);
  int dx = p.x - o.x;
  int dy = p.y - o.y;
  int angle = atan2(dy, dx) * 180.0 / PI;
  if (angle < 0) {
    angle += 360;
  }
  for (int i = 0; i < 360; ++i) {
    int new_angle = (angle + i) % 360;
    int new_x = o.x + radius * cos(new_angle);
    int new_y = o.y + radius * sin(new_angle);
    p_t new_p{new_x, new_y};
    if (new_p != p) {
      return new_p;
    }
  }
  return p;
}
