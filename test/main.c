#define CTEST_MAIN

#include <ctest.h>
#include <test4.h>

int
main (int argc, const char **argv)
{
  test_enter();
  return ctest_main (argc, argv);
}
