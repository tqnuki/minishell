/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:55:19 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/19 10:38:26 by mdoumi           ###   ########.fr       */
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
	char **env;
	int thing;
}		t_shell;

void mini_pwd();
void mini_export(char *str);
void mini_env();
void mini_echo(char **args);
void mini_unset(char *str);
int mini_cd(char **args);
void copy_char_array(char** source, char** dest);
char *get_value(char **lines, const char *key);
void prepend(char* s, const char* t);
char *trim_until_slash(char *str);
int strcmpeq(const char *s1, const char *s2, int n);
void delete_char_ptr(char **str_arr, char *str);
char *findString(char **strings, char *startString);
int launch(char **args);
int isdollar(char *str);
int mini_execute(char **args, char *line);
void signalHandler(int signal);
void loop();
char	**ft_split(const char *str, char charset);
size_t	ft_strcpy(char *dest, const char *src);
char	*ft_strnstr(const char *haystack, const char *to_find, size_t size);
size_t	ft_strlen(const char *str);

#endif
