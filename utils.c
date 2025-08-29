/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 21:13:04 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, t_model model, int is_rdonly)
{
	int	fd;

	if (is_rdonly)
		fd = open(file_name, O_RDONLY);
	else
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_error_exit(file_name, ": No such file or directory\n", model, 1);
	return (fd);
}

static void	init_cmds_arr(char **argv, int cmdc, char **cmds_arr,
		int is_heredoc)
{
	int	i;
	int	offset;

	i = 0;
	if (is_heredoc)
		offset = 3;
	else
		offset = 2;
	while (i < cmdc)
	{
		cmds_arr[i] = ft_strdup(argv[i + offset]);
		i++;
	}
	cmds_arr[i] = NULL;
}

static void	init_cmdv_arr(char ***cmdv_arr, char **cmds_arr, int cmdc)
{
	int	i;

	i = 0;
	while (i < cmdc)
	{
		cmdv_arr[i] = ft_split(cmds_arr[i], ' ');
		i++;
	}
	cmdv_arr[i] = NULL;
}

t_model	create_and_init_model(char **argv, int argc, char **envp,
		int is_heredoc, char *heredoc_tmp_file_name)
{
	t_model	model;
	char	**cmds_arr;
	char	***cmdv_arr;

	if (is_heredoc)
	{
		model.cmd_c = argc - 4;
		model.infile_name = heredoc_tmp_file_name;
	}
	else
	{
		model.cmd_c = argc - 3;
		model.infile_name = argv[1];
	}
	cmds_arr = (char **)malloc(sizeof(char *) * (model.cmd_c + 1));
	if (cmds_arr)
		init_cmds_arr(argv, model.cmd_c, cmds_arr, is_heredoc);
	cmdv_arr = (char ***)malloc(sizeof(char **) * (model.cmd_c + 1));
	if (cmdv_arr)
		init_cmdv_arr(cmdv_arr, cmds_arr, model.cmd_c);
	model.cmds_arr = cmds_arr;
	model.cmdv_arr = cmdv_arr;
	model.outfile_name = argv[argc - 1];
	model.envp = envp;
	return (model);
}

void	execute_cmd(char **cmdv, char **envp, t_model model)
{
	int		i;
	char	*path;

	i = 0;
	path = find_path(cmdv, envp);
	if (!path)
		ft_error_exit(cmdv[0], ": command not found\n", model, 127);
	if (execve(path, cmdv, envp) == -1)
	{
		perror("execv failed");
		free(path);
		clean_up_resources(model);
		exit(1);
	}
}
