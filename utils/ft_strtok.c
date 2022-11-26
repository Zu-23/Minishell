#include "../shell_header.h"

int	check_delim(char *str, char delim, char **token, int *i)
{
	if (str[(*i)] == delim)
	{
		if (*i == 0)
		{
			if ((str[0] == '>' && str[1] == '>')
				|| (str[0] == '<' && str[1] == '<'))
			{
				*token = ft_substr(str, 0, 2);//might be wrong
				*i += 2;
				return (1);
			}
			*token = ft_substr(str, 0, 1);
			*i = 1;
		}
		else
			*token = ft_substr(str, 0, *i);
		return (1);
	}
	return (0);
}


char	*ft_strtok( char *str, char *delim)
{
	static char	*loc;
	char		*token;
	int			j;
	int			i;

	if (!str)
		str = loc;
	if (!str || !str[0])
		return (NULL);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (delim[j])
		{
			if (check_delim(str, delim[j], &token, &i))
			{
				loc = str + i;
				return (token);
			}
			j++;
		}
		i++;
	}
	loc = NULL;
	return (ft_strdup(str));
}