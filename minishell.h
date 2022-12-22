/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:55:19 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 17:03:50 by mpankewi         ###   ########.fr       */
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
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**env;
	int		thing;
	int		q;
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
int		launch_executable(char *name, char *arguments[], char *line);

//utils.c

size_t	ft_strcpy(char *dest, const char *src);
int		strcmpeq(const char *s1, const char *s2, int n);
int		goofyahh(char **args);
int		ft_strcmp(char *str1, char *str2);
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

//utils4.c

int		pippin(char *str, char **av);
void	trim(char **av);
char	**cupid(char *str);
char	*ft_strtok(char *str, const char *delim);
char	*trim_quotes(char *s);
int		check_unclosed_quotes(char *s);
void	amongus(char **args);
int		echouwu(char **args);
void	pipeslmao(char **args, char *line);
void	sussy(char **args, char *line);
char	**ft_first_tab_split(char **args, char *str);
int		find_pos(char **av, char *str);
void	sussy2(char **args);
void	goofyahhfunction(char **args, int i, int q, char *str);
int		launch2(char *dir, char *path, char *exec_path, char **arguments);
int		launch3(char *name, int status, char **arguments, char *line);
void	wtfisthisfunction(char **args, char *str, int k, int i);
//redirection.c

void	pipe_execute(char **args, char *line);
void	right_arrow(char **args, char *line, int mode, char *arrow);
void	sussy(char **args, char *line);
void	sus(char *str);
int		echouwu(char **args);
void	amogus2(char *line, char **args, int i, char **tab);
void	amongusahh(char **args, char *str, int k, int i);
//single_split.c

char	**ft_single_split(const char *str, char charset);
#endif
