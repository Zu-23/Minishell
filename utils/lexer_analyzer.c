#include "../shell_header.h"

void	quote_syntax_err(t_cmd *cmd)
{
	t_cmd	*last;

	last = lst_last(cmd);
	if (last->state != GENERAL)
		perror("syntax error: open quotes");
}
void	unsupport_syntax_err(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, ";")
			|| !ft_strcmp(tmp->command, "\\")
			|| !ft_strcmp(tmp->command, "&")
			|| !ft_strcmp(tmp->command, "|"))
			perror("%s is unsupported\n");
		tmp = tmp->next;
	}
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
		while (tmp->type == W_SPACE)
			tmp = tmp->prev;
		while (tmp2->next->type == W_SPACE)
			tmp2 = tmp2->next;
		if (!tmp || !tmp2->command[0])
			perror("parse error near |\n");
		else if (tmp->type != WORD || tmp2->type != WORD)
			perror("parse error near |\n");
	}
	return (0);
}
void	pipe_syntax_err(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, "|"))
		{
			if (pipe_wspace(cmd));
			else if (tmp->prev->type != WORD || tmp->next->type != WORD)
				printf("parse error near |\n");
		}
		tmp = tmp->next;
	}
}

void	redirect_syntax_err(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, ">")
		|| !ft_strcmp(tmp->command, ">>")
		|| !ft_strcmp(tmp->command, "<<")
		|| !ft_strcmp(tmp->command, "<"))
		{
			if (tmp->next->type == W_SPACE)
			{
				tmp = tmp->next;
				while (tmp->type == W_SPACE)
					tmp = tmp->next;
				if (!tmp->command[0])
					printf("parse error near \\n\n");
				else if (tmp->type != WORD)
					printf("parse error near \\n\n");
			}
		}
		tmp = tmp->next;
	}
}
void	lexer_analyzer(t_cmd *cmd)
{
	quote_syntax_err(cmd);
	unsupport_syntax_err(cmd);
	pipe_syntax_err(cmd);
	redirect_syntax_err(cmd);
}
