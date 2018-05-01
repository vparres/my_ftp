/*
** EPITECH PROJECT, 2018
** PSU_myftp_2017
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
typedef struct s_params
{
	int port;
	int sock_fd;
	char *client_ip;
} t_params;
typedef struct s_shell
{
	char *user;
	char *ip;
	char *home;
	int cfd;
	int sfd;
	int pasv_fd;
	bool is_logged;
	bool pasv_avail;
	bool exit_f;
} t_shell;
/*
** socket.c
*/
void socket_init(t_params *params);
void socket_bind(t_params *params);
int socket_accept(t_params *params);
void socket_close(t_params *params);
/*
** useful.c
*/
void help(char *prg, int exit_code);
bool is_num(const char *str);
void strdown(char *str);
void epur_tok(char *str, char **arg);
/*
** misc.c
*/
void type(t_shell *shl, char **arg);
void stat(t_shell *shl, char **arg);
/*
** handle_client.c
*/
void handle_client(int client_fd, char const *ip, char const *home);
/*
** ftp_cmd.c
*/
void list(t_shell *shl, char **arg);
void pasv_accept(t_shell *shl, char **arg);
void noop(t_shell *shl, char **arg);
void quit(t_shell *shl, char **arg);
void f_help(t_shell *shl, char **arg);

/*
** ftp_dir.c
*/
char *get_abs_dir(t_shell *shl, char *dir);
void pwd(t_shell *shl, char **arg);
void cdup(t_shell *shl, char **arg);
void cwd(t_shell *shl, char **arg);
/*
** ftp_pasv.c
*/
void pasv(t_shell *shl, char **arg);
void pasv_close(t_shell *shl);
/*
** ftp_file.c
*/
void retr(t_shell *shl, char **arg);
void stor(t_shell *shl, char **arg);
void dele(t_shell *shl, char **arg);
/*
** ftp_user.c
*/
int tablen(char **tab);
void user(t_shell *shl, char **arg);
void pass(t_shell *shl, char **arg);
bool is_connected(t_shell *shl);

#endif /* !SERVER_H_ */
