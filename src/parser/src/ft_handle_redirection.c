

#include "../includes/pa_header.h"

/**
* ft_handle_redirection() : Gère l'ouverture des fichiers et la redirection des descripteurs de fichiers pour les redirections (>, >>, <).
*
*
*/

void ft_handle_redirection(t_files_list *files)
{
    t_file_node *current = files->head;
    int fd;

    while (current)
    {
        if (current->type == INFILE) // Redirection d'entrée
        {
            fd = open(current->filename, O_RDONLY);
            if (fd == -1)
            {
                perror("open infile");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (current->type == OUTFILE) // Redirection de sortie (écrasement)
        {
            fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open outfile");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (current->type == OUTFILE_APPEND) // Redirection de sortie (ajout)
        {
            fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open outfile append");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        current = current->next;
    }
}
