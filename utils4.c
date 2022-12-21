/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:15:03 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/21 16:21:50 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pippin(char *str, char **av)
{
	int	i;

	i = -1;
	while (av[++i])
		if (av[i][0] == str[0] && av[i][1] == '\0' && str[1] == '\0')
			return (1);
	return (0);
}

void	trim(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_strtrim(av[i], " ");
		i++;
	}
}

char	**cupid(char *str)
{
	char	**rep;

	rep = malloc(sizeof(char *) * 2);
	rep[0] = ft_strdup(str);
	rep[1] = NULL;
	return (rep);
}

char *ft_strtok(char *str, const char *delim)
{
  static char *s = NULL;
  if (str != NULL)
    s = str;

  if (s == NULL || *s == '\0')
    return NULL;

  size_t i = 0;
  while (s[i] != '\0' && ft_strchr(delim, s[i]) == NULL)
    i++;

  if (s[i] == '\0')
  {
    char *temp = s;
    s = NULL;
    return temp;
  }

  s[i] = '\0';
  char *temp = s;
  s += i + 1;
  return temp;
}

char *trim_quotes(char *s) {
  int len = ft_strlen(s);
  if (s[0] == '\'' || s[0] == '"') {
    if (s[0] == s[len - 1]) {
      s[len - 1] = '\0';
      return s + 1;
    }
    else
    {
      printf("Error: unclosed quotes\n");
      return(NULL);
    }
  }
  return s;
}

int check_unclosed_quotes(char *s) {
  if(!s)
    return(1);
  int len = ft_strlen(s);
  if (s[0] == '\'' || s[0] == '"') {
    if (s[0] != s[len - 1]) {
      printf("Error: unclosed quotes\n");
      return(1);
    }
  }
  return 0;
}
