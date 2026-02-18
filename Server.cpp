/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:32:39 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/17 18:09:19 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port) : _port(port), _serverFd(-1)
{
}

Server::~Server()
{
	clear();
}

int	Server::creatServerSocket(int port)
{
	int serverSocket;
	struct sockaddr_in sin;

	//create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Error to creat socket" << std::endl;
		std::exit(1);
	}
	//init data sockaddr_in for bind
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "Error : can't bind" << std::endl;
		close(serverSocket);
		std::exit(1);
	}
	//listen
	if (listen(serverSocket, 100) == -1)
	{
		std::cerr << "Error : can't listen" << std::endl;
		close(serverSocket);
		std::exit(1);
	}
	return (serverSocket);
}

void	Server::_newConnection()
{
	int					clientSocket = -1;
	struct sockaddr_in	sinClient;
	unsigned int		sizeLen;
	if (_allClients.size() > MAX_CLIENT)
		return ;
	clientSocket = accept(_serverFd, (struct sockaddr *)&sinClient, &sizeLen);
	if (clientSocket == -1)
	{
		_closeAllSocket();
		std::cerr << "Error : Accept\n";
		return ;
	}
	Client client(clientSocket);
	struct pollfd pFdClient;
	_allClients.push_back(client);
	pFdClient.fd = clientSocket;
	pFdClient.events = POLL_IN;
	pFdClient.revents = 0;
	_allPollFd.push_back(pFdClient);
}

void	Server::_recevDataClient(int fdClient)
{
	char	buffer[BUFFER_SIZE] = {0};
	Client	*client = NULL;

	ssize_t retRecv = recv(fdClient, buffer, BUFFER_SIZE - 1, 0);
	if (retRecv <= 0)
	{
		_removeClient(fdClient);
		return;
	}
	buffer[retRecv] = 0;
	client = findClient(fdClient);
	if (!client)
		return ;

}

void	Server::_removeClient(int fdClient)
{
	int	i = -1;
	for (i = 0; i < _allPollFd.size(); i++)
		if (_allPollFd[i].fd == fdClient)
			break;
	if (i > 0)
		_allPollFd.erase(_allPollFd.begin() + i);
	i = -1;
	for ( i = 0; i < _allClients.size(); i++)
		if (_allClients[i].getFd() == fdClient)
			break;
	if (i > 0)
		_allClients.erase(_allClients.begin() + i);
	close(fdClient);
}

void	Server::init()
{
	_serverFd = creatServerSocket(_port);

	struct pollfd pFdServer;

	pFdServer.fd = _serverFd;
	pFdServer.events = POLLIN;
	_allPollFd.push_back(pFdServer);
}

void	Server::run()
{
	int	retPoll = -1;

	while (true)
	{
		retPoll = poll(&_allPollFd[0], _allPollFd.size(), -1);
		if (retPoll < 0)
		{
			std::cerr << "Error Poll\n";
			break;
		}
		for (int i = 0; i < _allPollFd.size(); i++)
		{
			if (_allPollFd[i].revents == 0)
				continue ;
			if (_allPollFd[i].revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (i == 0)
				{
					std::cerr << "Error : Server\n";
					return ;
				}
				else
				{
					std::cerr << "Error : Client\n";
					_removeClient(_allPollFd[i].fd);
					continue;
				}
			}
			if (_allPollFd[i].revents & POLLIN)
			{
				if (i == 0)
					_newConnection();
				else
				{
					_recevDataClient(_allPollFd[i].fd);
					i--;
				}
			}
		}
	}
}

void	Server::clear()
{
	_closeAllSocket();
	_allClients.clear();
	_allPollFd.clear();
}

void	Server::_closeAllSocket()
{
	for (int i = 0; i < _allPollFd.size(); i++)
		if (_allPollFd[i].fd > 0)
			close (_allPollFd[i].fd);
}


Client	*Server::findClient(int fd) const
{
	for (int i = 0; i < _allClients.size(); i++)
	{
		if (_allClients[i].getFd() == fd)
			return ((Client *)&_allClients[i]);
	}
	return (NULL);
}
