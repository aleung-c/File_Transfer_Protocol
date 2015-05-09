/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 13:19:55 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 14:23:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_ls(int cs, char **input)
{
	pid_t child;

	if (serv_check_ls(input) != 0)
	{
		write_cs(cs, "ERROR - ls\nUsage: ls [-l]\n", 1);
		return ;
	}
	write_cs(cs, "SUCCESS - ls\n", 1);
	child = fork();
	if (child == 0)
	{
		dup2(cs, 1);
		execv("/bin/ls", input);
	}
	else
		wait(NULL);
}

int		serv_check_ls(char **input)
{
	if (input[1] && input[2])
	{
		ft_putendl("trop d'args");
		return (-1);
	}
	else if (input[1] && ft_strcmp(input[1], "-l") != 0)
	{
		return (-1);
	}
	return (0);
}
