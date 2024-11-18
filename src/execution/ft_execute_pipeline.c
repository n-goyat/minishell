/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maba <maba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:57:02 by maba              #+#    #+#             */
/*   Updated: 2024/11/12 23:19:54 by maba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pa_header.h"

static void close_fds(int *in_fd, int *pipefd, int is_last_cmd) 
{
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (!is_last_cmd)
        close(pipefd[1]);
    *in_fd = pipefd[0];
}

static void fork_and_exec_pipeline(t_pipeline_params *params) 
{
    pid_t pid = fork();
    int status;

    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) 
    {
        if (params->in_fd != STDIN_FILENO) 
        {
            dup2(params->in_fd, STDIN_FILENO);
            close(params->in_fd);
        }
        if (!params->is_last_cmd) 
        {
            dup2(params->out_fd, STDOUT_FILENO);
            close(params->out_fd);
        }
        execute_single_command(params->current, params->env_list);
        exit(0);
    } 
    waitpid(pid, &status, 0);
}

void execute_pipeline(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;
    int pipefd[2];
    int in_fd = STDIN_FILENO;
    int is_last_cmd;
    int out_fd;

    while (current != NULL) 
    {
        is_last_cmd = (current->next == NULL);
        if (!is_last_cmd && pipe(pipefd) == -1) 
        {   
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        if (is_last_cmd)
            out_fd = STDOUT_FILENO;
        else 
            out_fd = pipefd[1];
        t_pipeline_params params = {current, env_list, in_fd, out_fd, is_last_cmd};
        fork_and_exec_pipeline(&params);
        close_fds(&in_fd, pipefd, is_last_cmd);
        current = current->next;
    }
}


static void execute_individual_command(t_cmd_node *current, t_env_list *env_list) 
{
    pid_t pid = fork();

    if (pid == -1) 
    {
        perror("fork");
        return;
    }
    if (pid == 0) 
    {
        execute_single_command(current, env_list);
        exit(0);
    } 
    else 
        ft_wait_for_processes(pid);
}


void handle_commands(t_commands_list *cmd_list, t_env_list *env_list) 
{
    t_cmd_node *current = cmd_list->head;

    if (current == NULL)
        return;

    if (cmd_list->size > 1)
        execute_pipeline(cmd_list, env_list);
    else 
    {
        while (current != NULL) 
        {
            if (is_builtin(current->cmd))
                ft_execute_builtin(current, env_list);
            else
                execute_individual_command(current, env_list);
            current = current->next;
        }
    }
}
