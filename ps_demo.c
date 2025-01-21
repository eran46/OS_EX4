#include "types.h"
#include "user.h"
#include "fcntl.h"

void long_running_loop() {
    for (volatile int i = 0; i < 100000000; i++) {
        // Simulate a CPU-intensive task
    }
    exit();
}

void frequent_context_switch() {
    for (int i = 0; i < 50; i++) {
        sleep(10); // Yield the CPU frequently
    }
    exit();
}

void run_test() {
    int num_children = 16; // Number of child processes to create

    // Fork child processes to run different programs
    for (int i = 0; i < num_children; i++) {
        int pid = fork();
        if (pid == 0) {
            if (i % 5 == 0) {
                // CPU-intensive task
                long_running_loop();
            } else if (i % 5 == 1) {
                // Sleep to simulate long IO
                sleep(400);
                exit();
            } else if (i % 5 == 2) {
                // Run nfd_test
                exec("nfd_test", (char*[]){"nfd_test", 0});
                printf(1, "Failed to execute nfd_test\n");
                exit();
            } else if (i % 5 == 3) {
                // Run memtest
                exec("memtest", (char*[]){"memtest", 0});
                printf(1, "Failed to execute memtest\n");
                exit();
            } else {
                // Frequent context switching
                frequent_context_switch();
            }
        } else if (pid < 0) {
            printf(1, "Fork failed!\n");
        }
    }

    // Run `ps` in the parent process while children are active
    for (int j = 0; j < 10; j++) {
        sleep(50); // Delay between `ps` executions
        printf(1, "\nRunning ps iteration %d:\n", j + 1);

        int pid = fork();
        if (pid == 0) {
            exec("ps", (char*[]){"ps", 0}); // Execute ps
            printf(1, "Failed to execute ps\n");
            exit();
        }
        wait(); // Wait for `ps` to complete
    }

    // Wait for all child processes to finish
    while (wait() > 0)
        ;

    printf(1, "\nAll child processes completed.\n");
    exit();
}

int main() {
    run_test();
    return 0;
}

