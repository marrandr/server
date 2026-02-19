/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harinrak <harinrak@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:12:30 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/19 11:31:39 by harinrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>

class Client;
class Channel
{
private:
    std::string _name;
    std::string _topics;
    std::set<Client*> _clients;
    std::set<Client*> _ops;
    size_t user_limits;
    bool _invite_only;
public:
    Channel(const std::string& name);

    void set_usr_limits(size_t limits);
    void add_client(Client*to_add);
    void remove_client(Client*to_remove);
    void set_invite(bool inv);
    void add_operator(Client*ops);
    bool is_operator(Client*ops)const;
    const std::set<Client*>&getClient()const;

    void remove_ops(Client*cl);
    size_t get_user_limits()const;
    ~Channel();
};


#endif