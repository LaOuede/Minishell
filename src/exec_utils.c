#include "../include/minishell.h"

void	ft_free_exec(t_exec *exec)
{
	int	i;
	if (exec)
	{
		i = 0;
		if (exec->path_var)
		{
			while (exec->path_var[i])
				ft_freenull(exec->path_var[i++]);
			ft_freenull(exec->path_var);
			exec->path_var = NULL;
		}
		i = 0;
		if (exec->pipes)
		{
			while (i < exec->pipes_nb)
				ft_freenull(exec->pipes[i++]);
			ft_freenull(exec->pipes);
			exec->pipes = NULL;
		}
		i = 0;
		if (exec->readline)
		{
			while (exec->readline[i])
				ft_freenull(exec->readline[i++]);
			ft_freenull(exec->readline);
			exec->readline = NULL;
		}
		if (exec->pids)
			ft_freenull(exec->pids);
		// freenull(exec);
	}
}

void	ft_err(char *msg, t_exec *exec)
{
	ft_free_exec(exec);
	perror(msg);
	exit(1);
}

int	ft_path_var_qty(char **path_var)
{
	int	i;

	i = 0;
	while (path_var[i])
		i++;
	return (i);
}

char	**ft_get_path(char **envp, int i)
{
	char	**path_var;
	char	**new_path_var;

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		new_path_var = ft_calloc(1, sizeof(char *));
		new_path_var[0] = ft_calloc(1, sizeof(char));
		return (new_path_var);
	}
	path_var = ft_split(&envp[i][5], ':');
	if (!path_var)
		return (NULL);
	new_path_var = ft_calloc(ft_path_var_qty(path_var) + 1, sizeof(char *));
	if (!new_path_var)
		return (NULL);
	i = -1;
	while (path_var[++i])
	{
		new_path_var[i] = ft_strjoin(path_var[i], "/");
		free(path_var[i]);
	}
	free(path_var);
	return (new_path_var);
}

t_exec	*ft_init_exec(int ac, char **av, char **envp)
{
	static t_exec	*exec;

	(void)ac;
	(void)av;
	if (!exec)
	{
		exec = malloc(sizeof(*exec));
		exec->envp = envp;
		exec->path_var = ft_get_path(exec->envp, 0);
		exec->cmd_nb = 1;
		exec->pipes = ft_calloc(sizeof(int), 1);
		exec->pipes_nb = 0;
		exec->index = 0;
		exec->readline = ft_calloc(sizeof(char *), 1);
		exec->pids = ft_calloc(1,1);
		// exec->output = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		// exec->input = open(exec->av[1], O_RDONLY);
		// if (exec->output == -1)
		// 	ft_err("Error ! Couldn't create the output file", exec);
	}
	return(exec);
}