#pragma once

#include "HabboPacket.hpp"

namespace Network
{
	class HabboServer;

	class Player : public Framework::Network::Strategy<std::string>,
		public boost::enable_shared_from_this<Player>
	{
	public:

		typedef boost::shared_ptr<Player> pointer;
		typedef boost::weak_ptr<Player> weak_pointer;
		typedef void (Player::*PacketHandler)(HabboPacket& pPacket);

		Player(HabboServer* pServer);
		~Player();

		static void MapHandlers();

		void SetConnection(Framework::Network::TcpConnection::pointer pConnection);

		uint32_t GetHeaderSize();

		uint32_t HandleHeader(const std::string& pData);
		bool	 HandleContent(const std::string& pData);

		/*void ReceivePacket(Framework::Network::Packet& pPacket)
		{
			boost::mutex::scoped_lock locker(mLock);
			mPackets.push_back(pPacket);
		}*/

		bool HasPacket();

		std::string PopPacket();

		/**
		 * @brief Register a handler to an opcode.
		 * @param opcode The opcode.
		 * @param handler The handler to use.
		 */
		template <class T>
		static void Register(int16_t opcode, void (T::*handler)(HabboPacket& pPacket))
		{
			RegisterImpl(opcode, (PacketHandler)handler);
		}

		void Write(HabboPacket& pPacket);

	protected:

		void HandleVersion(HabboPacket& packet);
		void HandleInitCrypto(HabboPacket& packet);
		void HandleGenerateSecretKey(HabboPacket& Packet);

		void OnError(const std::string& pError);

	private:

		static void RegisterImpl(int16_t opcode, PacketHandler handler);

		static std::map<int16_t, Player::PacketHandler> handlers;

		boost::mutex mLock;
		std::string mReceivingPacket;
		std::list<std::string> mPackets;

		bool mPolicy;
		Framework::Network::TcpConnection::pointer mConnection;
		HabboServer* mServer;
	};
}