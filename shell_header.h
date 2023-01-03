#ifndef SHELL_HEADER_H
# define SHELL_HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h> 
typedef enum types
{
	WORD = -1,
	NULL_TERM = '\0',
	PIPE = '|',
	W_SPACE = ' ',
	ENV = '$',
	REDIR_OUT = 1,
	REDIR_IN = 2,
	HERE_DOC = 3,
	REDIR_DOC = 4,
	REDIR = 5,
	COMMAND = 6,
}t_types;

typedef enum states
{
	IN_DQ = '\"',
	IN_Q = '\'',
	GENERAL = 3,
}t_states;

// test area
typedef struct node t_node;
typedef struct cmarg
{
  char *command;
  char **arg;
}t_cmarg;

typedef struct pipe_redir
{
	t_node	*right;
	t_node	*left;
}t_pip_red;

typedef union ast_val
{
   t_cmarg		cmarg;
   t_pip_red	pipe;
}t_ast_val;

struct node
{
	t_types		node_type;
	t_ast_val 	node_data;
};

//end of test area

typedef struct cmd
{
	char 			*command;
	t_types			type;
	t_states		state;
	struct cmd		*next;
	struct cmd		*prev;
}t_cmd;

int     ft_isspace(char *str);
void	ft_perror(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtok( char *str, char *delim);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_cmd	*lst_add(t_cmd *cmd, char *token);
t_cmd 	*lst_last(t_cmd *cmd);
t_cmd	*lst_init(t_cmd *cmd, char *token);
t_cmd	*lst_delete(t_cmd *cmd);
t_cmd	*lexer(char *token, t_cmd *cmd);
t_cmd	*lexer_analyzer(t_cmd *cmd);
t_cmd 	*expander(t_cmd *cmd);
t_node 	*asyntax(t_cmd *cmd);
char	**ft_split(char const *s, char c);
t_states check_state(char *str);

#endif
