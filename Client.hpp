/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:17:08 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/19 18:24:46 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <set>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

enum StatusClient{
    NON_AUTH,
    AUTHENTICATED,
    REGISTERED
};

class Channel;

class Client{
    private:
    int fd;
    std::string _pass_word;
    std::string _nick_name;
    std::string _usr_name;
    std::string _r_name;
    StatusClient _state;
    std::string _recvBuffer;
    std::string _sendBuffer;
    std::set<Channel*> _channels;
    public:
    Client(int fd);

    void catrecvBuffer(const std::string&to_cat);

    int getFd()const;
    const std::string& getNickName()const;
    const std::string& getUsrName()const;
    const std::string& getRname()const;
    const StatusClient& getState()const;
    const std::set<Channel*>&getChannels()const;
    const std::string&get_recBufer()const;
    const std::string&get_sendBuffer()const;

    void set_recvBuffer(const std::string& rcv);
    void set_sendBuffer(const std::string& send);
    void setNickName(const std::string& nick);
    void setUsrName(const std::string& user);
    void setState(StatusClient stat);
    void setRname(const std::string& real);
    void setPassword(const std::string& pass);

    bool in_channel(Channel*ch)const;
    void joinChannel(Channel*ch);
    void leaveChannel(Channel*ch);
    void leaveAllChannel();
    size_t get_sizeAllchannel()const;


    bool isAuthenticated() const;
    const std::string& extractrcv_buffer()const;
    void tryRegister();

	void	trySendMessageOnBuffer();

};


#endif
