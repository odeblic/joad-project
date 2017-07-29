#include "single_instance.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <unistd.h>

int get_instance_pid(const char * filepath)
{
    pid_t pid = -1;

    int file = open("./lock.pid", O_CREAT | O_RDWR, 0666);

    if (file < 0)
    {
        perror("cannot open the file");
    }
    else
    {
        char buffer[16];

        if(!flock(file, LOCK_EX | LOCK_NB))
        {
            // this is the first instance
            sprintf(buffer, "%d", getpid());
            write(file, &buffer, strlen(buffer));
            pid = 0;
        }
        else if(errno == EWOULDBLOCK)
        {
            // there is another instance
            read(file, &buffer, sizeof(buffer));
            sscanf(buffer, "%d", &pid);
        }
        else
        {
            perror("cannot lock the file");
        }

        close(file);
    }

    return pid;
}

const get_instance_cmd_line(pid_t pid)
{
    //sprintf(buffer, "/proc/%d/cmdline", pid);
}
