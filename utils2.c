/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:29:22 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/19 11:35:27 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_char_array(char **source, char **dest)
{
	int	i;

	i = 0;
	while (source[i])
	{
		dest[i] = malloc(1000);
		ft_strcpy(dest[i], source[i]);
		i++;
	}
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

void	prepend(char *s, const char *t)
{
	size_t	len;

	len = ft_strlen(t);
	ft_memmove(s + len, s, ft_strlen(s) + 1);
	ft_memcpy(s, t, len);
}

char	*trim_until_slash(char *str)
{
	char	*slash_pos;

	slash_pos = ft_strchr(str, '/');
	if (slash_pos == NULL)
		return (NULL);
	else
		return (slash_pos + 1);
}

int	isdollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}
