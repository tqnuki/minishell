/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:29:06 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/27 16:36:51 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_shell
{
	char	**env;
	int		thing;
}			t_shell;

typedef struct s_norminette
{
	int		i;
	int		j;
	char	*str;
}	t_norminette;

//amongus.c

void		read_input_lines(char ***tab, int *j, char *delimiter);
void		print_input_lines(char **tab);
void		remove_delimiter_and_following_args(char **args, char *delimiter);
void		amongus(char **args);
int			check_unclosed_quotes(char *s);

//builtin.c

void		mini_pwd(void);
void		mini_export(char *str);
void		mini_env(void);
void		mini_echo(char **args);
int			mini_cd(char **args);

//minishell.c

int			launch_executable(char *name, char *arguments[], char *line);
int			launch(char **args, char *line);
void		sussy(char **args, char *line);
void		sussy2(char **args);
int			mini_execute(char **args, char *line);
void		signalHandler(int signal);
void		loop(void);
int			main(int ac, char **av, char **env);

//pipe.c

void		pipe_execute(char **args, char *line);
void		execute_second_command(int fd[], char **args, char *line);
void		execute_first_command(int fd[], char **args, char *line);

//redirection.c

int			find_pos(char **av, char *str);
char		**ft_first_tab_split(char **args, char *str);
void		right_arrow(char **args, char *line, int mode, char *arrow);

//single_split.c

char		**ft_single_split(const char *str, char charset);

//utils.c

size_t		ft_strcpy(char *dest, const char *src);
int			strcmpeq(const char *s1, const char *s2, int n);
int			goofyahh(char **args);
int			ft_strcmp(char *str1, char *str2);
int			isdollar(char *str);

//utils2.c

void		copy_char_array(char **source, char **dest);
void		prepend(char *s, const char *t);
void		delete_char_ptr(char **str_arr, char *str);
void		sus(char *str);
void		goofyahh2(char **args, int i, char *str);
void		mini_unset(char *str);

//utils3.c

char		*trim_until_slash(char *str);
char		*get_value(char **lines, const char *key);

//utils4.c

int			pippin(char *str, char **av);
void		trim(char **av);
char		**cupid(char *str);
char		*ft_strtok(char *str, const char *delim);
char		*trim_quotes(char *s);
int			check_unclosed_quotes(char *s);
void		amongus(char **args);

#endif
