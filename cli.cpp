#include <cassert>
#include <cstring>
#include <iostream>

void hi()
{
  std::cout << "< HI! >\n";
}

void hello()
{
  std::cout << "< HELLO! >\n";
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

int main()
{
  constexpr size_t cmds_count = 2;
  void(*cmds[cmds_count])() = {hi, hello};
  const char * const cmds_text[] = {"hi", "hello"};

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
        cmds[i]();
      } else {
        std::cerr << "< UNKNOWN COMMAND >\n";
      }
    }
  }
}
