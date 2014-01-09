#pragma once

namespace Network
{
	class HabboPacket
	{
	public:

		HabboPacket(uint16_t pOpcode);
		HabboPacket(uint16_t pOpcode, const std::string& pData);

		HabboPacket& operator<<(bool pData);
		HabboPacket& operator<<(char pData);
		HabboPacket& operator<<(const uint8_t& pData);
		HabboPacket& operator<<(const uint16_t& pData);
		HabboPacket& operator<<(const uint32_t& pData);
		HabboPacket& operator<<(const uint64_t& pData);
		HabboPacket& operator<<(const int8_t& pData);
		HabboPacket& operator<<(const int16_t& pData);
		HabboPacket& operator<<(const int32_t& pData);
		HabboPacket& operator<<(const int64_t& pData);
		HabboPacket& operator<<(const float& pData);
		HabboPacket& operator<<(const double& pData);
		HabboPacket& operator<<(const std::string& pData);

		HabboPacket& operator>>(char& pData);
		HabboPacket& operator>>(bool& pData);
		HabboPacket& operator>>(uint8_t& pData);
		HabboPacket& operator>>(uint16_t& pData);
		HabboPacket& operator>>(uint32_t& pData);
		HabboPacket& operator>>(uint64_t& pData);
		HabboPacket& operator>>(int8_t& pData);
		HabboPacket& operator>>(int16_t& pData);
		HabboPacket& operator>>(int32_t& pData);
		HabboPacket& operator>>(int64_t& pData);
		HabboPacket& operator>>(float& pData);
		HabboPacket& operator>>(double& pData);
		HabboPacket& operator>>(std::string& pData);

		template <class K, class U>
		HabboPacket& operator<<(const std::map<K, U>& pData)
		{
			*this << (uint32_t)pData.size();
			for(auto itor = pData.begin(), end = pData.end(); itor != end; ++itor)
			{
				*this << itor->first << itor->second;
			}

			return *this;
		}

		template <class K, class U>
		HabboPacket& operator>>(std::map<K, U>& pData)
		{
			uint32_t size;
			*this >> size;
			if(size > 1000)
				return *this;

			for(uint64_t i = 0; i < size; ++i)
			{
				K key;
				U data;
				*this >> key >> data;
				pData.insert(std::pair<K,U>(key, data));
			}

			return *this;
		}

		template <class U>
		HabboPacket& operator<<(const std::vector<U>& pData)
		{
			*this << (uint32_t)pData.size();
			for(auto itor = pData.begin(), end = pData.end(); itor != end; ++itor)
			{
				*this << *itor;
			}

			return *this;
		}

		template <class U>
		HabboPacket& operator>>(std::vector<U>& pData)
		{
			uint32_t size;
			*this >> size;
			if(size > 1000)
				return *this;

			for(uint64_t i = 0; i < size; ++i)
			{
				U data;
				*this >> data;
				pData.push_back(data);
			}

			return *this;
		}

		template <class U>
		HabboPacket& operator<<(const std::list<U>& pData)
		{
			*this << (uint32_t)pData.size();
			for(auto itor = pData.begin(), end = pData.end(); itor != end; ++itor)
			{
				*this << *itor;
			}

			return *this;
		}

		template <class U>
		HabboPacket& operator>>(std::list<U>& pData)
		{
			uint32_t size;
			*this >> size;
			if(size > 1000)
				return *this;

			for(uint64_t i = 0; i < size; ++i)
			{
				U data;
				*this >> data;
				pData.push_back(data);
			}

			return *this;
		}

		uint16_t Opcode;
		std::string Buffer;
	};
}