/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:50:16 by aleung-c          #+#    #+#             */
/*   Updated: 2015/05/12 12:14:04 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define RESET "\033[0m"

# define MSG_BUFSIZE 1025
# define FILE_BUFSIZE 4096
# define MAX_FILESIZE 1800000000

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>

char *g_home;

typedef struct		s_msg {
	int		ret_client;
	char	buf_client[MSG_BUFSIZE];
	int		ret_serv;
	char	buf_serv[MSG_BUFSIZE];
}					t_msg;

typedef struct		s_transfer {
	int		file_size;
	char	*file_name;
	int		fd_newfile;
	char	*file;
}					t_transfer;

typedef struct		s_progression {
	int somme;
	int percent;
	int prec_res;
}					t_progression;

/*
**	Functions prototypes - Serveur.
*/
int					check_arg1(char *arg);
void				check_input(int cs, char *buf_client);
char				*get_serv_home(void);
void				go_ls(int cs, char **input);
int					serv_check_ls(char **input);
void				go_pwd(int cs);
void				go_cd(int cs, char **input);
void				change_dir(int cs, char *path);
void				go_get(int cs, char **input);
void				write_cs(int cs, char *text, int visible);
void				file_transfer(int cs, int fd);
void				go_put(int cs, char **input);
char				*clean_line(char *line);
int					prepare_receive(int cs, t_msg *msg, t_transfer *tr);
void				serv_receive(int cs, int fd_newfile, int file_size);
void				check_filesize(int fd_newfile, char *file_name,
									int file_size);
int					serv_prepare_send(int cs, int fd, t_transfer *tr);
void				serv_send_datas(int cs, t_transfer *tr);

/*
**	Functions prototypes - Client.
*/
void				prompt();
void				usage(char *str);
int					check_args_client(int port);
int					create_client(char *addr, int port);
void				client_parse(int sock, char *buf, char *buf_serv);
void				client_get(int cs, char *buf_serv, char *buf);
void				client_receive(int sock, int fd_newfile, int file_size);
void				client_put(int sock, char *buf_serv, char *input);
int					client_put_filecheck(int sock, int fd, t_transfer *tr);
void				write_sock(int sock, char *text, int visible);
int					client_prepare_put(int sock, int fd, t_transfer *tr);
void				ready_send(int sock, t_transfer *tr);
void				display_input(char *buf);

#endif
