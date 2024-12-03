/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 09:10:04 by amysiv        #+#    #+#                 */
/*   Updated: 2024/12/03 15:57:49 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PROCESSES 1024
# define _GNU_SOURCE // This is for sigaction
# define WHITESPACE " "

# define INTERACTIVE 1
# define NON_INTERACTIVE 2
# define HERDOC_SIG 3

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_redirect_type
{
	HEREDOC_RE = 1,
	IN,
	OUT,
	OUT_A
}					t_redirect_type;

typedef enum s_built_in
{
	CD,
	PWD,
	ENV,
	ECHO,
	EXIT,
	UNSET,
	EXPORT,
	NO_BUILTIN
}					t_built_in;

typedef enum e_type
{
	DEFAULT,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIR_INPUT,
	HEREDOC,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	PIPE,
	SEPERATOR,
	UNCLOSED
}					t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;
}					t_token;

// typedef struct s_data
//{
//	int	err_code;

//} t_data;

typedef struct s_env
{
	char			*content;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_i_env
{
	int				err_code;
	t_env			*env;
}					t_i_env;

/**
 * @brief Data struct to hold redirection values
 * @param type redirection type.
 * @param filename name of the file.
 */
typedef struct s_redirect
{
	char			*filename;
	bool			is_expandable;
	t_redirect_type	type;
}					t_redirect;

typedef struct s_pars
{
	int				fd_in;
	char			**cmd;
	char			*path;
	t_redirect		*redir;
	struct s_pars	*next_process;
}					t_pars;

///**
// * @brief Data sructure for extractin the path from the environment.
// * @param all_pathes arrayy of pathes arrays.
// * @param temp_path		a temporary path with '/' joinedat the end.
// * @param true_path	the actuall path for execution.
// */
// typedef struct s_exec
//{
//	char	**all_pathes;
//	char	*temp_path;
//	char	*true_path;
//}t_exec;

/*Linked list*/
t_env				*ll_last(t_env *last);
int					ft_lst_size(t_env *lst);
t_env				*ft_env_lstnew(char *key, char *value);
void				ll_addback(t_env **env_head, t_env *new_node);
int					append_node(t_env **head_env, char *content);

/*Built_ins*/
int					ft_pwd(void);
int					ft_env(t_env *env);
int					ft_exit(char **arg, t_i_env *i_env);
int					is_builtin(char *arg);
int					ft_echo(char **commands);
int					ft_unset(t_env **env, char **arg);
int					ft_cd(t_env *env, char **commands);
int					ft_export(t_env *env, char **commands);
int					run_built_in(t_i_env *i_env, char **arg);

/*ENVIRONMENT*/
t_env				*set_env(char **env);
void				shell_lvl(t_env *env);
char				*get_key(char *content);
char				*get_value(char *content);
int					check_var_syntax(char *str);
char				**back_to_array(t_env *env);
int					add_var(t_env *env, char *arg);
int					is_exist(t_env *env, char *name);
char				*key_val_join(char *key, char *value);
void				init_pwd(t_env *env, char *name, char *value);
int					update_env_value(t_env *env, char *var_name, char *new);

/*PATH*/
char				*get_path(char *name, t_env *env);
void				set_extern_cmd_path(t_pars *pars, t_env *env);
void				path_handler(char *cmd, t_i_env *i_env, t_pars **pars);

/*STRING UTILITI*/
void				shell_putendl_fd(char *s, int fd);

/*PROCCESSES*/
int					wait_for_childs(int num_pid, pid_t *pids, t_pars *pars);
int					run_multi_cmd(t_pars *pars, t_i_env *env);
int					run_single_cmd(t_pars *pars, t_i_env *env);
void				my_dear_child(int fd_write_end, int process_num,
						t_pars *pars, t_i_env *i_env);

/*FREE*/
void				free_list(t_env *head);
void				free_node(t_env *node);
void				double_array_free(char **to_free);
void				free_key_value(char *key, char *value);

/*REDIRECTS*/
int					check_redirection_type(int process_num, t_pars *pars,
						int fd_write_end);
int					redirect_check(t_pars *pars);
void				close_fd(int in, int out);
int					run_herdoc(t_redirect *redirects, t_i_env *i_env);
int					is_herdoc(t_redirect *redirect);
int					go_all_herdoc(t_pars *pars, t_i_env *i_env);
int					redirect_herdoc(t_redirect *redirect);

/*SIGNALS*/
void				init_siagtion(int param);

/*ERROR*/
void				*null_exit(void *ptr);

/*PARSING*/
t_pars				*init_pars(char *line, t_i_env *i_env);
t_list				*tokenizer(char *line, t_i_env *i_env);
void				lexer(t_list **lst);
size_t				tokenize_sym(char *line, int i, t_token *token);
int					tokenize_quoted(char *line, int i, t_token *token);
int					is_whitespace(char c);
int					is_token_type_redir(t_token token);
int					is_token_type_text(t_token token);
int					is_expandable(t_token token);
void				split_tokens(t_list **lst);
void				combine_tokens(t_list **lst);
t_redirect_type		map_token_to_redirect(t_type type);
void				print_pars(t_pars *pars);
void				destroy_tokens(t_list *tokens);


/*CONVERT TOKENS*/
int					pars_err(t_pars *pars, t_list *lst, char *err_msg);
int					process_token(t_pars **head, t_pars **current,
						t_list **token_list, t_list *lst);
int					process_pipe_token(t_pars **head, t_pars **current,
						t_list *lst);
int					ensure_current_initialized(t_pars **head, t_pars **current,
						t_list *lst);
int					process_redirection_token(t_pars *current,
						t_list **token_list, t_list *lst, t_pars *head);
t_pars				*create_new_pars(void);
void				add_cmd_arg(t_pars *pars, char *arg);
void				add_redirection(t_pars *pars, t_redirect_type redir_type,
						t_token *filename);
void				free_pars(t_pars *pars);
t_pars				*convert_tokens(t_list *lst, t_i_env *i_env);
int					is_valid_tokens(t_list *tokens);


/*TOKEN*/
t_token				*init_token(void);
t_token				*destroy_token(t_token *token);
t_token				*create_token(char *str, t_type type);
void				repalce_t_list(t_list **lst, t_list *(*list_f)(t_list *));

/*EXPAND_VARS*/
void				expand_vars(t_list **tokens, t_i_env *i_env);
char				*expand_vars_str(char *input, t_type type, t_i_env *i_env);
char				*get_env_var(char *var, t_env *env);

#endif
