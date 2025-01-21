#include "types.h"
#include "user.h"

void child_context_switch_test() {
    for (int i = 0; i < 20; i++) {
        sleep(10); // Yield the CPU for predictable context switching
    }
    exit(); // End the child process
}

void run_test() {
    int pid = fork();

    if (pid == 0) {
        // Child process: Perform context switches
        child_context_switch_test();
    } else if (pid > 0) {
        // Parent process: Monitor the child with `ps`
        for (int i = 0; i < 10; i++) {
            sleep(15); // Delay to allow the child process to run and context switch
            printf(1, "\nRunning ps iteration %d:\n", i + 1);
            int ps_pid = fork();
            if (ps_pid == 0) {
                exec("ps", (char*[]){"ps", 0}); // Execute ps
                printf(1, "Failed to execute ps\n");
                exit();
            }
            wait(); // Wait for `ps` to complete
        }

        // Wait for the child process to finish
        wait();
        printf(1, "\nChild process has completed.\n");
        exit();
    } else {
        printf(1, "Fork failed!\n");
        exit();
    }
}

int main() {
    run_test();
    return 0;
}

