#include "stdafx.h"
#include "Network/HabboServer.hpp"
#include "Network/Player.hpp"

int main()
{
	Network::Player::MapHandlers();

	Network::HabboServer server;
	server.Run();

	return 0;
}