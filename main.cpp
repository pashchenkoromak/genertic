#include "world.hpp"
#include <iostream>

int
main()
{
  World test(std::make_pair(20, 60));
  int j = 0;
  while (true) {
    j++;
    system("clear");
    test.show();
    std::cout << "Iteration: " << j << std::endl;
    // getchar();
    system("sleep 0.1");
    test.getNextMove();
  }
  return 0;
}
