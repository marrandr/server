/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:39:59 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 10:16:43 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"
#include "../include/Channel.hpp"

void	Command::sendToChannel(Client *client, const t_parse &parse, size_t indexLstParam, const std::string &msg)
{
	Channel *channel = _server.getChannelManager().findChannel(parse.lst_param[indexLstParam]);
	//Channel *channel = _server.getChannelByName(parse.lst_param[indexLstParam]);
	if (!channel)
	{
		Logger::log(INFO, "Error cmd : " + parse.command + ERR_NOSUCHCHANNEL_MSG);
		client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NOSUCHCHANNEL, client->getNickName(), parse.lst_param[indexLstParam], ERR_NOSUCHCHANNEL_MSG));
	}
	else
	{
		if(channel->isInThisChannel(client))
		{
			Logger::log(INFO, "Message send To Channel");
			_server.getChannelManager().broadcastToChannel(channel,MessageBuilder::command(client->getNickName() + "!" + client->getUsrName() + "@" + client->getHname(), parse.command, parse.lst_param[indexLstParam], msg) ,client);
			//channel->send_to_member(client, MessageBuilder::command(client->getNickName() + "!" + client->getUsrName() + "@" + client->getHname(), parse.command, parse.lst_param[indexLstParam], msg));
		}
		else
		{
			Logger::log(INFO, "Error cmd : " + parse.command + " " + ERR_NOSUCHNICK_MSG);
			client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NOSUCHNICK, client->getNickName(), parse.lst_param[indexLstParam], ERR_NOSUCHNICK_MSG));
		}
	}
}

void	Command::handlePrivmsg(Client *client, const t_parse &parse)
{
	std::string msg="";
	for (size_t j = 1; j < parse.params.size(); j++)
	{
		msg += parse.params[j];
		if (j + 1 < parse.params.size())
			msg += " ";
	}
	for (size_t i = 0; i < parse.lst_param.size(); i++)
	{
		if (parse.lst_param[i][0] == '#' || parse.lst_param[i][0] == '&')
			sendToChannel(client, parse, i, msg);
		else
		{
			const std::map<std::string, Client *>::const_iterator it = _server.getCltManager().getClientByNick().find(parse.lst_param[i]);
			if (it != _server.getCltManager().getClientByNick().end())
			{
				Client *recev = it->second;
				Logger::log(INFO, "Msg Send to Client");
				recev->catsendBuffer(MessageBuilder::command(client->getNickName() + "!" + client->getUsrName() + "@" + client->getHname(), parse.command, parse.lst_param[i], msg));
			}
			else
			{
				Logger::log(INFO, "Error cmd : " + parse.command + " " + ERR_NOSUCHNICK_MSG);
				client->catsendBuffer(MessageBuilder::error(_server.getConfig().getServerName(), ERR_NOSUCHNICK, client->getNickName(), parse.lst_param[i], ERR_NOSUCHNICK_MSG));
			}
		}
	}
}

