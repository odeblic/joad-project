#pragma once

#include <sys/types.h>

/*
If the lockfile already exists, then the process should read the PID from it instead.
It should then check the file /proc/pid/cmdline, and extract the name of the running process.
If it is the same as the name of the current process, then the lockfile should be deleted,
and it should try again. Otherwise, it should exit.
Forward the arguments to the running instance.
http://stackoverflow.com/questions/5339200/how-to-create-a-single-instance-application-in-c-or-c
*/

int get_instance_pid(const char * filepath);

const get_instance_cmd_line(pid_t pid);
