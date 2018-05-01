/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ftp_files
*/

#include "server/server.h"
#include <fcntl.h>

void retr(t_shell *shl, char **arg)
{
	int ffd, rb;
	char buf[512];

	if (is_connected(shl) == true) {
		if (shl->pasv_avail == false) {
			dprintf(shl->cfd, "425 Use PORT or PASV first.\n");
			return;
		}
		if ((ffd = open(get_abs_dir(shl, arg[1]), O_RDONLY)) == -1) {
			dprintf(shl->cfd, "500 Failed to open file\n");
			return;
		}
		pasv_accept(shl, arg);
		dprintf(shl->cfd, "150 Opening ASCII mode data connection.\n");
		while ((rb = read(ffd, buf, sizeof(buf))) > 0)
			write(shl->pasv_fd, buf, rb);
		dprintf(shl->cfd, "226 Transfer Complete.\n");
		pasv_close(shl);
		close(ffd);
	}
}

static int stor_mgmt(t_shell *shl, char **arg)
{
	int ffd;

	if ((ffd = open(get_abs_dir(shl, arg[1]), \
	O_WRONLY | O_CREAT | O_TRUNC, 644)) == -1) {
		dprintf(shl->cfd, "500 Failed to open file\n");
		return (-1);
	}
	return (ffd);
}

void stor(t_shell *shl, char **arg)
{
	int ffd, rb;
	char buf[512];

	if (is_connected(shl) == true) {
		if (shl->pasv_avail == false) {
			dprintf(shl->cfd, "425 Use PORT or PASV first.\n");
			return;
		}
		if ((ffd = stor_mgmt(shl, arg)) == -1)
			return;
		pasv_accept(shl, arg);
		dprintf(shl->cfd, "150 Opening ASCII mode data connection.\n");
		while ((rb = read(shl->pasv_fd, buf, sizeof(buf))) > 0)
			write(ffd, buf, rb);
		dprintf(shl->cfd, "226 Transfer Complete.\n");
		pasv_close(shl);
		close(ffd);
	}
}

void dele(t_shell *shl, char **arg)
{
	if (is_connected(shl) == true) {
		if (tablen(arg) == 1){
			dprintf(shl->cfd, "500 Error while deleting file.\n");
			return;
		}
		if (remove(get_abs_dir(shl, arg[1])) == -1) {
			dprintf(shl->cfd, "500 Error while deleting file.\n");
			return;
		}
		dprintf(shl->cfd, "250 File deleted.\n");
		pasv_close(shl);
	}
}
