#include "../shell_header.h"
// /*grammar
// 	<cmdline>	::= <block>
// 		| <block> (";" | "&") <cmdline>

// <block>		::= <pipeline> {("&&" | "||") <pipeline>}

// <pipeline>	::= <command> {"|" <command>}

// <command>	::= <cmdlist>
// 		| "(" <cmdline> ")" <redir>	(* subshell *)

// <cmdlist>	::= <redir>+			(* at least one redirect - without WORDs *)
// 		| <redir> {<arg> <redir>}+	(* at least one WORD - zero or more <redir> in any place *)

// <redir>		::= {("<" | "<<" | ">" | ">>") <filename>}	(* a delimiter in case of heredoc *)

// <arg>		::= token WORD | token VAR | token GROUP

// <filename>	::= token WORD | token VAR | token GROUP
// */
// /// (aaa | (bbb | ccc))

// // arr[] aaa | bbb | ccc





t_cmd *expander(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->command, " ") && tmp->state == GENERAL) || !ft_strcmp(tmp->command, "\"") || !ft_strcmp(tmp->command, "\'"))
		{
			if (!tmp->prev && tmp->next)
			{
				cmd = tmp->next;
				tmp->next->prev = NULL;
			}
			else if (!tmp->next && tmp->prev)
				tmp->prev->next = NULL;
			else if (tmp->prev && tmp->next)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
			}
			free(tmp->command);
			free(tmp);
			tmp = cmd;
		}
		else
			tmp = tmp->next;
	}
	tmp = cmd;
	while (tmp)
	{
		printf("command: %s --- state: %d\n", tmp->command, tmp->state);
		tmp = tmp->next;
	}
	return (cmd);
}

// t_node *parse_pipe(t_cmd *cmd, t_node *tree)
// {
// 	t_node	*pip_red;

// 	pip_red = malloc(sizeof(t_node));
// 	if (cmd->prev->type == PIPE)
// 		pip_red->node_type = PIPE;
// 	else if (cmd->prev->type >= REDIR_IN && cmd->prev->type <= REDIR_DOC)
// 		pip_red->node_type = REDIR;
// 	pip_red->node_data.pipe.left = tree;
// 	pip_red->node_data.pipe.right = asyntax(cmd);
// 	return (pip_red);
// }

// void	parse_args(t_cmd *cmd, t_node **tree)
// {
// 	int		size;
// 	t_cmd 	*tmp;

// 	size = 0;
// 	tmp = cmd;
// 	while (tmp->next && tmp->next->type == WORD)
// 	{
// 		tmp = tmp->next;
// 		size++;
// 	}
// 	(*tree)->node_data.cmarg.arg = malloc(sizeof(char **) * (size + 1));
// 	if (!(*tree)->node_data.cmarg.arg)
// 		return ;
// 	tmp = cmd;
// 	size = 0;
// 	while (tmp->next && tmp->next->type == WORD)
// 	{
// 		tmp = tmp->next;
// 		(*tree)->node_data.cmarg.arg[size++] = tmp->command;
// 	}
// 	(*tree)->node_data.cmarg.arg[size] = NULL;
// }

// void parse_command(t_cmd *cmd, t_node **tree)//function that creates t_node node for command
// {
// 	if ((!cmd->prev || cmd->prev->type != WORD) && (cmd->type == WORD))
// 	{
// 		*tree = malloc(sizeof(t_node));
// 		if (!*tree)
// 			return ;
// 		(*tree)->node_type = COMMAND;
// 		(*tree)->node_data.cmarg.command = cmd->command;
// 		parse_args(cmd, tree);
// 	}
// 	else if (!cmd->prev)
// 		*tree = NULL;
// }
// // void	visit(t_node *tree)
// // {
// // 	if (tree->node_type != PIPE)
// // 		printf("command: %s\n",tree->node_data.cmarg.command);
// // 	else if (tree->node_type == PIPE)
// // 	{
// // 		printf("pipe |\n");
// // 		visit(tree->node_data.pipe.left);
// // 		visit(tree->node_data.pipe.right);
// // 	}
// // }

// t_node *asyntax(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	t_node	*tree;

// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		parse_command(tmp, &tree);
// 		if (tmp->type == PIPE || (tmp->type >= REDIR_OUT && tmp->type <= REDIR_DOC))
// 		{
// 			tmp = tmp->next;
// 			tree = parse_pipe(tmp, tree);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (tree);
// }