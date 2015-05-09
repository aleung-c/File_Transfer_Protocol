/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 17:01:39 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/09 15:05:25 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	go_pwd(int cs)
{
	char	*pwd;
	char	*buf_cwd;
	int		p_len;

	write_cs(cs, "SUCCESS - pwd", 1);
	buf_cwd = NULL;
	pwd = getcwd(buf_cwd, 4096);
	p_len = ft_strlen(pwd) - ft_strlen(g_home);
	pwd = ft_strjoin(pwd, "\n");
	if (p_len > 0)
		write(cs, &pwd[ft_strlen(g_home)], p_len + 1);
	else
		write(cs, "/\n", 2);
}
