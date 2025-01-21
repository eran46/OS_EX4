#include "types.h"
#include "user.h"

// Perform exactly 3 context switches in the child process
void child_context_switch_test() {
    printf(1, "Child process started. Performing 3 context switches.\n");

    for (int i = 0; i < 3; i++) {
        sleep(10); // Yield the CPU
        printf(1, "Child: Context switch %d completed.\n", i + 1);
    }

    printf(1, "Child process completed all context switches.\n");
    exit();
}

void run_test() {
    int pid = fork();

    if (pid == 0) {
        // Child process: Perform context switches
        child_context_switch_test();
    } else if (pid > 0) {
        // Parent process: Monitor the child with `ps`
        printf(1, "Parent process monitoring child process (PID: %d).\n", pid);

        // Initial `ps` call to get the starting `NRSWITCH`
        sleep(5);
        printf(1, "\nInitial `ps` output:\n");
        int ps_pid = fork();
        if (ps_pid == 0) {
            exec("ps", (char*[]){"ps", 0});
            printf(1, "Failed to execute ps\n");
            exit();
        }
        wait(); // Wait for `ps` to complete

        // Monitor after each context switch
        for (int i = 0; i < 3; i++) {
            sleep(20); // Ensure the child process performs one context switch
            printf(1, "\n`ps` output after context switch %d:\n", i + 1);
            ps_pid = fork();
            if (ps_pid == 0) {
                exec("ps", (char*[]){"ps", 0});
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

