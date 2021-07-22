#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int		max_sock = 0;
int		next_id = 0;
int		id[65536];
fd_set	rd, rw, a_sock;
char	rbuf[42 * 4096], sbuf[42 * 4096], wbuf[42 * 4096 + 42];

void	sall(int i)
{
	for (int j = 0; j <= max_sock; j++)
	{
		if (FD_ISSET(j, &rw) && j != i)
			send(j, wbuf, strlen(wbuf), 0);
	}
}

void	fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	uint16_t	port = atoi(argv[1]);
	int			server_sock = -1;
	struct sockaddr_in	ss_addr;
	ss_addr.sin_family = AF_INET;
	ss_addr.sin_addr.s_addr = (1 << 24) | 127;
	ss_addr.sin_port = (port >> 8) | (port << 8);
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
		fatal_error();
	if (bind(server_sock, (struct sockaddr *)&ss_addr, sizeof(ss_addr)) < 0)
	{
		close(server_sock);
		fatal_error();
	}
	if (listen(server_sock, 128) < 0)
	{
		close(server_sock);
		fatal_error();
	}
	bzero(id, sizeof(id));
	FD_ZERO(&a_sock);
	FD_SET(server_sock, &a_sock);
	max_sock = server_sock;
	while (1)
	{
		rd = rw = a_sock;
		if (select(max_sock + 1, &rd, &rw, 0, 0) <= 0)
			continue ;
		for (int j = 0; j <= max_sock; j++)
		{
			if (FD_ISSET(j, &rd))
			{
				if (j == server_sock)
				{
					struct sockaddr_in c_addr;
					socklen_t len_addr = sizeof(c_addr);
					int	clt = accept(server_sock, (struct sockaddr *)&c_addr, &len_addr);
					if (clt < 0)
						continue ;
					FD_SET(clt, &a_sock);
					id[clt] = next_id++;
					max_sock = (clt > max_sock) ? clt : max_sock;
					sprintf(wbuf, "server: client %d just arrived\n", id[clt]);
					sall(clt);
					break ;
				}
				else
				{
					int rec = recv(j, rbuf, 42 * 4096, 0);
					if (rec <= 0)
					{
						sprintf(wbuf, "server: client %d just left\n", id[j]);
						sall(j);
						FD_CLR(j, &a_sock);
						close(j);
						break ;
					}
					else
					{
						for (int i = 0, n = 0; i < rec; i++, n++)
						{
							sbuf[n] = rbuf[i];
							if (sbuf[n] == '\n')
							{
								sbuf[n] = '\0';
								sprintf(wbuf, "client %d: %s\n", id[j], sbuf);
								sall(j);
								n = -1;
							}
						}
					}
				}
			}
		}
	}
	return (0);
}
