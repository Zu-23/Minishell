#include "../shell_header.h"
int	err(char *str)
{
	printf("%s", str);
	return (1);
}

int	flag_val(int val, int flag, t_cmd *cmd)
{
	if (flag == 0)
		flag = val;
	else if (flag != val && cmd->next == NULL)
		return (-1);
	else if (flag == val)
		flag = 0;
	return (flag);
}
int	quote_syntax_err(t_cmd *cmd)
{
	static int	flag;

	if (!ft_strcmp(cmd->command, "\'"))
		flag = flag_val(1, flag, cmd);
	else if (!ft_strcmp(cmd->command, "\""))
		flag = flag_val(2, flag, cmd);

	if (flag == -1 || (cmd->next == NULL && flag))
	{
		flag = 0;
		return(err("unclosed quotes\n"));
	}
	return (0);
}
int	unsupport_syntax_err(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->command, ";")
		|| !ft_strcmp(cmd->command, "\\")
		|| !ft_strcmp(cmd->command, "&"))
		{
			printf("%s ",cmd->command);
			return (err("Unsupported token\n"));
		}
	return (0);			
}

int	pipe_wspace(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = cmd;
	tmp2 = cmd;
	if (tmp->prev->type == W_SPACE || tmp2->next->type == W_SPACE)
	{
		tmp = tmp->prev;
		tmp2 = tmp2->next;
		while (tmp && tmp->type == W_SPACE)
			tmp = tmp->prev;
		while (tmp2 && tmp2->type == W_SPACE)
			tmp2 = tmp2->next;
		if (!tmp || !tmp2)
			return (1);
		if (tmp->type != WORD || tmp2->type != WORD)
			return (1);
	}
	else if (cmd->prev->type != WORD || cmd->next->type != WORD)
		return (1);
	return (0);
}

int	pipe_syntax_err(t_cmd *cmd)
{
		if (!ft_strcmp(cmd->command, "|"))
		{
			if (cmd->prev == NULL || cmd->next == NULL)
				return (err("parse error near | 1\n"));
			else if (!ft_strcmp(cmd->next->command, "|"))
				return (err("|| unsupported token\n"));
			else if (pipe_wspace(cmd))
				return (err("parse error near | 2\n"));
		}
	return (0);
}

int	redirect_syntax_err(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->command, ">") || !ft_strcmp(cmd->command, ">>")
		|| !ft_strcmp(cmd->command, "<") || !ft_strcmp(cmd->command, "<<"))
		{
			if (cmd->next == NULL)
				return (err("parse error\n"));
			cmd = cmd->next;
			while (cmd && cmd->type == W_SPACE)
				cmd = cmd->next;
			if (!cmd || cmd->type != WORD)
				return (err("parse error\n"));
		}
	return (0);
}
t_cmd	*lexer_analyzer(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->state == GENERAL)
		{
			if (redirect_syntax_err(tmp) || unsupport_syntax_err(tmp)
				|| pipe_syntax_err(tmp) || pipe_syntax_err(tmp))
				return (NULL);
		}
		if (quote_syntax_err(tmp))
			return (NULL);
		tmp = tmp->next;
	}
	return (expander(cmd));
}
