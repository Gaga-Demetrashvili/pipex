/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/24 22:51:22 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	validations(int argc, char **argv, int pipe_res)
{
	if (argc != 5)
	{
		ft_printf("pipex: program should take 4 args\n");
		exit(1);
	}
	if (ft_strlen(argv[2]) == 0 || argv[2][0] == ' ' || ft_strlen(argv[3]) == 0
		|| argv[3][0] == ' ' || ft_strlen(argv[1]) == 0
		|| ft_strlen(argv[4]) == 0)
	{
		ft_printf("pipex: cmd is empty or has whitespace\n");
		exit(1);
	}
	if (pipe_res == -1)
	{
		perror("pipex: pipe creation error\n");
		exit(1);
	}
}

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

static void	init_cmds_arr(char **argv, int cmdc, char **cmds_arr)
{
	int	i;

	i = 0;
	while (i < cmdc)
	{
		cmds_arr[i] = ft_strdup(argv[i + 2]);
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

t_model	create_and_init_model(char **argv, int argc, char **envp)
{
	t_model	model;
	char	**cmds_arr;
	char	***cmdv_arr;
	int		cmdc;

	cmdc = argc - 3;
	cmds_arr = (char **)malloc(sizeof(char *) * (cmdc + 1));
	if (cmds_arr)
		init_cmds_arr(argv, cmdc, cmds_arr);
	cmdv_arr = (char ***)malloc(sizeof(char **) * (cmdc + 1));
	if (cmdv_arr)
		init_cmdv_arr(cmdv_arr, cmds_arr, cmdc);
	model.cmds_arr = cmds_arr;
	model.cmdv_arr = cmdv_arr;
	model.infile_name = argv[1];
	model.outfile_name = argv[argc - 1];
	model.envp = envp;
	return (model);
}
