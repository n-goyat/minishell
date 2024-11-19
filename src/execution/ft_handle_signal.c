/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:51:07 by maba              #+#    #+#             */
/*   Updated: 2024/11/19 15:48:12 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        // Imprimer une nouvelle ligne, réinitialiser la ligne et redistribuer le prompt
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void handle_sigquit(int sig)
{
    // Ignorer SIGQUIT (Ctrl-\)
    (void)sig;
}

void setup_signal_handlers(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // Configurer SIGINT
    sa_int.sa_handler = handle_sigint;
    sa_int.sa_flags = SA_RESTART; // Redémarrer les appels système interrompus
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Configurer SIGQUIT
    sa_quit.sa_handler = handle_sigquit;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void disable_readline_signals(void)
{
    rl_catch_signals = 0; // Empêche readline de gérer les signaux
}
