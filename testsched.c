#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h" // for O_CREATE

static int lockFile = -1;

void runLow() {
  int pid = getpid();
  for(int i = 0; i < (1 << 30); ++i) {

  }
  printf(2, "In Low PID: %d priority: %d\n", pid, 0);
  funlock(lockFile);
  int count = 4;
  while(count > 0) {
    for(int i = 0; i < (1 << 30); ++i) {

    }
    printf(2, "In Low PID: %d priority: %d\n", pid, 0);
    count -= 1;
  }
}

void runMedium() {
  int pid = getpid();
  nice(pid, 2);
  int count = 10;
  while(count > 0) {
    for(int i = 0; i < (1 << 30); ++i) {

    }
    printf(2, "In Med PID: %d priority: %d\n", pid, 2);
    count -= 1;
  }
}

int
main(int argc, char *argv[])
{
  lockFile = open("lock", O_CREATE | O_RDWR);
  flock(lockFile); // Acquire lock

  int highPID = fork();
  if(0 == highPID) {
    // In child that will have high priority
    int pid = getpid();
    nice(pid, 4);
    for(int i = 0; i < (1 << 30); ++i) {

    }
    printf(2, "Started High PID: %d priority: %d\n", pid, 4);
    flock(lockFile); // sleep here until parent releases lock
    printf(2, "In High PID: %d priority: %d\n", pid, 4);
    funlock(lockFile);
    wait();
    exit();

  } else {
    // In parent that will have low priority
    int pid = getpid();
    nice(getpid(), 0);
    printf(2, "Started Low PID: %d priority: %d\n", pid, 0);
    for(int i = 0; i < (1 << 30); ++i) {

    }

    if(1 < argc) {
      // Create medium priority process that prevents low priority
      // process from running
      int mediumPID = fork();
      if(0 == mediumPID) {
        runMedium();
      } else {
        runLow();
        wait();
      }
    } else {
      // There is no Medium priority process
      runLow();
    }
  }

  wait();
  exit();
}
