#include "types.h"
#include "user.h"

#ifndef PROCESSINFO
#define PROCESSINFO
#include "processInfo.h" // CHANGE
#endif

// Function to convert an integer to a string (base 10)
void itoa(int num, char *buf) {
    char temp[20];
    int i = 0, j = 0, is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    do {
        temp[i++] = '0' + (num % 10);
        num /= 10;
    } while (num > 0);

    if (is_negative) {
        temp[i++] = '-';
    }

    // Reverse the string
    while (i > 0) {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';
}

// Function to print a string
void print(const char *str) {
    write(1, str, strlen(str));
}

int main(void) {
    ProcessInfo pi;
    int pid = getpid(); // Example PID or a valid one to test
    char buf[20];

    if (getProcInfo(pid, &pi) == 0) {
        print("PID: ");
        itoa(pid, buf);
        print(buf);
        print(" PPID: ");
        itoa(pi.ppid, buf);
        print(buf);
        print(" sz: ");
        itoa(pi.sz, buf);
        print(buf);
        print(" state: ");
        itoa(pi.state, buf);
        print(buf);
        print(" nfd: ");
        itoa(pi.nfd, buf);
        print(buf);
        print(" nrswitch: ");
        itoa(pi.nrswitch, buf);
        print(buf);
        print("\n");
    } else {
        print("Error: Failed to retrieve process info\n");
    }

    exit();
}

