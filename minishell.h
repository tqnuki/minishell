/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:55:19 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/21 09:10:38 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**env;
	int		thing;
}		t_shell;

//builtin.c

void	mini_pwd(void);
void	mini_export(char *str);
void	mini_env(void);
void	mini_echo(char **args);
int		mini_cd(char **args);

//minishell.c

int		launch(char **args, char *line);
int		mini_execute(char **args, char *line);
void	signalHandler(int signal);
void	loop(void);
int 	launch_executable(const char *name, char *arguments[], char *line);

//utils.c

size_t	ft_strcpy(char *dest, const char *src);
int		strcmpeq(const char *s1, const char *s2, int n);
int		goofyahh(char **args);
int		ft_strcmp(const char *str1, const char *str2);
int		isdollar(char *str);

//utils2.c

void	copy_char_array(char **source, char **dest);
void	prepend(char *s, const char *t);
void	delete_char_ptr(char **str_arr, char *str);
void	goofyahh2(char **args, int i, char *str);
void	mini_unset(char *str);

//utils3.c

char	*trim_until_slash(char *str);
char	*get_value(char **lines, const char *key);
void	pipe_execute(char **args, char *line);

//utils4.c

int		pippin(char *str, char **av);
void	trim(char **av);
char	**cupid(char *str);
char *ft_strtok(char *str, const char *delim);

//better_split.c

char	**ft_single_split(const char *str, char charset);

#endif
