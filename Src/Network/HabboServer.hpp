#pragma once

#include "Player.hpp"

namespace Network
{
	class HabboServer
	{
	public:

		HabboServer();
		~HabboServer();

		void Run();

		void OnAccept(Framework::Network::TcpConnection::pointer pConnection);

		void Remove(Player::pointer pPlayer);

	private:

		Framework::Network::Server mServer;
		std::list<Player::pointer> mPlayers;
	};
}