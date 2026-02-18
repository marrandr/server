/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harinrak <harinrak@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:17:08 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/17 09:55:50 by harinrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>

enum StatusClient{
    NON_AUTH,
    AUTHENTICATED,
    REGISTERED
};

class Channel;

class Client{
    private:
    int fd;
    std::string _nick_name;
    std::string _usr_name;
    std::string _r_name;
    StatusClient _state;
    std::string _recvBuffer;
    std::string _sendBuffer;
    std::set<Channel*> _channels;
    public:
    Client(int fd);

    int getFd()const;
    const std::string& getNickName()const;
    const std::string& getUsrName()const;
    const std::string& getRname()const;
    const std::string& getState()const;
    const std::set<Channel*>&getChannels()const;

    void setNickName(const std::string& nick);
    void setUsrName(const std::string& user);
    void setState(StatusClient stat);
    void setRname(const std::string& real);

    void join(Channel*c);
    void leave(Channel*c);
    
};


#endif
