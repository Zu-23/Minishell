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

typedef struct cmarg
{
  char *command;
  char **arg;
} t_cmarg;

typedef struct pipeline
{
	t_node	*right;
	t_cmarg	*left;
} t_pipe;

typedef union ast_val  //union to ma
{
   t_cmarg cmarg;
   t_pipe  pipe;
}t_ast_val;

typedef struct node
{
	t_types		node_type;
	t_ast_val 	node_data;
}t_node;

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
	pipe_node->node_data.pipe.left = &tree->node_data.cmarg;
	pipe_node->node_data.pipe.right = asyntax(cmd);
	return (pipe_node);
}
int parse_command(t_cmd *cmd, t_node **command_node)
{
  t_types 	type;

  type = cmd->prev->type;
  if (!cmd->prev || type != WORD)
  {
	*command_node = malloc(sizeof(t_node));
	(*command_node)->node_type = COMMAND;
	(*command_node)->node_data.cmarg.command = cmd->command;
	return (1);
  }
  return (0);
}
t_node *asyntax(t_cmd *cmd)
{
	t_cmd *tmp;
	t_cmd *command;
	t_node *tree;

	tmp = cmd;
	while (tmp)
	{
		parse_command(tmp, &tree);
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			tree = parse_pipe(tmp, tree);
		}
		tmp = tmp->next;
	}
	return (tree);
}