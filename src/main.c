/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 12:56:16 by amysiv        #+#    #+#                 */
/*   Updated: 2024/10/29 15:03:46 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*check_built_in() checks if it is a built in, if so ,  calls the coresponding built in function*/
int	is_builtin(t_env **env, char **arg)
{
	if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0])))
		return (ft_cd(*env, arg));
	if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0])))
		return (ft_pwd());
	if (!ft_strncmp("env", arg[0], ft_strlen(arg[0])))
		return (ft_env(*env));
	if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])))
		return (ft_echo(arg));
	if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0])))
		ft_exit(arg);
	if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0])))
		return (ft_unset(env, arg));
	if (!ft_strncmp("export", arg[0], ft_strlen(arg[0])))
		return (ft_export(*env, arg));
	return (NO_BUILTIN);
}

/*This is a temporary parsing. Below in the main() I read the input from the console, then  I split it with the ft_split function
and initialize the temporary struct init_temp_struct() which should contain the data for exexution (such as redirections, amount of pipes, heredoc) */

t_redirect	*init_redirect(void)
{
	t_redirect			*redirects;
	int					i;
	int					count;
	char				*names[] = { "a", "b", "c", "outfile", NULL};
	t_redirect_type		type[] = {HEREDOC_RE, HEREDOC_RE, HEREDOC_RE, OUT, 0};


	count = 4;
	i = 0;
	redirects = (t_redirect *)malloc(sizeof(t_redirect) * (count + 1));
	if (redirects == NULL)
		return (NULL);
	while (count > i)
	{
		redirects[i] = (t_redirect){names[i], type[i]};
		i++;
	}
	redirects[i] = (t_redirect){names[i], type[i]};
	return (redirects);
}

void	init_pars_struct(char *input, t_pars *pars)
{
	pars->orig_in = dup(STDIN_FILENO);
	pars->orig_out = dup(STDOUT_FILENO);
	pars->cmd = ft_split(input, ' ');
	pars->next_process = NULL;
	pars->redir = NULL;
}


int main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_env		*env;
	t_pars		pars;

	if (argc == 1  && argv[0])
	{
		env = set_env(envp);
		if (env == NULL)
			return (1);
		while (1)
		{
			input = readline("Minishell>");
			if (input == NULL)
				return (1);
			if (!input[0])
				continue;
			add_history(input);
			init_pars_struct(input, &pars);
			/* lexer testing */
			init_pars(input);
			/* lexer testing*/
			free(input);
			if (pars.next_process == NULL)
			{
				if (is_builtin(&env, pars.cmd) == NO_BUILTIN)
					run_command(&pars, env);
			}
		}
		free_list(env);
	}
	return (0);
}
