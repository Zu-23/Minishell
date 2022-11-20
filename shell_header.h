#ifndef SHELL_HEADER_H
# define SHELL_HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h> 

typedef enum types
{
	WORD = 1,
	PIPE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	W_SPACE = ' ',
	ENV = '$',
	HERE_DOC,
	REDIR_DOC,
}t_types;

typedef enum states
{
	IN_DQ = '\"',
	IN_Q = '\'',
	GENERAL = 3,
}t_states;

typedef struct cmd
{
	char 			*command;
	t_types			type;
	t_states		state;
	struct cmd		*next;
	struct cmd		*prev;
}t_cmd;

int     ft_isspace(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtok( char *str, char *delim);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_cmd	*lst_add(t_cmd *cmd, char *token);
t_cmd 	*lst_last(t_cmd *cmd);
t_cmd	*lst_init(t_cmd *cmd, char *token);
t_cmd	*lexer(char *token, t_cmd *cmd);
t_states check_state(char *str);

#endif
