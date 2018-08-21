#include "world.hpp"
#include <iostream>

int
main()
{
  World test;
  test.show();
  int j = 0;
  while (true) {
    j++;
    system("clear");
    test.show();
    std::cout << std::endl << j << std::endl;
    test.getNextMove();
    // getchar();
    system("sleep 0.1");
  }
  return 0;
}
