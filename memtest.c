#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Allocating memory...\n");
    char* mem = sbrk(4096); // Allocate 4 KB
    if (mem == (char*)-1) {
        printf(1, "Memory allocation failed!\n");
    } else {
        printf(1, "Memory allocated at %p\n", mem);
    }

    printf(1, "Sleeping to observe ps output...\n");
    sleep(100); // Allow time to run ps
    exit();
}
