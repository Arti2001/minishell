/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   herdoc.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: amysiv <amysiv@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 05:01:20 by amysiv        #+#    #+#                 */
/*   Updated: 2024/11/14 14:29:25 by ydidenko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char *get_lastheredoc(t_redirect *redirects)
// {
// 	int		i;
// 	char	*last_heredoc_name;

// 	i = 0;
// 	last_heredoc_name  = NULL;
// 	while (redirects[i].filename)
// 	{
// 		if (redirects[i].type == HEREDOC_RE)
// 			last_heredoc_name = redirects[i].filename;
// 		i++;
// 	}
// 	return (last_heredoc_name);
// }

// void	child_heredoc(int fd[2], char *delimiter)
// {
// 	char 	*line;

// 	line =  NULL;
// 	close(fd[0]);
// 	while (1)
// 	{
// 		line = readline(">");
// 		if (line == NULL)
// 		{
// 			printf("bash: warning: here-document at line 2 delimited by end-of-file (wanted `%s'))", delimiter);
// 			exit(0);
// 		}
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		ft_putendl_fd(line, fd[1]);
// 		free(line);
// 	}
// 	close(fd[1]);
// 	exit(EXIT_SUCCESS);
// }

// int		redirect_herdoc(t_redirect *heredoc)
// {
// 	char	*delimiter;
// 	int		fd[2];
// 	pid_t	pid;

// 	delimiter = heredoc->filename;
// 	if (pipe(fd) == -1)
// 		return (perror("Faild to create pipe in heredoc"), 0);
// 	pid = fork();
// 	if (pid == -1)
// 		return (close_fd(fd[1], fd[2]), perror("Faild to fork in heredoc"), 0);
// 	if (pid == 0)
// 		child_heredoc(fd, delimiter);
// 	if (close(fd[1]) == -1)
// 		return (perror("Faild to close write-end in heredoc"), 0);
// 	waitpid(pid, NULL, 0);
// 	if (!ft_strncmp(delimiter, get_lastheredoc(heredoc), ft_strlen(delimiter)))
// 		if (dup2(fd[0], STDIN_FILENO) == -1)
// 			return (perror("redirect in heredoc error!"), 0);
// 	if (close(fd[0]) == -1)
// 		return (perror("Faild to close read-end in heredoc"),0);
// 	return (1);
// }

void    write_into_herdoc(int fd, t_redirect *redirect)
{
    char    *line;
    char    *delimiter;

    line = NULL;
    delimiter = redirect->filename;
    while (1)
    {
        line = readline(">");
        if (line == NULL)
		{
        	printf("Warning: Here-document is not properly closed. Expected delimiter: `%s'\n", delimiter);
			free(line);
			close(fd);
			exit(0);
		}
        if (ft_strncmp(line, redirect->filename, ft_strlen(redirect->filename)) == 0)
        {
            free(line);
    		close(fd);
            break;
        }
		ft_putendl_fd(line, fd);
        free(line);
    }
}

int    open_herdoc(t_redirect *redirect)
{
    int		fd;

    fd = open("/tmp/herdoc.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        perror("Faild to open the heredoc.txt");
        return (0);
    }
   write_into_herdoc(fd, redirect);
   return (1);
}


int	run_herdoc(t_redirect *redirects)
{
	int	i;

	i = 0;
	while (redirects[i].filename)
	{
		if (redirects[i].type == HEREDOC_RE)
		{
			if (!open_herdoc(&redirects[i]))
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}