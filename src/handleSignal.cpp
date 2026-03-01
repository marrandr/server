/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleSignal.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:48:57 by marrandr          #+#    #+#             */
/*   Updated: 2026/02/25 17:02:25 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handleSignal.hpp"

void	handleSignal(int sig)
{
	if (sig == SIGQUIT || sig == SIGINT || sig == SIGTERM)
		gRun = 0;
}


