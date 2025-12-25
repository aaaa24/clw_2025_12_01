#include <iostream>

void hi()
{
  std::cout << "< HI! >\n";
}

int main()
{
  size_t i = 0;
  while (!(std::cin >> i).eof()) {
    if (std::cin.fail()) {
      std::cerr << "< INVALID COMMAND >\n";
      return 1;
      // Написать пропуск ввода
    } else if (i == 0) {
      hi();
    } else {
      std::cerr << "< UNKNOWN COMMAND >\n";
    }
  }
}