#ifndef SHELL_H
# define SHELL_H

# include "minishell.h"


typedef enum e_token_type
{
	WORD,  //0
	PIPE, //1
	REDIR_IN, //2
	REDIR_OUT, //3
	HEREDOC,    //4
	APPEND,  //5
	DOUBLEQUOTED, //6
	SINGLEQUOTED,    //7
}t_token_type;

/*
only exampel for how we can sort the tokens in the list nothing in ore decided for now :)
*/
typedef struct s_node
{
	char *args;
	char **filename;
	char **redirections;
	bool pipe_flag;
	struct s_node *next;
	struct s_node *prev;
} t_node;

/*
token value == the string witch is teh token
type == ENUM Value
*/
typedef struct s_token
{
	char *token_value;
	t_token_type type;
	struct s_token *next;
}	t_token;

/*
input = the input from readline function
tokens = string with has all token strings inside
node = shoulde be int the future the node prom pipe to pipe
list = is the struct from libft with this i can use the ft_lstadd_back and the ft_lstnew function from libft
*/
typedef struct s_mini
{
	char *input;
	char **tokens;
	char **env;
	t_node *node_list;
	t_list *list;
} t_mini;

/**
 * typedef struct s_token
{
	char			*input;
	char			*input_backup;
	bool			var_check;
	int				type;
	int				status;
	bool			joined;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*infile;
	char			*outfile;
	char			*heredoc_delimiter;
	bool			heredoc_quotes;
	int				fd_in;
	int				fd_out;
	int				stdin_backup;
	int				stdout_backup;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**args_list;
	bool			if_pipe;
	int				*pipe_fd;
	t_redir			*io;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;
 */
// alter struct
// typedef struct s_mini
// {
// 	char *input;
// 	char **tokens;
// 	char **env;
// 	t_node *node;
// 	t_list *list;
// } t_mini;

typedef struct s_shell
{
	char	*input;
	char	**tokens; //neu
	char	**env;
	t_node *node;
	t_list *list;

	char	*cur_dir;
	char	*old_dir;
	char	*heredoc_file;
	int		heredoc_index;
	char	*history_file;
	bool	has_error;
	int		last_exitcode;
	int		lastexitcode;
}			t_shell;

bool		shell_init(t_shell *shell, char **envp);
t_shell		*get_shell(void);
int			kill_shell(t_shell *shell, int close_shell);

#endif /* SHELL_H */