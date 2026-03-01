/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 07:17:08 by harinrak          #+#    #+#             */
/*   Updated: 2026/02/28 19:04:02 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>
#include "ircReplyCode.hpp"
#include "Channel.hpp"

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
    std::string _h_name;
    std::string _s_name;
    std::string _r_name;
    StatusClient _state;
    std::string _recvBuffer;
    std::string _sendBuffer;
    std::set<Channel*> _channels;
	bool	_welcome;
    Client();

    public:
    Client(int fd);
    Client& operator=(const Client&to_cpy);
    Client (const Client&to_cpy);
    void catrecvBuffer(const std::string&to_cat);

    int getFd()const;
    const std::string& getNickName()const;
    const std::string& getUsrName()const;
    const std::string& getRname()const;
    const StatusClient& getState()const;
    const std::set<Channel*>&getChannels()const;
    const std::string&get_recBufer()const;
    const std::string&get_sendBuffer()const;
	bool getWelcome() const;
    const std::string&getSname()const;
    const std::string&getHname()const;

    void set_recvBuffer(const std::string& rcv);
    void set_sendBuffer(const std::string& send);
    void setNickName(const std::string& nick);
    void setUsrName(const std::string& user);
    void setState(StatusClient stat);
    void setRname(const std::string& real);
    void setPassword(const std::string& pass);
    void setHname(const std::string& real);
    void setSname(const std::string& real);
    void setWelcome();

	bool checkRecBuffer()const;
    bool checkSendBuffer()const;


	void catsendBuffer(const std::string&to_cat);

    bool in_channel(Channel*ch)const;
    void joinChannel(Channel*ch);
    void leaveChannel(Channel*ch);
    void leaveAllChannel();
    size_t get_sizeAllchannel()const;


    bool isAuthenticated() const;
    std::string getTrue_recvBuffer();
    void tryRegister();

};


#endif
