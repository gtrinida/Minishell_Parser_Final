#ifndef MINISHELL_H
# include <term.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <curses.h>
# include <errno.h>
#include <string.h>
# include "libft/libft.h"
// # include "color.h"
# define BUFFSIZE 100
# define TERM_TYPE_BUFF 2048

//..........Parser............

typedef struct s_rdir
{
	int			heredock_quote;
	int			type;
	int			fd;
	char		*arg;
	void		*next;
}				t_rdir;

typedef struct s_node
{
	int			need_to_free_str;
	int			need_to_free_arg;
	int			need_to_assign;
	int			n_arg; 
	int			n_rdir_arg;
	int			init_rdir;
	char		*cmd;
	char		**arg;
	void		*next;
	void		*prev;
	t_rdir		*rdir;
}				t_node;

typedef struct s_params
{
	int			key;
	char		*line;
	t_node		*node;
	t_node		*list;
}				t_params;

typedef struct s_quotes
{
	int		i_arg;
	int		i;
	int		j;
	int		start;
	int		end;
	int		pass_quote;
	int		env_i;
	int		len_env;
	char	flag;
}			t_quotes;

int	is_it_specsym(char sym);
void	write_one_sym(t_params *data, t_quotes *quot, char *line);
int	next_quot_check(char *line, int i);
int	not_env(t_quotes *quot, t_params *data, char *line);
int		check_multi_dollars(char *line, t_quotes *quot, t_params *data, int counter);
int		get_new_len(char *line, t_quotes *quot, char *env_line);
int		is_dollar_ahead(char *line, int i);
int		get_finish(char *line, int i);
int		is_it_env(char **env, char *line, int end, int start);
int		get_env(t_params *data, t_quotes *quot, char *line, char **env);
int		check_command_before(char *line, int i);
int		get_len(char *bf_dollar, char *af_dollar, char *instead_of);
int		argument_count(t_params *data, t_quotes *quot, int count, int flag);
int		find_arguments(t_params *data, t_quotes *quot);
int		check_ahead(char *line, int i);
int		check_after_rdir(char *line, int i, char *type);
int		find_arguments(t_params *data, t_quotes *quot);
int		before_after(char *line, int i, int type);
int		fast_quotes_check(char *line);
int		parser(char *line, char **env, t_params *data);
int		heredock_behind(char *line, int i);
int		is_rdir(char sym);
int		is_it_letter(char sym);
int		even_or_odd(int dight);
int		is_nothing(char sym);
int		start_info(t_params *data, char *line, int *i, int *len);
int		check_len_of_command(char *line, int i);
int		we_need_this_quotes(char *line, int i, char flag);
int		dollar_in_double_quotes(t_quotes *quot, char *line);
int		start_command(t_quotes *quot, t_params *data, char *line, char **env);
int		pipe_bad_syntax(char *line);
int		rdir_bad_syntax(char *line);
void	check_flag(t_params *data, t_quotes *quot, char *line);
void	copy_env(t_quotes *quot, t_params *data, char *env_line);
void	env_join(t_params *data, t_quotes *quot, char *env_value);
void	get_new_memory(t_params *data, int len, t_quotes *quot);
void	data_node_init(t_params *data);
void	fill_argument(t_params *data, t_quotes *quot);
void	fill_command(t_params *data, t_quotes *quot);
void	find_command(t_params *data, t_quotes *quot);
void	check_dollar_with_single(t_params *data, int i);
void	check_quotes_utils(char *line, t_params *data, char **env);
void	param_init(t_quotes *tmp_quot);
void	before_inside(t_quotes *tmp_quot, t_params *data, char *line, char **env);
void	not_quotes(char *line, t_quotes *tmp_quot, t_params *data);
void	inside_quotes(char *line, t_quotes *tmp_quot, t_params *data, char **env);
void	work_with_dollar(t_quotes *quot, char *line, t_params *data, char **env);
void	work_with_dollar_outside(char *line, t_quotes *quot, t_params *data, char **env);
void	check_dollar(char *line, int i, int steps_next_quote, int count);
void	last_preparation(t_params *data, t_quotes *quot, int i, int flag);
void	add_rdir(t_rdir **rdir);
void	clear_list(t_node **list);
void	print_list(t_node *list);
void	print_node(t_node *node);
void	print_node2(t_node *node);
void	correct_count(t_params *data, int *i);
void	start_work_rdir(t_params *data, t_quotes *quot);
void	rewrite(t_params *data, int i);
void	check_dollar_with_quest(t_params *data);
void	rewrite_new_line(char *bf_dollar, int *i, char *instead_of, t_params *data);
void	rewrite_new_line_utils(char *af_dollar, int i, t_params *data);
void	find_new_command(t_quotes *quot, t_params *data, char *line, char **env);
char	*get_value(char *tmp_line, char **env);
t_node	*add_node(t_node **list, t_node *node);
t_node	*new_node(char *cmd, char **arg);

#endif