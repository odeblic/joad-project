#include "zombie_factory.h"

#include <unistd.h>

void make_zombie(int n)
{
    if(n <= 0)
    {
        sleep(5);
        return;
    }

    if(fork() > 0)
    {
        make_zombie(n - 1);
    }
}
