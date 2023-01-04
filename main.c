#include "shell_header.h"

typedef struct environment
{
	char *var;
	char *value;
}env_struct;

t_cmd	*lexer(char *token, t_cmd *cmd)
{

	if (cmd == NULL)
		cmd = lst_init(cmd, token);
	else
		cmd = lst_add(cmd, token);
	return (cmd);
}

env_struct *get_env(char **env)
{
	int i;
	int	j;
    char ***splitted_2d_env;
    env_struct *env_var;

	i = 0;
	j = 0;
    while (env[i])
        i++;
    env_var = malloc(sizeof(env_struct) * i);
    splitted_2d_env = malloc(sizeof(char **) * (i + 1));
    i = -1;
    while (env[i])
        splitted_2d_env[i] = ft_split(env[i], '=');
    splitted_2d_env[i] = NULL;
    while (splitted_2d_env[j])
    {
		i = 0;
        while (splitted_2d_env[j][i])
        {
            env_var[j].var = ft_strdup(splitted_2d_env[j][i++]);
            env_var[j].value = ft_strdup(splitted_2d_env[j][i++]);
        }
        j++;
    }
	return (env_var);
}

void	visit(t_node *tree)//function to print the tree recursively
{
	int	i = 0;
	if (tree->node_type != PIPE)
	{
		printf("command: %s : ",tree->node_data.cmarg.command);
		while(tree->node_data.cmarg.arg[i])
			printf("arg: %s\n",tree->node_data.cmarg.arg[i++]);
	}
	else if (tree->node_type == PIPE)
	{
		printf("pipe |\n");
		visit(tree->node_data.pipe.left);
		visit(tree->node_data.pipe.right);
	}
}

int main(int ac, char **av, char **env)
{
	char		*input;
	char		*token;
	t_cmd		*cmd;
	//t_node		*tree;
	// char		**env_stock;

	cmd = NULL;
	(void)ac;
	(void)av;
	(void)env;
	// env_stock = get_env(env);
	while (1)
	{
		input = readline("$>");
		if (!input || input[0] == '\0' || ft_isspace(input))
			ft_perror("exit");
		if (ft_strlen(input) > 0)
			add_history(input);
		token = ft_strtok(input, " \'\"/$><&\\;|()");
		while (token)
		{
			cmd = lexer(token, cmd);
			free(token);
			token = ft_strtok(NULL, " \'\"/$><&\\;|()");
		}
		cmd = lexer_analyzer(cmd);
		//tree = asyntax(cmd);
		cmd = lst_delete(cmd);
	}
		// execute(cmd, env_stock);
	// 	t_cmd *tmp;
	// 	tmp = cmd;
	// 	while (tmp)
	// 	{
	// 		printf("command %s\n",tmp->command);
	// 		tmp = tmp->next;
	// 	}
	// }
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
