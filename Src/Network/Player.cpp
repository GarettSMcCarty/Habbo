#include "stdafx.h"
#include "Player.hpp"
#include "HabboServer.hpp"
#include "HabboPacket.hpp"

namespace Network
{
	std::map<int16_t, Player::PacketHandler> Player::handlers;
	//---------------------------------------------------------------------
	void Player::MapHandlers()
	{
		Register(4000, &Player::HandleVersion);
		Register(806, &Player::HandleInitCrypto);
		Register(3578, &Player::HandleGenerateSecretKey);
	}
	//---------------------------------------------------------------------
	void Player::RegisterImpl(int16_t opcode, PacketHandler handler)
	{
		handlers[opcode] = handler;
	}
	//---------------------------------------------------------------------
	Player::Player(HabboServer* pServer)
		:mServer(pServer)
	{

	}
	//---------------------------------------------------------------------
	Player::~Player()
	{
	}
	//---------------------------------------------------------------------
	void Player::SetConnection(Framework::Network::TcpConnection::pointer pConnection)
	{
		mConnection = pConnection;
		mConnection->SetStrategy(this);
		mConnection->OnError.connect(boost::bind(&Player::OnError, this, _1));
	}
	//---------------------------------------------------------------------
	void Player::OnError(const std::string& pError)
	{
		mServer->Remove(shared_from_this());
	}
	//---------------------------------------------------------------------
	uint32_t Player::GetHeaderSize()
	{
		return 4;
	}
	//---------------------------------------------------------------------
	uint32_t Player::HandleHeader(const std::string& pData)
	{
		if(*(int*)pData.data() == 1819242556)
		{
			mPolicy = true;
			return 19;
		}

		mPolicy = false;

		return ntohl(*(int*)pData.data());
	}
	//---------------------------------------------------------------------
	bool	 Player::HandleContent(const std::string& pData)
	{
		if(mPolicy)
		{
			std::string buff("<?xml version=\"1.0\"?> " \
				"<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\"> " \
				"<cross-domain-policy> " \
				"<allow-access-from domain=\"*\" to-ports=\"*\" /> " \
				"</cross-domain-policy>");

			buff.push_back('\0');
			buff.c_str();

			mConnection->Write(buff);

			return true;
		}
		
		short opcode = ntohs(*(short*)pData.data());
		std::string data = pData.substr(2);
		try
		{
			HabboPacket packet(opcode, data);
			(this->*handlers.at(opcode))(packet);
		}
		catch (std::exception& e)
		{
			std::ostringstream os;
			os << "Opcode : " << opcode << " | " << e.what();
			Framework::System::PrintBinary((uint8_t*)&pData[2], pData.length() - 2, os.str());
		}

		return true;
	}
	//---------------------------------------------------------------------
	bool Player::HasPacket()
	{
		return !mPackets.empty();
	}
	//---------------------------------------------------------------------
	std::string Player::PopPacket()
	{
		boost::mutex::scoped_lock locker(mLock);
		//Framework::Network::Packet packet = mPackets.front();
		//mPackets.pop_front();
		return "";				
	}
	//---------------------------------------------------------------------
	void Player::Write(HabboPacket& pPacket)
	{
		// reserve 4 bytes for size
		std::string data("size");
		// To big endian
		uint16_t opcode = htons(pPacket.Opcode);
		data.append((char*)&opcode, 2);
		data.append(pPacket.Buffer);

		// To big endian
		uint32_t size = htonl(data.size() - 4);
		std::memcpy(&data[0], (char*)&size, 4);

		//Framework::System::PrintBinary((uint8_t*)data.data(), data.size());

		mConnection->Write(data);
	}
	//---------------------------------------------------------------------
}