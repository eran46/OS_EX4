#include "types.h"
#include "stat.h"
#include "user.h"
#include "processInfo.h"

#define MAX_WIDTH 12 // Define a fixed width for columns

// Function to convert process state to string
char* get_state_name(int state) {
    switch (state) {
        case 0: return "EMBRYO";
        case 1: return "SLEEPING";
        case 2: return "RUNNABLE";
        case 3: return "RUNNING";
        case 4: return "ZOMBIE";
        default: return "UNKNOWN";
    }
}

// Function to convert integers to strings
void itoa(int n, char* str) {
    int i = 0, sign;
    if ((sign = n) < 0) {
        n = -n; // Handle negative numbers
    }
    do {
        str[i++] = n % 10 + '0'; // Get next digit
    } while ((n /= 10) > 0);
    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';

    // Reverse the string
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

// Function to print a fixed-width column
void print_fixed_width(int fd, const char* str, int width) {
    write(fd, str, strlen(str));
    for (int i = strlen(str); i < width; i++) {
        write(fd, " ", 1); // Add spaces to pad the column
    }
}

// Function to convert integer to string and print with fixed width
void print_int_fixed_width(int fd, int value, int width) {
    char buffer[16];
    itoa(value, buffer);
    print_fixed_width(fd, buffer, width);
}

int main() {
    int num_procs = getNumProc();
    int max_pid = getMaxPid();

    // Print header
    printf(1, "Total number of active processes: %d\n", num_procs);
    printf(1, "Maximum PID: %d\n", max_pid);
    printf(1, "PID         STATE       PPID        SZ          NFD         NRSWITCH\n");

    // Iterate over all possible PIDs
    for (int pid = 0; pid <= max_pid; pid++) {
        struct processInfo pinfo;
        if (getProcInfo(pid, &pinfo) == 0) { // If process exists
            print_int_fixed_width(1, pid, MAX_WIDTH);
            print_fixed_width(1, get_state_name(pinfo.state), MAX_WIDTH);
            print_int_fixed_width(1, pinfo.ppid, MAX_WIDTH);
            print_int_fixed_width(1, pinfo.sz, MAX_WIDTH);
            print_int_fixed_width(1, pinfo.nfd, MAX_WIDTH);
            print_int_fixed_width(1, pinfo.nrswitch, MAX_WIDTH);
            write(1, "\n", 1);
        }
    }

    exit();
}
