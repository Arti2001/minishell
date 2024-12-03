/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:56:16 by amysiv            #+#    #+#             */
/*   Updated: 2024/12/03 18:15:17 by amysiv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal;

int	is_builtin(char *arg)
{
	if (!ft_strncmp("cd", arg, ft_strlen(arg) + 1))
		return (CD);
	if (!ft_strncmp("pwd", arg, ft_strlen(arg) + 1))
		return (PWD);
	if (!ft_strncmp("env", arg, ft_strlen(arg) + 1))
		return (ENV);
	if (!ft_strncmp("echo", arg, ft_strlen(arg) + 1))
		return (ECHO);
	if (!ft_strncmp("exit", arg, ft_strlen(arg) + 1))
		return (EXIT);
	if (!ft_strncmp("unset", arg, ft_strlen(arg) + 1))
		return (UNSET);
	if (!ft_strncmp("export", arg, ft_strlen(arg) + 1))
		return (EXPORT);
	return (NO_BUILTIN);
}

int	run_built_in(t_i_env *i_env, t_pars *pars)
{
	char **arg;
	
	arg = pars->cmd;
	if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_cd(i_env->env, arg));
	if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_pwd());
	if (!ft_strncmp("env", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_env(i_env->env));
	if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_echo(arg));
	if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_exit(arg, i_env, pars));
	if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_unset(&i_env->env, arg));
	if (!ft_strncmp("export", arg[0], ft_strlen(arg[0]) + 1))
		return (ft_export(i_env->env, arg));
	return (1);
}

int	handle_built_in(t_pars *pars, t_i_env *i_env)
{
	int	fd_in;
	int	fd_out;
	int	ret;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (pars->redir != NULL)
		redirect_check(pars);
	ret = run_built_in(i_env, pars);
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Faild to restore stdin");
		exit(EXIT_FAILURE);
	}
	if (close(fd_in) == -1)
	{
		perror("Faild to close temporary stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Faild to restore stdout");
		exit(EXIT_FAILURE);
	}
	if (close(fd_out) == -1)
	{
		perror("Faild to close temporary stdout");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	execution(t_pars *pars, t_i_env *i_env)
{
	if (pars->next_process == NULL)
	{
		if (is_herdoc(pars->redir))
		{
			if (run_herdoc(pars->redir, i_env) == SIGINT)
			{
				i_env->err_code = 128 + g_signal;
				return (i_env->err_code);
			}
			else
				i_env->err_code = 0;
		}
		if (pars->cmd != NULL || pars->redir)
		{
			if (pars->cmd && is_builtin(pars->cmd[0]) != NO_BUILTIN)
				i_env->err_code = handle_built_in(pars, i_env);
			else
				i_env->err_code = run_single_cmd(pars, i_env);
		}
	}
	else
	{
		if (is_herdoc(pars->redir))
		{
			if (go_all_herdoc(pars, i_env) == SIGINT)
			{
				i_env->err_code = 128 + g_signal;
				return (i_env->err_code);
			}
			else
				i_env->err_code = 0;
		}
		if (pars->cmd != NULL)
		{
			i_env->err_code = run_multi_cmd(pars, i_env);
		}
	}
	return (i_env->err_code);
}

void	shell_lvl(t_env *env)
{
	char	*value;
	int		shlvl;

	value = get_path("SHLVL", env);
	shlvl = ft_atoi(value);
	shlvl += 1;
	value = ft_itoa(shlvl);
	update_env_value(env, "SHLVL", value);
	free(value);
}


int	use_readline(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDERR_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	else
		return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_pars	*pars;
	t_i_env	*i_env;
	int		ret;

	ret = 0;
	if (use_readline())
		return (1);
	if (argc == 1 && argv[0])
	{
		i_env = (t_i_env *)null_exit(malloc(sizeof(t_i_env)));
		i_env->err_code = 0;
		i_env->env = (t_env *)null_exit(set_env(envp));
		if (i_env->env == NULL)
			return (free(i_env), 1);
		shell_lvl(i_env->env);
		g_signal = 0;
		input = NULL;
		init_siagtion(INTERACTIVE);
		//here make function using isatty  and check if STDIN STDOUT & STDERROR are what they suppose to be if (!isatty(STDIN)){printf("Standard input is not a terminal\n"); return (1);}
	
		while (1)
		{
			input = readline("minishell$ ");
			if (input == NULL)
			{
				printf("exit\n");
				break ;
			}
			if (!input[0])
			{
				free(input);
				continue ;
			}
			if (g_signal == 2)
				i_env->err_code = 130;
			add_history(input);
			pars = init_pars(input, i_env);
			free(input);
			if (pars == NULL)
			{
				ret = i_env->err_code;
				continue ;
			}
			ret = execution(pars, i_env);
			g_signal = 0;
			free_pars(pars);
		}
		rl_clear_history();
		free_list(i_env->env);
		free(i_env);
	}
	return (ret);
}
