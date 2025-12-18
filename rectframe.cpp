#include <stdexcept>
#include "rectframe.hpp"

top::f_t top::make_valid_frame(p_t p, int a, int b) {
  if (a == 0 || b == 0)
    throw std::invalid_argument("side cannot be zero");
  p_t lb = p;
  int w = a, h = b;
  if (w < 0) {
    w = -w; lb.x -= w - 1;
  }
  if (h < 0) {
    h = -h; lb.y -= h - 1;
  }
  return {lb, {lb.x + w - 1, lb.y + h - 1}};
}

top::p_t top::next_on_rect_perimeter(p_t current, f_t frame) {
  p_t lb = frame.left_bot;
  p_t rt = frame.right_top;
  int w = rt.x - lb.x + 1;
  int h = rt.y - lb.y + 1;

  if (current.x == lb.x && current != lb) {
    return {current.x, current.y - 1};
  }
  if (current.y == rt.y) {
    return {current.x - 1, current.y};
  }
  if (current.x == rt.x) {
    return {current.x, current.y + 1};
  }
  return {current.x + 1, lb.y};
}

top::p_t top::next_in_filled_rect(p_t current, f_t frame) {
  p_t lb = frame.left_bot;
  p_t rt = frame.right_top;
  if (current.x == rt.x && current.y == rt.y) {
    return lb;
  }
  if (current.x == rt.x) {
    return {lb.x, current.y + 1};
  }
  return {current.x + 1, current.y};
}
