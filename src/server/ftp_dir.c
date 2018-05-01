/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** ftp_dir
*/

#include "server/server.h"

char	*get_abs_dir(t_shell *shl, char *dir)
{
	char	*abs_dir;

	if (!(abs_dir = malloc(sizeof(char) * (strlen(dir) +
		strlen(shl->home) + 1))))
		return (NULL);
	strcpy(abs_dir, shl->home);
	strcat(abs_dir, dir);
	return (abs_dir);
}

void	cwd(t_shell *shl, char **arg)
{
	if (is_connected(shl) == true) {
		if (chdir(get_abs_dir(shl, arg[1])) == 0)
			dprintf(shl->cfd, \
			"250 Directory successfully changed.\n");
		else
			dprintf(shl->cfd, "550 Failed to change directory.\n");
	}

}

void	cdup(t_shell *shl, char **arg)
{
	(void)arg;
	if (is_connected(shl) == true) {
		if (chdir(shl->home) == 0)
			dprintf(shl->cfd, \
			"250 Directory successfully changed.\n");
		else
			dprintf(shl->cfd, "550 Failed to change directory.\n");
	}

}

void	pwd(t_shell *shl, char **arg)
{
	(void)arg;
	char	cwd[4096];

	if (is_connected(shl) == true) {
		if (getcwd(cwd, sizeof(cwd)) != NULL){
			if ((strlen(shl->home) - 1) == strlen(cwd))
				dprintf(shl->cfd, "257 \"/\"\n");
			else
				dprintf(shl->cfd, "257 \"%s\"\n", cwd + \
				(strlen(shl->home) - 1));
		} else
			dprintf(shl->cfd, "550 PWD Internal error\n");
	}
}
