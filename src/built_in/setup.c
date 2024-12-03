/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ydidenko <ydidenko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 19:16:38 by ydidenko      #+#    #+#                 */
/*   Updated: 2024/12/03 19:24:08 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**arg;

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
		(perror("Faild to restore stdin"),
			exit(EXIT_FAILURE));
	if (close(fd_in) == -1)
		(perror("Faild to close temporary stdin"),
			exit(EXIT_FAILURE));
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		(perror("Faild to restore stdout"),
			exit(EXIT_FAILURE));
	if (close(fd_out) == -1)
		(perror("Faild to close temporary stdout"),
			exit(EXIT_FAILURE));
	return (ret);
}
