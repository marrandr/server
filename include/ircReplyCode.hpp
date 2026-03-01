/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircReplyCode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:47:25 by marrandr          #+#    #+#             */
/*   Updated: 2026/03/01 09:39:34 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                          IRC REPLY CODES                                   */
/* ************************************************************************** */
#ifndef IRCREPLYCODE_HPP
#define IRCREPLYCODE_HPP

#define	SERVER_VERSION "1.0"
#define END "\r\n"
#define DEFAUL_NICK ""
/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/*                        SUCCESS CODES (001-399)                             */
/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */


/* REGISTRATION SUCCESS */
#define RPL_WELCOME "001"
#define RPL_WELCOME_MSG "Welcome to the Internet Relay Network"

#define RPL_YOURHOST "002"
#define RPL_YOURHOST_MSG1 "Your host is"
#define RPL_YOURHOST_MSG2 ", running version "

#define RPL_CREATED "003"
#define RPL_CREATED_MSG "This server was created"

#define RPL_MYINFO "004"
#define RPL_MYINFO_MSG "Server info"

/* CHANNEL TOPIC */
#define RPL_NOTOPIC "331"
#define RPL_NOTOPIC_MSG "No topic is set"

#define RPL_TOPIC "332"
#define RPL_TOPIC_MSG "Channel topic"

/* INVITE */
#define RPL_INVITING "341"
#define RPL_INVITING_MSG "Inviting"

/* NAMES LIST */
#define RPL_NAMREPLY "353"
#define RPL_NAMREPLY_MSG "Names list"

#define RPL_ENDOFNAMES "366"
#define RPL_ENDOFNAMES_MSG "End of /NAMES list"

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/*                        ERROR CODES (400-599)                               */
/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/* PRIVMSG */
#define ERR_NOSUCHNICK "401"
#define ERR_NOSUCHNICK_MSG "No such nick/channel"

#define ERR_NOSUCHCHANNEL "403"
#define ERR_NOSUCHCHANNEL_MSG "No such channel"

#define ERR_CANNOTSENDTOCHAN "404"
#define ERR_CANNOTSENDTOCHAN_MSG "Cannot send to channel"

#define ERR_NORECIPIENT "411"
#define ERR_NORECIPIENT_MSG "No recipient given"

#define ERR_NOTEXTTOSEND "412"
#define ERR_NOTEXTTOSEND_MSG "No text to send"

/* NICK */
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_NONICKNAMEGIVEN_MSG "No nickname given"

#define ERR_ERRONEUSNICKNAME "432"
#define ERR_ERRONEUSNICKNAME_MSG "Erroneous nickname"

#define ERR_NICKNAMEINUSE "433"
#define ERR_NICKNAMEINUSE_MSG "Nickname is already in use"

/* KICK */
#define ERR_USERNOTINCHANNEL "441"
#define ERR_USERNOTINCHANNEL_MSG "They aren't on that channel"

/* TOPIC / INVITE / MODE / KICK */
#define ERR_NOTONCHANNEL "442"
#define ERR_NOTONCHANNEL_MSG "You're not on that channel"

/* INVITE */
#define ERR_USERONCHANNEL "443"
#define ERR_USERONCHANNEL_MSG "is already on channel"

/* GENERAL REGISTRATION */
#define ERR_NOTREGISTERED "451"
#define ERR_NOTREGISTERED_MSG "You have not registered"

/* PASS / NICK / USER / MODE */
#define ERR_NEEDMOREPARAMS "461"
#define ERR_NEEDMOREPARAMS_MSG "Not enough parameters"

/* PASS / USER */
#define ERR_ALREADYREGISTRED "462"
#define ERR_ALREADYREGISTRED_MSG "You may not reregister"

/* PASS */
#define ERR_PASSWDMISMATCH "464"
#define ERR_PASSWDMISMATCH_MSG "Password incorrect"

/* JOIN */
#define ERR_CHANNELISFULL "471"
#define ERR_CHANNELISFULL_MSG "Cannot join channel (+l)"

/* MODE */
#define ERR_UNKNOWNMODE "472"
#define ERR_UNKNOWNMODE_MSG "is unknown mode char to me"

/* JOIN */
#define ERR_INVITEONLYCHAN "473"
#define ERR_INVITEONLYCHAN_MSG "Cannot join channel (+i)"

#define ERR_BADCHANNELKEY "475"
#define ERR_BADCHANNELKEY_MSG "Cannot join channel (+k)"

/* MODE / KICK / INVITE / TOPIC */
#define ERR_CHANOPRIVSNEEDED "482"
#define ERR_CHANOPRIVSNEEDED_MSG "You're not channel operator"


/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/*                    COMMAND-SPECIFIC ERROR GROUPS                           */
/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/* ────────────────────────────── CAP ─────────────────────────────────────── */
// Pas de codes numériques - réponses textuelles uniquement
#define CAP_LS_RESPONSE "CAP * LS :"
#define CAP_NAK_RESPONSE "CAP * NAK :"
#define CAP_ACK_RESPONSE "CAP * ACK :"

/* ───────��────────────────────── PASS ────────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_ALREADYREGISTRED "462"     (déjà défini)
// ERR_PASSWDMISMATCH "464"       (déjà défini)

/* ────────────────────────────── NICK ────────────────────────────────────── */
// ERR_NONICKNAMEGIVEN "431"      (déjà défini)
// ERR_ERRONEUSNICKNAME "432"     (déjà défini)
// ERR_NICKNAMEINUSE "433"        (déjà défini)

/* ────────────────────────────── USER ────────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_ALREADYREGISTRED "462"     (déjà défini)
// RPL_WELCOME "001"              (déjà défini)
// RPL_YOURHOST "002"             (déjà défini)
// RPL_CREATED "003"              (déjà défini)
// RPL_MYINFO "004"               (déjà défini)

/* ────────────────────────────── PRIVMSG ─────────────────────────────────── */
// ERR_NORECIPIENT "411"          (déjà défini)
// ERR_NOTEXTTOSEND "412"         (déjà défini)
// ERR_NOSUCHNICK "401"           (déjà défini)
// ERR_CANNOTSENDTOCHAN "404"     (déjà défini)
// ERR_NOTREGISTERED "451"        (déjà défini)

/* ────────────────────────────── JOIN ────────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_NOSUCHCHANNEL "403"        (déjà défini)
// ERR_CHANNELISFULL "471"        (déjà défini)
// ERR_INVITEONLYCHAN "473"       (déjà défini)
// ERR_BADCHANNELKEY "475"        (déjà défini)
// ERR_NOTREGISTERED "451"        (déjà défini)

/* ────────────────────────────── KICK ────────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_NOSUCHCHANNEL "403"        (déjà défini)
// ERR_NOTONCHANNEL "442"         (déjà défini)
// ERR_CHANOPRIVSNEEDED "482"     (déjà défini)
// ERR_USERNOTINCHANNEL "441"     (déjà défini)
// ERR_NOTREGISTERED "451"        (déjà défini)

/* ────────────────────────────── INVITE ──────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_NOSUCHNICK "401"           (déjà défini)
// ERR_NOSUCHCHANNEL "403"        (déjà défini)
// ERR_NOTONCHANNEL "442"         (déjà défini)
// ERR_USERONCHANNEL "443"        (déjà défini)
// ERR_CHANOPRIVSNEEDED "482"     (déjà défini - si +i actif)
// ERR_NOTREGISTERED "451"        (déjà défini)
// RPL_INVITING "341"             (déjà défini)

/* ────────────────────────────── TOPIC ───────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_NOSUCHCHANNEL "403"        (déjà défini)
// ERR_NOTONCHANNEL "442"         (déjà défini)
// ERR_CHANOPRIVSNEEDED "482"     (déjà défini - si +t actif)
// ERR_NOTREGISTERED "451"        (déjà défini)
// RPL_NOTOPIC "331"              (déjà défini)
// RPL_TOPIC "332"                (déjà défini)

/* ────────────────────────────── MODE ────────────────────────────────────── */
// ERR_NEEDMOREPARAMS "461"       (déjà défini)
// ERR_NOSUCHCHANNEL "403"        (déjà défini)
// ERR_NOTONCHANNEL "442"         (déjà défini)
// ERR_CHANOPRIVSNEEDED "482"     (déjà défini)
// ERR_UNKNOWNMODE "472"          (déjà défini)
// ERR_NOTREGISTERED "451"        (déjà défini)
// ERR_USERNOTINCHANNEL "441"     (déjà défini - pour +o user)

/* ────────────────────────────── QUIT ────────────────────────────────────── */
// Pas de codes d'erreur - toujours accepté
#define QUIT_DEFAULT_MSG "Client exited"

/* ────────────────────────────── PING/PONG ───────────────────────────────── */
#define ERR_NOORIGIN "409"
#define ERR_NOORIGIN_MSG "No origin specified"

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/*                      ADDITIONAL USEFUL CODES                               */
/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/* CHANNEL INFO */
#define RPL_CHANNELMODEIS "324"
#define RPL_CHANNELMODEIS_MSG "Channel mode is"

#define RPL_CREATIONTIME "329"
#define RPL_CREATIONTIME_MSG "Channel created at"

/* WHOIS */
#define RPL_WHOISUSER "311"
#define RPL_WHOISUSER_MSG "User info"

#define RPL_ENDOFWHOIS "318"
#define RPL_ENDOFWHOIS_MSG "End of /WHOIS list"

/* WHO */
#define RPL_WHOREPLY "352"
#define RPL_WHOREPLY_MSG "Who reply"

#define RPL_ENDOFWHO "315"
#define RPL_ENDOFWHO_MSG "End of /WHO list"

/* LIST */
#define RPL_LISTSTART "321"
#define RPL_LISTSTART_MSG "Channel list"

#define RPL_LIST "322"
#define RPL_LIST_MSG "Channel info"

#define RPL_LISTEND "323"
#define RPL_LISTEND_MSG "End of /LIST"

/* PART */
#define ERR_NOSUCHCHANNEL_PART "403"
#define ERR_NOSUCHCHANNEL_PART_MSG "No such channel"

#define ERR_NOTONCHANNEL_PART "442"
#define ERR_NOTONCHANNEL_PART_MSG "You're not on that channel"

/* AWAY */
#define RPL_AWAY "301"
#define RPL_AWAY_MSG "User is away"

#define RPL_UNAWAY "305"
#define RPL_UNAWAY_MSG "You are no longer marked as being away"

#define RPL_NOWAWAY "306"
#define RPL_NOWAWAY_MSG "You have been marked as being away"
#define ERR_INVALIDUSERNAME "468"
#define ERR_INVALIDUSERNAME_MSG "Your username is not valid"

/* GENERAL ERRORS */
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_UNKNOWNCOMMAND_MSG "Unknown command"

#define ERR_NOMOTD "422"
#define ERR_NOMOTD_MSG "MOTD File is missing"

#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_UMODEUNKNOWNFLAG_MSG "Unknown MODE flag"

#define ERR_USERSDONTMATCH "502"
#define ERR_USERSDONTMATCH_MSG "Can't change mode for other users"


#endif
