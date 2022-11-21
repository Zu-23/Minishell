#include "../shell_header.h"
t_states    return_state(int flag)
{
	if (flag == 1)
		return (IN_DQ);
	else if (flag == 2)
		return (IN_Q);
	else
		return (GENERAL);
}
int flag_state(char quote, int flag)
{
	if ((quote == '\'' || quote == '\"') &&  flag)
		flag = 0;
	else if (quote == '\'')
	{
		flag = 1;
		return (flag);
	}
	else if (quote == '\"')
	{
		flag = 2;
		return (flag);
	}
	return (flag);
}
t_states check_state(char *str)
{
	int			i;
	static int	flag;

	i = 0;
	while (str[i])
	{
		flag = flag_state(str[i], flag);
		i++;
	}
	return (return_state(flag));
}

t_cmd	*lst_delete(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		free(cmd->command);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	return (cmd);
}