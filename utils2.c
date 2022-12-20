/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoumi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:29:22 by mpankewi          #+#    #+#             */
/*   Updated: 2022/12/20 06:59:50 by mdoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_s;

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
	int	l;
	int	k;

	k = 0;
	l = 0;
	while (args[i])
	{
		if (ft_strcmp((args[i]), "$?") == 0)
			printf("%d", g_s.thing);
		else if (isdollar(args[i]))
		{
			while (args[i][k] && args[i][k] != '$')
				printf("%c", args[i][k++]);
			k++;
			while (args[i][k])
				str[l++] = args[i][k++];
			printf("%s", get_value(g_s.env, str));
		}
		else
			printf("%s", args[i]);
		if (args[i +1])
			printf(" ");
		i++;
	}
}

void	mini_unset(char *str)
{
	delete_char_ptr(g_s.env, str);
}
