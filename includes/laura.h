#ifndef LAURA_H
# define LAURA_H

# include "minishell.h"

char **create_token(t_mini mini);
void convert_tokens(t_mini *mini);
t_token_type	token_type(char *token);
void print_token_list(t_list *list);
// void enviroment_list(t_list *list);
int syntax_error(const char *str);
void build_parsing_nodes(t_mini *mini);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_add_to_array(char **array, char *new_entry);
void print_node_list(t_node *node_list);
t_node *create_new_node();
void process_word_token(t_node *new_node, t_list **token_lst);
t_node *parse_tokens(t_list **token_lst);
void free_env(char **env);
char **copy_env(char **env);

#endif /* LAURA_H */