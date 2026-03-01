/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandeRegistration.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:45:23 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 05:49:01 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"
#include "../include/ClientManager.hpp"

void	Command::handleUser(Client *client, const t_parse &parse)
{
	client->setUsrName(parse.params[0]);
	client->setHname(parse.params[1]);
	client->setSname(parse.params[2]);
	client->setRname(parse.params[3]);
	if (client->getState() != REGISTERED && (!client->getNickName().empty()))
	{
		client->setState(REGISTERED);
		if (client->getWelcome() == false)
		{
			client->setWelcome();
			client->catsendBuffer(MessageBuilder::welcome(_server.getConfig().getServerName(), client->getNickName(), client->getUsrName(), client->getHname(), _server.getDateServer()));
		}
	}
}

void	Command::handleNick(Client *client, const t_parse &parse)
{
	if (_server.getCltManager().insNickUse(parse.lst_param[0]))
	{
		std::cout << "[INFO] : Error cmd : " << parse.command << "ERR_NICKNAMEINUSE :: "<<ERR_NICKNAMEINUSE_MSG <<" \n";
		client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_PASSWDMISMATCH, client->getNickName(),  parse.params[0], ERR_NICKNAMEINUSE_MSG));
		return;
	}
	else
	{
		if (client->getState() != REGISTERED && (!client->getUsrName().empty()))
		{
			client->setState(REGISTERED);
			if (client->getWelcome() == false)
			{
				client->setWelcome();
				client->catsendBuffer(MessageBuilder::welcome(_server.getConfig().getServerName(), client->getNickName(), client->getUsrName(), client->getHname(), _server.getDateServer()));
			}
		}
		_server.setCltManager(client, client->getNickName(), parse.lst_param[0]);
	}
}
