#include "daemon.h"

#include <stdlib.h>
#include <unistd.h>

void daemonize(void)
{
    int i;

    /* already a daemon */
    if(getppid() == 1) return;

    i = fork();

    /* fork error */
    if(i < 0) exit(1);

    /* parent exits */
    if(i > 0) exit(0);
}
