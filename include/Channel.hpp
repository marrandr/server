/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:12:30 by harinrak          #+#    #+#             */
/*   Updated: 2026/03/01 08:57:29 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include <iostream>
#include "MessageBuilder.hpp"
#include "Client.hpp"


class Client;

class Channel
{
private:
    std::string _name;
    std::string _topics;
    std::set<Client*> _clients;
    std::set<Client*> _ops;
    int user_limits;
    std::string _pass_word;
    bool _only_ops;
    bool _pass;
    bool _invite_only;
    Channel();
public:
    Channel(const std::string& name);
    Channel& operator=(const Channel& to_cpy);
    Channel(Channel* to_cpy);

	size_t	getNbUserChannel() const;

    bool get_inv_only()const;
    void set_usr_limits(int limits);
    const std::string& getName();

    void add_client(Client*to_add);
    void remove_client(Client*to_remove);
	//void send_to_member(Client *client, const std::string &msg);

	bool	isInThisChannel(Client *client) const;

	// void set_invite(bool inv);
    void add_operator(Client*ops);
    bool is_operator(Client*ops);

	const std::set<Client*> getClients() const;

    void set_topic(Client*cl,const std::string&topic);
    void remove_topic(Client*cl);
    void set_only_ops(Client*cl,bool status);
    void set_invite_only(Client*cl);
    void remove_invite_only(Client*cl);
    void set_only_pass(Client*cl,const std::string&pa);
    void remove_pass(Client*cl);
    void give_ops(Client*the_ops,Client*to_be_ops);
    void take_ops(Client*the_ops,Client*to_be_ops_rmv);
    void set_limits(Client*cl,int size);
    void rmv_usr_limits(Client*cl);

    void remove_ops(Client*cl);
    int get_user_limits()const;

    ~Channel();
};


#endif
