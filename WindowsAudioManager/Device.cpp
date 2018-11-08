#include "Device.hpp"

namespace WindowsAudioManager
{
	Device::Device(int id, std::wstring name, std::wstring systemID) : m_ID(id), m_name(name), m_systemID(systemID)
	{
		
	}
	Device::~Device()
	{
	}
}