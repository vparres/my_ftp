/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** handle_client
*/

#include "server/server.h"

void	init(t_shell *shl, int client_fd, const char *ip, const char *home)
{
	shl->user = NULL;
	shl->ip = strdup(ip);
	shl->home = strdup(home);
	shl->cfd = client_fd;
	shl->pasv_fd = -1;
	shl->pasv_avail = false;
	shl->is_logged = false;
	shl->exit_f = false;
}

static void	init_cmd(char **cmd)
{
	cmd[0] = "user";
	cmd[1] = "pass";
	cmd[2] = "list";
	cmd[3] = "pwd";
	cmd[4] = "noop";
	cmd[5] = "quit";
	cmd[6] = "help";
	cmd[7] = "pasv";
	cmd[8] = "stat";
	cmd[9] = "type";
	cmd[10] = "cwd";
	cmd[11] = "cdup";
	cmd[12] = "retr";
	cmd[13] = "stor";
	cmd[14] = "dele";
	cmd[15] = NULL;
}

static void	init_fct(void (**fct)(t_shell *shl, char **arg))
{
	fct[0] = &user;
	fct[1] = &pass;
	fct[2] = &list;
	fct[3] = &pwd;
	fct[4] = &noop;
	fct[5] = &quit;
	fct[6] = &f_help;
	fct[7] = &pasv;
	fct[8] = &stat;
	fct[9] = &type;
	fct[10] = &cwd;
	fct[11] = &cdup;
	fct[12] = &retr;
	fct[13] = &stor;
	fct[14] = &dele;
}

static void	parse(t_shell *shl, char *line)
{
	bool	found = false;
	char	*arg[3];
	char	*cmd[16];
	void	(*fct[15])(t_shell *shl, char **arg);

	init_cmd(cmd);
	init_fct(fct);
	epur_tok(line, arg);
	for (int i = 0; cmd[i] != NULL; i++){
		if (strcmp(arg[0], cmd[i]) == 0){
			fct[i](shl, arg);
			found = true;
			break;
		}
	}
	if (found == false)
		if (is_connected(shl) == true)
			dprintf(shl->cfd, "500 Unknown command.\n");
}

void	handle_client(int client_fd, char const *ip, char const *home)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read_2;
	t_shell shl;

	dprintf(client_fd, "220 (tailsFTPd v0.0.1)\n");
	fp = fdopen(client_fd, "rw");
	if (fp == NULL)
		return;
	init(&shl, client_fd, ip, home);
	while ((read_2 = getline(&line, &len, fp)) != -1) {
		parse(&shl, line);
		if (shl.exit_f == true)
			return;

	}
}
