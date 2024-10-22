

#include "../includes/pa_header.h"

/** 
* ft_copy_env() : Crée une copie des variables d’environnement au démarrage du shell pour les manipuler.
*
* ft_get_env() : Récupère la valeur d’une variable d’environnement spécifique.
* Entrée : Le nom de la variable.
* Sortie : La valeur de la variable ou NULL si elle n'existe pas.
*/

char **ft_copy_env(t_env *env_list)
{
    int size = 0;
    t_env *temp = env_list;
    while (temp)
    {
        size++;
        temp = temp->next;
    }

    char **envp = (char **)malloc(sizeof(char *) * (size + 1));
    temp = env_list;
    int i = 0;
    while (temp)
    {
        envp[i] = ft_strjoin(ft_strjoin(temp->key, "="), temp->value);
        temp = temp->next;
        i++;
    }
    envp[i] = NULL;
    return envp;
}

char *ft_get_env(char *key, t_env *env_list)
{
    t_env *temp = env_list;
    while (temp)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (temp->value);
        temp = temp->next;
    }
    return (NULL);
}
