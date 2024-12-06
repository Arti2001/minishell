/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_vars_str.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/06 17:56:37 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/06 16:32:06 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	var_is_valid_first(int c)
{
	if (c == '?' || c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

static void	lookup_var(char **var, t_i_env *i_env)
{
	char	*str;

	if (!ft_strncmp(*var, "?", 2))
		str = ft_itoa(i_env->err_code);
	else
		str = get_env_var(*var, i_env->env);
	free(*var);
	*var = str;
}

static size_t	calc_varlen(char *var)
{
	size_t	i;

	if (var[0] == '~')
		return (1);
	if (!var_is_valid_first(var[1]))
		return (2);
	if (var[1] == '?')
		return (2);
	i = 1;
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	return (i);
}

static void	replace_var(char **str, size_t start, size_t *len, t_i_env *i_env)
{
	char	*before;
	char	*var;
	char	*after;
	size_t	varlen;

	varlen = calc_varlen(&(*str)[start]);
	before = null_exit(ft_substr(*str, 0, start));
	if (*str[0] == '~')
		var = ft_strdup("HOME");
	else
		var = null_exit(ft_substr(*str, start + 1, varlen - 1));
	if ((*str)[start + varlen])
		after = null_exit(ft_strdup(&(*str)[start + varlen]));
	else
		after = ft_strdup("");
	lookup_var(&var, i_env);
	free(*str);
	*str = null_exit(ft_strjoin3(before, var, after));
	free(before);
	free(after);
	*len = ft_strlen(var);
	free(var);
}

/**
 * @brief expands all valid variables in string
 *
 * @param input string possibly containing variables
 * @param type string token type
 * @return char* string containing expanded variables
 */
char	*expand_vars_str(char *input, t_type type, t_i_env *i_env)
{
	size_t	i;
	size_t	varlen;
	char	*str;

	i = 0;
	str = null_exit(ft_strdup(input));
	while (str[i] != '\0')
	{
		if ((str[i] == '$'
				&& (var_is_valid_first(str[i + 1]) || ft_isalnum(str[i + 1])))
			|| (str[i] == '~' && type == DEFAULT))
		{
			replace_var(&str, i, &varlen, i_env);
			i += varlen;
		}
		else
			i++;
	}
	return (str);
}
