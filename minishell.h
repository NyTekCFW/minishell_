/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:07:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "token/token.h"
# include "parsing/parsing.h"
# include "error.h"

# define PROMPT "> MiniShell : "
# define PROMPT_ERROR "-MiniShell: "

enum	e_std
{
	IN,
	OUT
};

enum	e_quotes
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTES = '"'
};

enum	e_directions
{
	LEFT,
	RIGHT
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char			*input;
	char			**env;
	t_token			*tokens;
	t_cmd			*cmd;
	t_env			*envlst;
	char			**path;
	int				status_code;
	int				std[2];
	struct termios	ms_termios;
}	t_data;

// TOKEN
t_token			*ft_tokenization(t_data *data);
int				ft_get_args(t_data *data, char **ptr, t_token **lst);
int				ft_handle_meta(char **ptr, t_token **lst);
int				ft_ismeta(char *str);
int				ft_isquote(int c);
int				ft_check_quotes(t_data *data, char *str);
int				ft_skip_quotes(char *str, int *i);
int				ft_quote_error(t_data *data, char c);

// TOKEN LIST
t_token			*ft_toklst_new(char *value, t_typetok type);
t_token			*ft_toklst_last(t_token *token);
void			ft_toklst_add_back(t_token **lst, t_token *new);
void			ft_toklst_delone(t_token *token);
void			ft_toklst_clear(t_token **lst);

// PARSING
t_cmd			*ft_parse(t_data *data);
char			*ft_expand_var(t_data *data, char *str);
char			*ft_clear_quotes(char *str);
int				ft_status_len(t_data *data, char **str);
void			ft_create_cmd(t_cmd **lst, t_token *token);
void			ft_status_cpy(t_data *data, char **dst, char **src);
void			ft_inside_quotes(char c, int *in_sq, int *in_dq);
void			ft_free_array(char **arr);

// CMD LIST
t_cmd			*ft_cmdlst_new(t_cmd_type type);
t_cmd			*ft_cmdlst_last(t_cmd *cmd);
void			ft_cmdlst_add_back(t_cmd **lst, t_cmd *new);
void			ft_cmdlst_delone(t_cmd *cmd);
void			ft_cmdlst_clear(t_cmd **lst);

// IO LIST
t_io			*ft_iolst_new(t_cmd_type type, char *path);
t_io			*ft_iolst_last(t_io *io);
void			ft_iolst_add_back(t_io **lst, t_io *new);
void			ft_iolst_delone(t_io *io);
void			ft_iolst_clear(t_io **lst);

// BUILTINS
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(t_data *data, char *path);
int				ft_env(t_data *data);
int				ft_export(t_data *data, char **args);
int				ft_unset(t_data *data, char **args);
void			ft_exit(t_data *data, char **args);

// ENV
void			ft_init_env(t_data *data, char **envp);
void			ft_update_env(t_data *data, char *key, char *value);
char			*ft_extract_key(char *str);
char			*ft_extract_value(char *str);
char			*ft_get_env_value(t_data *data, char *key);
int				ft_check_env_key(t_data *data, char *key);
int				ft_isvalid_key(char *str);
char			**ft_lst_to_env(t_data	*data);
void			ft_free_env(t_data *data);

// ENV_LST
t_env			*ft_envlst_new(char *key, char *value);
t_env			*ft_envlst_last(t_env *env);
void			ft_envlst_add_back(t_data *data, t_env *new);
void			ft_envlst_delone(t_env *env);
void			ft_envlst_clear(t_env **lst);

// SIGNALS
void			ft_init_signals(t_data *data);
void			ft_sigint_handler(int signum);
void			ft_parent_handler(int signum);
void			ft_sigquit_handler(int signum);

// COMMANDS HANDLING
int				exec_commands(t_cmd *cmd_list, t_data *data);
bool			has_pipe(const t_cmd *cmd_node);
bool			has_redir_out(const t_cmd *cmd_node);
t_builtin_type	get_builtin_type(t_cmd command);
int				interpret_status(int status);
char			*get_bin_path(char *bin, t_data *data);

// IO STREAMS REDIRECTIONS
int				redirect_streams(const t_io *io, t_data *data);
int				ft_heredoc(t_data *data, const char *stop);

// Mr Propre
void			ft_clean_ms(t_data *data);

#endif
