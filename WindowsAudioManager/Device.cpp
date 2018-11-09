#include "Device.hpp"
#include <functional>

namespace WindowsAudioManager
{
	Device::Device(std::wstring name, std::wstring systemID, Status status, Type type) : m_name(name), m_systemID(systemID), m_status(status), m_type(type)
	{
		short hash = 0x648d;
		short prime = 0x735c;
		for (unsigned int i = 0; i < systemID.size(); i++)
		{
			hash ^= systemID[i];
			hash *= prime;
		}
		if (hash < 0)
			hash = -hash;
		m_ID = hash;
	}
	Device::~Device()
	{
	}
}