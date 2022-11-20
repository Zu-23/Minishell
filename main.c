#include "shell_header.h"
void	open_quote(t_cmd *cmd)
{
	t_cmd	*last;

	last = lst_last(cmd);
	if (last->state != GENERAL)
	{
		printf("syntax error: open quotes");
		exit(1);
	}
}
void	unsupport(t_cmd *cmd)
{
	t_cmd	*tmp;
	// ";" "\" "&&" "||" ""
	tmp = cmd;
	while (tmp)
	{
		if (ft_strcmp(tmp->command, ";")
			|| ft_strcmp(tmp->command, "\\")
			|| ft_strcmp(tmp->command, "&")
			|| ft_strcmp(tmp->command, "|"))
		{
			printf("%s is unsupported\n",tmp->command);
			exit(1);
		}
		tmp = tmp->next;
	}
}
void	lexer_analyzer(t_cmd *cmd)
{
	open_quote(cmd);
	unsupport(cmd);
}
t_cmd	*lexer(char *token, t_cmd *cmd)
{

	if (cmd == NULL)
		cmd = lst_init(cmd, token);
	else
		cmd = lst_add(cmd, token);
	return (cmd);
}

int main()
{
	char		*input;
	char		*token;
	t_cmd		*cmd;

	cmd = NULL;
	while (1)
	{
		input = readline("$>");
		if (!input || input[0] == '\0' || ft_isspace(input))
		{
			printf("exit");
			exit(1);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		token = ft_strtok(input, " \'\"-/$><&\\;");
		while (token)
		{
			printf("%s\n",token);
			cmd = lexer(token, cmd);
			free(token);
			token = ft_strtok(NULL, " \'\"-/$><");
		}
		lexer_analyzer(cmd);
		////test ground////
		while (cmd)
		{
			printf("command: %s		type: %d	status: %d\n",cmd->command, cmd->type, cmd->state);
			cmd = cmd->next;
		}
	}
}

///checking for syntax errors:
/* - UNEXPECTED TOKENS:
	- `;;' (this token is always unrecognized in bash and zsh shells)

* AND, OR, PIPE, FG, BG:
	- left: [WSPACE] (STRING | CPAR)
	- right: [WSPACE] (STRING | REDIRECT | OPAR | if <FG, BG> ENDOFCMD)

* OPAR "(":
	- left: CMDBEGIN | [WSPACE] (AND | OR | PIPE | OPAR)
	- right: [WSPACE] (STRING | REDIRECT | OPAR)

* CPAR ")":
	- left: [WSPACE] (STRING | CPAR)
	- right: [WSPACE] (AND | OR | PIPE | CPAR | ENDOFCMD)

* REDIRECT:
	- right: [WSPACE] STRING

* PARENTHESES MATCHING AND QUOTING:
	- inside each pair parentheses should not be an empthy command.
	- every open parentheses has to have a matching closing parentheses.
	- every single/double quote have to be closed.
	*/
