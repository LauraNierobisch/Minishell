#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

void			print_token_list(t_list *list);
char			*create_quote_token(char **start);
char			*create_word_token(char **start);
char			**create_token(t_shell shell);
t_token_type	token_type(char *token);
void			convert_tokens(t_shell *shell);
// char			**ft_add_to_array(char **array, char *new_entry);
t_node			*create_new_node(void);
void process_word_token(t_node **node_list, t_list **token_lst, bool *prev_was_redirect);
// void process_word_token(t_node *new_node, t_list **token_lst, bool *prev_was_redirect);
void			process_redirection_token(t_node *new_node, t_list **token_lst);
t_node			*parse_tokens(t_list **token_lst);
void			build_parsing_nodes(t_shell *shell);
void			print_node_list(t_node *node_list);
char            **ft_add_to_array(char **array, char *new_entry);
int             is_operator(char *token_value);
int             is_known_command(char *token_value);
void            lstremove(t_node **lst, t_node *node);
void            lstadd_back(t_node **lst, t_node *new);
t_node          *lstnew(char *args, char **filename, char **redirections);
#endif /* TOKEN_H */
