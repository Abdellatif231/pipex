/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:33:14 by amaaouni          #+#    #+#             */
/*   Updated: 2024/05/15 15:07:53 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_empty(t_par *var)
{
	if (var->arr[var->i][0] != '\0' &&
		!(var->arr[var->i][0] == ' ' && var->arr[var->i][1] == '\0'))
	{
		*(var->tmp) = ft_strdup(var->arr[var->i]);
		var->tmp++;
	}
	var->i++;
}

char	**final_split(char *str, char c)
{
	t_par	var;

	var.i = 0;
	var.count = 0;
	var.arr = split_command(str, c);
	while (var.arr[var.i])
	{
		if (var.arr[var.i][0] != '\0' ||
			!(var.arr[var.i][0] == ' ' && var.arr[var.i][1] == '\0'))
			var.count++;
		var.i++;
	}
	var.final = malloc(sizeof(char *) * (var.count + 1));
	var.tmp = var.final;
	var.i = 0;
	while (var.arr[var.i])
		check_empty(&var);
	*(var.tmp) = NULL;
	free_split(var.arr);
	return (var.final);
}

int	free_split(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(arr);
	return (1);
}

char	*check_path(char *cmd, char *ev[])
{
	char	*path;
	char	*pathname;
	char	**env_paths;
	char	**env_to_free;

	path = find_path(ev);
	if (!path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	env_paths = ft_split(path, ':');
	env_to_free = env_paths;
	while (*env_paths)
	{
		if (!ft_strchr(cmd, '/'))
			pathname = ft_strjoin(*env_paths, cmd);
		else
			pathname = ft_strdup(cmd);
		if (access(pathname, X_OK) == 0)
		{
			free_split(env_to_free);
			return (pathname);
		}
		free(pathname);
		pathname = NULL;
		env_paths++;
	}
	free_split(env_to_free);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
