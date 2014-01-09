#include "stdafx.h"
#include "Network/Player.hpp"


namespace Network
{
	void Player::HandleVersion(HabboPacket& pPacket)
	{
	}

	void Player::HandleInitCrypto(HabboPacket& packet)
	{
		HabboPacket reply(1741);
		reply << std::string("06f69e8b6687e4cae4bcd355ba2258f7") << false;
		Write(reply);
	}

	void Player::HandleGenerateSecretKey(HabboPacket& packet)
	{
		std::string key;
		packet >> key;
	}
}