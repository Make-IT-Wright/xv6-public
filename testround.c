#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(2, "If round robin scheduing works, parent and child\n");
  printf(2, "should alternate printing.\n");
  printf(2, "add command line argumnet to test priority: only\n");
  printf(2, "parent runs until done.\n");
  int childPID = fork();
  if(0 == childPID) {
    // In child
    for(int i = 0; i < 6; ++i) {
      for(int j = 0; j < (1 << 30); ++j) {

      }
      printf(2, "In child.\n");
    }
    exit();
  } else {
    // In parent
    // set own priority high so we don't get preempted bu child
    nice(getpid(), 4);

    if(1 == argc) {
      // Then set child priority high
      nice(childPID, 4);
    }

    for(int j = 0; j < (1 << 24); ++j) {

    }

    // Both child and parent should print
    for(int i = 0; i < 6; ++i) {
      for(int j = 0; j < (1 << 30); ++j) {

      }
      printf(2, "In parent.\n");
    }
    wait();
    exit();
  }
}
