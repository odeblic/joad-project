#include "daemon.h"

int main(void)
{
    daemonize();

    while(1);

    return 0;
}
