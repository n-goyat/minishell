

#include "../includes/pa_header.h"

/*
* ft_execute_command() : Fonction centrale qui exécute les commandes externes en utilisant fork() et execve().
*
* Entrée : Un tableau de tokens correspondant à une commande.
* Sortie : Le résultat de l'exécution.
*
*/


/*
* Fonction pour rechercher le chemin absolu d'une commande dans les répertoires spécifiés par PATH.
*/
char *find_command_in_path(char *command, t_env *env_list)
{
    char *path_env = get_env_value("PATH", env_list);  // Récupérer la valeur de la variable d'environnement PATH
    char **paths = ft_split(path_env, ':');  // Diviser PATH en différents répertoires
    char *full_path;
    int i = 0;

    // Boucle pour essayer chaque chemin dans PATH
    while (paths && paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, command);  // Concaténer le chemin avec la commande
        if (access(full_path, X_OK) == 0)  // Vérifier si le fichier est exécutable
        {
            free_split(paths);  // Libérer la mémoire du tableau de chemins
            return (full_path);  // Retourner le chemin complet de la commande
        }
        free(full_path);
        i++;
    }
    free_split(paths);  // Libérer la mémoire du tableau de chemins si la commande n'est pas trouvée
    return (NULL);  // Retourner NULL si la commande n'est pas trouvée
}

/*
* ft_execute_command() : Fonction centrale qui exécute les commandes externes en utilisant fork() et execve().
*
* Entrée : Un t_cmd_node contenant la commande et ses arguments.
* Sortie : Le résultat de l'exécution.
*/
// void ft_execute_command(t_cmd_node *cmd, t_env *env_list)
// {
//     pid_t pid;
//     char *cmd_path;
//     char **envp = ft_copy_env(env_list);  // Copier les variables d’environnement

//     // Chercher le chemin de la commande dans PATH si ce n'est pas un chemin absolu
//     if (ft_strchr(cmd->cmd[0], '/') == NULL)
//         cmd_path = find_command_in_path(cmd->cmd[0], env_list);  // Recherche dans PATH
//     else
//         cmd_path = ft_strdup(cmd->cmd[0]);  // Utiliser directement le chemin donné

//     if (!cmd_path)  // Si la commande n'a pas été trouvée
//     {
//         fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
//         free(envp);
//         return;
//     }

//     pid = fork();
//     if (pid == 0)  // Processus enfant
//     {
//         // Gérer les redirections s'il y en a
//         if (cmd->files)
//             ft_handle_redirection(cmd->files);

//         // Exécuter la commande externe avec execve
//         if (execve(cmd_path, cmd->cmd, envp) == -1)
//         {
//             perror("execve");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else if (pid < 0)  // Si fork échoue
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     else  // Processus parent
//     {
//         // Attendre la fin du processus enfant
//         ft_wait_for_processes(pid);
//     }

//     free(cmd_path);  // Libérer la mémoire du chemin de commande
//     free(envp);  // Libérer la mémoire des variables d'environnement
// }

void ft_execute_command(t_cmd_node *cmd, t_env *env_list)
{
    pid_t pid;
    char *cmd_path;
    char **envp = ft_copy_env(env_list);  // Copier les variables d’environnement

    // Chercher le chemin de la commande dans PATH si ce n'est pas un chemin absolu
    if (ft_strchr(cmd->cmd[0], '/') == NULL)
        cmd_path = find_command_in_path(cmd->cmd[0], env_list);  // Recherche dans PATH
    else
        cmd_path = ft_strdup(cmd->cmd[0]);  // Utiliser directement le chemin donné

    if (!cmd_path)  // Si la commande n'a pas été trouvée
    {
        fprintf(stderr, "Command not found: %s\n", cmd->cmd[0]);
        free(envp);
        return;
    }

    pid = fork();
    if (pid == 0)  // Processus enfant
    {
        // Afficher les fichiers et leurs types avant la redirection
        if (cmd->files)
        {
            printf("Files to redirect:\n");
            t_file_node *current_file = cmd->files->head;
            while (current_file) {
                printf("File: %s, Type: %d\n", current_file->filename, current_file->type);
                current_file = current_file->next;
            }
        }

        // Gérer les redirections s'il y en a
        if (cmd->files)
            ft_handle_redirection(cmd->files);

        // Exécuter la commande externe avec execve
        if (execve(cmd_path, cmd->cmd, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)  // Si fork échoue
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else  // Processus parent
    {
        // Attendre la fin du processus enfant
        ft_wait_for_processes(pid);
    }

    free(cmd_path);  // Libérer la mémoire du chemin de commande
    free(envp);  // Libérer la mémoire des variables d'environnement
}
