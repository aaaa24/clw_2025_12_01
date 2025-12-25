#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>

void skipline(std::istream & is)
{
  using lim_t = std::numeric_limits< std::streamsize >;
  is.ignore(lim_t::max(), '\n');
}

void next(std::istream & is, std::ostream & os, size_t & context)
{
  size_t i = 0;
  if (!(is >> i)) {
    throw std::runtime_error("next excepts ull in param");
  }
  skipline(std::cin);
  context = i;
  os << "< OK >\n";
}

void last(std::istream &, std::ostream & os, size_t & context)
{
  os << "< " << context << " >\n";
}

bool is_space(char c)
{
  return std::isspace(c);
}

std::istream & getword(std::istream & is, char * word, size_t k, size_t & size, bool(*c)(char))
{
  assert(k > 0 && "k must be greater than zero");
  if (!k || !word) {
    throw std::logic_error("bad buffer");
  }
  is >> std::noskipws;
  size_t i = 0;
  for (char next = 0; is && !c(next) && (i < k - 1); ++i) {
    is >> next;
    word[i] = next;
  }
  size = i;
  word[i] = '\0';
  is >> std::skipws;
  return is;
}

size_t match(const char * word, const char * const * words, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    bool matching = (std::strlen(word) == std::strlen(words[i]));
    matching = matching && !std::strcmp(word, words[i]);
    if (matching) {
      assert(i < k && "i must be less than k");
      return i;
    }
  }
  return k;
}

// Как вариант на будущее
struct Cmd {
  virtual const char * name() const = 0;
  virtual const char * help() const = 0;
  virtual const char * desc() const = 0;
  virtual void invoke() const = 0;
};

int main()
{
  constexpr size_t cmds_count = 2;
  using cmd_t = void(*)(std::istream &, std::ostream &, size_t &);
  cmd_t cmds[] = {next, last};
  const char * const cmds_text[] = {"next", "last"};

  size_t context = 0;

  constexpr size_t bcapacity = 255;
  char word[bcapacity + 1] = {};
  size_t size = 0;
  while (!(getword(std::cin, word, bcapacity, size, is_space)).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID COMMAND >\n";
      return 1;
      // Написать пропуск ввода
    } else {
      word[size - 1] = '\0';
      if (size_t i = match(word, cmds_text, cmds_count); i < cmds_count) {
        try {
          cmds[i](std::cin, std::cout, context);
        } catch (const std::exception & e) {
          std::cerr << "< INVALID COMMAND: " << e.what() << " >\n";
          if (std::cin.fail()) {
            std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
          }
          skipline(std::cin);
        }
      } else {
        std::cerr << "< UNKNOWN COMMAND >\n";
      }
    }
  }
}
