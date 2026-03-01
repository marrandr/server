/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandAuhentification.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:44:22 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/28 15:54:17 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

void	Command::handleCap(Client *client, const t_parse &parse)
{
	if (parse.params[0].empty())
		return ;
	if (parse.params[0] == "LS")
	{
		client->catsendBuffer(": " + _server.getConfig().getServerName() + " : CAP * LS :\r\n");
		Logger::log(INFO, "Answer cap send");
		return ;
	}
	else if (parse.params[0] == "END")
	{
		Logger::log(INFO, "CAP finish");
		return ;
	}
	else if (parse.params[0] == "REQ")
	{
		client->catsendBuffer(_server.getConfig().getServerName() + " : CAP * NAK :\r\n");
		return ;
	}
}

void Command::handlePass(Client *client, const t_parse& parse)
{
	if (client->getState() == REGISTERED)
	{
		Logger::log(INFO, "Error cmd : " +parse.command + ERR_ALREADYREGISTRED_MSG);
		client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_ALREADYREGISTRED, client->getNickName(), "", ERR_ALREADYREGISTRED_MSG));
		return ;
	}
	if ((parse.params.size() != 1 || parse.lst_param.size() != 1) || parse.params[0].empty())
	{
		Logger::log(INFO, "Error cmd : " +parse.command + " ERR_NEEDMOREPARAMS_MSG");
		client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NEEDMOREPARAMS, client->getNickName(),  parse.command, ERR_NEEDMOREPARAMS_MSG));
		return ;
	}
	if (parse.params[0] != _server.getConfig().getPass())
	{
		Logger::log(WARNING, "Wrong password send by client not connect");
		client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_PASSWDMISMATCH, client->getNickName(),  "", ERR_PASSWDMISMATCH_MSG));
		client->setState(NON_AUTH);
	}
	if (parse.params[0] == _server.getConfig().getPass())
	{
		if (client->getState() == AUTHENTICATED)
		{
			Logger::log(WARNING, "client  " + client->getNickName() + " sent pass AGAIN(Igniored)");
			return ;
		}
		client->setState(AUTHENTICATED);
		Logger::log(INFO, "a client is connect");
	}
}
