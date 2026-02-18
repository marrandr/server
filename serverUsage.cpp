/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUsage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:25 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/18 12:35:08 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void serverUsage(const std::string &ServerName)
{
	std::cerr << "Usage "<< ServerName << "port(0 -> 65535) password" << std::endl;
}
