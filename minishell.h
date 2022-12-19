/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:55:19 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/19 10:57:54 by mdoumi           ###   ########.fr       */
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
# include <string.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**env;
	int		thing;
}		t_shell;

void	mini_pwd(void);
void	mini_export(char *str);
void	mini_env(void);
void	mini_echo(char **args);
void	mini_unset(char *str);
void	signalHandler(int signal);
void	loop(void);
void	copy_char_array(char **source, char **dest);
void	prepend(char *s, const char *t);
void	delete_char_ptr(char **str_arr, char *str);
char	*get_value(char **lines, const char *key);
char	*trim_until_slash(char *str);
char	*ft_strnstr(const char *haystack, const char *to_find, size_t size);
char	**ft_split(const char *str, char charset);
char	*findString(char **strings, char *startString);
int		launch(char **args);
int		mini_cd(char **args);
int		strcmpeq(const char *s1, const char *s2, int n);
int		isdollar(char *str);
int		mini_execute(char **args, char *line);
size_t	ft_strcpy(char *dest, const char *src);
size_t	ft_strlen(const char *str);

#endif
