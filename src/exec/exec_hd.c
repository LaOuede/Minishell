#include "../../include/minishell.h"

void	ft_child_hd(char *delim, int fd_hd)
{
	char	*tmp;

	while (1)
	{
		ft_init_sig(HD);
		ft_putstr_fd("> ", 1);
		tmp = get_next_line(0);
		if ((ft_strncmp(tmp, delim, ft_strlen(delim))) == 0)
		{
			if (ft_strncmp(tmp + ft_strlen(delim), "\n", 2) == 0)
			{
				ft_freenull(tmp);
				break ;
			}
		}
		ft_putstr_fd(tmp, fd_hd);
		ft_freenull(tmp);
	}
}

int	exec_hd(char *delim)
{
	int		fd_hd;
	pid_t	pid_hd;
	int 	status;

	fd_hd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_hd < 0)
		perror("Error ! fd_hd:");
	pid_hd = fork();
	if(pid_hd == -1)
		perror("Error! pid_hd");
	if(pid_hd == 0)
		ft_child_hd(delim, fd_hd);
	waitpid(pid_hd, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status);	
	close(fd_hd);
	fd_hd = open("/tmp/here_doc", O_RDONLY, 0644);
	return (fd_hd);
}
