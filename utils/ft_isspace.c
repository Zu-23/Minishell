#include "../shell_header.h"
int ft_isspace(char *str)
{
	int	i;
	int	flag;
	i = 0;
    while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}