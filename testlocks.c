#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int fd = open("testlock", 0);
  flock(fd);
  funlock(fd);
  close(fd);
  exit();
}
