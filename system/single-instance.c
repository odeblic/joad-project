#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <unistd.h>

/*
If the lockfile already exists, then the process should read the PID from it instead.
It should then check the file /proc/pid/cmdline, and extract the name of the running process.
If it is the same as the name of the current process, then the lockfile should be deleted,
and it should try again. Otherwise, it should exit.
Forward the arguments to the running instance.
http://stackoverflow.com/questions/5339200/how-to-create-a-single-instance-application-in-c-or-c
*/

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
