#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_FILES 5 // Number of files to open
#define FILENAME_SIZE 16

void construct_filename(char* buffer, int index) {
    const char* prefix = "file";
    int i = 0;
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

void open_files() {
    for (int i = 0; i < NUM_FILES; i++) {
        char filename[FILENAME_SIZE];
        construct_filename(filename, i);
        int fd = open(filename, O_CREATE | O_RDWR);
        if (fd < 0) {
            printf(1, "Failed to create %s\n", filename);
            exit();
        }
    }
    sleep(100); // Keep the files open to allow `ps` to observe them
}

int main() {
    open_files();
    exit();
}

