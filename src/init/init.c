// src/init/init.c
// The first breath of a world that shouldn't be.

#include <stdio.h>      // For printf
#include <sys/mount.h>  // For the mount syscall
#include <sys/reboot.h> // <--- THE FIX IS HERE
#include <unistd.h>     // For syscalls like sync, sleep

// A simple function to handle the final, desperate moments.
void system_panic() {
  printf("The anchor is lost. The world is collapsing...\n");
  // sync(); // Attempt to write any buffered data to disk
  //  reboot(RB_AUTOBOOT); // In this reality, collapse means to start over.
  while (1) {
  }
}

// Changed the signature to void since we don't use arguments.
int main(void) {
  // The very first message from userspace.
  printf("Awakening process 1. It is alone.\n");

  // Mount the essential pseudo-filesystems.
  printf("  [MOUNT] Attaching the /proc filesystem (the system's mind)...\n");
  if (mount("proc", "/proc", "proc", 0, NULL) != 0) {
    printf("Failed to materialize the system's consciousness.\n");
    system_panic();
  }

  printf("  [MOUNT] Attaching the /sys filesystem (the system's nerves)...\n");
  if (mount("sysfs", "/sys", "sysfs", 0, NULL) != 0) {
    printf("Failed to connect the system's nerves.\n");
    system_panic();
  }

  printf("  [MOUNT] Attaching the /dev filesystem (the system's senses)...\n");
  if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) != 0) {
    printf("The system is blind and deaf.\n");
    system_panic();
  }

  printf("The basic structures of reality are now in place.\n");
  printf("The system will now idle in the void, waiting for a purpose...\n");

  // Our init simply exists, preventing a kernel panic from init exiting.
  while (1) {
  }

  // This part is unreachable.
  return 0;
}
