#include "minishell.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

static char	*ft_dollar_change(char *str, int start, int end, char *new_str)
{
	int		str_len;
	int		new_str_len;
	char	*result;

	str_len = ft_strlen(str);
	new_str_len = ft_strlen(new_str);
	result = ft_strnew(str_len - (end - start) + new_str_len);
	if (start < 0 || end < 0 || start >= str_len || end >= str_len)
	{
		printf("erreur de jugement \n");
		return (NULL);
	}
	ft_strncpy(result, str, start);
	ft_strcpy(result + start, new_str);
	ft_strcpy(result + start + new_str_len, str + end + start + 1);
	free(str);
	return (result);
}

static char	*ft_dollar_replace(t_struct *s, char *line, int i)
{
	char	*env_name;
	char	*env_value;
	int		k;
	int		start;

	printf("DOLLAR REPLACE\n");
	k = 0;
	start = i;
	i++;
	while (line[i] && ft_isalnum(line[i]))
		i++;
	env_name = malloc(sizeof(char) * (i - start + 1));
	i = start + 1;
	while (line[i] && ft_isalnum(line[i]))
	{
		env_name[k] = line[i];
		i++;
		k++;
	}
	env_name[k] = '\0';
	env_value = ft_get_env_value(s, env_name);
	printf("%s\n", env_value);
	line = ft_dollar_change(line, start, k, env_value);
	free(env_name);
	return (line);
}

static int	ft_is_flagged(char c, int flag)
{
	if (c == '\"' && flag == 1)
		flag = 0;
	else if (c == '\"' && flag == 0)
		flag = 1;
	return (flag);
}

char	*ft_dollar_check2(t_struct *s, char *line)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (line[i])
	{
		flag = ft_is_flagged(line[i], flag);
		if (line[i] == '\'' && flag == 0)
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}
		else if (line[i] == '$')
			line = ft_dollar_replace(s, line, i);
		else
			i++;
	}
	return (line);
}
