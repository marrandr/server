/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:32:39 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/19 18:00:18 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, const std::string &pass) : _serverFd(-1), _pass(pass) ,_port(port)
{}

Server::~Server()
{
	clear();
}

int	Server::creatServerSocket(int port)
{
	int	opt = 1;
	int serverSocket;
	struct sockaddr_in sin;

	//create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Error to creat socket" << std::endl;
		exit(1);
	}
	//Prepare Bind
	if (setsockopt(serverSocket, SOL_SOCKET, SOCK_STREAM, &opt, sizeof(opt)) == -1)
	{
		std::cerr << "[Error] : can't prepare bind by Setockopt" << std::endl;
		close(serverSocket);
		exit(1);
	}
	std::cout << "[INFO] : Socket creat \n";
	//init data sockaddr_in for bind
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "[Error] : can't init bind" << std::endl;
		close(serverSocket);
		exit(1);
	}
	std::cout << "[INFO] : Bind init \n";
	//listen
	if (listen(serverSocket, MAX_CLIENT) == -1)
	{
		std::cerr << "[Error] : can't init listen" << std::endl;
		close(serverSocket);
		exit(1);
	}
	std::cout << "[INFO] : Listen OK \n";
	return (serverSocket);
}

void	Server::init()
{
	std::cout << "----------Init server---------------\n";
	_serverFd = creatServerSocket(_port);

	struct pollfd pFdServer;

	pFdServer.fd = _serverFd;
	pFdServer.events = POLLIN | POLLOUT;
	_allPollFd.push_back(pFdServer);
	std::cout << "------------------------------------\n";
}

void	Server::run()
{
	std::cout << "-----------Run server----------------\n";
	int		retPoll = -1;
	Client	*client = NULL;

	while (true)
	{
		retPoll = poll(&_allPollFd[0], _allPollFd.size(), -1);
		if (retPoll < 0)
		{
			std::cerr << "[Error] Poll faild \n";
			break;
		}
		for (unsigned int i = 0; i < _allPollFd.size(); i++)
		{
			if (_allPollFd[i].revents == 0)
				continue ;
			if (_allPollFd[i].revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (i == 0)
				{
					std::cerr << "[Error] : Server have bug\n";
					return ;
				}
				else
				{
					std::cerr << "[Error] : Client have bug\n";
					_removeClient(_allPollFd[i].fd);
					continue;
				}
			}
			if (_allPollFd[i].revents & POLLIN)
			{
				if (i == 0)
				{
					_newConnection();
				}
				else
				{
					_recevDataClient(_allPollFd[i].fd);
				}
			}
			if (_allPollFd[i].revents & POLLOUT)
			{
				client = findClient(_allPollFd[i].fd);
				if (client)
					client->trySendMessageOnBuffer();
			}
		}
	}
	std::cout << "------------------------------------\n";
}
