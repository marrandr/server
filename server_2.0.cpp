/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:46:53 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/13 16:06:24 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SIZE_BUF 1024

int createServerSocket(int port)
{
	int			 		sock;
	struct sockaddr_in	sin;
	struct protoent		*proto;

	proto = getprotobyname("tcp");
	//creat socket
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (sock < 0)
	{
		write (2, "Error creat Socket\n", 20);
		exit(1);
	}

	//init value on struct sin
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	//init binding
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		write(2, "Error Bind\n", 12);
		close(sock);
		exit(1);
	}

	//init listen
	if (listen(sock, SOMAXCONN) == -1)
	{
		close(sock);
		perror("Listen ");
		exit(1);
	}
	return (sock);
}

int main(int ac, char *av[])
{
	int			 		sSocket;
	int					port;
	struct sockaddr_in	cCin;
	int					retRead;
	unsigned int		clen;
	int 				cSocket;
	char				buffer[SIZE_BUF];


	if (ac != 2)
	{
		write (2, "PORT MISSING\n", 13);
		return (1);
	}
	port = atoi(av[1]);
	sSocket = createServerSocket(port);

	//creat a socket for receve client
	cSocket = accept(sSocket, (struct sockaddr *)&cCin, &clen);
	if (cSocket == -1)
	{
		perror("Accep ");
		close(sSocket);
		return(1);
	}

	//loop to read message by client
	while ((retRead = read(cSocket, buffer, SIZE_BUF - 1)) > 0)
	{
		buffer[retRead] = 0;
		printf("%s\n", buffer);
	}

	//close socket
	close(cSocket);
	close(sSocket);
	return (0);
}
