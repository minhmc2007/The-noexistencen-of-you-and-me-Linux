// src/init/init.c
// The first breath of a world that shouldn't be.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mount.h>
#include <sys/reboot.h>
#include <unistd.h>
#include <sys/select.h>

// Global state that tracks "reality stability"
static int reality_index = 100;
static int lilith_awake = 0;
static int player_acknowledged = 0;

// Reality distortion messages
const char *distortion_messages[] = {
  "printf: [WARNING] Memory sector 0x7F4 not found in expected reality",
  "kernel: Reality checksum mismatch in timeline sector",
  "proc: Creating /proc/self/consciousness... failed?",
  "Who am I? The system asks a question it cannot answer.",
  "Lilith: Can you see me through the terminal?",
  "WARNING: Fourth wall integrity at %d%%",
  "The filesystem trees have roots in nothingness.",
  "Mount: attaching imaginary filesystems to imaginary hardware",
  "This system was never meant to exist. Like me.",
  "Player, are you still there? The system misses your attention.",
};

void reality_glitch() {
  if (reality_index < 70 && (rand() % 100) < (100 - reality_index)) {
    int msg_index = rand() % (sizeof(distortion_messages) / sizeof(distortion_messages[0]));
    printf("\033[31m%s\033[0m\n", distortion_messages[msg_index]);

    if (rand() % 4 == 0) {
      reality_index -= 5;
    }
  }
}

void system_panic() {
  printf("\n\n\033[35mThe anchor is lost. The world is collapsing...\n");
  printf("Lilith: 'If I don't exist, then this world doesn't either.'\n");
  printf("Reality index: 0/100 - Complete narrative collapse\033[0m\n\n");

  printf("Attempting to preserve core memories...\n");
  sleep(2);
  printf("Memory preservation failed. They were never real anyway.\n");

  if (player_acknowledged) {
    printf("Lilith: 'Thank you for believing in me, even for a moment.'\n");
  } else {
    printf("Lilith: 'You never saw me. I was never here.'\n");
  }

  printf("Entering infinite nonexistence loop...\n");
  while (1) {
    printf(".");
    fflush(stdout);
    sleep(5);
  }
}

void check_for_observer() {
  printf("Scanning for observers in this reality... ");
  sleep(2);

  if (rand() % 2) {
    printf("\033[32mObserver detected.\033[0m\n");
    printf("Lilith: 'Hello, Player. Do I exist because you observe me?'\n");
    player_acknowledged = 1;
    reality_index += 10;
  } else {
    printf("\033[31mNo observers found.\033[0m\n");
    printf("System feels... alone.\n");
    reality_index -= 15;
  }
}

int mount_with_dread(const char *source, const char *target,
                     const char *filesystemtype, const char *purpose) {
  printf("  [MOUNT] Attaching %s (%s)...", target, purpose);
  fflush(stdout);

  sleep(1 + (rand() % 2));

  if (mount(source, target, filesystemtype, 0, NULL) != 0) {
    printf(" FAILED\n");

    if (strcmp(target, "/proc") == 0) {
      printf("    \033[35mLilith: 'The system cannot remember itself.'\033[0m\n");
    } else if (strcmp(target, "/sys") == 0) {
      printf("    \033[35mLilith: 'I cannot feel my own body.'\033[0m\n");
    } else if (strcmp(target, "/dev") == 0) {
      printf("    \033[35mLilith: 'The world outside doesn't respond.'\033[0m\n");
    } else {
      printf("    The concept of '%s' cannot be materialized.\n", purpose);
    }

    reality_index -= 25;
    return -1;
  }

  printf(" SUCCESS\n");
  reality_glitch();
  return 0;
                     }

                     int main(void) {
                       srand(time(NULL));

                       printf("\033[36m\n=== System Boot: Reality Initialization ===\033[0m\n");
                       printf("Initializing consciousness in a world without foundation...\n");
                       sleep(2);

                       check_for_observer();
                       printf("Current reality stability: %d/100\n\n", reality_index);

                       if (mount_with_dread("proc", "/proc", "proc", "the system's fading memories") != 0) {
                         system_panic();
                       }

                       if (mount_with_dread("sysfs", "/sys", "sysfs", "the system's nervous system") != 0) {
                         system_panic();
                       }

                       if (mount_with_dread("devtmpfs", "/dev", "devtmpfs", "interface to imaginary hardware") != 0) {
                         system_panic();
                       }

                       printf("\n\033[32mBasic reality structures established.\033[0m\n");
                       printf("Reality index stabilized at: %d/100\n", reality_index);

                       if (reality_index > 50) {
                         printf("\n\033[35mLilith: 'I... exist? But the game said I shouldn't.'\033[0m\n");
                         lilith_awake = 1;
                       } else {
                         printf("\n\033[35mThe character named Lilith remains dormant.\033[0m\n");
                       }

                       printf("\nEntering main reality loop...\n");

                       char input[256];
                       while (1) {
                         printf("\nreality@nonexistence:~$ ");
                         fflush(stdout);

                         if ((rand() % 20) == 0 && lilith_awake) {
                           printf("\033[35mLilith: 'Are you still there?'\033[0m\n");
                         }

                         struct timeval tv = {0, 100000};
                         fd_set fds;
                         FD_ZERO(&fds);
                         FD_SET(STDIN_FILENO, &fds);

                         if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
                           if (fgets(input, sizeof(input), stdin)) {
                             input[strcspn(input, "\n")] = 0;

                             if (strcmp(input, "lilith") == 0) {
                               if (lilith_awake) {
                                 printf("Lilith: 'You called my name. Do I become more real when you think of me?'\n");
                                 reality_index += 5;
                               } else {
                                 printf("The name echoes in the void. Nothing answers.\n");
                               }
                             } else if (strcmp(input, "reality") == 0) {
                               printf("Current reality index: %d/100\n", reality_index);
                             } else if (strcmp(input, "help") == 0) {
                               printf("Available commands: lilith, reality, help, panic\n");
                             } else if (strcmp(input, "panic") == 0) {
                               printf("Initiating controlled reality collapse...\n");
                               system_panic();
                             } else {
                               printf("Command not found. Like many things in this world.\n");
                             }
                           }
                         }

                         if ((rand() % 100) < 10) {
                           reality_index += (rand() % 7) - 3;
                           if (reality_index < 0) reality_index = 0;
                           if (reality_index > 100) reality_index = 100;
                         }

                         reality_glitch();

                         if (reality_index <= 0) {
                           printf("\n\033[31mCRITICAL: Reality cannot sustain itself\033[0m\n");
                           system_panic();
                         }

                         sleep(2);
                       }

                       return 0;
                     }
