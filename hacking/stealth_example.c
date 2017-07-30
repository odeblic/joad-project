#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    printf("original program name: %s\n", argv[0]);

    sleep(5);

    strncpy(argv[0], "hacked!", strlen(argv[0]));

    printf("corrupted program name: %s\n", argv[0]);

    sleep(5);

    int i;

    for (i = 1; i < argc; i++)
    {
        strncpy(argv[i], "@", strlen(argv[i]));
    }

    struct rlimit no_core = {0, 0};

    setrlimit(RLIMIT_CORE, &no_core);

    return 0;
}
