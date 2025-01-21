#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_FILES 5 // Number of files to open

// Function to construct file names like "file0.txt", "file1.txt", etc.
void construct_filename(char* buffer, int index) {
    int i = 0;
    const char* prefix = "file";
    while (*prefix) {
        buffer[i++] = *prefix++;
    }
    buffer[i++] = '0' + index; // Convert index to character
    buffer[i++] = '.';
    buffer[i++] = 't';
    buffer[i++] = 'x';
    buffer[i++] = 't';
    buffer[i] = '\0'; // Null-terminate the string
}

void create_files() {
    for (int i = 0; i < NUM_FILES; i++) {
        char filename[16];
        construct_filename(filename, i);
        int fd = open(filename, O_CREATE | O_RDWR);
        if (fd < 0) {
            printf(1, "Failed to create %s\n", filename);
            exit();
        }
        printf(1, "Opened file: %s (fd = %d)\n", filename, fd);
    }
}

void run_test() {
    int pid = fork();
    if (pid == 0) {
        // Child process: Open files and sleep
        printf(1, "Child process: Opening %d files...\n", NUM_FILES);
        create_files();

        printf(1, "Child process: Sleeping to allow ps_demo to observe...\n");
        sleep(200); // Allow `ps_demo` to run and observe NFD
        exit();
    } else {
        // Parent process: Wait for child to complete
        printf(1, "Parent process: Waiting for child...\n");
        wait();
        printf(1, "Parent process: Test completed.\n");
        exit();
    }
}

int main() {
    run_test();
    return 0;
}
