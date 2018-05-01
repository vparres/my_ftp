/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ftp_user
*/

#include "server/server.h"

int tablen(char **tab)
{
	int i = 0;
	for (; tab[i] != NULL; i++);
	return (i);
}

void user(t_shell *shl, char **arg)
{
	if (tablen(arg) != 2)
		dprintf(shl->cfd, "530 Permission denied\n");
	shl->user = strdup(arg[1]);
	strdown(shl->user);
	dprintf(shl->cfd, "331 Please specify the password.\n");
}

void pass(t_shell *shl, char **arg)
{
	(void)arg;
	if (shl->user != NULL) {
		if (strcmp(shl->user, "anonymous") == 0) {
			shl->is_logged = true;
			dprintf(shl->cfd, "230 Login successful.\n");
			return;
		}
		dprintf(shl->cfd, "530 Login incorrect.\n");
		return;
	}
	dprintf(shl->cfd, "503 Login with USER first.\n");
}

bool is_connected(t_shell *shl)
{
	if (shl->is_logged == false) {
		dprintf(shl->cfd, "530 Please login with USER and PASS.\n");
		return (false);
	}
	return (true);
}
