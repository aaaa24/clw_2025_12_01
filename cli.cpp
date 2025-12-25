#include <iostream>

void hi()
{
  std::cout << "< HI! >\n";
}

int main()
{
  constexpr size_t cmds_count = 1;
  void(*cmds[cmds_count])() = {hi};

  size_t i = 0;
  while (!(std::cin >> i).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID COMMAND >\n";
      return 1;
      // Написать пропуск ввода
    } else if (i < cmds_count) {
      cmds[i]();
    } else {
      std::cerr << "< UNKNOWN COMMAND >\n";
    }
  }
}
