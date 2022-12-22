/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpankewi <mpankewi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:52:49 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 17:04:33 by mpankewi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

int	echouwu(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_unclosed_quotes(args[i++]) == 1)
			return (1);
	}
	return (0);
}

char	*trim_quotes(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (s[0] == '\'' || s[0] == '"')
	{
		if (s[0] == s[len - 1])
		{
			s[len - 1] = '\0';
			return (s + 1);
		}
		else
		{
			printf("Error: unclosed quotes\n");
			return (NULL);
		}
	}
	return (s);
}

int	check_unclosed_quotes(char *s)
{
	int	len;

	if (!s)
		return (1);
	len = ft_strlen(s);
	if (s[0] == '\'' || s[0] == '"')
	{
		if (s[0] != s[len - 1])
		{
			printf("Error: unclosed quotes\n");
			return (1);
		}
	}
	return (0);
}

void	sussy2(char **args)
{
	char	*buf;
	int		rd;
	int		fd;

	fd = open(args[1], O_RDONLY);
	buf = malloc(10);
	while (rd && rd != -1)
	{
		rd = read(fd, buf, 1);
		printf("%s", buf);
	}
}

void	wtfisthisfunction(char **args, char *str, int k, int i)
{
	int	l;

	l = 0;
	while (args[i][k])
	{
		if (!ft_isalnum(args[i][k]))
		{
			printf("%s", get_value(g_s->env, str));
			while (args[i])
			{
				if (g_s->q && k == ft_strlen(args[i]) - 1)
					break ;
				printf("%c", args[i][k++]);
			}
		}
		str[l++] = args[i][k++];
		if (k == ft_strlen(args[i]) - 1)
			break ;
	}
}
