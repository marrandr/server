/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerNetwork.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:10:10 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/19 17:41:12 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_newConnection()
{
	int					clientSocket = -1;
	struct sockaddr_in	sinClient;
	unsigned int		sizeLen = sizeof(sinClient);
	if (_allClients.size() > MAX_CLIENT)
	{
		std::cerr << "[WARNING] : max client on server now\n";
		return ;
	}
	clientSocket = accept(_serverFd, (struct sockaddr *)&sinClient, &sizeLen);
	if (clientSocket == -1)
	{
		_closeAllSocket();
		std::cerr << "[Error] : Accept have a problem\n";
		return ;
	}
	std::cout << "[INFO] : New client try connect\n";
	Client client(clientSocket);
	struct pollfd pFdClient;
	_allClients.push_back(client);
	pFdClient.fd = clientSocket;
	pFdClient.events = POLLIN;
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
	client->catrecvBuffer(buffer);
	std::cout << "[INFO] : Message receved by client" << std::endl;
}

void	Server::_sendToClient(int fdClient, const std::string &msg)
{
	(void)fdClient;
	(void)msg;
}
