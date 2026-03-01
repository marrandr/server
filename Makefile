NAME = ft_irc

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(SRC_DIR)/Channel.cpp\
		$(SRC_DIR)/ChannelTool.cpp\
		$(SRC_DIR)/checkArgServer.cpp\
		$(SRC_DIR)/Client.cpp\
		$(SRC_DIR)/CommandAuhentification.cpp\
		$(SRC_DIR)/CommandConnect.cpp\
		$(SRC_DIR)/Command.cpp\
		$(SRC_DIR)/CommandeRegistration.cpp\
		$(SRC_DIR)/CommandMessage.cpp\
		$(SRC_DIR)/main.cpp\
		$(SRC_DIR)/parse.cpp\
		$(SRC_DIR)/Server.cpp\
		$(SRC_DIR)/ServerError.cpp\
		$(SRC_DIR)/ServerNetwork.cpp\
		$(SRC_DIR)/ServerToolChannel.cpp\
		$(SRC_DIR)/ServerTools.cpp\
		$(SRC_DIR)/serverUsage.cpp\
		$(SRC_DIR)/handleSignal.cpp\
		$(SRC_DIR)/handleJoin.cpp\
		$(SRC_DIR)/Logger.cpp\
		$(SRC_DIR)/Config.cpp\
		$(SRC_DIR)/Utils.cpp\
		$(SRC_DIR)/parseValide.cpp\
		$(SRC_DIR)/ClientManager.cpp\
		$(SRC_DIR)/MessageBuilder.cpp\
		$(SRC_DIR)/ChannelManager.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))


all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
