#include <include/lib.hpp>
#include <iostream>
#include <cstdlib>

int main()
{
  std::cout << "Trying library" << std::endl;
  greeter g;
  g.greet();
  std::cout << "Done!" << std::endl;
  return EXIT_SUCCESS;
}
