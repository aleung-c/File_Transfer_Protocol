/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/03 14:14:46 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/11 14:24:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_cd(int cs, char **input)
{
	char	*buf;
	char	*cwd;

	cwd = NULL;
	buf = NULL;
	write_cs(cs, "SUCCESS - cd", 1);
	if (input[1] && input[1][0])
		change_dir(cs, input[1]);
	else
		chdir(g_home);
}

void	change_dir(int cs, char *path)
{
	char	*new_cwd;
	char	*buf_cwd;
	int		p_len;

	if (chdir(path) != 0)
	{
		write_cs(cs, "ERROR - Invalid folder\n", 1);
		return ;
	}
	buf_cwd = NULL;
	new_cwd = getcwd(buf_cwd, 4096);
	p_len = ft_strlen(new_cwd) - ft_strlen(g_home);
	if (p_len > 0)
	{
		write_cs(cs, "SUCCESS - directory changed\n", 1);
		return ;
	}
	else
	{
		chdir(g_home);
		write_cs(cs, "SUCCESS - going home\n", 1);
	}
}
