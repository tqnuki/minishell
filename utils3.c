/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:01 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/20 13:14:2 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

char	*trim_until_slash(char *str)
{
	char	*slash_pos;

	slash_pos = ft_strchr(str, '/');
	if (slash_pos == NULL)
		return (NULL);
	else
		return (slash_pos + 1);
}

char	*get_value(char **lines, const char *key)
{
	int		i;
	char	*equals_pos;

	i = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], key, ft_strlen(key)) == 0)
		{
			equals_pos = ft_strchr(lines[i], '=');
			if (equals_pos == NULL)
				return ("");
			else
				return (equals_pos + 1);
		}
		i++;
	}
	return ("");
}

void	goofyahhfunction(char **args, int i, char *str)
{
	if (isdollar(args[i]) && !g_s->sq)
	{
		amongusahh(args, str, i);
	}
	else
	{
		if (g_s->sq || g_s-> q)
			sus(args[i]);
		else
			printf("%s", args[i]);
	}
}

void	sus(char *str)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = ft_strlen(str);
	if (len > 2)
	{
		while (i < len - 1)
		{
			printf("%c", str[i++]);
		}
	}
	else
	{
		printf("%s", str);
	}
}
