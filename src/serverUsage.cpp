/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverUsage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:09:25 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/27 10:10:30 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void serverUsage(const std::string &ServerName)
{
	Logger::log(ERROR, "Usage " + ServerName + " \'port{0->65535}\' \'password\'");
}
