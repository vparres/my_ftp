/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** misc
*/

#include "server/server.h"

void	stat(t_shell *shl, char **arg)
{
	(void)arg;
	dprintf(shl->cfd, "200-Status\nUser: %s\nip: %s\ncfd: %d\npasv_fd: %d\
	\npasv_avail: %d\n200 Status OK.\n", shl->user, shl->ip, shl->cfd, \
	shl->pasv_fd, shl->pasv_avail);
}

void	type(t_shell *shl, char **arg)
{
	(void)arg;
	dprintf(shl->cfd, "200 Filezilla hack OK\n");
}
