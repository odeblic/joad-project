#include "single_instance.h"

#include <stdio.h>

int main(int argc, char ** argv)
{
    pid_t instance = get_instance_pid("./lock.pid");

    if (instance)
    {
        printf("another instance is running (pid=%d)\n", instance);
    }
    else
    {
        printf("this is the first instance (pid=%d)\n", getpid());
    }

    return 0;
}
