#include "../shell_header.h"

t_types	check_type(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (PIPE);
		else if (str[i] == '<')
			return (REDIR_IN);
		else if (str[i] == '>')
			return (REDIR_OUT);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (HERE_DOC);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (REDIR_DOC);
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (W_SPACE);
		else if (str[i] == '$')
			return (ENV);
		i++;
	}
	return (WORD);
}

t_cmd	*lst_init(t_cmd *cmd, char *token)
{
	if (cmd == NULL)
	{
		cmd = malloc(sizeof(t_cmd));
		cmd->command = ft_strdup(token);
		cmd->type = check_type(token);
		cmd->state = check_state(token);
		cmd->next = NULL;
		cmd->prev = NULL;
	}
	return (cmd);
}
t_cmd *lst_last(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_cmd	*lst_add(t_cmd *cmd, char *token)
{
	t_cmd	*tmp;
	t_cmd	*last;

	tmp = cmd;
	if (cmd == NULL)
		return (NULL);
	else
	{
		tmp = malloc(sizeof(t_cmd));
		tmp->command = ft_strdup(token);
		tmp->type = check_type(token);
		tmp->state = check_state(token);
		last = lst_last(cmd);
		last->next = tmp;
		tmp->prev = last;
		tmp->next = NULL;
	}
	return (cmd);
}