

#include "../includes/pa_header.h"

/*
* ft_wait_for_processes() : Attend la fin de tous les processus enfants lancés, avec wait() ou waitpid().
*
* 
*
*/

void ft_wait_for_processes(pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        int exit_status = WEXITSTATUS(status);
        if (exit_status != 0)
        {
            fprintf(stderr, "Process exited with status %d\n", exit_status);
        }
    }
    else if (WIFSIGNALED(status))
    {
        int signal = WTERMSIG(status);
        fprintf(stderr, "Process terminated by signal %d\n", signal);
    }
}

