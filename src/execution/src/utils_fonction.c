

#include "../includes/pa_header.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;
    
    while (split[i])
    {
        free(split[i]);  // Libérer chaque sous-chaîne
        i++;
    }
    free(split);  // Libérer le tableau de pointeurs
}
