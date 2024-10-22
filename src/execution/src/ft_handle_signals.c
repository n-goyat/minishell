

#include "../includes/pa_header.h"

/**
* ft_handle_signals() : Intercepte les signaux comme SIGINT et SIGQUIT, et définit les actions à prendre lorsque ces signaux sont reçus.
*
* Utilise : signal() ou sigaction()
*
*/

void sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(STDOUT_FILENO, "\nminishell> ", 12);
    }
}

void ft_handle_signals(void)
{
    signal(SIGINT, sigint_handler);  // Intercepter SIGINT (Ctrl+C)
    signal(SIGQUIT, SIG_IGN);  // Ignorer SIGQUIT (Ctrl+\)
}
