#include "types.h"
#include "user.h"

void long_running_loop() {
    for (volatile int i = 0; i < 100000000; i++) {
        // Simulate a CPU-intensive task
    }
    exit();
}

void run_test() {
    int num_children = 9; // Number of child processes to create
    int pids[num_children];

    // Fork child processes to run different programs
    for (int i = 0; i < num_children; i++) {
        int pid = fork();
        if (pid == 0) {
            if (i % 3 == 0) {
                // Run a CPU-intensive loop in even-indexed children
                long_running_loop();
            } else if(i % 3 == 1) {
                // Run sleep in odd-indexed children
                sleep(200); // Simulate long IO
                exit();
            }
            else{
            	exec("memtest", (char*[]){"memtest", 0});
            	exec("nfd_test", (char*[]){"nfd_test", 0});
            }
        } else if (pid > 0) {
            pids[i] = pid; // Track child PIDs
        } else {
            printf(1, "Fork failed!\n");
        }
    }

    // Run `ps` in the parent process while children are active
    for (int j = 0; j < 5; j++) { // Run `ps` multiple times during execution
        printf(1, "\nRunning ps iteration %d:\n", j + 1);
        if (fork() == 0) {
            exec("ps", (char*[]){"ps", 0}); // Execute ps
            exit(); // Should never return
        }
        wait(); // Wait for the `ps` command to finish
        sleep(50); // Wait before next `ps` iteration
    }

    // Wait for all children to finish
    for (int i = 0; i < num_children; i++) {
        wait();
    }

    printf(1, "\nAll child processes completed.\n");
    exit();
}

int main() {
    run_test();
    return 0;
}

