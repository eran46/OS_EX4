#include "types.h"
#include "stat.h"
#include "user.h"
#include "processInfo.h"

// integer to string
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

    // reverse
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void print(int fd, const char* str) {
    write(fd, str, strlen(str));
}

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

int main() {
    char str[64]; // buffer
    int numProcs = getNumProc();
    int maxPid = getMaxPid();

    print(1, "Total number of active processes: ");
    itoa(numProcs, str);
    print(1, str);
    print(1, "\nMaximum PID: ");
    itoa(maxPid, str);
    print(1, str);
    print(1, "\nPID\tSTATE\t\tPPID\tSZ\tNFD\tNRSWITCH\n");

      

    exit();
}
