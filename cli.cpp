#include <cassert>
#include <iostream>

void hi()
{
  std::cout << "< HI! >\n";
}

bool is_space(char c)
{
  return std::isspace(c);
}

std::istream & getword(std::istream & is, char * word, size_t k, bool(*c)(char))
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
  is >> std::skipws;
  return is;
}

size_t match(const char * word, const char * const * words, size_t k);

int main()
{
  constexpr size_t cmds_count = 1;
  void(*cmds[cmds_count])() = {hi};
  const char * const cmds_text[] = {"hi"};

  constexpr size_t bsize = 255;
  char word[255 + 1] = {};
  while (!(getword(std::cin, word, bsize, is_space)).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID COMMAND >\n";
      return 1;
      // Написать пропуск ввода
    } else if (size_t i = match(word, cmds_text, cmds_count) < cmds_count) {
      cmds[i]();
    } else {
      std::cerr << "< UNKNOWN COMMAND >\n";
    }
  }
}
