/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:32:39 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/18 14:56:16 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port) : _serverFd(-1),  _port(port)
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
		exit(1);
	}
	std::cout << "Socket creat \n";
	//init data sockaddr_in for bind
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "Error : can't bind" << std::endl;
		close(serverSocket);
		exit(1);
	}
	std::cout << "Bind init \n";
	//listen
	if (listen(serverSocket, MAX_CLIENT) == -1)
	{
		std::cerr << "Error : can't listen" << std::endl;
		close(serverSocket);
		exit(1);
	}
	std::cout << "Listen OK \n";
	return (serverSocket);
}

void	Server::_newConnection()
{
	static int			idxClt = 1;
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
	std::cout << "A client num "<< idxClt++ << " connect\n";
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
	std::cout << "Recever by client : " << buffer << std::endl;
}

void	Server::_removeClient(int fdClient)
{
	int	i = -1;
	for (i = 0; i < (int)_allPollFd.size(); i++)
		if (_allPollFd[i].fd == fdClient)
			break;
	if (i > 0)
		_allPollFd.erase(_allPollFd.begin() + i);
	i = -1;
	for (i = 0; i < (int)_allClients.size(); i++)
		if (_allClients[i].getFd() == fdClient)
			break;
	if (i > 0)
		_allClients.erase(_allClients.begin() + i);
	std::cout << "A client delete \n";
	close(fdClient);
}

void	Server::init()
{
	std::cout << "----------Init server---------------\n";
	_serverFd = creatServerSocket(_port);

	struct pollfd pFdServer;

	pFdServer.fd = _serverFd;
	pFdServer.events = POLLIN;
	_allPollFd.push_back(pFdServer);
	std::cout << "------------------------------------\n";
}

void	Server::run()
{
	std::cout << "-----------Run server----------------\n";
	int	retPoll = -1;

	while (true)
	{
		retPoll = poll(&_allPollFd[0], _allPollFd.size(), -1);
		if (retPoll < 0)
		{
			std::cerr << "Error Poll\n";
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
				{
					std::cout << "A client try to connect\n";
					_newConnection();
				}
				else
				{
					std::cout << "Receve msg by fd ""\n";
					_recevDataClient(_allPollFd[i].fd);
					i--;
				}
			}
		}
	}
	std::cout << "------------------------------------\n";
}

void	Server::clear()
{
	std::cout << "----------Close server--------------\n";
	_closeAllSocket();
	_allClients.clear();
	_allPollFd.clear();
}

void	Server::_closeAllSocket()
{
	for (unsigned int i = 0; i < _allPollFd.size(); i++)
		if (_allPollFd[i].fd > 0)
			close (_allPollFd[i].fd);
}


Client	*Server::findClient(int fd) const
{
	for (unsigned int i = 0; i < _allClients.size(); i++)
	{
		if (_allClients[i].getFd() == fd)
			return ((Client *)&_allClients[i]);
	}
	return (NULL);
}
