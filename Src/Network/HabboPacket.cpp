#include "stdafx.h"
#include "HabboPacket.hpp"

namespace Network
{
	//---------------------------------------------------------------------
	HabboPacket::HabboPacket(uint16_t pOpcode)
		:Opcode(pOpcode)
	{

	}
	//---------------------------------------------------------------------
	HabboPacket::HabboPacket(uint16_t pOpcode, const std::string& pData)
		:Opcode(pOpcode), Buffer(pData)
	{

	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(bool pData)
	{
		*this << uint8_t(pData ? 1 : 0);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(char pData)
	{
		Buffer.append((char*)&pData, 1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const uint8_t& pData)
	{
		Buffer.append((char*)&pData, 1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const uint16_t& pData)
	{
		int16_t a = htons(pData);
		Buffer.append((char*)&a, 2);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const uint32_t& pData)
	{
		int32_t a = htonl(pData);
		Buffer.append((char*)&a, 4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const uint64_t& pData)
	{
		Buffer.append((char*)&pData, 8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const int8_t& pData)
	{
		Buffer.append((char*)&pData, 1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const int16_t& pData)
	{
		int16_t a = htons(pData);
		Buffer.append((char*)&a, 2);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const int32_t& pData)
	{
		int32_t a = htonl(pData);
		Buffer.append((char*)&a, 4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const int64_t& pData)
	{
		Buffer.append((char*)&pData, 8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const float& pData)
	{
		Buffer.append((char*)&pData, 4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const double& pData)
	{
		Buffer.append((char*)&pData, 8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator<<(const std::string& pData)
	{
		*this << (uint16_t)pData.size();
		Buffer.append(pData.c_str(), pData.size());

		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(bool& pData)
	{
		uint8_t i;
		*this >> i;
		pData = i ? true : false;
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(char& pData)
	{
		if(Buffer.size() < 1)
		{
			pData = 0;
			return *this;
		}
		pData = *(uint8_t*)&Buffer[0];
		Buffer.erase(0,1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(uint8_t& pData)
	{
		if(Buffer.size() < 1)
		{
			pData = 0;
			return *this;
		}
		pData = *(uint8_t*)&Buffer[0];
		Buffer.erase(0,1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(uint16_t& pData)
	{
		if(Buffer.size() < 2)
		{
			pData = 0;
			return *this;
		}
		pData = ntohs(*(uint16_t*)&Buffer[0]);
		Buffer.erase(0,2);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(uint32_t& pData)
	{
		if(Buffer.size() < 4)
		{
			pData = 0;
			return *this;
		}
		pData = ntohl(*(uint32_t*)&Buffer[0]);
		Buffer.erase(0,4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(uint64_t& pData)
	{
		if(Buffer.size() < 8)
		{
			pData = 0;
			return *this;
		}
		pData = *(uint64_t*)&Buffer[0];
		Buffer.erase(0,8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(int8_t& pData)
	{
		if(Buffer.size() < 1)
		{
			pData = 0;
			return *this;
		}
		pData = *(int8_t*)&Buffer[0];
		Buffer.erase(0,1);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(int16_t& pData)
	{
		if(Buffer.size() < 2)
		{
			pData = 0;
			return *this;
		}
		pData = ntohs(*(int16_t*)&Buffer[0]);
		Buffer.erase(0,2);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(int32_t& pData)
	{
		if(Buffer.size() < 4)
		{
			pData = 0;
			return *this;
		}
		pData = ntohl(*(int32_t*)&Buffer[0]);
		Buffer.erase(0,4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(int64_t& pData)
	{
		if(Buffer.size() < 8)
		{
			pData = 0;
			return *this;
		}
		pData = *(int64_t*)&Buffer[0];
		Buffer.erase(0,8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(float& pData)
	{
		if(Buffer.size() < 4)
		{
			pData = 0.f;
			return *this;
		}
		pData = *(float*)&Buffer[0];
		Buffer.erase(0,4);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(double& pData)
	{
		if(Buffer.size() < 8)
		{
			pData = 0;
			return *this;
		}
		pData = *(double*)&Buffer[0];
		Buffer.erase(0,8);
		return *this;
	}
	//---------------------------------------------------------------------
	HabboPacket& HabboPacket::operator>>(std::string& pData)
	{
		uint16_t size = 0;
		*this >> size;

		// Check for fake string size to prevent memory hacks
		if(size > Buffer.size())
		{
			std::ostringstream os;
			os << "String size (" << size << ") > HabboPacket size (" << Buffer.size() << ")";
			throw std::out_of_range(os.str());
		}
		if(size == 0)
		{
			pData = "";
			return *this;
		}

		pData = Buffer.substr(0,size);

		pData.shrink_to_fit();

		Buffer.erase(0,size);
		return *this;
	}
}