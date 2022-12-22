#include "minishell.h"

extern t_shell *g_s;

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