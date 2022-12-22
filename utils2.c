/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:43:58 by mdoumi            #+#    #+#             */
/*   Updated: 2022/12/22 16:43:59 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	*g_s;

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

void	prepend(char *s, const char *t)
{
	size_t	len;

	len = ft_strlen(t);
	ft_memmove(s + len, s, ft_strlen(s) + 1);
	ft_memcpy(s, t, len);
}

void	delete_char_ptr(char **str_arr, char *str)
{
	char	**ptr;

	ptr = str_arr;
	while (*ptr)
	{
		if (strcmpeq(*ptr, str, ft_strlen(str)) == 0)
		{
			while (*ptr++)
				*ptr = *(ptr + 1);
			break ;
		}
	ptr++;
	}
}

void	goofyahh2(char **args, int i, char *str)
{
	int	q;
	int	sq;

	q = 0;
	sq = 0;
	if (args[i])
	{
		if (args[i][0] == '"')
			q = 1;
		if (args[i][0] == '\'')
			sq = 1;
	}
	while (args[i])
	{
		goofyahhfunction(args, i, q, str);
		if (args[i +1])
			printf(" ");
		i++;
	}
}

void	mini_unset(char *str)
{
	int	i;
	int	boul;

	i = -1;
	boul = 0;
	if (!str)
		return ;
	str = trim_quotes(str);
	if (!str)
		return ;
	while (g_s->env[++i])
	{
		if (ft_strcmp(ft_split(g_s->env[i], '=')[0], str) == 0)
		{
			boul = 1;
			break ;
		}
	}
	if (boul != 1)
		return ;
	i--;
	while (g_s->env[++i + 1])
		g_s->env[i] = g_s->env[i + 1];
	g_s->env[i] = NULL;
}
