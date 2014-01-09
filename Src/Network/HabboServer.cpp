#include "stdafx.h"

#include "HabboServer.hpp"


namespace Network
{
	//---------------------------------------------------------------------
	HabboServer::HabboServer()
		:mServer(3015)
	{
		mServer.OnConnection.connect(boost::bind(&HabboServer::OnAccept, this, _1));
		mServer.Start();
	}
	//---------------------------------------------------------------------
	HabboServer::~HabboServer()
	{
		mServer.Stop();
	}
	//---------------------------------------------------------------------
	void HabboServer::Run()
	{
		mServer.Run();
	}
	//---------------------------------------------------------------------
	void HabboServer::Remove(Player::pointer pPlayer)
	{
		mPlayers.remove(pPlayer);
	}
	//---------------------------------------------------------------------
	void HabboServer::OnAccept(Framework::Network::TcpConnection::pointer pConnection)
	{
		auto player = boost::make_shared<Player>(this);

		player->SetConnection(pConnection);

		mPlayers.push_back(player);
	}
	//---------------------------------------------------------------------
}