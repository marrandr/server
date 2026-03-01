*This project has been created as part of the 42 curriculum by marrandr, harinrak, arasoloa*

# Description
This is a basic IRC (Internet Relay Chat) server development project with fundamental functionalities such as private client conversations and the creation and generation of channels where clients can chat. Its objective is to learn how the internet and internal servers work.

# Instructions
## Compilation
This project is built using a Makefile.
#### To ompile:
```bash
make
```

#### To recompile from scratch:
```bash

make re
```
To clean object files:
```bash
make clean
```
To remove object files and executable:
```bash
make fclean
```
## Usage
#### Start the IRC server with:
```bash
./ircserv <port> <password>
```
## Connecting with a Client
#### Using irssi
```bash
irssi
```
#### Connect to your server:
```bash
/connect localhost 6667 mypassword
```
#### Important:
+ irssi automatically sends NICK and USER
+ No need to manually type USER command

#### Optionally change nickname:
```bash
/nick yourNick
```
#### Using netcat (for testing)
```bash
nc -C localhost 6667
```
##### Then manually send:
```bash
PASS mypassword
NICK yourNick
USER yourUser 0 * :Real Name
```
#### Authentication
If the password is:
+ Missing
+ Incorrect
The server will reject registration.

Ensure the password matches the one used when starting the server.
# Resources
### Man page
```bash
man 7 ip
man poll
man socket
man bind
man listen
man accept
man setsockopt
```
### Internet resources
+ [IPV4 TCP server client program with Poll system call](https://www.c-pointers.com/lsp/sockets/ipv4_af_inet_tcp/poll/poll.html)

+ [Modern IRC Client Protocol](https://modern.ircdocs.horse/#nick-message)

+ [Internet Relay Chat by The UChicago χ-Projects](http://chi.cs.uchicago.edu/chirc/irc.html)
