#include "types.h"
#include "user.h"
#include "processInfo.h"

void assert(int condition, const char *message) {
    if (!condition) {
        printf(1, "Test failed: %s\n", message);
        exit();
    }
}

void test_nrswitch() {
    struct processInfo info;
    int pid = getpid(); // Get the current process PID
    int result = getProcInfo(pid, &info);

    if (result < 0) {
        printf(1, "Failed to retrieve process info for PID %d\n", pid);
        return;
    }

    int initial_nrswitch = info.nrswitch;
    printf(1, "Initial context switches for PID %d: %d\n", pid, initial_nrswitch);

    // Fork a child process to trigger context switches
    int child_pid = fork();
    if (child_pid == 0) {
        // Child process: Perform some controlled sleeps
        for (int i = 0; i < 50; i++) {
            sleep(1); // Sleep for 1 tick to allow the parent process to run
        }
        exit(); // Exit after completing the work
    } else if (child_pid > 0) {
        // Parent process: Wait for the child process to finish
        for (int i = 0; i < 50; i++) {
            sleep(1); // Sleep for 1 tick to allow the child process to run
        }
        wait(); // Wait for the child process to finish
    } else {
        printf(1, "Fork failed\n");
        return;
    }

    // Retrieve process info again
    result = getProcInfo(pid, &info);
    if (result < 0) {
        printf(1, "Failed to retrieve process info after operations for PID %d\n", pid);
    } else {
        printf(1, "Context switches after fork and sleep for PID %d: %d\n", pid, info.nrswitch);
        int switch_increase = info.nrswitch - initial_nrswitch;
        printf(1, "Context switches increased by: %d\n", switch_increase);

        // Assert that the switch count increased by at least 5
        if (switch_increase >= 50) {
            printf(1, "Test passed: nrswitch increased correctly by at least 50.\n");
        } else {
            printf(1, "Test failed: Expected increase of at least 50, but got %d.\n", switch_increase);
        }
    }
}

// Main function
int main() {
    printf(1, "Starting nrswitch test...\n");
    test_nrswitch();
    exit();
}

