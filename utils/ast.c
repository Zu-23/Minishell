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
	if (!strcmp(tmp->command, " ") || !strcmp(tmp->command, "\"") || !strcmp(tmp->command, "\'"))
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
  return (cmd);
}

t_node *parse_pipe(t_cmd *cmd, t_node *tree)
{
	t_node	*pipe_node;

	pipe_node = malloc(sizeof(t_node));
	pipe_node->node_type = PIPE;
	pipe_node->node_data.pipe.left = tree;
	pipe_node->node_data.pipe.right = asyntax(cmd);
	return (pipe_node);
}

void	parse_args(t_cmd *cmd, t_node **tree)
{
	int		size;
	t_cmd 	*tmp;

	size = 0;
	tmp = cmd;
	while (tmp->next && tmp->next->type == WORD)
	{
		tmp = tmp->next;
		size++;
	}
	(*tree)->node_data.cmarg.arg = malloc(sizeof(char **) * (size + 1));
	if (!(*tree)->node_data.cmarg.arg)
		return ;
	tmp = cmd;
	size = 0;
	while (tmp->next && tmp->next->type == WORD)
	{
		tmp = tmp->next;
		(*tree)->node_data.cmarg.arg[size++] = tmp->command;
	}
	(*tree)->node_data.cmarg.arg[size] = NULL;
}
void parse_command(t_cmd *cmd, t_node **tree)//function that creates t_node node for command
{
	if (!cmd->prev || cmd->prev->type != WORD)
	{
		*tree = malloc(sizeof(t_node));
		if (!*tree)
			return ;
		(*tree)->node_type = COMMAND;
		(*tree)->node_data.cmarg.command = cmd->command;
		parse_args(cmd, tree);
	}
}
// void	visit(t_node *tree)
// {
// 	if (tree->node_type != PIPE)
// 		printf("command: %s\n",tree->node_data.cmarg.command);
// 	else if (tree->node_type == PIPE)
// 	{
// 		printf("pipe |\n");
// 		visit(tree->node_data.pipe.left);
// 		visit(tree->node_data.pipe.right);
// 	}
// }

t_node *asyntax(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_node	*tree;

	tmp = cmd;
	while (tmp)
	{
		parse_command(tmp, &tree);
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			tree = parse_pipe(tmp, tree);
			break ;
		}
		else if (tmp->type == HERE_DOC)
		else if (tmp->type == REDIR_DOC)
		else if (tmp->type == REDIR_IN)
		else if (tmp->type == REDIR_OUT)
		tmp = tmp->next;
	}
	return (tree);
}