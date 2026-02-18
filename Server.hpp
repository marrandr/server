/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:21 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/18 17:56:34 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include "Client.hpp"
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <poll.h>
#include <cstdlib>

#define BUFFER_SIZE 1048576
#define MAX_CLIENT SOMAXCONN

class Server
{
	private:
		int					 		_serverFd;
		const std::string			_pass;
		int							_port;
		std::vector<Client>			_allClients;
		std::vector<struct pollfd>	_allPollFd;
		void						_newConnection();
		void						_recevDataClient(int fdClient);
		void						_sendToClient(int fdClient, const std::string &msg);
		void						_removeClient(int fdClient);
		void						_closeAllSocket();

	public:
		Server(int port, const std::string &pwd);
		~Server();
		int		creatServerSocket(int port);
		void	init();
		void	run();
		void	clear();
		Client	*findClient(int fd) const;
};

void	serverUsage(const std::string &ServerName);
void	checkArgServer(const std::string &serverName, const std::string &port,  const std::string &pass);

#endif
