#include "world.hpp"
#include <iostream>

int
main()
{
  World test;
  test.show();
  while (true) {
    for (int j = 0; j < 1000; j++) {
      system("clear");
      test.show();
      std::cout << j << std::endl;
      test.getNextMove();
      getchar();
    }
  }
  return 0;
}
