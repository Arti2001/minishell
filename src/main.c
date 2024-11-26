/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:56:16 by amysiv            #+#    #+#             */
/*   Updated: 2024/11/26 18:22:04 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal;

int	is_builtin(char *arg)
{
	if (!ft_strncmp("cd", arg, ft_strlen(arg)))
		return (CD);
	if (!ft_strncmp("pwd", arg, ft_strlen(arg)))
		return (PWD);
	if (!ft_strncmp("env", arg, ft_strlen(arg)))
		return (ENV);
	if (!ft_strncmp("echo", arg, ft_strlen(arg)))
		return (ECHO);
	if (!ft_strncmp("exit", arg, ft_strlen(arg)))
		return (EXIT);
	if (!ft_strncmp("unset", arg, ft_strlen(arg)))
		return (UNSET);
	if (!ft_strncmp("export", arg, ft_strlen(arg)))
		return (EXPORT);
	return (NO_BUILTIN);
}

int	run_built_in(t_i_env *i_env, char **arg)
{
	if (arg == NULL)
		return (NO_BUILTIN);
	if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_cd(i_env->env, arg));
	if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_pwd());
	if (!ft_strncmp("env", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_env(i_env->env));
	if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_echo(arg));
	if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_exit(arg, i_env));
	if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_unset(&i_env->env, arg));
	if (!ft_strncmp("export", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_export(i_env->env, arg));
	return (NO_BUILTIN);
}

void	handle_built_in(t_pars *pars, t_i_env *i_env)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (pars->redir != NULL)
		redirect_check(pars);
	i_env->err_code = run_built_in(i_env, pars->cmd);
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Faild to restore stdin");
		return ;
	}
	if (close(fd_in) == -1)
	{
		perror("Faild to close temporary stdin");
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Faild to restore stdout");
		return ;
	}
	if (close(fd_out) == -1)
	{
		perror("Faild to close temporary stdout");
		return ;
	}
}

int	execution(t_pars *pars, t_i_env *i_env)
{
	if (pars->next_process == NULL)
	{
		
		if (is_herdoc(pars->redir))
			if (run_herdoc(pars->redir, i_env) == SIGINT)
			{
					i_env->err_code = g_signal + 128;
					return (1);
			}
		if (pars->cmd != NULL)
		{
			if (is_builtin(pars->cmd[0]) != NO_BUILTIN)
			{
					handle_built_in(pars, i_env);
					return (1);
			}
			run_single_cmd(pars, i_env);
		}
	}
	else
		return(run_multi_cmd(pars, i_env));
	return (1);
}
char	*path_promt(char *curr_path)
{
	char *str;
	
	str = ft_strjoin(curr_path, "$ ");
	if (str == NULL)
		return (NULL);
	return (str);
}

//int	free_return(t_i_env **i_env)
//{
//	int		
//}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_pars	*pars;
	char	*promt;
	t_i_env	*i_env;

	if (argc == 1 && argv[0])
	{
		i_env = (t_i_env *)null_exit(malloc(sizeof(t_i_env)));
		i_env->env = (t_env *)null_exit(set_env(envp));
		g_signal = 0;
		input = NULL;
		init_siagtion(INTERACTIVE);
		while (1)
		{
			promt = path_promt(getcwd(NULL, 0));
			input = readline(promt);
			free(promt);
			if (input == NULL)
				return (1);
			if (!input[0])
				continue ;
			if (g_signal == 2)
				i_env->err_code = 130;
			add_history(input);
			pars = init_pars(input, i_env);
			free(input);
			if (pars == NULL)
			{
				i_env->err_code = 258;
				continue ;
			}
			execution(pars, i_env);
			g_signal = 0;
			free_pars(pars);
		}
		free_list(i_env->env);
		free(i_env);
	}
	return (0);
}
